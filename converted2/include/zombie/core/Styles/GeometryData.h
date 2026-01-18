#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace Styles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Really basic geometry data which is used by
 */
class GeometryData {
public:
  const FloatList vertexData;
  const ShortList indexData;

  /**
   * C'tor
   */
public
  GeometryData(FloatList _vertexData, ShortList _indexData) {
    this.vertexData = _vertexData;
    this.indexData = _indexData;
  }

  void clear() {
    this.vertexData.clear();
    this.indexData.clear();
  }

  FloatList getVertexData() { return this.vertexData; }

  ShortList getIndexData() { return this.indexData; }
}
} // namespace Styles
} // namespace core
} // namespace zombie
