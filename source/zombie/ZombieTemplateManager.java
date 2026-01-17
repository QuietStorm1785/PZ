// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie;

import java.util.ArrayList;
import zombie.characters.BodyDamage.BodyPartType;
import zombie.core.textures.Texture;

public class ZombieTemplateManager {
    public Texture addOverlayToTexture(ArrayList<ZombieTemplateManager.BodyOverlay> var1, Texture var2) {
        return null;
    }

    public class BodyOverlay {
        public BodyPartType location;
        public ZombieTemplateManager.OverlayType type;
    }

    public static enum OverlayType {
        BloodLight,
        BloodMedium,
        BloodHeavy;
    }

    public class ZombieTemplate {
        public Texture tex;
    }
}
