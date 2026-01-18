// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.iso.sprite.shapers;

import zombie.core.textures.TextureDraw;

public class FloorShaperDiamond extends FloorShaper {
    public static final FloorShaperDiamond instance = new FloorShaperDiamond();

    @Override
    public void accept(TextureDraw textureDraw) {
        super.accept(textureDraw);
        DiamondShaper.instance.accept(textureDraw);
    }
}
