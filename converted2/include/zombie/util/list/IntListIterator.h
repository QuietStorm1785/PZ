#pragma once
#include "zombie/util/IntIterator.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace list {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IntListIterator {
public:
  virtual ~IntListIterator() = default;
  void add(int var1);

  bool hasPrevious();

  int nextIndex();

  int previous();

  int previousIndex();

  void set(int var1);
}
} // namespace list
} // namespace util
} // namespace zombie
