// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.network;

import java.nio.ByteBuffer;
import zombie.iso.IsoObject;

public class WorldItemTypes {
    public static IsoObject createFromBuffer(ByteBuffer byteBuffer) {
        Object object = null;
        return IsoObject.factoryFromFileInput(null, byteBuffer);
    }
}
