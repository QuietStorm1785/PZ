// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.spnetwork;

import java.nio.ByteBuffer;

public abstract class UdpEngine {
    public abstract void Send(ByteBuffer bb);

    public abstract void Receive(ByteBuffer bb);
}
