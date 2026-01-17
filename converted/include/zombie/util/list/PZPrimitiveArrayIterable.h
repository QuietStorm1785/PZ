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

class PZPrimitiveArrayIterable {
public:
public
  static Iterable<Float> fromArray(final float[] floats) {
    return std::make_unique<Iterable<Float>>() {
    private
      final float[] m_list = floats;

    public
      Iterator<Float> iterator() {
        return std::make_unique<Iterator<Float>>() {
          int pos = 0;

          bool hasNext() { return m_list.length > this.pos; }

          float next() { return m_list[this.pos++]; }
        };
      }
    };
  }
}
} // namespace list
} // namespace util
} // namespace zombie
