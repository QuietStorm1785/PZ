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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class BucketManager {
public:
 static const Bucket SharedBucket = new Bucket();

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
