#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PooledArrayObject {
public:
private
  T[] m_array = nullptr;

public
  T[] array() { return this.m_array; }

  int length() { return this.m_array.length; }

  T get(int int0) { return this.m_array[int0]; }

  void set(int int0, T object) { this.m_array[int0] = (T)object; }

  void initCapacity(int int0, T[] > function) {
    if (this.m_array == nullptr || this.m_array.length != int0) {
      this.m_array = (T[])((Object[])function.apply(int0));
    }
  }

  bool isEmpty() { return this.m_array == nullptr || this.m_array.length == 0; }
}
} // namespace util
} // namespace zombie
