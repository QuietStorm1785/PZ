#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/apache/http/conn/HttpClientConnectionManager.h"
#include <algorithm>

namespace com {
namespace mashape {
namespace unirest {
namespace http {
namespace utils {


class SyncIdleConnectionMonitorThread : public Thread {
public:
    const HttpClientConnectionManager connMgr;

    public SyncIdleConnectionMonitorThread(HttpClientConnectionManager connMgr) {
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
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
