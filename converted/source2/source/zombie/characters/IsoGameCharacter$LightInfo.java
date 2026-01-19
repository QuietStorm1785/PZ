package zombie.characters;

import java.util.ArrayList;
import zombie.characters.IsoGameCharacter.TorchInfo;
import zombie.iso.IsoGridSquare;

public class IsoGameCharacter$LightInfo {
   public IsoGridSquare square;
   public float x;
   public float y;
   public float z;
   public float angleX;
   public float angleY;
   public ArrayList<TorchInfo> torches = new ArrayList<>();
   public long time;
   public float night;
   public float rmod;
   public float gmod;
   public float bmod;

   public void initFrom(IsoGameCharacter$LightInfo var1) {
      this.square = var1.square;
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.angleX = var1.angleX;
      this.angleY = var1.angleY;
      this.torches.clear();
      this.torches.addAll(var1.torches);
      this.time = (long)(System.nanoTime() / 1000000.0);
      this.night = var1.night;
      this.rmod = var1.rmod;
      this.gmod = var1.gmod;
      this.bmod = var1.bmod;
   }
}
