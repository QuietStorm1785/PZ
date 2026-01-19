package zombie.modding;

import java.util.ArrayList;
import java.util.Objects;
import zombie.GameWindow;
import zombie.MapGroups;
import zombie.core.Core;
import zombie.core.SpriteRenderer;
import zombie.debug.DebugOptions;
import zombie.gameStates.ChooseGameInfo;
import zombie.ui.TextManager;
import zombie.ui.UIFont;
import zombie.util.StringUtils;

public final class ActiveMods {
   private static final ArrayList<ActiveMods> s_activeMods = new ArrayList<>();
   private static final ActiveMods s_loaded = new ActiveMods("loaded");
   private final String id;
   private final ArrayList<String> mods = new ArrayList<>();
   private final ArrayList<String> mapOrder = new ArrayList<>();

   private static int count() {
      return s_activeMods.size();
   }

   public static ActiveMods getByIndex(int var0) {
      return s_activeMods.get(var0);
   }

   public static ActiveMods getById(String var0) {
      int var1 = indexOf(var0);
      return var1 == -1 ? create(var0) : s_activeMods.get(var1);
   }

   public static int indexOf(String var0) {
      var0 = var0.trim();
      requireValidId(var0);

      for (int var1 = 0; var1 < s_activeMods.size(); var1++) {
         ActiveMods var2 = s_activeMods.get(var1);
         if (var2.id.equalsIgnoreCase(var0)) {
            return var1;
         }
      }

      return -1;
   }

   private static ActiveMods create(String var0) {
      requireValidId(var0);
      if (indexOf(var0) != -1) {
         throw new IllegalStateException("id \"" + var0 + "\" exists");
      } else {
         ActiveMods var1 = new ActiveMods(var0);
         s_activeMods.add(var1);
         return var1;
      }
   }

   private static void requireValidId(String var0) {
      if (StringUtils.isNullOrWhitespace(var0)) {
         throw new IllegalArgumentException("id is null or whitespace");
      }
   }

   public static void setLoadedMods(ActiveMods var0) {
      if (var0 != null) {
         s_loaded.copyFrom(var0);
      }
   }

   public static boolean requiresResetLua(ActiveMods var0) {
      Objects.requireNonNull(var0);
      return !s_loaded.mods.equals(var0.mods);
   }

   public static void renderUI() {
      if (DebugOptions.instance.ModRenderLoaded.getValue()) {
         if (!GameWindow.DrawReloadingLua) {
            UIFont var0 = UIFont.DebugConsole;
            int var1 = TextManager.instance.getFontHeight(var0);
            String var2 = "Active Mods:";
            int var3 = TextManager.instance.MeasureStringX(var0, var2);

            for (int var4 = 0; var4 < s_loaded.mods.size(); var4++) {
               String var5 = s_loaded.mods.get(var4);
               int var6 = TextManager.instance.MeasureStringX(var0, var5);
               var3 = Math.max(var3, var6);
            }

            byte var11 = 10;
            var3 += var11 * 2;
            int var12 = Core.width - 20 - var3;
            byte var13 = 20;
            int var7 = (1 + s_loaded.mods.size()) * var1 + var11 * 2;
            SpriteRenderer.instance.renderi(null, var12, var13, var3, var7, 0.0F, 0.5F, 0.75F, 1.0F, null);
            int var14;
            TextManager.instance.DrawString(var0, var12 + var11, var14 = var13 + var11, var2, 1.0, 1.0, 1.0, 1.0);

            for (int var8 = 0; var8 < s_loaded.mods.size(); var8++) {
               String var9 = s_loaded.mods.get(var8);
               TextManager.instance.DrawString(var0, var12 + var11, var14 += var1, var9, 1.0, 1.0, 1.0, 1.0);
            }
         }
      }
   }

   public static void Reset() {
      s_loaded.clear();
   }

   public ActiveMods(String var1) {
      requireValidId(var1);
      this.id = var1;
   }

   public void clear() {
      this.mods.clear();
      this.mapOrder.clear();
   }

   public ArrayList<String> getMods() {
      return this.mods;
   }

   public ArrayList<String> getMapOrder() {
      return this.mapOrder;
   }

   public void copyFrom(ActiveMods var1) {
      this.mods.clear();
      this.mapOrder.clear();
      this.mods.addAll(var1.mods);
      this.mapOrder.addAll(var1.mapOrder);
   }

   public void setModActive(String var1, boolean var2) {
      var1 = var1.trim();
      if (!StringUtils.isNullOrWhitespace(var1)) {
         if (var2) {
            if (!this.mods.contains(var1)) {
               this.mods.add(var1);
            }
         } else {
            this.mods.remove(var1);
         }
      }
   }

   public boolean isModActive(String var1) {
      var1 = var1.trim();
      return StringUtils.isNullOrWhitespace(var1) ? false : this.mods.contains(var1);
   }

   public void removeMod(String var1) {
      var1 = var1.trim();
      this.mods.remove(var1);
   }

   public void removeMapOrder(String var1) {
      this.mapOrder.remove(var1);
   }

   public void checkMissingMods() {
      if (!this.mods.isEmpty()) {
         for (int var1 = this.mods.size() - 1; var1 >= 0; var1--) {
            String var2 = this.mods.get(var1);
            if (ChooseGameInfo.getAvailableModDetails(var2) == null) {
               this.mods.remove(var1);
            }
         }
      }
   }

   public void checkMissingMaps() {
      if (!this.mapOrder.isEmpty()) {
         MapGroups var1 = new MapGroups();
         var1.createGroups(this, false);
         if (var1.checkMapConflicts()) {
            ArrayList var2 = var1.getAllMapsInOrder();

            for (int var3 = this.mapOrder.size() - 1; var3 >= 0; var3--) {
               String var4 = this.mapOrder.get(var3);
               if (!var2.contains(var4)) {
                  this.mapOrder.remove(var3);
               }
            }
         } else {
            this.mapOrder.clear();
         }
      }
   }
}
