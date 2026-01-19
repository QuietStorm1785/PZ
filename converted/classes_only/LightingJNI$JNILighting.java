package zombie.iso;

import zombie.characters.IsoPlayer;
import zombie.core.textures.ColorInfo;
import zombie.iso.IsoGridSquare.ILighting;
import zombie.iso.IsoGridSquare.ResultLight;
import zombie.meta.Meta;
import zombie.network.GameClient;
import zombie.network.GameServer;

public final class LightingJNI$JNILighting implements ILighting {
   private static final int RESULT_LIGHTS_PER_SQUARE = 5;
   private static final int[] lightInts = new int[43];
   private static final byte VIS_SEEN = 1;
   private static final byte VIS_CAN_SEE = 2;
   private static final byte VIS_COULD_SEE = 4;
   private int playerIndex;
   private final IsoGridSquare square;
   private ColorInfo lightInfo = new ColorInfo();
   private byte vis;
   private float cacheDarkMulti;
   private float cacheTargetDarkMulti;
   private int[] cacheVertLight;
   private int updateTick = -1;
   private int lightsCount;
   private ResultLight[] lights;

   public LightingJNI$JNILighting(int var1, IsoGridSquare var2) {
      this.playerIndex = var1;
      this.square = var2;
      this.cacheDarkMulti = 0.0F;
      this.cacheTargetDarkMulti = 0.0F;
      this.cacheVertLight = new int[8];

      for (int var3 = 0; var3 < 8; var3++) {
         this.cacheVertLight[var3] = 0;
      }
   }

   public int lightverts(int var1) {
      return this.cacheVertLight[var1];
   }

   public float lampostTotalR() {
      return 0.0F;
   }

   public float lampostTotalG() {
      return 0.0F;
   }

   public float lampostTotalB() {
      return 0.0F;
   }

   public boolean bSeen() {
      this.update();
      return (this.vis & 1) != 0;
   }

   public boolean bCanSee() {
      this.update();
      return (this.vis & 2) != 0;
   }

   public boolean bCouldSee() {
      this.update();
      return (this.vis & 4) != 0;
   }

   public float darkMulti() {
      return this.cacheDarkMulti;
   }

   public float targetDarkMulti() {
      return this.cacheTargetDarkMulti;
   }

   public ColorInfo lightInfo() {
      this.update();
      return this.lightInfo;
   }

   public void lightverts(int var1, int var2) {
      throw new IllegalStateException();
   }

   public void lampostTotalR(float var1) {
      throw new IllegalStateException();
   }

   public void lampostTotalG(float var1) {
      throw new IllegalStateException();
   }

   public void lampostTotalB(float var1) {
      throw new IllegalStateException();
   }

   public void bSeen(boolean var1) {
      throw new IllegalStateException();
   }

   public void bCanSee(boolean var1) {
      throw new IllegalStateException();
   }

   public void bCouldSee(boolean var1) {
      throw new IllegalStateException();
   }

   public void darkMulti(float var1) {
      throw new IllegalStateException();
   }

   public void targetDarkMulti(float var1) {
      throw new IllegalStateException();
   }

   public int resultLightCount() {
      return this.lightsCount;
   }

   public ResultLight getResultLight(int var1) {
      return this.lights[var1];
   }

   public void reset() {
      this.updateTick = -1;
   }

