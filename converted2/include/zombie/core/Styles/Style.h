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
 * The default sprite renderer has various different styles of rendering, which
 * affect what data it uses from the buffer and what GL state that it sets and
 * resets before and after rendering.
 */
class Style {
public:
  virtual ~Style() = default;
  /**
   * Called to set up GL rendering state before actual drawing is done.
   */
  void setupState();

  /**
   * Called to reset GL rendering state after actual drawing is done.
   */
  void resetState();

  /**
   * @return the style's ID, which affects its rendering order
   */
  int getStyleID();

  /**
   * @return the style's alpha operation
   */
  AlphaOp getAlphaOp();

  /**
   * Whether to actually render a sprite when using this Style.
   * @return boolean
   */
  bool getRenderSprite();

  /**
   * If not rendering a sprite, then we perform a build() to create
   * @return the vertex data, or null
   */
  GeometryData build();

  /**
   * If not rendering a sprite, then render stuff. Our geometry was written to a
   * pre-prepared buffer which is pointed to  already.
   */
  void render(int vertexOffset, int indexOffset);
}
} // namespace Styles
} // namespace core
} // namespace zombie
