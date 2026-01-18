// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.iso.objects.interfaces;

import zombie.characters.IsoGameCharacter;
import zombie.inventory.types.HandWeapon;
import zombie.iso.IsoMovingObject;

public interface Thumpable {
    boolean isDestroyed();

    void Thump(IsoMovingObject thumper);

    void WeaponHit(IsoGameCharacter chr, HandWeapon weapon);

    Thumpable getThumpableFor(IsoGameCharacter chr);

    float getThumpCondition();
}
