#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/ListeningExecutorService.h"
#include "com/google/common/util/concurrent/MoreExecutors.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {


class ThreadPool {
public:
    static const int CORE_POOL_SIZE = 1;
    static const int MAXIMUM_POOL_SIZE = int.MAX_VALUE;
    static const int KEEP_ALIVE_TIME = 60;
    static const TimeUnit TIME_UNIT = TimeUnit.SECONDS;
    ExecutorService executorService = nullptr;
    ListeningExecutorService listeningExecutorService = nullptr;
   private const ConcurrentHashMap<std::string, ExecutorService> executorServiceSingeThreads = std::make_unique<ConcurrentHashMap<>>();

    public ThreadPool() {
      this.executorService = std::make_shared<ThreadPoolExecutor>(1, int.MAX_VALUE, 60L, TIME_UNIT, std::make_unique<SynchronousQueue<>>());
      this.listeningExecutorService = MoreExecutors.listeningDecorator(this.executorService);
   }

    ExecutorService getExecutorService() {
      return this.executorService;
   }

    ExecutorService getSingleThreadExecutorService(const std::string& id) {
      /* synchronized - TODO: add std::mutex */ (this.executorServiceSingeThreads) {
    ExecutorService service = this.executorServiceSingeThreads.get(id);
         if (service == nullptr) {
            service = Executors.newSingleThreadExecutor();
            this.executorServiceSingeThreads.put(id, service);
         }

    return service;
      }
   }

    ListeningExecutorService getListeningExecutorService() {
      return this.listeningExecutorService;
   }
}
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
