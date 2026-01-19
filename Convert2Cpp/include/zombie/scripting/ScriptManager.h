#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URI.h"
#include "zombie/GameSounds.h"
#include "zombie/SoundManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/IndieFileLoader.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/skinnedmodel/runtime/RuntimeAnimationScript.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/inventory/RecipeManager.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/MultiStageBuilding.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/NetChecksum.h"
#include "zombie/network/NetChecksum/GroupOfFiles.h"
#include "zombie/scripting/ScriptManager/1.h"
#include "zombie/scripting/objects/AnimationsMesh.h"
#include "zombie/scripting/objects/EvolvedRecipe.h"
#include "zombie/scripting/objects/Fixing.h"
#include "zombie/scripting/objects/GameSoundScript.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/scripting/objects/MannequinScript.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/scripting/objects/Recipe.h"
#include "zombie/scripting/objects/ScriptModule.h"
#include "zombie/scripting/objects/SoundTimelineScript.h"
#include "zombie/scripting/objects/UniqueRecipe.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/scripting/objects/VehicleTemplate.h"
#include "zombie/util/StringUtils.h"
#include "zombie/vehicles/VehicleEngineRPM.h"
#include "zombie/world/WorldDictionary.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace scripting {


class ScriptManager {
public:
    static auto instance = std::make_shared<ScriptManager>();
    std::string currentFileName;
   public final ArrayList<String> scriptsWithVehicles = std::make_unique<ArrayList<>>();
   public final ArrayList<String> scriptsWithVehicleTemplates = std::make_unique<ArrayList<>>();
   public final HashMap<String, ScriptModule> ModuleMap = std::make_unique<HashMap<>>();
   public final ArrayList<ScriptModule> ModuleList = std::make_unique<ArrayList<>>();
   private final HashMap<String, Item> FullTypeToItemMap = std::make_unique<HashMap<>>();
   private final HashMap<String, SoundTimelineScript> SoundTimelineMap = std::make_unique<HashMap<>>();
    ScriptModule CurrentLoadingModule = null;
   private final HashMap<String, String> ModuleAliases = std::make_unique<HashMap<>>();
    auto buf = std::make_shared<StringBuilder>();
   private final HashMap<String, ScriptModule> CachedModules = std::make_unique<HashMap<>>();
   private final ArrayList<Recipe> recipesTempList = std::make_unique<ArrayList<>>();
   private final Stack<EvolvedRecipe> evolvedRecipesTempList = std::make_unique<Stack<>>();
   private final Stack<UniqueRecipe> uniqueRecipesTempList = std::make_unique<Stack<>>();
   private final ArrayList<Item> itemTempList = std::make_unique<ArrayList<>>();
   private final HashMap<String, ArrayList<Item>> tagToItemMap = std::make_unique<HashMap<>>();
   private final HashMap<String, ArrayList<Item>> typeToItemMap = std::make_unique<HashMap<>>();
   private final ArrayList<AnimationsMesh> animationsMeshTempList = std::make_unique<ArrayList<>>();
   private final ArrayList<MannequinScript> mannequinScriptTempList = std::make_unique<ArrayList<>>();
   private final ArrayList<ModelScript> modelScriptTempList = std::make_unique<ArrayList<>>();
   private final ArrayList<VehicleScript> vehicleScriptTempList = std::make_unique<ArrayList<>>();
   private final HashMap<String, String> clothingToItemMap = std::make_unique<HashMap<>>();
   private final ArrayList<String> visualDamagesList = std::make_unique<ArrayList<>>();
    static const std::string Base = "Base";
    static const std::string Base_Module = "Base.";
    std::string checksum = "";
   private HashMap<String, String> tempFileToModMap;
    static std::string currentLoadFileMod;
    static std::string currentLoadFileAbsPath;
    static const std::string VanillaID = "pz-vanilla";

    void ParseScript(const std::string& var1) {
      if (DebugLog.isEnabled(DebugType.Script)) {
         DebugLog.Script.debugln("Parsing...");
      }

    std::vector var2 = ScriptParser.parseTokens(var1);

      for (int var3 = 0; var3 < var2.size(); var3++) {
    std::string var4 = static_cast<String>(var2).get(var3);
         this.CreateFromToken(var4);
      }
   }

    void update() {
   }

