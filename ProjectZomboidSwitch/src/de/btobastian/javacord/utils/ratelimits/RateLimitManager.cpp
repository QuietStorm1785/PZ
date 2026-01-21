#include "de/btobastian/javacord/utils/ratelimits/RateLimitManager.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace ratelimits {

void RateLimitManager::addRateLimit(RateLimitType type, long retryAfter) {
    // TODO: Implement addRateLimit
}

void RateLimitManager::addRateLimit(RateLimitType type, Server server, Channel channel, long retryAfter) {
    // TODO: Implement addRateLimit
}

bool RateLimitManager::isRateLimited(RateLimitType type) {
    // TODO: Implement isRateLimited
    return false;
}

bool RateLimitManager::isRateLimited(RateLimitType type, Server server) {
    // TODO: Implement isRateLimited
    return false;
}

bool RateLimitManager::isRateLimited(RateLimitType type, Channel channel) {
    // TODO: Implement isRateLimited
    return false;
}

bool RateLimitManager::isRateLimited(RateLimitType type, Server server, Channel channel) {
    // TODO: Implement isRateLimited
    return false;
}

long RateLimitManager::getRateLimit(RateLimitType type) {
    // TODO: Implement getRateLimit
    return 0;
}

long RateLimitManager::getRateLimit(RateLimitType type, Server server, Channel channel) {
    // TODO: Implement getRateLimit
    return 0;
}

} // namespace ratelimits
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
