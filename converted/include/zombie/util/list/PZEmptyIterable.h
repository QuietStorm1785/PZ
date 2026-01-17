#pragma once
#include <cstdint>
#include <iterator>
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

class PZEmptyIterable {
public:
private
  static final PZEmptyIterable<Object> instance =
      std::make_unique<PZEmptyIterable<>>();
private
  final Iterator<T> s_it =
      std::make_unique<Iterator<T>>(){bool hasNext(){return false;
}

    T next() {
  throw new ArrayIndexOutOfBoundsException("Empty Iterator. Has no data.");
}
}; // namespace list

private
PZEmptyIterable() {}

public
static<E> PZEmptyIterable<E> getInstance() {
  return (PZEmptyIterable<E>)instance;
}

public
Iterator<T> iterator() { return this.s_it; }
} // namespace util
} // namespace zombie
} // namespace util
} // namespace zombie
