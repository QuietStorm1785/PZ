package zombie.scripting.objects;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.TreeMap;
import zombie.core.logger.ExceptionLogger;
import zombie.core.math.PZMath;
import zombie.core.skinnedmodel.runtime.RuntimeAnimationScript;
import zombie.debug.DebugLog;
import zombie.iso.MultiStageBuilding;
import zombie.iso.MultiStageBuilding.Stage;
import zombie.scripting.IScriptObjectStore;
import zombie.scripting.ScriptManager;
import zombie.scripting.ScriptParser;
import zombie.vehicles.VehicleEngineRPM;

public final class ScriptModule extends BaseScriptObject implements IScriptObjectStore {
   public String name;
   public String value;
   public final HashMap<String, Item> ItemMap = new HashMap<>();
   public final HashMap<String, GameSoundScript> GameSoundMap = new HashMap<>();
   public final ArrayList<GameSoundScript> GameSoundList = new ArrayList<>();
   public final HashMap<String, AnimationsMesh> AnimationsMeshMap = new HashMap<>();
   public final HashMap<String, MannequinScript> MannequinScriptMap = new HashMap<>();
   public final TreeMap<String, ModelScript> ModelScriptMap = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
   public final HashMap<String, RuntimeAnimationScript> RuntimeAnimationScriptMap = new HashMap<>();
   public final HashMap<String, SoundTimelineScript> SoundTimelineMap = new HashMap<>();
   public final HashMap<String, VehicleScript> VehicleMap = new HashMap<>();
   public final HashMap<String, VehicleTemplate> VehicleTemplateMap = new HashMap<>();
   public final HashMap<String, VehicleEngineRPM> VehicleEngineRPMMap = new HashMap<>();
   public final ArrayList<Recipe> RecipeMap = new ArrayList<>();
   public final HashMap<String, Recipe> RecipeByName = new HashMap<>();
   public final HashMap<String, Recipe> RecipesWithDotInName = new HashMap<>();
   public final ArrayList<EvolvedRecipe> EvolvedRecipeMap = new ArrayList<>();
   public final ArrayList<UniqueRecipe> UniqueRecipeMap = new ArrayList<>();
   public final HashMap<String, Fixing> FixingMap = new HashMap<>();
   public final ArrayList<String> Imports = new ArrayList<>();
   public boolean disabled = false;

   public void Load(String var1, String var2) {
      this.name = var1;
      this.value = var2.trim();
      ScriptManager.instance.CurrentLoadingModule = this;
      this.ParseScriptPP(this.value);
      this.ParseScript(this.value);
      this.value = "";
   }

   private String GetTokenType(String var1) {
      int var2 = var1.indexOf(123);
      if (var2 == -1) {
         return null;
      } else {
         String var3 = var1.substring(0, var2).trim();
         int var4 = var3.indexOf(32);
         int var5 = var3.indexOf(9);
         if (var4 != -1 && var5 != -1) {
            return var3.substring(0, PZMath.min(var4, var5));
         } else if (var4 != -1) {
            return var3.substring(0, var4);
         } else {
            return var5 != -1 ? var3.substring(0, var5) : var3;
         }
      }
   }

