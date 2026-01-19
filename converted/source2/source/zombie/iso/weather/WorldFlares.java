package zombie.iso.weather;

import java.util.ArrayList;
import zombie.characters.IsoPlayer;
import zombie.core.opengl.RenderSettings.PlayerRenderSettings;
import zombie.debug.LineDrawer;
import zombie.iso.IsoUtils;
import zombie.iso.weather.WorldFlares.Flare;

public class WorldFlares {
   public static final boolean ENABLED = true;
   public static boolean DEBUG_DRAW = false;
   public static int NEXT_ID = 0;
   private static ArrayList<Flare> flares = new ArrayList<>();

   public static void Clear() {
      flares.clear();
   }

   public static int getFlareCount() {
      return flares.size();
   }

   public static Flare getFlare(int var0) {
      return flares.get(var0);
   }

   public static Flare getFlareID(int var0) {
      for (int var1 = 0; var1 < flares.size(); var1++) {
         if (flares.get(var1).id == var0) {
            return flares.get(var1);
         }
      }

      return null;
   }

   public static void launchFlare(float var0, int var1, int var2, int var3, float var4, float var5, float var6, float var7, float var8, float var9, float var10) {
      if (flares.size() > 100) {
         flares.remove(0);
      }

      Flare var11 = new Flare();
      var11.id = NEXT_ID++;
      var11.x = var1;
      var11.y = var2;
      var11.range = var3;
      var11.windSpeed = var4;
      var11.color.setExterior(var5, var6, var7, 1.0F);
      var11.color.setInterior(var8, var9, var10, 1.0F);
      var11.hasLaunched = true;
      var11.maxLifeTime = var0;
      flares.add(var11);
   }

   public static void update() {
      for (int var0 = flares.size() - 1; var0 >= 0; var0--) {
         flares.get(var0).update();
         if (!flares.get(var0).hasLaunched) {
            flares.remove(var0);
         }
      }
   }

   public static void applyFlaresForPlayer(PlayerRenderSettings var0, int var1, IsoPlayer var2) {
      for (int var3 = flares.size() - 1; var3 >= 0; var3--) {
         if (flares.get(var3).hasLaunched) {
            flares.get(var3).applyFlare(var0, var1, var2);
         }
      }
   }

   public static void setDebugDraw(boolean var0) {
      DEBUG_DRAW = var0;
   }

   public static boolean getDebugDraw() {
      return DEBUG_DRAW;
   }

   public static void debugRender() {
      if (DEBUG_DRAW) {
         float var0 = 0.0F;

         for (int var1 = flares.size() - 1; var1 >= 0; var1--) {
            Flare var2 = flares.get(var1);
            float var3 = 0.5F;

            for (double var4 = 0.0; var4 < Math.PI * 2; var4 += Math.PI / 20) {
               DrawIsoLine(
                  var2.x + var2.range * (float)Math.cos(var4),
                  var2.y + var2.range * (float)Math.sin(var4),
                  var2.x + var2.range * (float)Math.cos(var4 + (Math.PI / 20)),
                  var2.y + var2.range * (float)Math.sin(var4 + (Math.PI / 20)),
                  var0,
                  1.0F,
                  1.0F,
                  1.0F,
                  0.25F,
                  1
               );
               DrawIsoLine(
                  var2.x + var3 * (float)Math.cos(var4),
                  var2.y + var3 * (float)Math.sin(var4),
                  var2.x + var3 * (float)Math.cos(var4 + (Math.PI / 20)),
                  var2.y + var3 * (float)Math.sin(var4 + (Math.PI / 20)),
                  var0,
                  1.0F,
                  1.0F,
                  1.0F,
                  0.25F,
                  1
               );
            }
         }
      }
   }

   private static void DrawIsoLine(float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, int var9) {
      float var10 = IsoUtils.XToScreenExact(var0, var1, var4, 0);
      float var11 = IsoUtils.YToScreenExact(var0, var1, var4, 0);
      float var12 = IsoUtils.XToScreenExact(var2, var3, var4, 0);
      float var13 = IsoUtils.YToScreenExact(var2, var3, var4, 0);
      LineDrawer.drawLine(var10, var11, var12, var13, var5, var6, var7, var8, var9);
   }
}
