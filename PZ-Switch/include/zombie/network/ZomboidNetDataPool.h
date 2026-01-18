#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZomboidNetDataPool {
public:
 static const ZomboidNetDataPool instance = new ZomboidNetDataPool();
 ConcurrentLinkedQueue<ZomboidNetData> Pool =
 std::make_unique<ConcurrentLinkedQueue<>>();

 ZomboidNetData get() {
 ZomboidNetData zomboidNetData = this->Pool.poll();
 return zomboidNetData = = nullptr ? new ZomboidNetData() : zomboidNetData;
 }

 void discard(ZomboidNetData zomboidNetData) {
 zomboidNetData.reset();
 if (zomboidNetData.buffer.capacity() == 2048) {
 this->Pool.add(zomboidNetData);
 }
 }

 ZomboidNetData getLong(int int0) { return new ZomboidNetData(int0); }
}
} // namespace network
} // namespace zombie
