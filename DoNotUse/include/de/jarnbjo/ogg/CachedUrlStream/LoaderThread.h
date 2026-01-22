#pragma once
#include <thread>
#include <atomic>
#include <memory>
#include <vector>
#include <istream>
#include <fstream>

namespace de { namespace jarnbjo { namespace ogg {

class CachedUrlStream; // forward

class LoaderThread {
public:
    LoaderThread(CachedUrlStream* parent,
                 std::shared_ptr<std::istream> source,
                 std::fstream* drain,
                 std::vector<uint8_t>* memoryCache);
    ~LoaderThread();

    // Non-copyable
    LoaderThread(const LoaderThread&) = delete;
    LoaderThread& operator=(const LoaderThread&) = delete;

    bool isBosDone() const { return bosDone_.load(); }
    void join();

private:
    void run();

    CachedUrlStream* parent_;
    std::shared_ptr<std::istream> source_;
    std::fstream* drain_;
    std::vector<uint8_t>* memoryCache_;
    std::thread thread_;
    std::atomic<bool> stopFlag_{false};
    std::atomic<bool> bosDone_{false};
};

}}} // namespace