   private void CreateFromTokenPP(String var1) {
      var1 = var1.trim();
      String var2 = this.GetTokenType(var1);
      if (var2 != null) {
         if ("item".equals(var2)) {
            String[] var3 = var1.split("[{}]");
            String var4 = var3[0];
            var4 = var4.replace("item", "");
            var4 = var4.trim();
            Item var5 = new Item();
            this.ItemMap.put(var4, var5);
         } else if ("animationsMesh".equals(var2)) {
            String[] var10 = var1.split("[{}]");
            String var21 = var10[0];
            var21 = var21.replace("animationsMesh", "");
            var21 = var21.trim();
            if (this.AnimationsMeshMap.containsKey(var21)) {
               AnimationsMesh var47 = this.AnimationsMeshMap.get(var21);
               var47.reset();
            } else {
               AnimationsMesh var48 = new AnimationsMesh();
               this.AnimationsMeshMap.put(var21, var48);
            }
         } else if ("mannequin".equals(var2)) {
            String[] var11 = var1.split("[{}]");
            String var24 = var11[0];
            var24 = var24.replace("mannequin", "");
            var24 = var24.trim();
            if (this.MannequinScriptMap.containsKey(var24)) {
               MannequinScript var49 = this.MannequinScriptMap.get(var24);
               var49.reset();
            } else {
               MannequinScript var50 = new MannequinScript();
               this.MannequinScriptMap.put(var24, var50);
            }
         } else if ("model".equals(var2)) {
            String[] var12 = var1.split("[{}]");
            String var27 = var12[0];
            var27 = var27.replace("model", "");
            var27 = var27.trim();
            if (this.ModelScriptMap.containsKey(var27)) {
               ModelScript var51 = this.ModelScriptMap.get(var27);
               var51.reset();
            } else {
               ModelScript var52 = new ModelScript();
               this.ModelScriptMap.put(var27, var52);
            }
         } else if ("sound".equals(var2)) {
            String[] var13 = var1.split("[{}]");
            String var30 = var13[0];
            var30 = var30.replace("sound", "");
            var30 = var30.trim();
            if (this.GameSoundMap.containsKey(var30)) {
               GameSoundScript var53 = this.GameSoundMap.get(var30);
               var53.reset();
            } else {
               GameSoundScript var54 = new GameSoundScript();
               this.GameSoundMap.put(var30, var54);
               this.GameSoundList.add(var54);
            }
         } else if ("soundTimeline".equals(var2)) {
            String[] var14 = var1.split("[{}]");
            String var33 = var14[0];
            var33 = var33.replace("soundTimeline", "");
            var33 = var33.trim();
            if (this.SoundTimelineMap.containsKey(var33)) {
               SoundTimelineScript var55 = this.SoundTimelineMap.get(var33);
               var55.reset();
            } else {
               SoundTimelineScript var56 = new SoundTimelineScript();
               this.SoundTimelineMap.put(var33, var56);
            }
         } else if ("vehicle".equals(var2)) {
            String[] var15 = var1.split("[{}]");
            String var36 = var15[0];
            var36 = var36.replace("vehicle", "");
            var36 = var36.trim();
            VehicleScript var57 = new VehicleScript();
            this.VehicleMap.put(var36, var57);
         } else if ("template".equals(var2)) {
            String[] var16 = var1.split("[{}]");
            String var39 = var16[0];
            var39 = var39.replace("template", "");
            String[] var58 = var39.trim().split("\\s+");
            if (var58.length == 2) {
               String var6 = var58[0].trim();
               String var7 = var58[1].trim();
               if ("vehicle".equals(var6)) {
                  VehicleTemplate var8 = new VehicleTemplate(this, var7, var1);
                  var8.module = this;
                  this.VehicleTemplateMap.put(var7, var8);
               }
            }
         } else if ("animation".equals(var2)) {
            String[] var17 = var1.split("[{}]");
            String var41 = var17[0];
            var41 = var41.replace("animation", "");
            var41 = var41.trim();
            if (this.RuntimeAnimationScriptMap.containsKey(var41)) {
               RuntimeAnimationScript var59 = this.RuntimeAnimationScriptMap.get(var41);
               var59.reset();
            } else {
               RuntimeAnimationScript var60 = new RuntimeAnimationScript();
               this.RuntimeAnimationScriptMap.put(var41, var60);
            }
         } else if ("vehicleEngineRPM".equals(var2)) {
            String[] var18 = var1.split("[{}]");
            String var44 = var18[0];
            var44 = var44.replace("vehicleEngineRPM", "");
            var44 = var44.trim();
            if (this.VehicleEngineRPMMap.containsKey(var44)) {
               VehicleEngineRPM var61 = this.VehicleEngineRPMMap.get(var44);
               var61.reset();
            } else {
               VehicleEngineRPM var62 = new VehicleEngineRPM();
               this.VehicleEngineRPMMap.put(var44, var62);
            }
         }
      }
   }

