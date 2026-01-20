#include "de/jarnbjo/ogg/CachedUrlStream/LoaderThread.h"
#include "de/jarnbjo/ogg/CachedUrlStream.h"
#include <algorithm>

using namespace de::jarnbjo::ogg;

LoaderThread::LoaderThread(CachedUrlStream* parent,
                           std::shared_ptr<std::istream> source,
                           std::fstream* drain,
                           std::vector<uint8_t>* memoryCache)
    : parent_(parent), source_(source), drain_(drain), memoryCache_(memoryCache) {
    thread_ = std::thread(&LoaderThread::run, this);
}

LoaderThread::~LoaderThread() {
    stopFlag_.store(true);
    if (thread_.joinable()) thread_.join();
}

void LoaderThread::join() {
    stopFlag_.store(true);
    if (thread_.joinable()) thread_.join();
}

void LoaderThread::run() {
    constexpr std::size_t CHUNK = 16 * 1024;
    std::vector<char> buf(CHUNK);

    try {
        while (!stopFlag_.load() && source_ && !source_->eof()) {
            source_->read(buf.data(), static_cast<std::streamsize>(buf.size()));
            std::streamsize r = source_->gcount();
            if (r <= 0) break;

            {
                // append into parent's memory cache under the drain lock
                std::lock_guard<std::mutex> lk(parent_->drainLock);
                memoryCache_->insert(memoryCache_->end(), buf.begin(), buf.begin() + r);
                parent_->cacheLength = static_cast<int64_t>(memoryCache_->size());
                // TODO: parse Ogg page boundaries here and populate parent_->pageOffsets & pageLengths
            }

            // also write through to drain file if provided
            if (drain_ && drain_->is_open()) {
                drain_->write(buf.data(), r);
                drain_->flush();
            }

            // after initial buffer is filled, mark bosDone
            if (!bosDone_.load() && memoryCache_->size() >= 64 * 1024) {
                bosDone_.store(true);
            }

            // lightweight throttle to avoid busy loop
            if (source_->rdstate() & std::ios::eofbit) break;
        }

        // mark bosDone when finished reading
        bosDone_.store(true);
    } catch (...) {
        // swallow exceptions for now; TODO: propagate/log
        bosDone_.store(true);
    }
}
