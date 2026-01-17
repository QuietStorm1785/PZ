// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.chat;

import zombie.iso.IsoGridSquare;

/**
 * Turbo
 */
public interface ChatElementOwner {
    float getX();

    float getY();

    float getZ();

    IsoGridSquare getSquare();
}
