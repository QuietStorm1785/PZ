package zombie.audio.parameters;

enum ParameterRoomType$RoomType {
   Generic(0),
   Barn(1),
   Mall(2),
   Warehouse(3),
   Prison(4),
   Church(5),
   Office(6),
   Factory(7);

   final int label;

   private ParameterRoomType$RoomType(int var3) {
      this.label = var3;
   }
}
