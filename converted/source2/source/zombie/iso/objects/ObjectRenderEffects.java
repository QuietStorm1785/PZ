package zombie.iso.objects;

import java.util.ArrayDeque;
import java.util.ArrayList;
import zombie.GameTime;
import zombie.core.Core;
import zombie.core.Rand;
import zombie.iso.IsoObject;
import zombie.iso.objects.ObjectRenderEffects.1;
import zombie.iso.weather.ClimateManager;
import zombie.network.GameServer;

public class ObjectRenderEffects {
   public static final boolean ENABLED = true;
   private static ArrayDeque<ObjectRenderEffects> pool = new ArrayDeque<>();
   public double x1;
   public double y1;
   public double x2;
   public double y2;
   public double x3;
   public double y3;
   public double x4;
   public double y4;
   private double tx1;
   private double ty1;
   private double tx2;
   private double ty2;
   private double tx3;
   private double ty3;
   private double tx4;
   private double ty4;
   private double lx1;
   private double ly1;
   private double lx2;
   private double ly2;
   private double lx3;
   private double ly3;
   private double lx4;
   private double ly4;
   private double maxX;
   private double maxY;
   private float curTime = 0.0F;
   private float maxTime = 0.0F;
   private float totalTime = 0.0F;
   private float totalMaxTime = 0.0F;
   private RenderEffectType type;
   private IsoObject parent;
   private boolean finish = false;
   private boolean isTree = false;
   private boolean isBig = false;
   private boolean gust = false;
   private int windType = 1;
   private static float T_MOD = 1.0F;
   private static int windCount = 0;
   private static int windCountTree = 0;
   private static final int EFFECTS_COUNT = 15;
   private static final int TYPE_COUNT = 3;
   private static final ObjectRenderEffects[][] WIND_EFFECTS = new ObjectRenderEffects[3][15];
   private static final ObjectRenderEffects[][] WIND_EFFECTS_TREES = new ObjectRenderEffects[3][15];
   private static final ArrayList<ObjectRenderEffects> DYNAMIC_EFFECTS = new ArrayList<>();
   private static ObjectRenderEffects RANDOM_RUSTLE;
   private static float randomRustleTime = 0.0F;
   private static float randomRustleTotalTime = 0.0F;
   private static int randomRustleTarget = 0;
   private static int randomRustleType = 0;

   public static ObjectRenderEffects alloc() {
      return !pool.isEmpty() ? pool.pop() : new ObjectRenderEffects();
   }

   public static void release(ObjectRenderEffects var0) {
      assert !pool.contains(var0);

      pool.push(var0.reset());
   }

   private ObjectRenderEffects() {
   }

   private ObjectRenderEffects reset() {
      this.parent = null;
      this.finish = false;
      this.isBig = false;
      this.isTree = false;
      this.curTime = 0.0F;
      this.maxTime = 0.0F;
      this.totalTime = 0.0F;
      this.totalMaxTime = 0.0F;
      this.x1 = 0.0;
      this.y1 = 0.0;
      this.x2 = 0.0;
      this.y2 = 0.0;
      this.x3 = 0.0;
      this.y3 = 0.0;
      this.x4 = 0.0;
      this.y4 = 0.0;
      this.tx1 = 0.0;
      this.ty1 = 0.0;
      this.tx2 = 0.0;
      this.ty2 = 0.0;
      this.tx3 = 0.0;
      this.ty3 = 0.0;
      this.tx4 = 0.0;
      this.ty4 = 0.0;
      this.swapTargetToLast();
      return this;
   }

