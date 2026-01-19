package zombie.characters;

import zombie.iso.IsoUtils;
import zombie.network.NetworkVariables.PredictionTypes;

public class NetworkTeleport$NetworkTeleportDebug {
   short id;
   float nx;
   float ny;
   float nz;
   float lx;
   float ly;
   float lz;
   PredictionTypes type;

   public NetworkTeleport$NetworkTeleportDebug(short var1, float var2, float var3, float var4, float var5, float var6, float var7, PredictionTypes var8) {
      this.id = var1;
      this.nx = var5;
      this.ny = var6;
      this.nz = var7;
      this.lx = var2;
      this.ly = var3;
      this.lz = var4;
      this.type = var8;
   }

   public float getDistance() {
      return IsoUtils.DistanceTo(this.lx, this.ly, this.lz, this.nx, this.ny, this.nz);
   }
}
