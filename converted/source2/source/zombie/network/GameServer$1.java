package zombie.network;

import zombie.network.PacketTypes.PacketType;

// $VF: synthetic class
class GameServer$1 {
   static {
      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.Login.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.Ping.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.ScoreboardUpdate.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
