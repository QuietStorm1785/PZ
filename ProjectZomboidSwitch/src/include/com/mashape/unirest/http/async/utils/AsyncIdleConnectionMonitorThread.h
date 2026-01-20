#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/apache/http/impl/nio/conn/PoolingNHttpClientConnectionManager.h"
#include <algorithm>

namespace com {
namespace mashape {
namespace unirest {
namespace http {
namespace async {
namespace utils {


class AsyncIdleConnectionMonitorThread : public Thread {
public:
    const PoolingNHttpClientConnectionManager connMgr;

    public AsyncIdleConnectionMonitorThread(PoolingNHttpClientConnectionManager connMgr) {
      super.setDaemon(true);
      this.connMgr = connMgr;
   }

    void run() {
      try {
         while (!Thread.currentThread().isInterrupted()) {
            /* synchronized - TODO: add std::mutex */ (this) {
               this.wait(5000L);
               this.connMgr.closeExpiredConnections();
               this.connMgr.closeIdleConnections(30L, TimeUnit.SECONDS);
            }
         }
      } catch (InterruptedException var4) {
      }
   }
}
} // namespace utils
} // namespace async
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
