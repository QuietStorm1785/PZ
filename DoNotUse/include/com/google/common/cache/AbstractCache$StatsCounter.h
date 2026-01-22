#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace cache {

class AbstractCache {
public:
    virtual ~AbstractCache() = default;
    void recordHits(int var1);

    void recordMisses(int var1);

    void recordLoadSuccess(long var1);

    void recordLoadException(long var1);

    void recordEviction();

    CacheStats snapshot();
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
