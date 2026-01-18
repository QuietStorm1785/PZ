#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace utils {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class UpdateTimer {
public:
 long time = 0L;

public
 UpdateTimer() { this->time = System.currentTimeMillis() + 3800L; }

 void reset(long _time) { this->time = System.currentTimeMillis() + _time; }

 bool check() {
 return this->time != 0L && System.currentTimeMillis() + 200L >= this->time;
 }

 long getTime() { return this->time; }
}
} // namespace utils
} // namespace core
} // namespace zombie
