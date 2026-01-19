package zombie.network;

import java.util.Map;
import java.util.TreeMap;
import se.krka.kahlua.vm.KahluaTable;
import zombie.Lua.LuaManager;
import zombie.core.network.ByteBufferWriter;
import zombie.debug.DebugLog;
import zombie.network.PacketTypes.PacketType;

public class PacketTypes {
   public static final short ContainerDeadBody = 0;
   public static final short ContainerWorldObject = 1;
   public static final short ContainerObject = 2;
   public static final short ContainerVehicle = 3;
   public static final Map<Short, PacketType> packetTypes = new TreeMap<>();
   public static final KahluaTable packetCountTable = LuaManager.platform.newTable();

   public static void doPingPacket(ByteBufferWriter var0) {
      var0.putInt(28);
   }

   public static KahluaTable getPacketCounts(int var0) {
      packetCountTable.wipe();
      if (GameClient.bClient) {
         for (PacketType var2 : packetTypes.values()) {
            if (var0 == 1) {
               packetCountTable.rawset(String.format("%03d-%s", var2.id, var2.name()), String.valueOf(var2.serverPacketCount));
            } else {
               packetCountTable.rawset(String.format("%03d-%s", var2.id, var2.name()), String.valueOf(var2.clientPacketCount));
            }
         }
      }

      return packetCountTable;
   }

   static {
      for (PacketType var3 : PacketType.values()) {
         PacketType var4 = packetTypes.put(var3.getId(), var3);
         if (var4 != null) {
            DebugLog.Multiplayer.error(String.format("PacketType: duplicate \"%s\" \"%s\" id=%d", var4.name(), var3.name(), var3.getId()));
         }
      }
   }
}
