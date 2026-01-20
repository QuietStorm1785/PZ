#include <string>
#include "com\google\common\cache/CacheStats.h"

namespace com {
namespace google {
namespace common {
namespace cache {

public CacheStats::CacheStats(long hitCount, long missCount, long loadSuccessCount, long loadExceptionCount, long totalLoadTime, long evictionCount) {
    // TODO: Implement CacheStats
    return nullptr;
}

long CacheStats::requestCount() {
    // TODO: Implement requestCount
    return 0;
}

long CacheStats::hitCount() {
    // TODO: Implement hitCount
    return 0;
}

double CacheStats::hitRate() {
    // TODO: Implement hitRate
    return 0;
}

long CacheStats::missCount() {
    // TODO: Implement missCount
    return 0;
}

double CacheStats::missRate() {
    // TODO: Implement missRate
    return 0;
}

long CacheStats::loadCount() {
    // TODO: Implement loadCount
    return 0;
}

long CacheStats::loadSuccessCount() {
    // TODO: Implement loadSuccessCount
    return 0;
}

long CacheStats::loadExceptionCount() {
    // TODO: Implement loadExceptionCount
    return 0;
}

double CacheStats::loadExceptionRate() {
    // TODO: Implement loadExceptionRate
    return 0;
}

long CacheStats::totalLoadTime() {
    // TODO: Implement totalLoadTime
    return 0;
}

double CacheStats::averageLoadPenalty() {
    // TODO: Implement averageLoadPenalty
    return 0;
}

long CacheStats::evictionCount() {
    // TODO: Implement evictionCount
    return 0;
}

CacheStats CacheStats::minus(CacheStats other) {
    // TODO: Implement minus
    return nullptr;
}

CacheStats CacheStats::plus(CacheStats other) {
    // TODO: Implement plus
    return nullptr;
}

int CacheStats::hashCode() {
    // TODO: Implement hashCode
    return 0;
}

bool CacheStats::equals(@Nullable Object) {
    // TODO: Implement equals
    return false;
}

std::string CacheStats::toString() {
    // TODO: Implement toString
    return "";
}

} // namespace cache
} // namespace common
} // namespace google
} // namespace com