   private void CreateFromToken(String var1) {
      var1 = var1.trim();
      String var2 = this.GetTokenType(var1);
      if (var2 != null) {
         if ("imports".equals(var2)) {
            String[] var3 = var1.split("[{}]");
            String[] var4 = var3[1].split(",");

            for (int var5 = 0; var5 < var4.length; var5++) {
               if (var4[var5].trim().length() > 0) {
                  String var6 = var4[var5].trim();
                  if (var6.equals(this.getName())) {
                     DebugLog.log("ERROR: module \"" + this.getName() + "\" imports itself");
                  } else {
                     this.Imports.add(var6);
                  }
               }
            }
         } else if ("item".equals(var2)) {
            String[] var19 = var1.split("[{}]");
            String var33 = var19[0];
            var33 = var33.replace("item", "");
            var33 = var33.trim();
            String[] var75 = var19[1].split(",");
            Item var89 = this.ItemMap.get(var33);
            var89.module = this;

            try {
               var89.Load(var33, var75);
            } catch (Exception var17) {
               DebugLog.log(var17);
            }
         } else if ("recipe".equals(var2)) {
            String[] var20 = var1.split("[{}]");
            String var36 = var20[0];
            var36 = var36.replace("recipe", "");
            var36 = var36.trim();
            String[] var76 = var20[1].split(",");
            Recipe var90 = new Recipe();
            this.RecipeMap.add(var90);
            if (!this.RecipeByName.containsKey(var36)) {
               this.RecipeByName.put(var36, var90);
            }

            if (var36.contains(".")) {
               this.RecipesWithDotInName.put(var36, var90);
            }

            var90.module = this;
            var90.Load(var36, var76);
         } else if ("uniquerecipe".equals(var2)) {
            String[] var21 = var1.split("[{}]");
            String var39 = var21[0];
            var39 = var39.replace("uniquerecipe", "");
            var39 = var39.trim();
            String[] var77 = var21[1].split(",");
            UniqueRecipe var91 = new UniqueRecipe(var39);
            this.UniqueRecipeMap.add(var91);
            var91.module = this;
            var91.Load(var39, var77);
         } else if ("evolvedrecipe".equals(var2)) {
            String[] var22 = var1.split("[{}]");
            String var42 = var22[0];
            var42 = var42.replace("evolvedrecipe", "");
            var42 = var42.trim();
            String[] var78 = var22[1].split(",");
            boolean var92 = false;

            for (EvolvedRecipe var8 : this.EvolvedRecipeMap) {
               if (var8.name.equals(var42)) {
                  var8.Load(var42, var78);
                  var8.module = this;
                  var92 = true;
               }
            }

            if (!var92) {
               EvolvedRecipe var95 = new EvolvedRecipe(var42);
               this.EvolvedRecipeMap.add(var95);
               var95.module = this;
               var95.Load(var42, var78);
            }
         } else if ("fixing".equals(var2)) {
            String[] var23 = var1.split("[{}]");
            String var45 = var23[0];
            var45 = var45.replace("fixing", "");
            var45 = var45.trim();
            String[] var79 = var23[1].split(",");
            Fixing var93 = new Fixing();
            var93.module = this;
            this.FixingMap.put(var45, var93);
            var93.Load(var45, var79);
         } else if ("animationsMesh".equals(var2)) {
            String[] var24 = var1.split("[{}]");
            String var48 = var24[0];
            var48 = var48.replace("animationsMesh", "");
            var48 = var48.trim();
            AnimationsMesh var80 = this.AnimationsMeshMap.get(var48);
            var80.module = this;

            try {
               var80.Load(var48, var1);
            } catch (Throwable var16) {
               ExceptionLogger.logException(var16);
            }
         } else if ("mannequin".equals(var2)) {
            String[] var25 = var1.split("[{}]");
            String var51 = var25[0];
            var51 = var51.replace("mannequin", "");
            var51 = var51.trim();
            MannequinScript var81 = this.MannequinScriptMap.get(var51);
            var81.module = this;

            try {
               var81.Load(var51, var1);
            } catch (Throwable var15) {
               ExceptionLogger.logException(var15);
            }
         } else if ("multistagebuild".equals(var2)) {
            String[] var26 = var1.split("[{}]");
            String var54 = var26[0];
            var54 = var54.replace("multistagebuild", "");
            var54 = var54.trim();
            String[] var82 = var26[1].split(",");
            Stage var94 = new Stage(new MultiStageBuilding());
            var94.Load(var54, var82);
            MultiStageBuilding.addStage(var94);
         } else if ("model".equals(var2)) {
            String[] var27 = var1.split("[{}]");
            String var57 = var27[0];
            var57 = var57.replace("model", "");
            var57 = var57.trim();
            ModelScript var83 = this.ModelScriptMap.get(var57);
            var83.module = this;

            try {
               var83.Load(var57, var1);
            } catch (Throwable var14) {
               ExceptionLogger.logException(var14);
            }
         } else if ("sound".equals(var2)) {
            String[] var28 = var1.split("[{}]");
            String var60 = var28[0];
            var60 = var60.replace("sound", "");
            var60 = var60.trim();
            GameSoundScript var84 = this.GameSoundMap.get(var60);
            var84.module = this;

            try {
               var84.Load(var60, var1);
            } catch (Throwable var13) {
               ExceptionLogger.logException(var13);
            }
         } else if ("soundTimeline".equals(var2)) {
            String[] var29 = var1.split("[{}]");
            String var63 = var29[0];
            var63 = var63.replace("soundTimeline", "");
            var63 = var63.trim();
            SoundTimelineScript var85 = this.SoundTimelineMap.get(var63);
            var85.module = this;

            try {
               var85.Load(var63, var1);
            } catch (Throwable var12) {
               ExceptionLogger.logException(var12);
            }
         } else if ("vehicle".equals(var2)) {
            String[] var30 = var1.split("[{}]");
            String var66 = var30[0];
            var66 = var66.replace("vehicle", "");
            var66 = var66.trim();
            VehicleScript var86 = this.VehicleMap.get(var66);
            var86.module = this;

            try {
               var86.Load(var66, var1);
               var86.Loaded();
            } catch (Exception var11) {
               ExceptionLogger.logException(var11);
            }
         } else if (!"template".equals(var2)) {
            if ("animation".equals(var2)) {
               String[] var31 = var1.split("[{}]");
               String var69 = var31[0];
               var69 = var69.replace("animation", "");
               var69 = var69.trim();
               RuntimeAnimationScript var87 = this.RuntimeAnimationScriptMap.get(var69);
               var87.module = this;

               try {
                  var87.Load(var69, var1);
               } catch (Throwable var10) {
                  ExceptionLogger.logException(var10);
               }
            } else if ("vehicleEngineRPM".equals(var2)) {
               String[] var32 = var1.split("[{}]");
               String var72 = var32[0];
               var72 = var72.replace("vehicleEngineRPM", "");
               var72 = var72.trim();
               VehicleEngineRPM var88 = this.VehicleEngineRPMMap.get(var72);
               var88.module = this;

               try {
                  var88.Load(var72, var1);
               } catch (Throwable var9) {
                  this.VehicleEngineRPMMap.remove(var72);
                  ExceptionLogger.logException(var9);
               }
            } else {
               DebugLog.Script.warn("unknown script object \"%s\"", new Object[]{var2});
            }
         }
      }
   }

