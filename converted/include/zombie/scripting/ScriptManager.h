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
#include "zombie/scripting/objects/AnimationsMesh.h"
#include "zombie/scripting/objects/EvolvedRecipe.h"
#include "zombie/scripting/objects/Fixing.h"
#include "zombie/scripting/objects/GameSoundScript.h"
#include "zombie/scripting/objects/Item.h"
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ScriptManager {
public:
 static const ScriptManager instance = new ScriptManager();
 std::string currentFileName;
 public ArrayList<String> scriptsWithVehicles = std::make_unique<ArrayList<>>();
 public ArrayList<String> scriptsWithVehicleTemplates = std::make_unique<ArrayList<>>();
 public HashMap<String, ScriptModule> ModuleMap = std::make_unique<HashMap<>>();
 public ArrayList<ScriptModule> ModuleList = std::make_unique<ArrayList<>>();
 private HashMap<String, Item> FullTypeToItemMap = std::make_unique<HashMap<>>();
 private HashMap<String, SoundTimelineScript> SoundTimelineMap = std::make_unique<HashMap<>>();
 ScriptModule CurrentLoadingModule = nullptr;
 private HashMap<String, String> ModuleAliases = std::make_unique<HashMap<>>();
 const StringBuilder buf = new StringBuilder();
 private HashMap<String, ScriptModule> CachedModules = std::make_unique<HashMap<>>();
 private ArrayList<Recipe> recipesTempList = std::make_unique<ArrayList<>>();
 private Stack<EvolvedRecipe> evolvedRecipesTempList = std::make_unique<Stack<>>();
 private Stack<UniqueRecipe> uniqueRecipesTempList = std::make_unique<Stack<>>();
 private ArrayList<Item> itemTempList = std::make_unique<ArrayList<>>();
 private HashMap<String, ArrayList<Item>> tagToItemMap = std::make_unique<HashMap<>>();
 private HashMap<String, ArrayList<Item>> typeToItemMap = std::make_unique<HashMap<>>();
 private ArrayList<AnimationsMesh> animationsMeshTempList = std::make_unique<ArrayList<>>();
 private ArrayList<MannequinScript> mannequinScriptTempList = std::make_unique<ArrayList<>>();
 private ArrayList<ModelScript> modelScriptTempList = std::make_unique<ArrayList<>>();
 private ArrayList<VehicleScript> vehicleScriptTempList = std::make_unique<ArrayList<>>();
 private HashMap<String, String> clothingToItemMap = std::make_unique<HashMap<>>();
 private ArrayList<String> visualDamagesList = std::make_unique<ArrayList<>>();
 static const std::string Base = "Base";
 static const std::string Base_Module = "Base.";
 std::string checksum = "";
 private HashMap<String, String> tempFileToModMap;
 static std::string currentLoadFileMod;
 static std::string currentLoadFileAbsPath;
 static const std::string VanillaID = "pz-vanilla";

 void ParseScript(const std::string& totalFile) {
 if (DebugLog.isEnabled(DebugType.Script) {
 DebugLog.Script.debugln("Parsing...");
 }

 std::vector arrayList = ScriptParser.parseTokens(totalFile);

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 std::string string = (String)arrayList.get(int0);
 this->CreateFromToken(string);
 }
 }

 void update() {
 }

 void LoadFile(const std::string& filename, bool bLoadJar) {
 if (DebugLog.isEnabled(DebugType.Script) {
 DebugLog.Script.debugln(filename + (bLoadJar ? " bLoadJar" : ""));
 }

 if (!GameServer.bServer) {
 Thread.yield();
 Core.getInstance().DoFrameReady();
 }

 if (filename.contains(".tmx")) {
 IsoWorld.mapPath = filename.substring(0, filename.lastIndexOf("/"));
 IsoWorld.mapUseJar = bLoadJar;
 DebugLog.Script.debugln(" file is a .tmx (map) file. Set mapPath to " + IsoWorld.mapPath + (IsoWorld.mapUseJar ? " mapUseJar" : ""));
 } else if (!filename.endsWith(".txt")) {
 DebugLog.Script.warn(" file is not a .txt (script) file: " + filename);
 } else {
 InputStreamReader inputStreamReader = IndieFileLoader.getStreamReader(filename, !bLoadJar);
 BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
 this->buf.setLength(0);
 void* object = nullptr;
 std::string string = "";

 label108: {
 try {
 while (true) {
 if ((object = bufferedReader.readLine()) == nullptr) {
 break label108;
 }

 this->buf.append((String)object);
 this->buf.append('\n');
 }
 } catch (Exception exception0) {
 DebugLog.Script.error("Exception thrown reading file " + filename + "\n " + exception0);
 } finally {
 try {
 bufferedReader.close();
 inputStreamReader.close();
 } catch (Exception exception1) {
 DebugLog.Script.error("Exception thrown closing file " + filename + "\n " + exception1);
 exception1.printStackTrace(DebugLog.Script);
 }
 }

 return;
 }

 string = this->buf.toString();
 string = ScriptParser.stripComments(string);
 this->currentFileName = filename;
 this->ParseScript(string);
 this->currentFileName = nullptr;
 }
 }

 void CreateFromToken(const std::string& string0) {
 string0 = string0.trim();
 if (string0.indexOf("module") == 0) {
 int int0 = string0.indexOf("{");
 int int1 = string0.lastIndexOf("}");
 String[] strings = string0.split("[{}]");
 std::string string1 = strings[0];
 string1 = string1.replace("module", "");
 string1 = string1.trim();
 std::string string2 = string0.substring(int0 + 1, int1);
 ScriptModule scriptModule = this->ModuleMap.get(string1);
 if (scriptModule == nullptr) {
 if (DebugLog.isEnabled(DebugType.Script) {
 DebugLog.Script.debugln("Adding new module: " + string1);
 }

 scriptModule = std::make_unique<ScriptModule>();
 this->ModuleMap.put(string1, scriptModule);
 this->ModuleList.add(scriptModule);
 }

 scriptModule.Load(string1, string2);
 }
 }

 void searchFolders(URI base, File fo, ArrayList<String> loadList) {
 if (fo.isDirectory()) {
 String[] strings = fo.list();

 for (int int0 = 0; int0 < strings.length; int0++) {
 this->searchFolders(base, new File(fo.getAbsolutePath() + File.separator + strings[int0]), loadList);
 }
 } else if (fo.getAbsolutePath().toLowerCase().endsWith(".txt")) {
 std::string string = ZomboidFileSystem.instance.getRelativeFile(base, fo.getAbsolutePath());
 string = string.toLowerCase(Locale.ENGLISH);
 loadList.add(string);
 }
 }

 static std::string getItemName(const std::string& name) {
 int int0 = name.indexOf(46);
 return int0 = = -1 ? name : name.substring(int0 + 1);
 }

 ScriptModule getModule(const std::string& name) {
 return this->getModule(name, true);
 }

 ScriptModule getModule(const std::string& name, bool defaultToBase) {
 if (name.trim() == "Base") || name.startsWith("Base.")) {
 return this->ModuleMap.get("Base");
 } else if (this->CachedModules.containsKey(name) {
 return this->CachedModules.get(name);
 } else {
 ScriptModule scriptModule = nullptr;
 if (this->ModuleAliases.containsKey(name) {
 name = this->ModuleAliases.get(name);
 }

 if (this->CachedModules.containsKey(name) {
 return this->CachedModules.get(name);
 } else {
 if (this->ModuleMap.containsKey(name) {
 if (this->ModuleMap.get(name).disabled) {
 scriptModule = nullptr;
 } else {
 scriptModule = this->ModuleMap.get(name);
 }
 }

 if (scriptModule != nullptr) {
 this->CachedModules.put(name, scriptModule);
 return scriptModule;
 } else {
 int int0 = name.indexOf(".");
 if (int0 != -1) {
 scriptModule = this->getModule(name.substring(0, int0);
 }

 if (scriptModule != nullptr) {
 this->CachedModules.put(name, scriptModule);
 return scriptModule;
 } else {
 return defaultToBase ? this->ModuleMap.get("Base") : nullptr;
 }
 }
 }
 }
 }

 ScriptModule getModuleNoDisableCheck(const std::string& name) {
 if (this->ModuleAliases.containsKey(name) {
 name = this->ModuleAliases.get(name);
 }

 if (this->ModuleMap.containsKey(name) {
 return this->ModuleMap.get(name);
 } else {
 return name.indexOf(".") != -1 ? this->getModule(name.split("\\.")[0]) : nullptr;
 }
 }

 Item getItem(const std::string& name) {
 if (name.contains(".") && this->FullTypeToItemMap.containsKey(name) {
 return this->FullTypeToItemMap.get(name);
 } else {
 ScriptModule scriptModule = this->getModule(name);
 return scriptModule = = nullptr ? nullptr : scriptModule.getItem(getItemName(name);
 }
 }

 Item FindItem(const std::string& name) {
 return this->FindItem(name, true);
 }

 Item FindItem(const std::string& name, bool moduleDefaultsToBase) {
 if (name.contains(".") && this->FullTypeToItemMap.containsKey(name) {
 return this->FullTypeToItemMap.get(name);
 } else {
 ScriptModule scriptModule0 = this->getModule(name, moduleDefaultsToBase);
 if (scriptModule0 == nullptr) {
 return nullptr;
 } else {
 Item item = scriptModule0.getItem(getItemName(name);
 if (item == nullptr) {
 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule1 = this->ModuleList.get(int0);
 if (!scriptModule1.disabled) {
 item = scriptModule0.getItem(getItemName(name);
 if (item != nullptr) {
 return item;
 }
 }
 }
 }

 return item;
 }
 }
 }

 bool isDrainableItemType(const std::string& itemType) {
 Item item = this->FindItem(itemType);
 return item != nullptr ? item.getType() == Item.Type.Drainable : false;
 }

 Recipe getRecipe(const std::string& name) {
 ScriptModule scriptModule = this->getModule(name);
 return scriptModule = = nullptr ? nullptr : scriptModule.getRecipe(getItemName(name);
 }

 VehicleScript getVehicle(const std::string& name) {
 ScriptModule scriptModule = this->getModule(name);
 return scriptModule = = nullptr ? nullptr : scriptModule.getVehicle(getItemName(name);
 }

 VehicleTemplate getVehicleTemplate(const std::string& name) {
 ScriptModule scriptModule = this->getModule(name);
 return scriptModule = = nullptr ? nullptr : scriptModule.getVehicleTemplate(getItemName(name);
 }

 VehicleEngineRPM getVehicleEngineRPM(const std::string& name) {
 ScriptModule scriptModule = this->getModule(name);
 return scriptModule = = nullptr ? nullptr : scriptModule.getVehicleEngineRPM(getItemName(name);
 }

 void CheckExitPoints() {
 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled && scriptModule.CheckExitPoints()) {
 return;
 }
 }
 }

 public ArrayList<Item> getAllItems() {
 if (this->itemTempList.empty()) {
 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 for (Item item : scriptModule.ItemMap.values()) {
 this->itemTempList.add(item);
 }
 }
 }
 }

 return this->itemTempList;
 }

 public ArrayList<Item> getItemsTag(String tag) {
 if (StringUtils.isNullOrWhitespace(tag) {
 throw IllegalArgumentException("invalid tag \"" + tag + "\"");
 } else {
 tag = tag.toLowerCase(Locale.ENGLISH);
 std::vector arrayList0 = this->tagToItemMap.get(tag);
 if (arrayList0 != nullptr) {
 return arrayList0;
 } else {
 arrayList0 = std::make_unique<ArrayList>();
 std::vector arrayList1 = this->getAllItems();

 for (int int0 = 0; int0 < arrayList1.size(); int0++) {
 Item item = (Item)arrayList1.get(int0);

 for (int int1 = 0; int1 < item.Tags.size(); int1++) {
 if (item.Tags.get(int1).equalsIgnoreCase(tag) {
 arrayList0.add(item);
 break;
 }
 }
 }

 this->tagToItemMap.put(tag, arrayList0);
 return arrayList0;
 }
 }
 }

 public ArrayList<Item> getItemsByType(String type) {
 if (StringUtils.isNullOrWhitespace(type) {
 throw IllegalArgumentException("invalid type \"" + type + "\"");
 } else {
 std::vector arrayList = this->typeToItemMap.get(type);
 if (arrayList != nullptr) {
 return arrayList;
 } else {
 arrayList = std::make_unique<ArrayList>();

 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 Item item = this->FullTypeToItemMap.get(StringUtils.moduleDotType(scriptModule.name, type);
 if (item != nullptr) {
 arrayList.add(item);
 }
 }
 }

 this->tagToItemMap.put(type, arrayList);
 return arrayList;
 }
 }
 }

 public List<Fixing> getAllFixing(List<Fixing> result) {
 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 result.addAll(scriptModule.FixingMap.values());
 }
 }

 return result;
 }

 public ArrayList<Recipe> getAllRecipes() {
 this->recipesTempList.clear();

 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 for (int int1 = 0; int1 < scriptModule.RecipeMap.size(); int1++) {
 Recipe recipe = scriptModule.RecipeMap.get(int1);
 this->recipesTempList.add(recipe);
 }
 }
 }

 return this->recipesTempList;
 }

 public Stack<EvolvedRecipe> getAllEvolvedRecipes() {
 this->evolvedRecipesTempList.clear();

 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 for (int int1 = 0; int1 < scriptModule.EvolvedRecipeMap.size(); int1++) {
 EvolvedRecipe evolvedRecipe = scriptModule.EvolvedRecipeMap.get(int1);
 this->evolvedRecipesTempList.add(evolvedRecipe);
 }
 }
 }

 return this->evolvedRecipesTempList;
 }

 public Stack<UniqueRecipe> getAllUniqueRecipes() {
 this->uniqueRecipesTempList.clear();

 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 Iterator iterator = scriptModule.UniqueRecipeMap.iterator();

 while (iterator != nullptr && iterator.hasNext()) {
 UniqueRecipe uniqueRecipe = (UniqueRecipe)iterator.next();
 this->uniqueRecipesTempList.add(uniqueRecipe);
 }
 }
 }

 return this->uniqueRecipesTempList;
 }

 public ArrayList<GameSoundScript> getAllGameSounds() {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 arrayList.addAll(scriptModule.GameSoundList);
 }
 }

 return arrayList;
 }

 public ArrayList<RuntimeAnimationScript> getAllRuntimeAnimationScripts() {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 arrayList.addAll(scriptModule.RuntimeAnimationScriptMap.values());
 }
 }

 return arrayList;
 }

 AnimationsMesh getAnimationsMesh(const std::string& name) {
 ScriptModule scriptModule = this->getModule(name);
 if (scriptModule == nullptr) {
 return nullptr;
 } else {
 name = getItemName(name);
 return scriptModule.AnimationsMeshMap.get(name);
 }
 }

 public ArrayList<AnimationsMesh> getAllAnimationsMeshes() {
 this->animationsMeshTempList.clear();

 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 this->animationsMeshTempList.addAll(scriptModule.AnimationsMeshMap.values());
 }
 }

 return this->animationsMeshTempList;
 }

 MannequinScript getMannequinScript(const std::string& name) {
 ScriptModule scriptModule = this->getModule(name);
 if (scriptModule == nullptr) {
 return nullptr;
 } else {
 name = getItemName(name);
 return scriptModule.MannequinScriptMap.get(name);
 }
 }

 public ArrayList<MannequinScript> getAllMannequinScripts() {
 this->mannequinScriptTempList.clear();

 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 this->mannequinScriptTempList.addAll(scriptModule.MannequinScriptMap.values());
 }
 }

 this->mannequinScriptTempList
 .sort((mannequinScript1, mannequinScript0) -> String.CASE_INSENSITIVE_ORDER.compare(mannequinScript1.getName(), mannequinScript0.getName()));
 return this->mannequinScriptTempList;
 }

 ModelScript getModelScript(const std::string& name) {
 ScriptModule scriptModule = this->getModule(name);
 if (scriptModule == nullptr) {
 return nullptr;
 } else {
 name = getItemName(name);
 return scriptModule.ModelScriptMap.get(name);
 }
 }

 public ArrayList<ModelScript> getAllModelScripts() {
 this->modelScriptTempList.clear();

 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 this->modelScriptTempList.addAll(scriptModule.ModelScriptMap.values());
 }
 }

 return this->modelScriptTempList;
 }

 public ArrayList<VehicleScript> getAllVehicleScripts() {
 this->vehicleScriptTempList.clear();

 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 this->vehicleScriptTempList.addAll(scriptModule.VehicleMap.values());
 }
 }

 return this->vehicleScriptTempList;
 }

 SoundTimelineScript getSoundTimeline(const std::string& eventName) {
 if (this->SoundTimelineMap.empty()) {
 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 this->SoundTimelineMap.putAll(scriptModule.SoundTimelineMap);
 }
 }
 }

 return this->SoundTimelineMap.get(eventName);
 }

 void Reset() {
 for (ScriptModule scriptModule : this->ModuleList) {
 scriptModule.Reset();
 }

 this->ModuleMap.clear();
 this->ModuleList.clear();
 this->ModuleAliases.clear();
 this->CachedModules.clear();
 this->FullTypeToItemMap.clear();
 this->itemTempList.clear();
 this->tagToItemMap.clear();
 this->typeToItemMap.clear();
 this->clothingToItemMap.clear();
 this->scriptsWithVehicles.clear();
 this->scriptsWithVehicleTemplates.clear();
 this->SoundTimelineMap.clear();
 }

 std::string getChecksum() {
 return this->checksum;
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
 this->tempFileToModMap = std::make_unique<HashMap<>>();
 std::vector arrayList0 = new ArrayList();
 this->searchFolders(ZomboidFileSystem.instance.baseURI, ZomboidFileSystem.instance.getMediaFile("scripts"), arrayList0);

 for (auto& string0 : arrayList0) this->tempFileToModMap.put(ZomboidFileSystem.instance.getAbsolutePath(string0), "pz-vanilla");
 }

 std::vector arrayList1 = new ArrayList();
 std::vector arrayList2 = ZomboidFileSystem.instance.getModIDs();

 for (int int0 = 0; int0 < arrayList2.size(); int0++) {
 std::string string1 = ZomboidFileSystem.instance.getModDir((String)arrayList2.get(int0);
 if (string1 != nullptr) {
 File file0 = new File(string1);
 URI uri = file0.toURI();
 int int1 = arrayList1.size();
 File file1 = ZomboidFileSystem.instance.getCanonicalFile(file0, "media");
 File file2 = ZomboidFileSystem.instance.getCanonicalFile(file1, "scripts");
 this->searchFolders(uri, file2, arrayList1);
 if (((String)arrayList2.get(int0) == "pz-vanilla")) {
 throw RuntimeException("Warning mod id is named pz-vanilla!");
 }

 for (int int2 = int1; int2 < arrayList1.size(); int2++) {
 std::string string2 = (String)arrayList1.get(int2);
 this->tempFileToModMap.put(ZomboidFileSystem.instance.getAbsolutePath(string2), (String)arrayList2.get(int0);
 }
 }
 }

 Comparator comparator = std::make_unique<Comparator<String>>() {
 int compare(const std::string& string1, const std::string& string3) {
 std::string string0 = new File(string1).getName();
 std::string string2 = new File(string3).getName();
 if (string0.startsWith("template_") && !string2.startsWith("template_")) {
 return -1;
 } else {
 return !string0.startsWith("template_") && string2.startsWith("template_") ? 1 : string1.compareTo(string3);
 }
 }
 };
 Collections.sort(arrayList0, comparator);
 Collections.sort(arrayList1, comparator);
 arrayList0.addAll(arrayList1);
 if (GameClient.bClient || GameServer.bServer) {
 NetChecksum.checksummer.reset(true);
 NetChecksum.GroupOfFiles.initChecksum();
 }

 MultiStageBuilding.stages.clear();
 std::unordered_set hashSet = new HashSet();

 for (auto& string3 : arrayList0) if (!hashSet.contains(string3) {
 hashSet.add(string3);
 std::string string4 = ZomboidFileSystem.instance.getAbsolutePath(string3);
 currentLoadFileAbsPath = string4;
 currentLoadFileMod = this->tempFileToModMap.get(string4);
 this->LoadFile(string3, false);
 if (GameClient.bClient || GameServer.bServer) {
 NetChecksum.checksummer.addFile(string3, string4);
 }
 }
 }

 if (GameClient.bClient || GameServer.bServer) {
 this->checksum = NetChecksum.checksummer.checksumToString();
 if (GameServer.bServer) {
 DebugLog.General.println("scriptChecksum: " + this->checksum);
 }
 }
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }

 this->buf.setLength(0);

 for (int int3 = 0; int3 < this->ModuleList.size(); int3++) {
 ScriptModule scriptModule = this->ModuleList.get(int3);

 for (Item item : scriptModule.ItemMap.values()) {
 this->FullTypeToItemMap.put(item.getFullName(), item);
 }
 }

 this->debugItems();
 this->resolveItemTypes();
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
 this->createClothingItemMap();
 this->createZedDmgMap();
 }

 void debugItems() {
 for (Item item : instance.getAllItems()) {
 if (item.getType() == Item.Type.Drainable && item.getReplaceOnUse() != nullptr) {
 DebugLog.Script.warn("%s ReplaceOnUse instead of ReplaceOnDeplete", item.getFullName());
 }

 if (item.getType() == Item.Type.Weapon && !item.HitSound == item.hitFloorSound) {
 bool boolean0 = true;
 }

 if (!StringUtils.isNullOrEmpty(item.worldStaticModel) {
 ModelScript modelScript = this->getModelScript(item.worldStaticModel);
 if (modelScript != nullptr && modelScript.getAttachmentById("world") != nullptr) {
 bool boolean1 = true;
 }
 }
 }
 }

 public ArrayList<Recipe> getAllRecipesFor(String result) {
 std::vector arrayList0 = this->getAllRecipes();
 std::vector arrayList1 = new ArrayList();

 for (int int0 = 0; int0 < arrayList0.size(); int0++) {
 std::string string = ((Recipe)arrayList0.get(int0).Result.type;
 if (string.contains(".")) {
 string = string.substring(string.indexOf(".") + 1);
 }

 if (string == result) {
 arrayList1.add((Recipe)arrayList0.get(int0);
 }
 }

 return arrayList1;
 }

 std::string getItemTypeForClothingItem(const std::string& clothingItem) {
 return this->clothingToItemMap.get(clothingItem);
 }

 Item getItemForClothingItem(const std::string& clothingName) {
 std::string string = this->getItemTypeForClothingItem(clothingName);
 return string = = nullptr ? nullptr : this->FindItem(string);
 }

 void createZedDmgMap() {
 this->visualDamagesList.clear();
 ScriptModule scriptModule = this->getModule("Base");

 for (Item item : scriptModule.ItemMap.values()) {
 if (!StringUtils.isNullOrWhitespace(item.getBodyLocation()) && "ZedDmg" == item.getBodyLocation())) {
 this->visualDamagesList.add(item.getName());
 }
 }
 }

 public ArrayList<String> getZedDmgMap() {
 return this->visualDamagesList;
 }

 void createClothingItemMap() {
 for (Item item : this->getAllItems()) {
 if (!StringUtils.isNullOrWhitespace(item.getClothingItem())) {
 if (DebugLog.isEnabled(DebugType.Script) {
 DebugLog.Script.debugln("ClothingItem \"%s\" <---> Item \"%s\"", item.getClothingItem(), item.getFullName());
 }

 this->clothingToItemMap.put(item.getClothingItem(), item.getFullName());
 }
 }
 }

 void resolveItemTypes() {
 for (Item item : this->getAllItems()) {
 item.resolveItemTypes();
 }
 }

 std::string resolveItemType(ScriptModule module, const std::string& itemType) {
 if (StringUtils.isNullOrWhitespace(itemType) {
 return nullptr;
 } else if (itemType.contains(".")) {
 return itemType;
 } else {
 Item item = module.getItem(itemType);
 if (item != nullptr) {
 return item.getFullName();
 } else {
 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (!scriptModule.disabled) {
 item = scriptModule.getItem(itemType);
 if (item != nullptr) {
 return item.getFullName();
 }
 }
 }

 return "???." + itemType;
 }
 }
 }

 std::string resolveModelScript(ScriptModule module, const std::string& modelScriptName) {
 if (StringUtils.isNullOrWhitespace(modelScriptName) {
 return nullptr;
 } else if (modelScriptName.contains(".")) {
 return modelScriptName;
 } else {
 ModelScript modelScript = module.getModelScript(modelScriptName);
 if (modelScript != nullptr) {
 return modelScript.getFullType();
 } else {
 for (int int0 = 0; int0 < this->ModuleList.size(); int0++) {
 ScriptModule scriptModule = this->ModuleList.get(int0);
 if (scriptModule != module && !scriptModule.disabled) {
 modelScript = scriptModule.getModelScript(modelScriptName);
 if (modelScript != nullptr) {
 return modelScript.getFullType();
 }
 }
 }

 return "???." + modelScriptName;
 }
 }
 }

 /**
 * Attempts to get the specific item of "module.type" without defaulting to module "Base".
 */
 Item getSpecificItem(const std::string& name) {
 if (!name.contains(".")) {
 DebugLog.log("ScriptManager.getSpecificItem requires a full type name, cannot find: " + name);
 if (Core.bDebug) {
 throw RuntimeException("ScriptManager.getSpecificItem requires a full type name, cannot find: " + name);
 } else {
 return nullptr;
 }
 } else if (this->FullTypeToItemMap.containsKey(name) {
 return this->FullTypeToItemMap.get(name);
 } else {
 int int0 = name.indexOf(".");
 std::string string0 = name.substring(0, int0);
 std::string string1 = name.substring(int0 + 1);
 ScriptModule scriptModule = this->getModule(string0, false);
 return scriptModule = = nullptr ? nullptr : scriptModule.getSpecificItem(string1);
 }
 }
}
} // namespace scripting
} // namespace zombie