    void LoadFile(const std::string& var1, bool var2) {
      if (DebugLog.isEnabled(DebugType.Script)) {
         DebugLog.Script.debugln(var1 + (var2 ? " bLoadJar" : ""));
      }

      if (!GameServer.bServer) {
         Thread.yield();
         Core.getInstance().DoFrameReady();
      }

      if (var1.contains(".tmx")) {
         IsoWorld.mapPath = var1.substring(0, var1.lastIndexOf("/"));
         IsoWorld.mapUseJar = var2;
         DebugLog.Script.debugln("  file is a .tmx (map) file. Set mapPath to " + IsoWorld.mapPath + (IsoWorld.mapUseJar ? " mapUseJar" : ""));
      } else if (!var1.endsWith(".txt")) {
         DebugLog.Script.warn(" file is not a .txt (script) file: " + var1);
      } else {
    InputStreamReader var3 = IndieFileLoader.getStreamReader(var1, !var2);
    auto var4 = std::make_shared<BufferedReader>(var3);
         this.buf.setLength(0);
    void* var5 = null;
    std::string var6 = "";

         label108: {
            try {
               while (true) {
                  if ((var5 = var4.readLine()) == nullptr) {
    break label108;
                  }

                  this.buf.append(static_cast<String>(var5));
                  this.buf.append('\n');
               }
            } catch (Exception var17) {
               DebugLog.Script.error("Exception thrown reading file " + var1 + "\n  " + var17);
            } finally {
               try {
                  var4.close();
                  var3.close();
               } catch (Exception var16) {
                  DebugLog.Script.error("Exception thrown closing file " + var1 + "\n  " + var16);
                  var16.printStackTrace(DebugLog.Script);
               }
            }

            return;
         }

         var6 = this.buf.toString();
         var6 = ScriptParser.stripComments(var6);
         this.currentFileName = var1;
         this.ParseScript(var6);
         this.currentFileName = nullptr;
      }
   }

    void CreateFromToken(const std::string& var1) {
      var1 = var1.trim();
      if (var1.indexOf("module") == 0) {
    int var2 = var1.indexOf("{");
    int var3 = var1.lastIndexOf("}");
         std::vector<String> var4 = var1.split("[{}]");
    std::string var5 = var4[0];
         var5 = var5.replace("module", "");
         var5 = var5.trim();
    std::string var6 = var1.substring(var2 + 1, var3);
    ScriptModule var7 = this.ModuleMap.get(var5);
         if (var7 == nullptr) {
            if (DebugLog.isEnabled(DebugType.Script)) {
               DebugLog.Script.debugln("Adding new module: " + var5);
            }

            var7 = std::make_unique<ScriptModule>();
            this.ModuleMap.put(var5, var7);
            this.ModuleList.add(var7);
         }

         var7.Load(var5, var6);
      }
   }

    void searchFolders(URI var1, File var2, ArrayList<String> var3) {
      if (var2.isDirectory()) {
         std::vector<String> var4 = var2.list();

         for (int var5 = 0; var5 < var4.length; var5++) {
            this.searchFolders(var1, new File(var2.getAbsolutePath() + File.separator + var4[var5]), var3);
         }
      } else if (var2.getAbsolutePath().toLowerCase().endsWith(".txt")) {
    std::string var6 = ZomboidFileSystem.instance.getRelativeFile(var1, var2.getAbsolutePath());
         var6 = var6.toLowerCase(Locale.ENGLISH);
         var3.add(var6);
      }
   }

    static std::string getItemName(const std::string& var0) {
    int var1 = var0.indexOf(46);
    return var1 = = -1 ? var0 : var0.substring(var1 + 1);
   }

    ScriptModule getModule(const std::string& var1) {
      return this.getModule(var1, true);
   }

