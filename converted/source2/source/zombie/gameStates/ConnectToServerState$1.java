package zombie.gameStates;

import zombie.gameStates.ConnectToServerState.State;
import zombie.gameStates.ConnectToServerState.WorkshopItemState;

// $VF: synthetic class
class ConnectToServerState$1 {
   static {
      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$WorkshopItemState[WorkshopItemState.CheckItemState.ordinal()] = 1;
      } catch (NoSuchFieldError var14) {
      }

      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$WorkshopItemState[WorkshopItemState.SubscribePending.ordinal()] = 2;
      } catch (NoSuchFieldError var13) {
      }

      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$WorkshopItemState[WorkshopItemState.DownloadPending.ordinal()] = 3;
      } catch (NoSuchFieldError var12) {
      }

      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$WorkshopItemState[WorkshopItemState.Ready.ordinal()] = 4;
      } catch (NoSuchFieldError var11) {
      }

      $SwitchMap$zombie$gameStates$ConnectToServerState$State = new int[State.values().length];

      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$State[State.Start.ordinal()] = 1;
      } catch (NoSuchFieldError var10) {
      }

      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$State[State.TestTCP.ordinal()] = 2;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$State[State.WorkshopInit.ordinal()] = 3;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$State[State.WorkshopQuery.ordinal()] = 4;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$State[State.WorkshopConfirm.ordinal()] = 5;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$State[State.ServerWorkshopItemScreen.ordinal()] = 6;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$State[State.WorkshopUpdate.ordinal()] = 7;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$State[State.CheckMods.ordinal()] = 8;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$State[State.Finish.ordinal()] = 9;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$gameStates$ConnectToServerState$State[State.Exit.ordinal()] = 10;
      } catch (NoSuchFieldError var1) {
      }
   }
}
