package zombie.randomizedWorld.randomizedVehicleStory;

import zombie.iso.IsoGridSquare;
import zombie.iso.Vector2;

public final class VehicleStorySpawner$Element {
   String id;
   final Vector2 position = new Vector2();
   float direction;
   float width;
   float height;
   float z;
   IsoGridSquare square;

   VehicleStorySpawner$Element init(String var1, float var2, float var3, float var4, float var5, float var6) {
      this.id = var1;
      this.position.set(var2, var3);
      this.direction = var4;
      this.width = var5;
      this.height = var6;
      this.z = 0.0F;
      this.square = null;
      return this;
   }
}
