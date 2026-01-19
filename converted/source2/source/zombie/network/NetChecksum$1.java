package zombie.network;

import zombie.network.NetChecksum.Comparer.State;

// $VF: synthetic class
class NetChecksum$1 {
   static {
      try {
         $SwitchMap$zombie$network$NetChecksum$Comparer$State[State.Init.ordinal()] = 1;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$network$NetChecksum$Comparer$State[State.SentTotalChecksum.ordinal()] = 2;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$network$NetChecksum$Comparer$State[State.SentGroupChecksum.ordinal()] = 3;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$network$NetChecksum$Comparer$State[State.SentFileChecksums.ordinal()] = 4;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$network$NetChecksum$Comparer$State[State.Success.ordinal()] = 5;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$network$NetChecksum$Comparer$State[State.Failed.ordinal()] = 6;
      } catch (NoSuchFieldError var1) {
      }
   }
}
