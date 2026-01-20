#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace bucket {

class BucketManager {
public:
    static const Bucket SharedBucket = std::make_shared<Bucket>();

    static Bucket Active() {
    return SharedBucket;
   }

    static Bucket Shared() {
    return SharedBucket;
   }
}
} // namespace bucket
} // namespace core
} // namespace zombie
