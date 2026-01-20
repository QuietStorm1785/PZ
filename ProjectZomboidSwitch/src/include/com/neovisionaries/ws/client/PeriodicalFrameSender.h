#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/neovisionaries/ws/client/PeriodicalFrameSender/Task.h"
#include <algorithm>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class PeriodicalFrameSender {
public:
    const WebSocket mWebSocket;
    const std::string mTimerName;
    Timer mTimer;
    bool mScheduled;
    long mInterval;
    PayloadGenerator mGenerator;

    public PeriodicalFrameSender(WebSocket webSocket, const std::string& timerName, PayloadGenerator generator) {
      this.mWebSocket = webSocket;
      this.mTimerName = timerName;
      this.mGenerator = generator;
   }

    void start() {
      this.setInterval(this.getInterval());
   }

    void stop() {
      /* synchronized - TODO: add std::mutex */ (this) {
         if (this.mTimer != nullptr) {
            this.mScheduled = false;
            this.mTimer.cancel();
         }
      }
   }

    long getInterval() {
      /* synchronized - TODO: add std::mutex */ (this) {
         return this.mInterval;
      }
   }

    void setInterval(long interval) {
      if (interval < 0L) {
         interval = 0L;
      }

      /* synchronized - TODO: add std::mutex */ (this) {
         this.mInterval = interval;
      }

      if (interval != 0L) {
         if (this.mWebSocket.isOpen()) {
            /* synchronized - TODO: add std::mutex */ (this) {
               if (this.mTimer == nullptr) {
                  this.mTimer = std::make_shared<Timer>(this.mTimerName);
               }

               if (!this.mScheduled) {
                  this.mScheduled = schedule(this.mTimer, std::make_shared<Task>(this, nullptr), interval);
               }
            }
         }
      }
   }

    PayloadGenerator getPayloadGenerator() {
      /* synchronized - TODO: add std::mutex */ (this) {
         return this.mGenerator;
      }
   }

    void setPayloadGenerator(PayloadGenerator generator) {
      /* synchronized - TODO: add std::mutex */ (this) {
         this.mGenerator = generator;
      }
   }

    void doTask() {
      /* synchronized - TODO: add std::mutex */ (this) {
         if (this.mInterval != 0L && this.mWebSocket.isOpen()) {
            this.mWebSocket.sendFrame(this.createFrame());
            this.mScheduled = schedule(this.mTimer, std::make_shared<Task>(this, nullptr), this.mInterval);
         } else {
            this.mScheduled = false;
         }
      }
   }

    WebSocketFrame createFrame() {
      byte[] payload = this.generatePayload();
      return this.createFrame(payload);
   }

   private byte[] generatePayload() {
      if (this.mGenerator == nullptr) {
    return nullptr;
      } else {
         try {
            return this.mGenerator.generate();
         } catch (Throwable var2) {
    return nullptr;
         }
      }
   }

    static bool schedule(Timer timer, Task task, long interval) {
      try {
         timer.schedule(task, interval);
    return true;
      } catch (RuntimeException var5) {
    return false;
      }
   }

   protected abstract WebSocketFrame createFrame(byte[] var1);
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