    ScriptModule getModule(const std::string& var1, bool var2) {
      if (var1.trim() == "Base") || var1.startsWith("Base.")) {
         return this.ModuleMap.get("Base");
      } else if (this.CachedModules.containsKey(var1)) {
         return this.CachedModules.get(var1);
      } else {
    ScriptModule var3 = null;
         if (this.ModuleAliases.containsKey(var1)) {
            var1 = this.ModuleAliases.get(var1);
         }

         if (this.CachedModules.containsKey(var1)) {
            return this.CachedModules.get(var1);
         } else {
            if (this.ModuleMap.containsKey(var1)) {
               if (this.ModuleMap.get(var1).disabled) {
                  var3 = nullptr;
               } else {
                  var3 = this.ModuleMap.get(var1);
               }
            }

            if (var3 != nullptr) {
               this.CachedModules.put(var1, var3);
    return var3;
            } else {
    int var4 = var1.indexOf(".");
               if (var4 != -1) {
                  var3 = this.getModule(var1.substring(0, var4));
               }

               if (var3 != nullptr) {
                  this.CachedModules.put(var1, var3);
    return var3;
               } else {
                  return var2 ? this.ModuleMap.get("Base") : nullptr;
               }
            }
         }
      }
   }

    ScriptModule getModuleNoDisableCheck(const std::string& var1) {
      if (this.ModuleAliases.containsKey(var1)) {
         var1 = this.ModuleAliases.get(var1);
      }

      if (this.ModuleMap.containsKey(var1)) {
         return this.ModuleMap.get(var1);
      } else {
         return var1.indexOf(".") != -1 ? this.getModule(var1.split("\\.")[0]) : nullptr;
      }
   }

    Item getItem(const std::string& var1) {
      if (var1.contains(".") && this.FullTypeToItemMap.containsKey(var1)) {
         return this.FullTypeToItemMap.get(var1);
      } else {
    ScriptModule var2 = this.getModule(var1);
    return var2 = = null ? null : var2.getItem(getItemName(var1));
      }
   }

    Item FindItem(const std::string& var1) {
      return this.FindItem(var1, true);
   }

    Item FindItem(const std::string& var1, bool var2) {
      if (var1.contains(".") && this.FullTypeToItemMap.containsKey(var1)) {
         return this.FullTypeToItemMap.get(var1);
      } else {
    ScriptModule var3 = this.getModule(var1, var2);
         if (var3 == nullptr) {
    return null;
         } else {
    Item var4 = var3.getItem(getItemName(var1));
            if (var4 == nullptr) {
               for (int var5 = 0; var5 < this.ModuleList.size(); var5++) {
    ScriptModule var6 = this.ModuleList.get(var5);
                  if (!var6.disabled) {
                     var4 = var3.getItem(getItemName(var1));
                     if (var4 != nullptr) {
    return var4;
                     }
                  }
               }
            }

    return var4;
         }
      }
   }

    bool isDrainableItemType(const std::string& var1) {
    Item var2 = this.FindItem(var1);
      return var2 != nullptr ? var2.getType() == Type.Drainable : false;
   }

    Recipe getRecipe(const std::string& var1) {
    ScriptModule var2 = this.getModule(var1);
    return var2 = = null ? null : var2.getRecipe(getItemName(var1));
   }

    VehicleScript getVehicle(const std::string& var1) {
    ScriptModule var2 = this.getModule(var1);
    return var2 = = null ? null : var2.getVehicle(getItemName(var1));
   }

    VehicleTemplate getVehicleTemplate(const std::string& var1) {
    ScriptModule var2 = this.getModule(var1);
    return var2 = = null ? null : var2.getVehicleTemplate(getItemName(var1));
   }

    VehicleEngineRPM getVehicleEngineRPM(const std::string& var1) {
    ScriptModule var2 = this.getModule(var1);
    return var2 = = null ? null : var2.getVehicleEngineRPM(getItemName(var1));
   }

    void CheckExitPoints() {
      for (int var1 = 0; var1 < this.ModuleList.size(); var1++) {
    ScriptModule var2 = this.ModuleList.get(var1);
         if (!var2.disabled && var2.CheckExitPoints()) {
            return;
         }
      }
   }

   public ArrayList<Item> getAllItems() {
      if (this.itemTempList.isEmpty()) {
         for (int var1 = 0; var1 < this.ModuleList.size(); var1++) {
    ScriptModule var2 = this.ModuleList.get(var1);
            if (!var2.disabled) {
               for (Item var4 : var2.ItemMap.values()) {
                  this.itemTempList.add(var4);
               }
            }
         }
      }

      return this.itemTempList;
   }

   public ArrayList<Item> getItemsTag(String var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
         throw new IllegalArgumentException("invalid tag \"" + var1 + "\"");
      } else {
         var1 = var1.toLowerCase(Locale.ENGLISH);
    std::vector var2 = this.tagToItemMap.get(var1);
         if (var2 != nullptr) {
    return var2;
         } else {
            var2 = std::make_unique<ArrayList>();
    std::vector var3 = this.getAllItems();

            for (int var4 = 0; var4 < var3.size(); var4++) {
    Item var5 = static_cast<Item>(var3).get(var4);

               for (int var6 = 0; var6 < var5.Tags.size(); var6++) {
                  if ((static_cast<String>(var5).Tags.get(var6)).equalsIgnoreCase(var1)) {
                     var2.add(var5);
                     break;
                  }
               }
            }

            this.tagToItemMap.put(var1, var2);
    return var2;
         }
      }
   }

   public ArrayList<Item> getItemsByType(String var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
         throw new IllegalArgumentException("invalid type \"" + var1 + "\"");
      } else {
    std::vector var2 = this.typeToItemMap.get(var1);
         if (var2 != nullptr) {
    return var2;
         } else {
            var2 = std::make_unique<ArrayList>();

            for (int var3 = 0; var3 < this.ModuleList.size(); var3++) {
    ScriptModule var4 = this.ModuleList.get(var3);
               if (!var4.disabled) {
    Item var5 = this.FullTypeToItemMap.get(StringUtils.moduleDotType(var4.name, var1));
                  if (var5 != nullptr) {
                     var2.add(var5);
                  }
               }
            }

            this.tagToItemMap.put(var1, var2);
    return var2;
         }
      }
   }

   public List<Fixing> getAllFixing(List<Fixing> var1) {
      for (int var2 = 0; var2 < this.ModuleList.size(); var2++) {
    ScriptModule var3 = this.ModuleList.get(var2);
         if (!var3.disabled) {
            var1.addAll(var3.FixingMap.values());
         }
      }

    return var1;
   }

   public ArrayList<Recipe> getAllRecipes() {
      this.recipesTempList.clear();

      for (int var1 = 0; var1 < this.ModuleList.size(); var1++) {
    ScriptModule var2 = this.ModuleList.get(var1);
         if (!var2.disabled) {
            for (int var3 = 0; var3 < var2.RecipeMap.size(); var3++) {
    Recipe var4 = static_cast<Recipe>(var2).RecipeMap.get(var3);
               this.recipesTempList.add(var4);
            }
         }
      }

      return this.recipesTempList;
   }

   public Stack<EvolvedRecipe> getAllEvolvedRecipes() {
      this.evolvedRecipesTempList.clear();

      for (int var1 = 0; var1 < this.ModuleList.size(); var1++) {
    ScriptModule var2 = this.ModuleList.get(var1);
         if (!var2.disabled) {
            for (int var3 = 0; var3 < var2.EvolvedRecipeMap.size(); var3++) {
    EvolvedRecipe var4 = static_cast<EvolvedRecipe>(var2).EvolvedRecipeMap.get(var3);
               this.evolvedRecipesTempList.add(var4);
            }
         }
      }

      return this.evolvedRecipesTempList;
   }

   public Stack<UniqueRecipe> getAllUniqueRecipes() {
      this.uniqueRecipesTempList.clear();

      for (int var1 = 0; var1 < this.ModuleList.size(); var1++) {
    ScriptModule var2 = this.ModuleList.get(var1);
         if (!var2.disabled) {
    Iterator var3 = var2.UniqueRecipeMap.iterator();

            while (var3 != nullptr && var3.hasNext()) {
    UniqueRecipe var4 = static_cast<UniqueRecipe>(var3).next();
               this.uniqueRecipesTempList.add(var4);
            }
         }
      }

      return this.uniqueRecipesTempList;
   }

   public ArrayList<GameSoundScript> getAllGameSounds() {
    std::vector var1 = new ArrayList();

      for (int var2 = 0; var2 < this.ModuleList.size(); var2++) {
    ScriptModule var3 = this.ModuleList.get(var2);
         if (!var3.disabled) {
            var1.addAll(var3.GameSoundList);
         }
      }

    return var1;
   }

   public ArrayList<RuntimeAnimationScript> getAllRuntimeAnimationScripts() {
    std::vector var1 = new ArrayList();

      for (int var2 = 0; var2 < this.ModuleList.size(); var2++) {
    ScriptModule var3 = this.ModuleList.get(var2);
         if (!var3.disabled) {
            var1.addAll(var3.RuntimeAnimationScriptMap.values());
         }
      }

    return var1;
   }

    AnimationsMesh getAnimationsMesh(const std::string& var1) {
    ScriptModule var2 = this.getModule(var1);
      if (var2 == nullptr) {
    return null;
      } else {
         var1 = getItemName(var1);
         return static_cast<AnimationsMesh>(var2).AnimationsMeshMap.get(var1);
      }
   }

   public ArrayList<AnimationsMesh> getAllAnimationsMeshes() {
      this.animationsMeshTempList.clear();

      for (int var1 = 0; var1 < this.ModuleList.size(); var1++) {
    ScriptModule var2 = this.ModuleList.get(var1);
         if (!var2.disabled) {
            this.animationsMeshTempList.addAll(var2.AnimationsMeshMap.values());
         }
      }

      return this.animationsMeshTempList;
   }

    MannequinScript getMannequinScript(const std::string& var1) {
    ScriptModule var2 = this.getModule(var1);
      if (var2 == nullptr) {
    return null;
      } else {
         var1 = getItemName(var1);
         return static_cast<MannequinScript>(var2).MannequinScriptMap.get(var1);
      }
   }

   public ArrayList<MannequinScript> getAllMannequinScripts() {
      this.mannequinScriptTempList.clear();

      for (int var1 = 0; var1 < this.ModuleList.size(); var1++) {
    ScriptModule var2 = this.ModuleList.get(var1);
         if (!var2.disabled) {
            this.mannequinScriptTempList.addAll(var2.MannequinScriptMap.values());
         }
      }

      this.mannequinScriptTempList.sort((var0, var1x) -> String.CASE_INSENSITIVE_ORDER.compare(var0.getName(), var1x.getName()));
      return this.mannequinScriptTempList;
   }

    ModelScript getModelScript(const std::string& var1) {
    ScriptModule var2 = this.getModule(var1);
      if (var2 == nullptr) {
    return null;
      } else {
         var1 = getItemName(var1);
         return static_cast<ModelScript>(var2).ModelScriptMap.get(var1);
      }
   }

   public ArrayList<ModelScript> getAllModelScripts() {
      this.modelScriptTempList.clear();

      for (int var1 = 0; var1 < this.ModuleList.size(); var1++) {
    ScriptModule var2 = this.ModuleList.get(var1);
         if (!var2.disabled) {
            this.modelScriptTempList.addAll(var2.ModelScriptMap.values());
         }
      }

      return this.modelScriptTempList;
   }

   public ArrayList<VehicleScript> getAllVehicleScripts() {
      this.vehicleScriptTempList.clear();

      for (int var1 = 0; var1 < this.ModuleList.size(); var1++) {
    ScriptModule var2 = this.ModuleList.get(var1);
         if (!var2.disabled) {
            this.vehicleScriptTempList.addAll(var2.VehicleMap.values());
         }
      }

      return this.vehicleScriptTempList;
   }

    SoundTimelineScript getSoundTimeline(const std::string& var1) {
      if (this.SoundTimelineMap.isEmpty()) {
         for (int var2 = 0; var2 < this.ModuleList.size(); var2++) {
    ScriptModule var3 = this.ModuleList.get(var2);
            if (!var3.disabled) {
               this.SoundTimelineMap.putAll(var3.SoundTimelineMap);
            }
         }
      }

      return this.SoundTimelineMap.get(var1);
   }

    void Reset() {
      for (ScriptModule var2 : this.ModuleList) {
         var2.Reset();
      }

      this.ModuleMap.clear();
      this.ModuleList.clear();
      this.ModuleAliases.clear();
      this.CachedModules.clear();
      this.FullTypeToItemMap.clear();
      this.itemTempList.clear();
      this.tagToItemMap.clear();
      this.typeToItemMap.clear();
      this.clothingToItemMap.clear();
      this.scriptsWithVehicles.clear();
      this.scriptsWithVehicleTemplates.clear();
      this.SoundTimelineMap.clear();
   }

    std::string getChecksum() {
      return this.checksum;
   }

    static std::string getCurrentLoadFileMod() {
    return currentLoadFileMod;
   }

    static std::string getCurrentLoadFileAbsPath() {
    return currentLoadFileAbsPath;
   }

    void Load() {
      try {
         WorldDictionary.StartScriptLoading();
         this.tempFileToModMap = std::make_unique<HashMap<>>();
    std::vector var1 = new ArrayList();
         this.searchFolders(ZomboidFileSystem.instance.baseURI, ZomboidFileSystem.instance.getMediaFile("scripts"), var1);

    for (auto& var3 : var1)            this.tempFileToModMap.put(ZomboidFileSystem.instance.getAbsolutePath(var3), "pz-vanilla");
         }

    std::vector var15 = new ArrayList();
    std::vector var17 = ZomboidFileSystem.instance.getModIDs();

         for (int var4 = 0; var4 < var17.size(); var4++) {
    std::string var5 = ZomboidFileSystem.instance.getModDir(static_cast<String>(var17).get(var4));
            if (var5 != nullptr) {
    auto var6 = std::make_shared<File>(var5);
    URI var7 = var6.toURI();
    int var8 = var15.size();
    File var9 = ZomboidFileSystem.instance.getCanonicalFile(var6, "media");
    File var10 = ZomboidFileSystem.instance.getCanonicalFile(var9, "scripts");
               this.searchFolders(var7, var10, var15);
               if ((static_cast<String>(var17).get(var4)) == "pz-vanilla")) {
                  throw new RuntimeException("Warning mod id is named pz-vanilla!");
               }

               for (int var11 = var8; var11 < var15.size(); var11++) {
    std::string var12 = static_cast<String>(var15).get(var11);
                  this.tempFileToModMap.put(ZomboidFileSystem.instance.getAbsolutePath(var12), static_cast<String>(var17).get(var4));
               }
            }
         }

    auto var19 = std::make_shared<1>(this);
         Collections.sort(var1, var19);
         Collections.sort(var15, var19);
         var1.addAll(var15);
         if (GameClient.bClient || GameServer.bServer) {
            NetChecksum.checksummer.reset(true);
            GroupOfFiles.initChecksum();
         }

         MultiStageBuilding.stages.clear();
    std::unordered_set var21 = new HashSet();

    for (auto& var23 : var1)            if (!var21.contains(var23)) {
               var21.add(var23);
    std::string var24 = ZomboidFileSystem.instance.getAbsolutePath(var23);
               currentLoadFileAbsPath = var24;
               currentLoadFileMod = this.tempFileToModMap.get(var24);
               this.LoadFile(var23, false);
               if (GameClient.bClient || GameServer.bServer) {
                  NetChecksum.checksummer.addFile(var23, var24);
               }
            }
         }

         if (GameClient.bClient || GameServer.bServer) {
            this.checksum = NetChecksum.checksummer.checksumToString();
            if (GameServer.bServer) {
               DebugLog.General.println("scriptChecksum: " + this.checksum);
            }
         }
      } catch (Exception var13) {
         ExceptionLogger.logException(var13);
      }

      this.buf.setLength(0);

      for (int var14 = 0; var14 < this.ModuleList.size(); var14++) {
    ScriptModule var16 = this.ModuleList.get(var14);

         for (Item var20 : var16.ItemMap.values()) {
            this.FullTypeToItemMap.put(var20.getFullName(), var20);
         }
      }

      this.debugItems();
      this.resolveItemTypes();
      WorldDictionary.ScriptsLoaded();
      RecipeManager.Loaded();
      GameSounds.ScriptsLoaded();
      ModelScript.ScriptsLoaded();
      if (SoundManager.instance != nullptr) {
         SoundManager.instance.debugScriptSounds();
      }

      Translator.debugItemEvolvedRecipeNames();
      Translator.debugItemNames();
      Translator.debugMultiStageBuildNames();
      Translator.debugRecipeNames();
      this.createClothingItemMap();
      this.createZedDmgMap();
   }

    void debugItems() {
      for (Item var3 : instance.getAllItems()) {
         if (var3.getType() == Type.Drainable && var3.getReplaceOnUse() != nullptr) {
            DebugLog.Script.warn("%s ReplaceOnUse instead of ReplaceOnDeplete", std::make_shared<std::vector<Object>>(){var3.getFullName()});
         }

         if (var3.getType() == Type.Weapon && !var3.HitSound == var3.hitFloorSound)) {
    bool var4 = true;
         }

         if (!StringUtils.isNullOrEmpty(var3.worldStaticModel)) {
    ModelScript var6 = this.getModelScript(var3.worldStaticModel);
            if (var6 != nullptr && var6.getAttachmentById("world") != nullptr) {
    bool var5 = true;
            }
         }
      }
   }

   public ArrayList<Recipe> getAllRecipesFor(String var1) {
    std::vector var2 = this.getAllRecipes();
    std::vector var3 = new ArrayList();

      for (int var4 = 0; var4 < var2.size(); var4++) {
    std::string var5 = (static_cast<Recipe>(var2).get(var4)).Result.type;
         if (var5.contains(".")) {
            var5 = var5.substring(var5.indexOf(".") + 1);
         }

         if (var5 == var1)) {
            var3.add(static_cast<Recipe>(var2).get(var4));
         }
      }

    return var3;
   }

    std::string getItemTypeForClothingItem(const std::string& var1) {
      return this.clothingToItemMap.get(var1);
   }

    Item getItemForClothingItem(const std::string& var1) {
    std::string var2 = this.getItemTypeForClothingItem(var1);
    return var2 = = null ? null : this.FindItem(var2);
   }

    void createZedDmgMap() {
      this.visualDamagesList.clear();
    ScriptModule var1 = this.getModule("Base");

      for (Item var3 : var1.ItemMap.values()) {
         if (!StringUtils.isNullOrWhitespace(var3.getBodyLocation()) && "ZedDmg" == var3.getBodyLocation())) {
            this.visualDamagesList.add(var3.getName());
         }
      }
   }

   public ArrayList<String> getZedDmgMap() {
      return this.visualDamagesList;
   }

    void createClothingItemMap() {
      for (Item var2 : this.getAllItems()) {
         if (!StringUtils.isNullOrWhitespace(var2.getClothingItem())) {
            if (DebugLog.isEnabled(DebugType.Script)) {
               DebugLog.Script.debugln("ClothingItem \"%s\" <---> Item \"%s\"", var2.getClothingItem(), var2.getFullName());
            }

            this.clothingToItemMap.put(var2.getClothingItem(), var2.getFullName());
         }
      }
   }

    void resolveItemTypes() {
      for (Item var2 : this.getAllItems()) {
         var2.resolveItemTypes();
      }
   }

    std::string resolveItemType(ScriptModule var1, const std::string& var2) {
      if (StringUtils.isNullOrWhitespace(var2)) {
    return null;
      } else if (var2.contains(".")) {
    return var2;
      } else {
    Item var3 = var1.getItem(var2);
         if (var3 != nullptr) {
            return var3.getFullName();
         } else {
            for (int var4 = 0; var4 < this.ModuleList.size(); var4++) {
    ScriptModule var5 = this.ModuleList.get(var4);
               if (!var5.disabled) {
                  var3 = var5.getItem(var2);
                  if (var3 != nullptr) {
                     return var3.getFullName();
                  }
               }
            }

            return "???." + var2;
         }
      }
   }

    std::string resolveModelScript(ScriptModule var1, const std::string& var2) {
      if (StringUtils.isNullOrWhitespace(var2)) {
    return null;
      } else if (var2.contains(".")) {
    return var2;
      } else {
    ModelScript var3 = var1.getModelScript(var2);
         if (var3 != nullptr) {
            return var3.getFullType();
         } else {
            for (int var4 = 0; var4 < this.ModuleList.size(); var4++) {
    ScriptModule var5 = this.ModuleList.get(var4);
               if (var5 != var1 && !var5.disabled) {
                  var3 = var5.getModelScript(var2);
                  if (var3 != nullptr) {
                     return var3.getFullType();
                  }
               }
            }

            return "???." + var2;
         }
      }
   }

    Item getSpecificItem(const std::string& var1) {
      if (!var1.contains(".")) {
         DebugLog.log("ScriptManager.getSpecificItem requires a full type name, cannot find: " + var1);
         if (Core.bDebug) {
            throw new RuntimeException("ScriptManager.getSpecificItem requires a full type name, cannot find: " + var1);
         } else {
    return null;
         }
      } else if (this.FullTypeToItemMap.containsKey(var1)) {
         return this.FullTypeToItemMap.get(var1);
      } else {
    int var2 = var1.indexOf(".");
    std::string var3 = var1.substring(0, var2);
    std::string var4 = var1.substring(var2 + 1);
    ScriptModule var5 = this.getModule(var3, false);
    return var5 = = null ? null : var5.getSpecificItem(var4);
      }
   }
}
} // namespace scripting
} // namespace zombie
