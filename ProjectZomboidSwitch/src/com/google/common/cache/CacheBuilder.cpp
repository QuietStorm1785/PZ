#include <string>
#include "com\google\common\cache/CacheBuilder.h"

namespace com {
namespace google {
namespace common {
namespace cache {

return CacheBuilder::from() {
    // TODO: Implement from
    return nullptr;
}

int CacheBuilder::getInitialCapacity() {
    // TODO: Implement getInitialCapacity
    return 0;
}

int CacheBuilder::getConcurrencyLevel() {
    // TODO: Implement getConcurrencyLevel
    return 0;
}

long CacheBuilder::getMaximumWeight() {
    // TODO: Implement getMaximumWeight
    return 0;
}

Strength CacheBuilder::getKeyStrength() {
    // TODO: Implement getKeyStrength
    return nullptr;
}

Strength CacheBuilder::getValueStrength() {
    // TODO: Implement getValueStrength
    return nullptr;
}

long CacheBuilder::getExpireAfterWriteNanos() {
    // TODO: Implement getExpireAfterWriteNanos
    return 0;
}

long CacheBuilder::getExpireAfterAccessNanos() {
    // TODO: Implement getExpireAfterAccessNanos
    return 0;
}

long CacheBuilder::getRefreshNanos() {
    // TODO: Implement getRefreshNanos
    return 0;
}

Ticker CacheBuilder::getTicker(bool recordsTime) {
    // TODO: Implement getTicker
    return nullptr;
}

bool CacheBuilder::isRecordingStats() {
    // TODO: Implement isRecordingStats
    return false;
}

void CacheBuilder::checkNonLoadingCache() {
    // TODO: Implement checkNonLoadingCache
}

void CacheBuilder::checkWeightWithWeigher() {
    // TODO: Implement checkWeightWithWeigher
}

std::string CacheBuilder::toString() {
    // TODO: Implement toString
    return "";
}

} // namespace cache
} // namespace common
} // namespace google
} // namespace com
