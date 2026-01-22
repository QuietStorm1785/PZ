#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace ratelimits {


class RateLimitManager {
public:
    static const Logger logger = LoggerUtil.getLogger(RateLimitManager.class);
   private const std::unordered_map<RateLimitType, int64_t> rateLimits = std::make_unique<std::unordered_map<>>();
   private const std::unordered_map<Server, std::unordered_map<RateLimitType, int64_t>> serverRateLimits = std::make_unique<std::unordered_map<>>();
   private const std::unordered_map<Channel, std::unordered_map<RateLimitType, int64_t>> channelRateLimits = std::make_unique<std::unordered_map<>>();

    void addRateLimit(RateLimitType type, long retryAfter) {
      this.addRateLimit(type, nullptr, nullptr, retryAfter);
   }

    void addRateLimit(RateLimitType type, Server server, Channel channel, long retryAfter) {
      if (server == nullptr && channel == nullptr) {
         this.rateLimits.put(type, System.currentTimeMillis() + retryAfter);
      } else if (channel == nullptr) {
         std::unordered_map<RateLimitType, int64_t> rateLimits = this.serverRateLimits.get(server);
         if (rateLimits == nullptr) {
            rateLimits = std::make_unique<std::unordered_map<>>();
            this.serverRateLimits.put(server, rateLimits);
         }

         rateLimits.put(type, System.currentTimeMillis() + retryAfter);
      } else {
         std::unordered_map<RateLimitType, int64_t> rateLimits = this.channelRateLimits.get(channel);
         if (rateLimits == nullptr) {
            rateLimits = std::make_unique<std::unordered_map<>>();
            this.channelRateLimits.put(channel, rateLimits);
         }

         rateLimits.put(type, System.currentTimeMillis() + retryAfter);
      }
   }

    bool isRateLimited(RateLimitType type) {
      return this.getRateLimit(type, nullptr, nullptr) > 0L;
   }

    bool isRateLimited(RateLimitType type, Server server) {
      return this.getRateLimit(type, server, nullptr) > 0L;
   }

    bool isRateLimited(RateLimitType type, Channel channel) {
      return this.getRateLimit(type, nullptr, channel) > 0L;
   }

    bool isRateLimited(RateLimitType type, Server server, Channel channel) {
      return this.getRateLimit(type, server, channel) > 0L;
   }

    long getRateLimit(RateLimitType type) {
      return this.getRateLimit(type, nullptr, nullptr);
   }

    long getRateLimit(RateLimitType type, Server server, Channel channel) {
      if (server == nullptr && channel == nullptr) {
    long retryAt = this.rateLimits.get(type);
         if (retryAt == nullptr) {
            return -1L;
         } else {
    long retryAfter = retryAt - System.currentTimeMillis();
            return retryAfter <= 0L ? -1L : retryAfter;
         }
      } else if (channel == nullptr) {
         std::unordered_map<RateLimitType, int64_t> rateLimits = this.serverRateLimits.get(server);
         if (rateLimits == nullptr) {
            return -1L;
         } else {
    long retryAt = rateLimits.get(type);
            if (retryAt == nullptr) {
               return -1L;
            } else {
    long retryAfter = retryAt - System.currentTimeMillis();
               return retryAfter <= 0L ? -1L : retryAfter;
            }
         }
      } else {
         std::unordered_map<RateLimitType, int64_t> rateLimits = this.channelRateLimits.get(channel);
         if (rateLimits == nullptr) {
            return -1L;
         } else {
    long retryAt = rateLimits.get(type);
            if (retryAt == nullptr) {
               return -1L;
            } else {
    long retryAfter = retryAt - System.currentTimeMillis();
               return retryAfter <= 0L ? -1L : retryAfter;
            }
         }
      }
   }
}
} // namespace ratelimits
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
