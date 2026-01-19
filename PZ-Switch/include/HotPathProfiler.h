#pragma once

#include <chrono>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <memory>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <cstdio>

namespace jni {
namespace profiling {

// ============================================================================
// TIMING SAMPLE
// ============================================================================

struct TimingSample {
    std::chrono::microseconds duration;
    std::chrono::system_clock::time_point timestamp;

    TimingSample(std::chrono::microseconds dur)
        : duration(dur), timestamp(std::chrono::system_clock::now()) {}
};

// ============================================================================
// PERFORMANCE STATISTICS
// ============================================================================

struct PerformanceStats {
    std::string function_name;
    uint64_t call_count = 0;
    std::chrono::microseconds total_time{0};
    std::chrono::microseconds min_time{std::numeric_limits<int64_t>::max()};
    std::chrono::microseconds max_time{0};

    // Calculated stats
    double average_time_us() const noexcept {
        return call_count > 0 
            ? static_cast<double>(total_time.count()) / call_count 
            : 0.0;
    }

    double total_time_ms() const noexcept {
        return static_cast<double>(total_time.count()) / 1000.0;
    }

    double min_time_us() const noexcept {
        return min_time.count() == std::numeric_limits<int64_t>::max()
            ? 0.0
            : static_cast<double>(min_time.count());
    }

    double max_time_us() const noexcept {
        return static_cast<double>(max_time.count());
    }

    double percentage_of_total(std::chrono::microseconds total) const noexcept {
        return total.count() > 0
            ? (static_cast<double>(total_time.count()) / total.count()) * 100.0
            : 0.0;
    }
};

// ============================================================================
// HOT-PATH PROFILER
// ============================================================================

class HotPathProfiler {
public:
    HotPathProfiler() = default;
    ~HotPathProfiler() = default;

    // Get or create a profiler for a function
    void record_sample(std::string_view function_name,
                      std::chrono::microseconds duration) noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        auto& stats = stats_map_[std::string(function_name)];
        if (stats.function_name.empty()) {
            stats.function_name = function_name;
        }

        stats.call_count++;
        stats.total_time += duration;
        stats.min_time = std::min(stats.min_time, duration);
        stats.max_time = std::max(stats.max_time, duration);

        // Keep last N samples for detailed analysis
        if (samples_[std::string(function_name)].size() >= 1000) {
            samples_[std::string(function_name)].erase(
                samples_[std::string(function_name)].begin());
        }
        samples_[std::string(function_name)].emplace_back(duration);

        total_time_ += duration;
    }

    // Get statistics for a function
    PerformanceStats get_stats(std::string_view function_name) const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = stats_map_.find(std::string(function_name));
        if (it != stats_map_.end()) {
            return it->second;
        }
        return PerformanceStats{};
    }

    // Get all statistics
    std::vector<PerformanceStats> get_all_stats() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        std::vector<PerformanceStats> result;
        for (const auto& pair : stats_map_) {
            result.push_back(pair.second);
        }
        // Sort by total time descending
        std::sort(result.begin(), result.end(),
                  [](const PerformanceStats& a, const PerformanceStats& b) {
                      return a.total_time > b.total_time;
                  });
        return result;
    }

    // Get top N hottest functions
    std::vector<PerformanceStats> get_hottest_functions(size_t n) const noexcept {
        auto all = get_all_stats();
        if (all.size() > n) {
            all.resize(n);
        }
        return all;
    }

    // Reset statistics
    void reset() noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        stats_map_.clear();
        samples_.clear();
        total_time_ = std::chrono::microseconds{0};
    }

    // Print report
    void print_report(std::string_view title = "Hot-Path Profile") const noexcept {
        auto all_stats = get_all_stats();

        printf("\n");
        printf("╔════════════════════════════════════════════════════════════╗\n");
        printf("║ %s\n", title.data());
        printf("╚════════════════════════════════════════════════════════════╝\n");

        if (all_stats.empty()) {
            printf("No profiling data available.\n");
            return;
        }

        printf("\n%-50s %12s %12s %12s %12s %8s\n",
               "Function", "Calls", "Total (ms)", "Avg (us)", "Max (us)", "%");
        printf("%-50s %12s %12s %12s %12s %8s\n",
               "─────────────────────────────", "────", "────────",
               "────────", "────────", "────");

        for (const auto& stat : all_stats) {
            printf("%-50s %12llu %12.2f %12.2f %12.2f %8.2f%%\n",
                   stat.function_name.c_str(),
                   stat.call_count,
                   stat.total_time_ms(),
                   stat.average_time_us(),
                   stat.max_time_us(),
                   stat.percentage_of_total(total_time_));
        }

        printf("\n");
        printf("Total Time: %.2f ms\n", 
               static_cast<double>(total_time_.count()) / 1000.0);
        printf("Total Functions Tracked: %zu\n", all_stats.size());
        printf("════════════════════════════════════════════════════════════\n\n");
    }

    // Print detailed statistics for a specific function
    void print_detailed_stats(std::string_view function_name) const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = stats_map_.find(std::string(function_name));
        if (it == stats_map_.end()) {
            printf("No statistics for function: %s\n", function_name.data());
            return;
        }

        const auto& stats = it->second;
        printf("\n");
        printf("═══════════════════════════════════════════\n");
        printf("Detailed Statistics: %s\n", function_name.data());
        printf("═══════════════════════════════════════════\n");
        printf("Call Count:      %llu\n", stats.call_count);
        printf("Total Time:      %.3f ms\n", stats.total_time_ms());
        printf("Average Time:    %.3f us\n", stats.average_time_us());
        printf("Min Time:        %.3f us\n", stats.min_time_us());
        printf("Max Time:        %.3f us\n", stats.max_time_us());
        printf("═══════════════════════════════════════════\n\n");
    }

    // Get total profiling time
    std::chrono::microseconds get_total_time() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        return total_time_;
    }

private:
    std::unordered_map<std::string, PerformanceStats> stats_map_;
    std::unordered_map<std::string, std::vector<TimingSample>> samples_;
    std::chrono::microseconds total_time_{0};
    mutable std::mutex mutex_;
};

// ============================================================================
// SCOPED PROFILER (RAII TIMING)
// ============================================================================

class ScopedProfiler {
public:
    explicit ScopedProfiler(HotPathProfiler& profiler,
                           std::string_view function_name)
        : profiler_(profiler),
          function_name_(function_name),
          start_time_(std::chrono::high_resolution_clock::now()) {}

    ~ScopedProfiler() noexcept {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            end_time - start_time_);
        profiler_.record_sample(function_name_, duration);
    }

    // Delete copy operations
    ScopedProfiler(const ScopedProfiler&) = delete;
    ScopedProfiler& operator=(const ScopedProfiler&) = delete;

private:
    HotPathProfiler& profiler_;
    std::string function_name_;
    std::chrono::high_resolution_clock::time_point start_time_;
};

// ============================================================================
// GLOBAL PROFILER INSTANCE
// ============================================================================

inline HotPathProfiler& get_global_profiler() noexcept {
    static HotPathProfiler profiler;
    return profiler;
}

}  // namespace profiling
}  // namespace jni

// ============================================================================
// CONVENIENCE MACROS
// ============================================================================

#define PROFILE_SCOPE(name)                                              \
    ::jni::profiling::ScopedProfiler _profiler_##__LINE__(              \
        ::jni::profiling::get_global_profiler(), name)

#define PROFILE_FUNCTION() PROFILE_SCOPE(__PRETTY_FUNCTION__)

#endif  // HOT_PATH_PROFILER_H
