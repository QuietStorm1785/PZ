#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace Styles {

class GeometryData {
public:
    const FloatList vertexData;
    const ShortList indexData;

    public GeometryData(FloatList var1, ShortList var2) {
      this.vertexData = var1;
      this.indexData = var2;
   }

    void clear() {
      this.vertexData.clear();
      this.indexData.clear();
   }

    FloatList getVertexData() {
      return this.vertexData;
   }

    ShortList getIndexData() {
      return this.indexData;
   }
}
} // namespace Styles
} // namespace core
} // namespace zombie
