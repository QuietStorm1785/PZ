// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.characters;

import zombie.iso.IsoCamera;

public final class IsoDummyCameraCharacter extends IsoGameCharacter {
    public IsoDummyCameraCharacter(float x, float y, float z) {
        super(null, x, y, z);
        IsoCamera.CamCharacter = this;
    }

    @Override
    public void update() {
    }
}
