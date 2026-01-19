package zombie.spnetwork;

import zombie.network.PacketTypes.PacketType;

// $VF: synthetic class
class SinglePlayerClient$1 {
   static {
      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.ClientCommand.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.GlobalObjects.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.ObjectChange.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