   public void ParseScript(String var1) {
      ArrayList var2 = ScriptParser.parseTokens(var1);

      for (int var3 = 0; var3 < var2.size(); var3++) {
         String var4 = (String)var2.get(var3);
         this.CreateFromToken(var4);
      }
   }

   public void ParseScriptPP(String var1) {
      ArrayList var2 = ScriptParser.parseTokens(var1);

      for (int var3 = 0; var3 < var2.size(); var3++) {
         String var4 = (String)var2.get(var3);
         this.CreateFromTokenPP(var4);
      }
   }

   public Item getItem(String var1) {
      if (var1.contains(".")) {
         return ScriptManager.instance.getItem(var1);
      } else if (!this.ItemMap.containsKey(var1)) {
         for (int var2 = 0; var2 < this.Imports.size(); var2++) {
            String var3 = this.Imports.get(var2);
            ScriptModule var4 = ScriptManager.instance.getModule(var3);
            Item var5 = var4.getItem(var1);
            if (var5 != null) {
               return var5;
            }
         }

         return null;
      } else {
         return this.ItemMap.get(var1);
      }
   }

   public ModelScript getModelScript(String var1) {
      if (var1.contains(".")) {
         return ScriptManager.instance.getModelScript(var1);
      } else {
         ModelScript var2 = this.ModelScriptMap.get(var1);
         if (var2 == null) {
            for (int var3 = 0; var3 < this.Imports.size(); var3++) {
               String var4 = this.Imports.get(var3);
               ScriptModule var5 = ScriptManager.instance.getModule(var4);
               var2 = var5.getModelScript(var1);
               if (var2 != null) {
                  return var2;
               }
            }

            return null;
         } else {
            return var2;
         }
      }
   }

