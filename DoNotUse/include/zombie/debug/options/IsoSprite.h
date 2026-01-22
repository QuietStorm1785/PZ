#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"

namespace zombie {
namespace debug {
namespace options {


class IsoSprite : public OptionGroup {
public:
    const BooleanDebugOption RenderSprites = newDebugOnlyOption(this.Group, "Render.Sprites", true);
    const BooleanDebugOption RenderModels = newDebugOnlyOption(this.Group, "Render.Models", true);
    const BooleanDebugOption MovingObjectEdges = newDebugOnlyOption(this.Group, "Render.MovingObjectEdges", false);
    const BooleanDebugOption DropShadowEdges = newDebugOnlyOption(this.Group, "Render.DropShadowEdges", false);
    const BooleanDebugOption NearestMagFilterAtMinZoom = newDebugOnlyOption(this.Group, "Render.NearestMagFilterAtMinZoom", true);
    const BooleanDebugOption ItemHeight = newDebugOnlyOption(this.Group, "Render.ItemHeight", false);
    const BooleanDebugOption Surface = newDebugOnlyOption(this.Group, "Render.Surface", false);
    const BooleanDebugOption TextureWrapClampToEdge = newDebugOnlyOption(this.Group, "Render.TextureWrap.ClampToEdge", false);
    const BooleanDebugOption TextureWrapRepeat = newDebugOnlyOption(this.Group, "Render.TextureWrap.Repeat", false);
    const BooleanDebugOption ForceLinearMagFilter = newDebugOnlyOption(this.Group, "Render.ForceLinearMagFilter", false);
    const BooleanDebugOption ForceNearestMagFilter = newDebugOnlyOption(this.Group, "Render.ForceNearestMagFilter", false);
    const BooleanDebugOption ForceNearestMipMapping = newDebugOnlyOption(this.Group, "Render.ForceNearestMipMapping", false);
    const BooleanDebugOption CharacterMipmapColors = newDebugOnlyOption(this.Group, "Render.CharacterMipmapColors", false);
    const BooleanDebugOption WorldMipmapColors = newDebugOnlyOption(this.Group, "Render.WorldMipmapColors", false);

    public IsoSprite() {
      super("IsoSprite");
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
