#include <string>
#include "de\btobastian\javacord\exceptions/RateLimitedException.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace exceptions {

public RateLimitedException::RateLimitedException(const std::string& message, long retryAfter, RateLimitType type, Server server, Channel channel, RateLimitManager manager) {
    // TODO: Implement RateLimitedException
    return nullptr;
}

RateLimitType RateLimitedException::getType() {
    // TODO: Implement getType
    return nullptr;
}

Server RateLimitedException::getServer() {
    // TODO: Implement getServer
    return nullptr;
}

long RateLimitedException::getRetryAfter() {
    // TODO: Implement getRetryAfter
    return 0;
}

long RateLimitedException::getRetryAt() {
    // TODO: Implement getRetryAt
    return 0;
}

void RateLimitedException::waitTillRetry() {
    // TODO: Implement waitTillRetry
}

} // namespace exceptions
} // namespace javacord
} // namespace btobastian
} // namespace de
