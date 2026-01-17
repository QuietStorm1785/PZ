// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.ai.permission;

import zombie.characters.IsoGameCharacter;

public interface IStatePermissions {
    boolean isDeferredMovementAllowed(IsoGameCharacter chr);

    boolean isPlayerInputAllowed(IsoGameCharacter chr);
}
