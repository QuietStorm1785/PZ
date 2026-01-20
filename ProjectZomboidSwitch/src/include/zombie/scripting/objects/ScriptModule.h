#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/runtime/RuntimeAnimationScript.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/MultiStageBuilding.h"
#include "zombie/iso/MultiStageBuilding/Stage.h"
#include "zombie/scripting/IScriptObjectStore.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/vehicles/VehicleEngineRPM.h"

namespace zombie {
namespace scripting {
namespace objects {


class ScriptModule : public BaseScriptObject {
public:
    std::string name;
    std::string value;
   public const std::unordered_map<std::string, Item> ItemMap = std::make_unique<std::unordered_map<>>();
   public const std::unordered_map<std::string, GameSoundScript> GameSoundMap = std::make_unique<std::unordered_map<>>();
   public const std::vector<GameSoundScript> GameSoundList = std::make_unique<std::vector<>>();
   public const std::unordered_map<std::string, AnimationsMesh> AnimationsMeshMap = std::make_unique<std::unordered_map<>>();
   public const std::unordered_map<std::string, MannequinScript> MannequinScriptMap = std::make_unique<std::unordered_map<>>();
   public const std::map<std::string, ModelScript> ModelScriptMap = new std::map<>(std::string.CASE_INSENSITIVE_ORDER);
   public const std::unordered_map<std::string, RuntimeAnimationScript> RuntimeAnimationScriptMap = std::make_unique<std::unordered_map<>>();
   public const std::unordered_map<std::string, SoundTimelineScript> SoundTimelineMap = std::make_unique<std::unordered_map<>>();
   public const std::unordered_map<std::string, VehicleScript> VehicleMap = std::make_unique<std::unordered_map<>>();
   public const std::unordered_map<std::string, VehicleTemplate> VehicleTemplateMap = std::make_unique<std::unordered_map<>>();
   public const std::unordered_map<std::string, VehicleEngineRPM> VehicleEngineRPMMap = std::make_unique<std::unordered_map<>>();
   public const std::vector<Recipe> RecipeMap = std::make_unique<std::vector<>>();
   public const std::unordered_map<std::string, Recipe> RecipeByName = std::make_unique<std::unordered_map<>>();
   public const std::unordered_map<std::string, Recipe> RecipesWithDotInName = std::make_unique<std::unordered_map<>>();
   public const std::vector<EvolvedRecipe> EvolvedRecipeMap = std::make_unique<std::vector<>>();
   public const std::vector<UniqueRecipe> UniqueRecipeMap = std::make_unique<std::vector<>>();
   public const std::unordered_map<std::string, Fixing> FixingMap = std::make_unique<std::unordered_map<>>();
   public const std::vector<std::string> Imports = std::make_unique<std::vector<>>();
    bool disabled = false;

    void Load(const std::string& var1, const std::string& var2) {
      this.name = var1;
      this.value = var2.trim();
      ScriptManager.instance.CurrentLoadingModule = this;
      this.ParseScriptPP(this.value);
      this.ParseScript(this.value);
      this.value = "";
   }

    std::string GetTokenType(const std::string& var1) {
    int var2 = var1.indexOf(123);
      if (var2 == -1) {
    return nullptr;
      } else {
    std::string var3 = var1.substr(0, var2).trim();
    int var4 = var3.indexOf(32);
    int var5 = var3.indexOf(9);
         if (var4 != -1 && var5 != -1) {
            return var3.substr(0, PZMath.min(var4, var5));
         } else if (var4 != -1) {
            return var3.substr(0, var4);
         } else {
            return var5 != -1 ? var3.substr(0, var5) : var3;
         }
      }
   }

