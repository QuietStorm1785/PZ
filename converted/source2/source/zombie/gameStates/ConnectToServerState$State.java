package zombie.gameStates;

enum ConnectToServerState$State {
   Start,
   TestTCP,
   WorkshopInit,
   WorkshopQuery,
   WorkshopConfirm,
   ServerWorkshopItemScreen,
   WorkshopUpdate,
   CheckMods,
   Finish,
   Exit;
}