   private void update() {
      if (LightingJNI.updateCounter[this.playerIndex] != -1) {
         if (this.updateTick != LightingJNI.updateCounter[this.playerIndex]
            && LightingJNI.getSquareLighting(this.playerIndex, this.square.x, this.square.y, this.square.z, lightInts)) {
            IsoPlayer var1 = IsoPlayer.players[this.playerIndex];
            boolean var2 = (this.vis & 1) != 0;
            int var3 = 0;
            this.vis = (byte)(lightInts[var3++] & 7);
            this.lightInfo.r = (lightInts[var3] & 0xFF) / 255.0F;
            this.lightInfo.g = (lightInts[var3] >> 8 & 0xFF) / 255.0F;
            this.lightInfo.b = (lightInts[var3++] >> 16 & 0xFF) / 255.0F;
            this.cacheDarkMulti = lightInts[var3++] / 100000.0F;
            this.cacheTargetDarkMulti = lightInts[var3++] / 100000.0F;
            float var4 = 1.0F;
            float var5 = 1.0F;
            if (var1 != null) {
               int var6 = this.square.z - (int)var1.z;
               if (var6 == -1) {
                  var4 = 1.0F;
                  var5 = 0.85F;
               } else if (var6 < -1) {
                  var4 = 0.85F;
                  var5 = 0.85F;
               }

               if ((this.vis & 2) == 0 && (this.vis & 4) != 0) {
                  int var7 = (int)var1.x;
                  int var8 = (int)var1.y;
                  int var9 = this.square.x - var7;
                  int var10 = this.square.y - var8;
                  if (var1.dir != IsoDirections.Max && Math.abs(var9) <= 2 && Math.abs(var10) <= 2) {
                     int[] var11 = LightingJNI.ForcedVis[var1.dir.index()];

                     for (byte var12 = 0; var12 < var11.length; var12 += 2) {
                        if (var9 == var11[var12] && var10 == var11[var12 + 1]) {
                           this.vis = (byte)(this.vis | 2);
                           break;
                        }
                     }
                  }
               }
            }

            for (int var23 = 0; var23 < 4; var23++) {
               int var27 = lightInts[var3++];
               float var30 = (var27 & 0xFF) * var5;
               float var32 = ((var27 & 0xFF00) >> 8) * var5;
               float var34 = ((var27 & 0xFF0000) >> 16) * var5;
               this.cacheVertLight[var23] = (int)var30 << 0 | (int)var32 << 8 | (int)var34 << 16 | 0xFF000000;
            }

            for (int var24 = 4; var24 < 8; var24++) {
               int var28 = lightInts[var3++];
               float var31 = (var28 & 0xFF) * var4;
               float var33 = ((var28 & 0xFF00) >> 8) * var4;
               float var35 = ((var28 & 0xFF0000) >> 16) * var4;
               this.cacheVertLight[var24] = (int)var31 << 0 | (int)var33 << 8 | (int)var35 << 16 | 0xFF000000;
            }

            this.lightsCount = lightInts[var3++];

            for (int var25 = 0; var25 < this.lightsCount; var25++) {
               if (this.lights == null) {
                  this.lights = new ResultLight[5];
               }

               if (this.lights[var25] == null) {
                  this.lights[var25] = new ResultLight();
               }

               this.lights[var25].id = lightInts[var3++];
               this.lights[var25].x = lightInts[var3++];
               this.lights[var25].y = lightInts[var3++];
               this.lights[var25].z = lightInts[var3++];
               this.lights[var25].radius = lightInts[var3++];
               int var29 = lightInts[var3++];
               this.lights[var25].r = (var29 & 0xFF) / 255.0F;
               this.lights[var25].g = (var29 >> 8 & 0xFF) / 255.0F;
               this.lights[var25].b = (var29 >> 16 & 0xFF) / 255.0F;
               this.lights[var25].flags = var29 >> 24 & 0xFF;
            }

            this.updateTick = LightingJNI.updateCounter[this.playerIndex];
            if ((this.vis & 1) != 0) {
               if (var2 && this.square.getRoom() != null && this.square.getRoom().def != null && !this.square.getRoom().def.bExplored) {
                  boolean var26 = true;
               }

               this.square.checkRoomSeen(this.playerIndex);
               if (!var2) {
                  if (!$assertionsDisabled && GameServer.bServer) {
                     throw new AssertionError();
                  }

                  if (!GameClient.bClient) {
                     Meta.instance.dealWithSquareSeen(this.square);
                  }
               }
            }
         }
      }
   }
}
