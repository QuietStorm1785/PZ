// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.network.packets;

import java.nio.ByteBuffer;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;

public interface INetworkPacket {
    void parse(ByteBuffer b, UdpConnection connection);

    void write(ByteBufferWriter b);

    default int getPacketSizeBytes() {
        return 0;
    }

    default boolean isConsistent() {
        return true;
    }

    default String getDescription() {
        return this.getClass().getSimpleName();
    }

    default void log(UdpConnection connection, String tag) {
    }
}
