#pragma once
#include <mutex>
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace spnetwork {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZomboidNetDataPool {
public:

 // Mutexes for synchronized blocks
 static std::mutex Pool_mutex;
 static ZomboidNetDataPool instance = new ZomboidNetDataPool();
private
 ArrayDeque<ZomboidNetData> Pool = std::make_unique<ArrayDeque<>>();

 ZomboidNetData get() {
 { std::lock_guard<std::mutex> __sync_lock__(Pool_mutex);
 return this->Pool.empty() ? std::make_unique<ZomboidNetData>()
 : this->Pool.pop();
 }
 }

 void discard(ZomboidNetData zomboidNetData) {
 zomboidNetData.reset();
 if (zomboidNetData.buffer.capacity() == 2048) {
 { std::lock_guard<std::mutex> __sync_lock__(Pool_mutex); this->Pool.add(zomboidNetData); }
 }
 }

 ZomboidNetData getLong(int int0) { return new ZomboidNetData(int0); }
}
} // namespace spnetwork
} // namespace zombie