    void CreateFromTokenPP(const std::string& var1) {
      var1 = var1.trim();
    std::string var2 = this.GetTokenType(var1);
      if (var2 != nullptr) {
         if ("item" == var2)) {
            std::string[] var3 = var1.split("[{}]");
    std::string var4 = var3[0];
            var4 = var4.replace("item", "");
            var4 = var4.trim();
    Item var5 = std::make_shared<Item>();
            this.ItemMap.put(var4, var5);
         } else if ("animationsMesh" == var2)) {
            std::string[] var10 = var1.split("[{}]");
    std::string var21 = var10[0];
            var21 = var21.replace("animationsMesh", "");
            var21 = var21.trim();
            if (this.AnimationsMeshMap.containsKey(var21)) {
    AnimationsMesh var47 = this.AnimationsMeshMap.get(var21);
               var47.reset();
            } else {
    AnimationsMesh var48 = std::make_shared<AnimationsMesh>();
               this.AnimationsMeshMap.put(var21, var48);
            }
         } else if ("mannequin" == var2)) {
            std::string[] var11 = var1.split("[{}]");
    std::string var24 = var11[0];
            var24 = var24.replace("mannequin", "");
            var24 = var24.trim();
            if (this.MannequinScriptMap.containsKey(var24)) {
    MannequinScript var49 = this.MannequinScriptMap.get(var24);
               var49.reset();
            } else {
    MannequinScript var50 = std::make_shared<MannequinScript>();
               this.MannequinScriptMap.put(var24, var50);
            }
         } else if ("model" == var2)) {
            std::string[] var12 = var1.split("[{}]");
    std::string var27 = var12[0];
            var27 = var27.replace("model", "");
            var27 = var27.trim();
            if (this.ModelScriptMap.containsKey(var27)) {
    ModelScript var51 = this.ModelScriptMap.get(var27);
               var51.reset();
            } else {
    ModelScript var52 = std::make_shared<ModelScript>();
               this.ModelScriptMap.put(var27, var52);
            }
         } else if ("sound" == var2)) {
            std::string[] var13 = var1.split("[{}]");
    std::string var30 = var13[0];
            var30 = var30.replace("sound", "");
            var30 = var30.trim();
            if (this.GameSoundMap.containsKey(var30)) {
    GameSoundScript var53 = this.GameSoundMap.get(var30);
               var53.reset();
            } else {
    GameSoundScript var54 = std::make_shared<GameSoundScript>();
               this.GameSoundMap.put(var30, var54);
               this.GameSoundList.push_back(var54);
            }
         } else if ("soundTimeline" == var2)) {
            std::string[] var14 = var1.split("[{}]");
    std::string var33 = var14[0];
            var33 = var33.replace("soundTimeline", "");
            var33 = var33.trim();
            if (this.SoundTimelineMap.containsKey(var33)) {
    SoundTimelineScript var55 = this.SoundTimelineMap.get(var33);
               var55.reset();
            } else {
    SoundTimelineScript var56 = std::make_shared<SoundTimelineScript>();
               this.SoundTimelineMap.put(var33, var56);
            }
         } else if ("vehicle" == var2)) {
            std::string[] var15 = var1.split("[{}]");
    std::string var36 = var15[0];
            var36 = var36.replace("vehicle", "");
            var36 = var36.trim();
    VehicleScript var57 = std::make_shared<VehicleScript>();
            this.VehicleMap.put(var36, var57);
         } else if ("template" == var2)) {
            std::string[] var16 = var1.split("[{}]");
    std::string var39 = var16[0];
            var39 = var39.replace("template", "");
            std::string[] var58 = var39.trim().split("\\s+");
            if (var58.length == 2) {
    std::string var6 = var58[0].trim();
    std::string var7 = var58[1].trim();
               if ("vehicle" == var6)) {
    VehicleTemplate var8 = std::make_shared<VehicleTemplate>(this, var7, var1);
                  var8.module = this;
                  this.VehicleTemplateMap.put(var7, var8);
               }
            }
         } else if ("animation" == var2)) {
            std::string[] var17 = var1.split("[{}]");
    std::string var41 = var17[0];
            var41 = var41.replace("animation", "");
            var41 = var41.trim();
            if (this.RuntimeAnimationScriptMap.containsKey(var41)) {
    RuntimeAnimationScript var59 = this.RuntimeAnimationScriptMap.get(var41);
               var59.reset();
            } else {
    RuntimeAnimationScript var60 = std::make_shared<RuntimeAnimationScript>();
               this.RuntimeAnimationScriptMap.put(var41, var60);
            }
         } else if ("vehicleEngineRPM" == var2)) {
            std::string[] var18 = var1.split("[{}]");
    std::string var44 = var18[0];
            var44 = var44.replace("vehicleEngineRPM", "");
            var44 = var44.trim();
            if (this.VehicleEngineRPMMap.containsKey(var44)) {
    VehicleEngineRPM var61 = this.VehicleEngineRPMMap.get(var44);
               var61.reset();
            } else {
    VehicleEngineRPM var62 = std::make_shared<VehicleEngineRPM>();
               this.VehicleEngineRPMMap.put(var44, var62);
            }
         }
      }
   }

    void CreateFromToken(const std::string& var1) {
      var1 = var1.trim();
    std::string var2 = this.GetTokenType(var1);
      if (var2 != nullptr) {
         if ("imports" == var2)) {
            std::string[] var3 = var1.split("[{}]");
            std::string[] var4 = var3[1].split(",");

            for (int var5 = 0; var5 < var4.length; var5++) {
               if (var4[var5].trim().length() > 0) {
    std::string var6 = var4[var5].trim();
                  if (var6 == this.getName())) {
                     DebugLog.log("ERROR: module \"" + this.getName() + "\" imports itself");
                  } else {
                     this.Imports.push_back(var6);
                  }
               }
            }
         } else if ("item" == var2)) {
            std::string[] var19 = var1.split("[{}]");
    std::string var33 = var19[0];
            var33 = var33.replace("item", "");
            var33 = var33.trim();
            std::string[] var75 = var19[1].split(",");
    Item var89 = this.ItemMap.get(var33);
            var89.module = this;

            try {
               var89.Load(var33, var75);
            } catch (Exception var17) {
               DebugLog.log(var17);
            }
         } else if ("recipe" == var2)) {
            std::string[] var20 = var1.split("[{}]");
    std::string var36 = var20[0];
            var36 = var36.replace("recipe", "");
            var36 = var36.trim();
            std::string[] var76 = var20[1].split(",");
    Recipe var90 = std::make_shared<Recipe>();
            this.RecipeMap.push_back(var90);
            if (!this.RecipeByName.containsKey(var36)) {
               this.RecipeByName.put(var36, var90);
            }

            if (var36.contains(".")) {
               this.RecipesWithDotInName.put(var36, var90);
            }

            var90.module = this;
            var90.Load(var36, var76);
         } else if ("uniquerecipe" == var2)) {
            std::string[] var21 = var1.split("[{}]");
    std::string var39 = var21[0];
            var39 = var39.replace("uniquerecipe", "");
            var39 = var39.trim();
            std::string[] var77 = var21[1].split(",");
    UniqueRecipe var91 = std::make_shared<UniqueRecipe>(var39);
            this.UniqueRecipeMap.push_back(var91);
            var91.module = this;
            var91.Load(var39, var77);
         } else if ("evolvedrecipe" == var2)) {
            std::string[] var22 = var1.split("[{}]");
    std::string var42 = var22[0];
            var42 = var42.replace("evolvedrecipe", "");
            var42 = var42.trim();
            std::string[] var78 = var22[1].split(",");
    bool var92 = false;

            for (EvolvedRecipe var8 : this.EvolvedRecipeMap) {
               if (var8.name == var42)) {
                  var8.Load(var42, var78);
                  var8.module = this;
                  var92 = true;
               }
            }

            if (!var92) {
    EvolvedRecipe var95 = std::make_shared<EvolvedRecipe>(var42);
               this.EvolvedRecipeMap.push_back(var95);
               var95.module = this;
               var95.Load(var42, var78);
            }
         } else if ("fixing" == var2)) {
            std::string[] var23 = var1.split("[{}]");
    std::string var45 = var23[0];
            var45 = var45.replace("fixing", "");
            var45 = var45.trim();
            std::string[] var79 = var23[1].split(",");
    Fixing var93 = std::make_shared<Fixing>();
            var93.module = this;
            this.FixingMap.put(var45, var93);
            var93.Load(var45, var79);
         } else if ("animationsMesh" == var2)) {
            std::string[] var24 = var1.split("[{}]");
    std::string var48 = var24[0];
            var48 = var48.replace("animationsMesh", "");
            var48 = var48.trim();
    AnimationsMesh var80 = this.AnimationsMeshMap.get(var48);
            var80.module = this;

            try {
               var80.Load(var48, var1);
            } catch (Throwable var16) {
               ExceptionLogger.logException(var16);
            }
         } else if ("mannequin" == var2)) {
            std::string[] var25 = var1.split("[{}]");
    std::string var51 = var25[0];
            var51 = var51.replace("mannequin", "");
            var51 = var51.trim();
    MannequinScript var81 = this.MannequinScriptMap.get(var51);
            var81.module = this;

            try {
               var81.Load(var51, var1);
            } catch (Throwable var15) {
               ExceptionLogger.logException(var15);
            }
         } else if ("multistagebuild" == var2)) {
            std::string[] var26 = var1.split("[{}]");
    std::string var54 = var26[0];
            var54 = var54.replace("multistagebuild", "");
            var54 = var54.trim();
            std::string[] var82 = var26[1].split(",");
    Stage var94 = std::make_shared<Stage>(std::make_shared<MultiStageBuilding>());
            var94.Load(var54, var82);
            MultiStageBuilding.addStage(var94);
         } else if ("model" == var2)) {
            std::string[] var27 = var1.split("[{}]");
    std::string var57 = var27[0];
            var57 = var57.replace("model", "");
            var57 = var57.trim();
    ModelScript var83 = this.ModelScriptMap.get(var57);
            var83.module = this;

            try {
               var83.Load(var57, var1);
            } catch (Throwable var14) {
               ExceptionLogger.logException(var14);
            }
         } else if ("sound" == var2)) {
            std::string[] var28 = var1.split("[{}]");
    std::string var60 = var28[0];
            var60 = var60.replace("sound", "");
            var60 = var60.trim();
    GameSoundScript var84 = this.GameSoundMap.get(var60);
            var84.module = this;

            try {
               var84.Load(var60, var1);
            } catch (Throwable var13) {
               ExceptionLogger.logException(var13);
            }
         } else if ("soundTimeline" == var2)) {
            std::string[] var29 = var1.split("[{}]");
    std::string var63 = var29[0];
            var63 = var63.replace("soundTimeline", "");
            var63 = var63.trim();
    SoundTimelineScript var85 = this.SoundTimelineMap.get(var63);
            var85.module = this;

            try {
               var85.Load(var63, var1);
            } catch (Throwable var12) {
               ExceptionLogger.logException(var12);
            }
         } else if ("vehicle" == var2)) {
            std::string[] var30 = var1.split("[{}]");
    std::string var66 = var30[0];
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
         } else if (!"template" == var2)) {
            if ("animation" == var2)) {
               std::string[] var31 = var1.split("[{}]");
    std::string var69 = var31[0];
               var69 = var69.replace("animation", "");
               var69 = var69.trim();
    RuntimeAnimationScript var87 = this.RuntimeAnimationScriptMap.get(var69);
               var87.module = this;

               try {
                  var87.Load(var69, var1);
               } catch (Throwable var10) {
                  ExceptionLogger.logException(var10);
               }
            } else if ("vehicleEngineRPM" == var2)) {
               std::string[] var32 = var1.split("[{}]");
    std::string var72 = var32[0];
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

    void ParseScript(const std::string& var1) {
    std::vector var2 = ScriptParser.parseTokens(var1);

      for (int var3 = 0; var3 < var2.size(); var3++) {
    std::string var4 = (std::string)var2.get(var3);
         this.CreateFromToken(var4);
      }
   }

    void ParseScriptPP(const std::string& var1) {
    std::vector var2 = ScriptParser.parseTokens(var1);

      for (int var3 = 0; var3 < var2.size(); var3++) {
    std::string var4 = (std::string)var2.get(var3);
         this.CreateFromTokenPP(var4);
      }
   }

    Item getItem(const std::string& var1) {
      if (var1.contains(".")) {
         return ScriptManager.instance.getItem(var1);
      } else if (!this.ItemMap.containsKey(var1)) {
         for (int var2 = 0; var2 < this.Imports.size(); var2++) {
    std::string var3 = this.Imports.get(var2);
    ScriptModule var4 = ScriptManager.instance.getModule(var3);
    Item var5 = var4.getItem(var1);
            if (var5 != nullptr) {
    return var5;
            }
         }

    return nullptr;
      } else {
         return this.ItemMap.get(var1);
      }
   }

    ModelScript getModelScript(const std::string& var1) {
      if (var1.contains(".")) {
         return ScriptManager.instance.getModelScript(var1);
      } else {
    ModelScript var2 = this.ModelScriptMap.get(var1);
         if (var2 == nullptr) {
            for (int var3 = 0; var3 < this.Imports.size(); var3++) {
    std::string var4 = this.Imports.get(var3);
    ScriptModule var5 = ScriptManager.instance.getModule(var4);
               var2 = var5.getModelScript(var1);
               if (var2 != nullptr) {
    return var2;
               }
            }

    return nullptr;
         } else {
    return var2;
         }
      }
   }

    Recipe getRecipe(const std::string& var1) {
      if (var1.contains(".") && !this.RecipesWithDotInName.containsKey(var1)) {
         return ScriptManager.instance.getRecipe(var1);
      } else {
    Recipe var2 = this.RecipeByName.get(var1);
         if (var2 != nullptr) {
    return var2;
         } else {
            for (int var3 = 0; var3 < this.Imports.size(); var3++) {
    ScriptModule var4 = ScriptManager.instance.getModule(this.Imports.get(var3));
               if (var4 != nullptr) {
                  var2 = var4.getRecipe(var1);
                  if (var2 != nullptr) {
    return var2;
                  }
               }
            }

    return nullptr;
         }
      }
   }

    VehicleScript getVehicle(const std::string& var1) {
      if (var1.contains(".")) {
         return ScriptManager.instance.getVehicle(var1);
      } else if (!this.VehicleMap.containsKey(var1)) {
         for (int var2 = 0; var2 < this.Imports.size(); var2++) {
    VehicleScript var3 = ScriptManager.instance.getModule(this.Imports.get(var2)).getVehicle(var1);
            if (var3 != nullptr) {
    return var3;
            }
         }

    return nullptr;
      } else {
         return this.VehicleMap.get(var1);
      }
   }

    VehicleTemplate getVehicleTemplate(const std::string& var1) {
      if (var1.contains(".")) {
         return ScriptManager.instance.getVehicleTemplate(var1);
      } else if (!this.VehicleTemplateMap.containsKey(var1)) {
         for (int var2 = 0; var2 < this.Imports.size(); var2++) {
    VehicleTemplate var3 = ScriptManager.instance.getModule(this.Imports.get(var2)).getVehicleTemplate(var1);
            if (var3 != nullptr) {
    return var3;
            }
         }

    return nullptr;
      } else {
         return this.VehicleTemplateMap.get(var1);
      }
   }

    VehicleEngineRPM getVehicleEngineRPM(const std::string& var1) {
      return var1.contains(".") ? ScriptManager.instance.getVehicleEngineRPM(var1) : this.VehicleEngineRPMMap.get(var1);
   }

    bool CheckExitPoints() {
    return false;
   }

    std::string getName() {
      return this.name;
   }

    void Reset() {
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

    Item getSpecificItem(const std::string& var1) {
      return this.ItemMap.get(var1);
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
