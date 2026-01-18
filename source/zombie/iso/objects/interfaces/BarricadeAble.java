// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.iso.objects.interfaces;

import zombie.characters.IsoGameCharacter;
import zombie.iso.IsoGridSquare;
import zombie.iso.objects.IsoBarricade;

public interface BarricadeAble {
    boolean isBarricaded();

    boolean isBarricadeAllowed();

    IsoBarricade getBarricadeOnSameSquare();

    IsoBarricade getBarricadeOnOppositeSquare();

    IsoBarricade getBarricadeForCharacter(IsoGameCharacter chr);

    IsoBarricade getBarricadeOppositeCharacter(IsoGameCharacter chr);

    IsoGridSquare getSquare();

    IsoGridSquare getOppositeSquare();

    boolean getNorth();
}
