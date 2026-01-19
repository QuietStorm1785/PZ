package zombie.audio.parameters;

enum ParameterVehicleRoadMaterial$Material {
   Concrete(0),
   Grass(1),
   Gravel(2),
   Puddle(3),
   Snow(4),
   Wood(5),
   Carpet(6),
   Dirt(7),
   Sand(8);

   final int label;

   private ParameterVehicleRoadMaterial$Material(int var3) {
      this.label = var3;
   }
}
