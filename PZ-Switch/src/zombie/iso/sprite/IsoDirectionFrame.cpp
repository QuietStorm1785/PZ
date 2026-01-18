#include "zombie/iso/sprite/IsoDirectionFrame.h"

namespace zombie {
namespace iso {
namespace sprite {

public
IsoDirectionFrame::IsoDirectionFrame(Texture tex) {
 // TODO: Implement IsoDirectionFrame
 return nullptr;
}

public
IsoDirectionFrame::IsoDirectionFrame() {
 // TODO: Implement IsoDirectionFrame
 return nullptr;
}

public
IsoDirectionFrame::IsoDirectionFrame(Texture nw, Texture n, Texture ne,
 Texture e, Texture se) {
 // TODO: Implement IsoDirectionFrame
 return nullptr;
}

public
IsoDirectionFrame::IsoDirectionFrame(Texture n, Texture nw, Texture w,
 Texture sw, Texture s, Texture se,
 Texture e, Texture ne) {
 // TODO: Implement IsoDirectionFrame
 return nullptr;
}

public
IsoDirectionFrame::IsoDirectionFrame(Texture n, Texture s, Texture e,
 Texture w) {
 // TODO: Implement IsoDirectionFrame
 return nullptr;
}

Texture IsoDirectionFrame::getTexture(IsoDirections dir) {
 // TODO: Implement getTexture
 return nullptr;
}

void IsoDirectionFrame::SetAllDirections(Texture tex) {
 // TODO: Implement SetAllDirections
}

void IsoDirectionFrame::SetDirection(Texture tex, IsoDirections dir) {
 // TODO: Implement SetDirection
}

void IsoDirectionFrame::render(float sx, float sy, IsoDirections dir,
 ColorInfo info, bool Flip,
 Consumer<TextureDraw> texdModifier) {
 // TODO: Implement render
}

void IsoDirectionFrame::renderexplicit(int sx, int sy, IsoDirections dir,
 float scale) {
 // TODO: Implement renderexplicit
}

void IsoDirectionFrame::renderexplicit(int sx, int sy, IsoDirections dir,
 float scale, ColorInfo color) {
 // TODO: Implement renderexplicit
}

} // namespace sprite
} // namespace iso
} // namespace zombie
