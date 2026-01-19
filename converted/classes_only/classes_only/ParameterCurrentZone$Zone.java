package zombie.audio.parameters;

enum ParameterCurrentZone$Zone {
   None(0),
   DeepForest(1),
   Farm(2),
   Forest(3),
   Nav(4),
   Town(5),
   TrailerPark(6),
   Vegetation(7);

   final int label;

   private ParameterCurrentZone$Zone(int var3) {
      this.label = var3;
   }
}
