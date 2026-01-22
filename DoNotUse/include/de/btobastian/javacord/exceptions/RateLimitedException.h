#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitManager.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace exceptions {


class RateLimitedException : public Exception {
public:
    const long retryAfter;
    const RateLimitType type;
    const Server server;
    const Channel channel;
    const RateLimitManager manager;

    public RateLimitedException(const std::string& message, long retryAfter, RateLimitType type, Server server, Channel channel, RateLimitManager manager) {
      super(message);
      this.retryAfter = retryAfter;
      this.type = type;
      this.server = server;
      this.channel = channel;
      this.manager = manager;
   }

    RateLimitType getType() {
      return this.type;
   }

    Server getServer() {
      return this.server;
   }

    long getRetryAfter() {
      return this.retryAfter;
   }

    long getRetryAt() {
      return System.currentTimeMillis() + this.manager.getRateLimit(this.type, this.server, this.channel);
   }

    void waitTillRetry() {
    long time = this.manager.getRateLimit(this.type, this.server, this.channel);
      if (time >= 1L) {
         Thread.sleep(time);
      }
   }
}
} // namespace exceptions
} // namespace javacord
} // namespace btobastian
} // namespace de
