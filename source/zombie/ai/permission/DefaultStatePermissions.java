// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.ai.permission;

import zombie.characters.IsoGameCharacter;

public class DefaultStatePermissions implements IStatePermissions {
    public static final DefaultStatePermissions Instance = new DefaultStatePermissions();

    @Override
    public boolean isDeferredMovementAllowed(IsoGameCharacter var1) {
        return true;
    }

    @Override
    public boolean isPlayerInputAllowed(IsoGameCharacter var1) {
        return true;
    }
}
