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
 * Convenient base class implementation of
 */
class AbstractStyle {
public:
  static const long serialVersionUID = 1L;

  /**
   * Description copied from interface: Style
   * @return boolean
   */
  bool getRenderSprite() { return false; }

  /**
   * @return the style's alpha operation
   */
  AlphaOp getAlphaOp() { return null; }

  /**
   * @return the style's ID, which affects its rendering order
   */
  int getStyleID() { return this.hashCode(); }

  /**
   * Description copied from interface: Style
   */
  void resetState() {}

  /**
   * Description copied from interface: Style
   */
  void setupState() {}

  /**
   * Description copied from interface: Style
   * @return the vertex data, or null
   */
  GeometryData build() { return null; }

  /**
   * Description copied from interface: Style
   */
  void render(int vertexOffset, int indexOffset) {}
}
} // namespace Styles
} // namespace core
} // namespace zombie