   public static ObjectRenderEffects getNew(IsoObject var0, RenderEffectType var1, boolean var2) {
      return getNew(var0, var1, var2, false);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public static ObjectRenderEffects getNew(IsoObject var0, RenderEffectType var1, boolean var2, boolean var3) {
      if (GameServer.bServer) {
         return null;
      } else if (var1 == RenderEffectType.Hit_Door && !Core.getInstance().getOptionDoDoorSpriteEffects()) {
         return null;
      } else {
         ObjectRenderEffects var4 = null;

         try {
            boolean var5 = false;
            if (var2 && var0 != null && var0.getObjectRenderEffects() != null && var0.getObjectRenderEffects().type == var1) {
               var4 = var0.getObjectRenderEffects();
               var5 = true;
            } else {
               var4 = alloc();
            }

            var4.type = var1;
            var4.parent = var0;
            var4.finish = false;
            var4.isBig = false;
            var4.totalTime = 0.0F;
            switch (1.$SwitchMap$zombie$iso$objects$RenderEffectType[var1.ordinal()]) {
               case 1:
                  var4.totalMaxTime = Rand.Next(45.0F, 60.0F) * T_MOD;
                  break;
               case 2:
                  var4.totalMaxTime = Rand.Next(45.0F, 60.0F) * T_MOD;
                  if (var0 != null && var0 instanceof IsoTree) {
                     var4.isTree = true;
                     var4.isBig = ((IsoTree)var0).size > 4;
                  }
                  break;
               case 3:
                  var4.totalMaxTime = Rand.Next(15.0F, 30.0F) * T_MOD;
            }

            if (!var5 && var0 != null && var0.getWindRenderEffects() != null && Core.getInstance().getOptionDoWindSpriteEffects()) {
               var4.copyMainFromOther(var0.getWindRenderEffects());
            }

            if (!var5 && !var3) {
               DYNAMIC_EFFECTS.add(var4);
            }
         } catch (Exception var6) {
            var6.printStackTrace();
         }

         return var4;
      }
   }

   public static ObjectRenderEffects getNextWindEffect(int var0, boolean var1) {
      int var2 = var0 - 1;
      if (var2 < 0 || var2 >= 3) {
         return null;
      } else if (var1) {
         if (++windCountTree >= 15) {
            windCountTree = 0;
         }

         return WIND_EFFECTS_TREES[var2][windCountTree];
      } else {
         if (++windCount >= 15) {
            windCount = 0;
         }

         return WIND_EFFECTS[var2][windCount];
      }
   }

   public static void init() {
      if (!GameServer.bServer) {
         for (int var0 = 0; var0 < 3; var0++) {
            for (int var1 = 0; var1 < 15; var1++) {
               ObjectRenderEffects var2 = new ObjectRenderEffects();
               var2.windType = var0 + 1;
               WIND_EFFECTS[var0][var1] = var2;
            }

            for (int var3 = 0; var3 < 15; var3++) {
               ObjectRenderEffects var4 = new ObjectRenderEffects();
               var4.isTree = true;
               var4.windType = var0 + 1;
               WIND_EFFECTS_TREES[var0][var3] = var4;
            }
         }

         DYNAMIC_EFFECTS.clear();
         windCount = 0;
         windCountTree = 0;
         RANDOM_RUSTLE = null;
         randomRustleTime = 0.0F;
         randomRustleTotalTime = 0.0F;
         randomRustleTarget = 0;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public boolean update() {
      this.curTime = this.curTime + 1.0F * GameTime.getInstance().getMultiplier();
      this.totalTime = this.totalTime + 1.0F * GameTime.getInstance().getMultiplier();
      if (this.curTime > this.maxTime) {
         if (this.finish) {
            return false;
         }

         this.curTime = 0.0F;
         this.swapTargetToLast();
         float var1 = ClimateManager.clamp01(this.totalTime / this.totalMaxTime);
         float var2 = 1.0F - var1;
         switch (1.$SwitchMap$zombie$iso$objects$RenderEffectType[this.type.ordinal()]) {
            case 1:
               if (this.totalTime > this.totalMaxTime) {
                  this.maxTime = 10.0F * T_MOD;
                  this.tx1 = 0.0;
                  this.tx2 = 0.0;
                  this.finish = true;
               } else {
                  this.maxTime = (3.0F + 15.0F * var1) * T_MOD;
                  double var8 = this.isBig ? Rand.Next(-0.01F + -0.08F * var2, 0.01F + 0.08F * var2) : Rand.Next(-0.02F + -0.16F * var2, 0.02F + 0.16F * var2);
                  this.tx1 = var8;
                  this.tx2 = var8;
               }
               break;
            case 2:
               if (this.totalTime > this.totalMaxTime) {
                  this.maxTime = 3.0F * T_MOD;
                  this.tx1 = 0.0;
                  this.tx2 = 0.0;
                  this.finish = true;
               } else {
                  this.maxTime = (2.0F + 6.0F * var1) * T_MOD;
                  double var7 = this.isBig ? Rand.Next(-0.00625F, 0.00625F) : Rand.Next(-0.015F, 0.015F);
                  double var9 = this.isBig ? Rand.Next(-0.00625F, 0.00625F) : Rand.Next(-0.015F, 0.015F);
                  if (ClimateManager.getWindTickFinal() < 0.15) {
                     var7 *= 0.6;
                     var9 *= 0.6;
                  }

                  this.tx1 = var7;
                  this.ty1 = var9;
                  this.tx2 = var7;
                  this.ty2 = var9;
               }
               break;
            case 3:
               if (this.totalTime > this.totalMaxTime) {
                  this.maxTime = 3.0F * T_MOD;
                  this.tx1 = 0.0;
                  this.tx2 = 0.0;
                  this.finish = true;
               } else {
                  this.maxTime = (1.0F + 2.0F * var1) * T_MOD;
                  double var3 = Rand.Next(-0.005F, 0.005F);
                  double var5 = Rand.Next(-0.0075F, 0.0075F);
                  this.tx1 = var3;
                  this.ty1 = var5;
                  this.tx2 = var3;
                  this.ty2 = var5;
                  this.tx3 = var3;
                  this.ty3 = var5;
                  this.tx4 = var3;
                  this.ty4 = var5;
               }
               break;
            default:
               this.finish = true;
         }
      }

      this.lerpAll(this.curTime / this.maxTime);
      if (this.parent != null && this.parent.getWindRenderEffects() != null && Core.getInstance().getOptionDoWindSpriteEffects()) {
         this.add(this.parent.getWindRenderEffects());
      }

      return true;
   }

   private void update(float var1, float var2) {
      this.curTime = this.curTime + 1.0F * GameTime.getInstance().getMultiplier();
      if (this.curTime >= this.maxTime) {
         this.swapTargetToLast();
         if (this.isTree) {
            float var3 = 0.0F;
            float var4 = 0.04F;
            if (this.windType == 1) {
               var3 = 0.6F;
               var1 = var1 <= 0.08F ? 0.0F : (var1 - 0.08F) / 0.92F;
            } else if (this.windType == 2) {
               var3 = 0.3F;
               var4 = 0.06F;
               var1 = var1 <= 0.15F ? 0.0F : (var1 - 0.15F) / 0.85F;
            } else if (this.windType == 3) {
               var3 = 0.15F;
               var1 = var1 <= 0.3F ? 0.0F : (var1 - 0.3F) / 0.7F;
            }

            float var5 = ClimateManager.clamp01(1.0F - var1);
            this.curTime = 0.0F;
            this.maxTime = Rand.Next(20.0F + 100.0F * var5, 70.0F + 200.0F * var5) * T_MOD;
            if (var1 <= 0.01F || !Core.OptionDoWindSpriteEffects) {
               this.tx1 = 0.0;
               this.tx2 = 0.0;
               this.ty1 = 0.0;
               this.ty2 = 0.0;
               return;
            }

            float var6 = 0.6F * var1 + 0.4F * (var1 * var1);
            double var7;
            if (this.gust) {
               var7 = Rand.Next(-0.1F + 0.6F * var1, 1.0F) * var2;
               if (Rand.Next(0.0F, 1.0F) > Rand.Next(0.0F, 0.75F * var1)) {
                  this.gust = false;
               }
            } else {
               var7 = Rand.Next(-0.1F, 0.2F) * var2;
               this.gust = true;
            }

            var7 *= var3 * var6;
            this.tx1 = var7;
            this.tx2 = var7;
            double var9 = Rand.Next(-1.0F, 1.0F);
            var9 *= 0.01 + var4 * var6;
            this.ty1 = var9;
            var9 = Rand.Next(-1.0F, 1.0F);
            var9 *= 0.01 + var4 * var6;
            this.ty2 = var9;
         } else {
            float var11 = 0.0F;
            if (this.windType == 1) {
               var11 = 0.575F;
               var1 = var1 <= 0.02F ? 0.0F : (var1 - 0.02F) / 0.98F;
            } else if (this.windType == 2) {
               var11 = 0.375F;
               var1 = var1 <= 0.2F ? 0.0F : (var1 - 0.2F) / 0.8F;
            } else if (this.windType == 3) {
               var11 = 0.175F;
               var1 = var1 <= 0.6F ? 0.0F : (var1 - 0.6F) / 0.4F;
            }

            float var12 = ClimateManager.clamp01(1.0F - var1);
            this.curTime = 0.0F;
            this.maxTime = Rand.Next(20.0F + 50.0F * var12, 60.0F + 100.0F * var12) * T_MOD;
            if (var1 <= 0.05F || !Core.OptionDoWindSpriteEffects) {
               this.tx1 = 0.0;
               this.tx2 = 0.0;
               this.ty1 = 0.0;
               this.ty2 = 0.0;
               return;
            }

            float var13 = 0.55F * var1 + 0.45F * (var1 * var1);
            double var14;
            if (this.gust) {
               var14 = Rand.Next(-0.1F + 0.9F * var1, 1.0F) * var2;
               if (Rand.Next(0.0F, 1.0F) > Rand.Next(0.0F, 0.95F * var1)) {
                  this.gust = false;
               }
            } else {
               var14 = Rand.Next(-0.1F, 0.2F) * var2;
               this.gust = true;
            }

            var14 *= 0.025F + var11 * var13;
            this.tx1 = var14;
            this.tx2 = var14;
            if (var1 > 0.5F) {
               double var8 = Rand.Next(-1.0F, 1.0F);
               var8 *= 0.05F * var13;
               this.ty1 = var8;
               var8 = Rand.Next(-1.0F, 1.0F);
               var8 *= 0.05F * var13;
               this.ty2 = var8;
            } else {
               this.ty1 = 0.0;
               this.ty2 = 0.0;
            }
         }
      } else {
         this.lerpAll(this.curTime / this.maxTime);
      }
   }

   private void updateOLD(float var1, float var2) {
      this.curTime = this.curTime + 1.0F * GameTime.getInstance().getMultiplier();
      if (this.curTime >= this.maxTime) {
         this.curTime = 0.0F;
         float var3 = ClimateManager.clamp01(1.0F - var1);
         this.maxTime = Rand.Next(20.0F + 100.0F * var3, 70.0F + 200.0F * var3) * T_MOD;
         this.swapTargetToLast();
         float var9 = ClimateManager.clamp01(var1 * 1.25F);
         double var5 = Rand.Next(-0.65F, 0.65F);
         var5 += var1 * var2 * 0.7F;
         var5 *= 0.4F * var9;
         this.tx1 = var5;
         this.tx2 = var5;
         double var7 = Rand.Next(-1.0F, 1.0F);
         var7 *= 0.05F * var9;
         this.ty1 = var7;
         var7 = Rand.Next(-1.0F, 1.0F);
         var7 *= 0.05F * var9;
         this.ty2 = var7;
      } else {
         this.lerpAll(this.curTime / this.maxTime);
      }
   }

   private void lerpAll(float var1) {
      this.x1 = ClimateManager.clerp(var1, (float)this.lx1, (float)this.tx1);
      this.y1 = ClimateManager.clerp(var1, (float)this.ly1, (float)this.ty1);
      this.x2 = ClimateManager.clerp(var1, (float)this.lx2, (float)this.tx2);
      this.y2 = ClimateManager.clerp(var1, (float)this.ly2, (float)this.ty2);
      this.x3 = ClimateManager.clerp(var1, (float)this.lx3, (float)this.tx3);
      this.y3 = ClimateManager.clerp(var1, (float)this.ly3, (float)this.ty3);
      this.x4 = ClimateManager.clerp(var1, (float)this.lx4, (float)this.tx4);
      this.y4 = ClimateManager.clerp(var1, (float)this.ly4, (float)this.ty4);
   }

   private void swapTargetToLast() {
      this.lx1 = this.tx1;
      this.ly1 = this.ty1;
      this.lx2 = this.tx2;
      this.ly2 = this.ty2;
      this.lx3 = this.tx3;
      this.ly3 = this.ty3;
      this.lx4 = this.tx4;
      this.ly4 = this.ty4;
   }

   public void copyMainFromOther(ObjectRenderEffects var1) {
      this.x1 = var1.x1;
      this.y1 = var1.y1;
      this.x2 = var1.x2;
      this.y2 = var1.y2;
      this.x3 = var1.x3;
      this.y3 = var1.y3;
      this.x4 = var1.x4;
      this.y4 = var1.y4;
   }

   public void add(ObjectRenderEffects var1) {
      this.x1 = this.x1 + var1.x1;
      this.y1 = this.y1 + var1.y1;
      this.x2 = this.x2 + var1.x2;
      this.y2 = this.y2 + var1.y2;
      this.x3 = this.x3 + var1.x3;
      this.y3 = this.y3 + var1.y3;
      this.x4 = this.x4 + var1.x4;
      this.y4 = this.y4 + var1.y4;
   }

   public static void updateStatic() {
      if (!GameServer.bServer) {
         try {
            float var0 = (float)ClimateManager.getWindTickFinal();
            float var1 = ClimateManager.getInstance().getWindAngleIntensity();
            if (var1 < 0.0F) {
               var1 = -1.0F;
            } else {
               var1 = 1.0F;
            }

            for (int var2 = 0; var2 < 3; var2++) {
               for (int var3 = 0; var3 < 15; var3++) {
                  ObjectRenderEffects var4 = WIND_EFFECTS[var2][var3];
                  var4.update(var0, var1);
               }

               for (int var10 = 0; var10 < 15; var10++) {
                  ObjectRenderEffects var12 = WIND_EFFECTS_TREES[var2][var10];
                  var12.update(var0, var1);
               }
            }

            randomRustleTime = randomRustleTime + 1.0F * GameTime.getInstance().getMultiplier();
            if (randomRustleTime > randomRustleTotalTime && RANDOM_RUSTLE == null) {
               float var7 = 1.0F - var0;
               RANDOM_RUSTLE = getNew(null, RenderEffectType.Vegetation_Rustle, false, true);
               RANDOM_RUSTLE.isBig = false;
               if (var0 > 0.45F && Rand.Next(0.0F, 1.0F) < Rand.Next(0.0F, 0.8F * var0)) {
                  RANDOM_RUSTLE.isBig = true;
               }

               randomRustleType = Rand.Next(3);
               randomRustleTarget = Rand.Next(15);
               randomRustleTime = 0.0F;
               randomRustleTotalTime = Rand.Next(400.0F + 400.0F * var7, 1200.0F + 3200.0F * var7);
            }

            if (RANDOM_RUSTLE != null) {
               if (!RANDOM_RUSTLE.update()) {
                  release(RANDOM_RUSTLE);
                  RANDOM_RUSTLE = null;
               } else {
                  ObjectRenderEffects var8 = WIND_EFFECTS_TREES[randomRustleType][randomRustleTarget];
                  var8.add(RANDOM_RUSTLE);
               }
            }

            for (int var9 = DYNAMIC_EFFECTS.size() - 1; var9 >= 0; var9--) {
               ObjectRenderEffects var11 = DYNAMIC_EFFECTS.get(var9);
               if (!var11.update()) {
                  if (var11.parent != null) {
                     var11.parent.removeRenderEffect(var11);
                  }

                  DYNAMIC_EFFECTS.remove(var9);
                  release(var11);
               }
            }
         } catch (Exception var5) {
            var5.printStackTrace();
         }
      }
   }
}
