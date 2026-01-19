#pragma once

#include "HotPathProfiler.h"

namespace zombie {
namespace profiling {

// ============================================================================
// PROFILING SETUP & HELPER FUNCTIONS
// ============================================================================

class GameProfiler {
public:
    static GameProfiler& instance() noexcept {
        static GameProfiler profiler;
        return profiler;
    }

    // Access global profiler
    jni::profiling::HotPathProfiler& get_profiler() noexcept {
        return jni::profiling::get_global_profiler();
    }

    // Print comprehensive profiling report
    void print_full_report() const noexcept {
        printf("\n╔═════════════════════════════════════════════════════════════╗\n");
        printf("║          PROJECT ZOMBOID PERFORMANCE PROFILE                  ║\n");
        printf("║                     Comprehensive Report                       ║\n");
        printf("╚═════════════════════════════════════════════════════════════╝\n\n");

        // Print top 20 hottest functions
        auto& profiler = jni::profiling::get_global_profiler();
        profiler.print_report("Top Functions (by Total Time)");

        // Hottest functions
        auto hottest = profiler.get_hottest_functions(20);
        printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("Top 5 Hottest Functions (optimization targets):\n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        for (size_t i = 0; i < std::min(size_t(5), hottest.size()); ++i) {
            const auto& stat = hottest[i];
            printf("%zu. %s\n", i + 1, stat.function_name.c_str());
            printf("   Calls: %llu | Avg: %.2f us | Total: %.2f ms (%.1f%%)\n",
                   stat.call_count,
                   stat.average_time_us(),
                   stat.total_time_ms(),
                   stat.percentage_of_total(profiler.get_total_time()));
        }

        printf("\n");
    }

    // Reset profiling
    void reset() noexcept {
        jni::profiling::get_global_profiler().reset();
    }

private:
    GameProfiler() = default;
};

}  // namespace profiling
}  // namespace zombie

// ============================================================================
// CONVENIENCE MACROS FOR PROFILING
// ============================================================================

// Profile entire function
#define PROFILE_FUNCTION_CALL() \
    ::jni::profiling::ScopedProfiler _profiler_##__LINE__( \
        ::jni::profiling::get_global_profiler(), __PRETTY_FUNCTION__)

// Profile code block
#define PROFILE_BLOCK(name) \
    ::jni::profiling::ScopedProfiler _profiler_##__LINE__( \
        ::jni::profiling::get_global_profiler(), name)

// Print profiling report
#define PRINT_PROFILE_REPORT() \
    ::zombie::profiling::GameProfiler::instance().print_full_report()

// Get profiler instance
#define GET_PROFILER() \
    ::jni::profiling::get_global_profiler()

#endif  // GAME_PROFILER_H
