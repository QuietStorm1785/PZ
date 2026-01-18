#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace spnetwork {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZomboidNetDataPool {
public:
 static ZomboidNetDataPool instance = new ZomboidNetDataPool();
 private ArrayDeque<ZomboidNetData> Pool = std::make_unique<ArrayDeque<>>();

 ZomboidNetData get() {
 synchronized (this->Pool) {
 return this->Pool.empty() ? std::make_unique<ZomboidNetData>() : this->Pool.pop();
 }
 }

 void discard(ZomboidNetData zomboidNetData) {
 zomboidNetData.reset();
 if (zomboidNetData.buffer.capacity() == 2048) {
 synchronized (this->Pool) {
 this->Pool.add(zomboidNetData);
 }
 }
 }

 ZomboidNetData getLong(int int0) {
 return new ZomboidNetData(int0);
 }
}
} // namespace spnetwork
} // namespace zombie