   public Recipe getRecipe(String var1) {
      if (var1.contains(".") && !this.RecipesWithDotInName.containsKey(var1)) {
         return ScriptManager.instance.getRecipe(var1);
      } else {
         Recipe var2 = this.RecipeByName.get(var1);
         if (var2 != null) {
            return var2;
         } else {
            for (int var3 = 0; var3 < this.Imports.size(); var3++) {
               ScriptModule var4 = ScriptManager.instance.getModule(this.Imports.get(var3));
               if (var4 != null) {
                  var2 = var4.getRecipe(var1);
                  if (var2 != null) {
                     return var2;
                  }
               }
            }

            return null;
         }
      }
   }

   public VehicleScript getVehicle(String var1) {
      if (var1.contains(".")) {
         return ScriptManager.instance.getVehicle(var1);
      } else if (!this.VehicleMap.containsKey(var1)) {
         for (int var2 = 0; var2 < this.Imports.size(); var2++) {
            VehicleScript var3 = ScriptManager.instance.getModule(this.Imports.get(var2)).getVehicle(var1);
            if (var3 != null) {
               return var3;
            }
         }

         return null;
      } else {
         return this.VehicleMap.get(var1);
      }
   }

   public VehicleTemplate getVehicleTemplate(String var1) {
      if (var1.contains(".")) {
         return ScriptManager.instance.getVehicleTemplate(var1);
      } else if (!this.VehicleTemplateMap.containsKey(var1)) {
         for (int var2 = 0; var2 < this.Imports.size(); var2++) {
            VehicleTemplate var3 = ScriptManager.instance.getModule(this.Imports.get(var2)).getVehicleTemplate(var1);
            if (var3 != null) {
               return var3;
            }
         }

         return null;
      } else {
         return this.VehicleTemplateMap.get(var1);
      }
   }

   public VehicleEngineRPM getVehicleEngineRPM(String var1) {
      return var1.contains(".") ? ScriptManager.instance.getVehicleEngineRPM(var1) : this.VehicleEngineRPMMap.get(var1);
   }

   public boolean CheckExitPoints() {
      return false;
   }

   public String getName() {
      return this.name;
   }

   public void Reset() {
      this.ItemMap.clear();
      this.GameSoundMap.clear();
      this.GameSoundList.clear();
      this.AnimationsMeshMap.clear();
      this.MannequinScriptMap.clear();
      this.ModelScriptMap.clear();
      this.RuntimeAnimationScriptMap.clear();
      this.SoundTimelineMap.clear();
      this.VehicleMap.clear();
      this.VehicleTemplateMap.clear();
      this.VehicleEngineRPMMap.clear();
      this.RecipeMap.clear();
      this.RecipeByName.clear();
      this.RecipesWithDotInName.clear();
      this.EvolvedRecipeMap.clear();
      this.UniqueRecipeMap.clear();
      this.FixingMap.clear();
      this.Imports.clear();
   }

   public Item getSpecificItem(String var1) {
      return this.ItemMap.get(var1);
   }
}
