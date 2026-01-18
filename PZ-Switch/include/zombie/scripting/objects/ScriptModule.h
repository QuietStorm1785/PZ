#pragma once
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/runtime/RuntimeAnimationScript.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/MultiStageBuilding.h"
#include "zombie/scripting/IScriptObjectStore.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/vehicles/VehicleEngineRPM.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ScriptModule : public BaseScriptObject {
public:
 std::string name;
 std::string value;
public
 HashMap<String, Item> ItemMap = std::make_unique<HashMap<>>();
public
 HashMap<String, GameSoundScript> GameSoundMap =
 std::make_unique<HashMap<>>();
public
 ArrayList<GameSoundScript> GameSoundList =
 std::make_unique<ArrayList<>>();
public
 HashMap<String, AnimationsMesh> AnimationsMeshMap =
 std::make_unique<HashMap<>>();
public
 HashMap<String, MannequinScript> MannequinScriptMap =
 std::make_unique<HashMap<>>();
public
 TreeMap<String, ModelScript> ModelScriptMap =
 new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
public
 HashMap<String, RuntimeAnimationScript> RuntimeAnimationScriptMap =
 std::make_unique<HashMap<>>();
public
 HashMap<String, SoundTimelineScript> SoundTimelineMap =
 std::make_unique<HashMap<>>();
public
 HashMap<String, VehicleScript> VehicleMap =
 std::make_unique<HashMap<>>();
public
 HashMap<String, VehicleTemplate> VehicleTemplateMap =
 std::make_unique<HashMap<>>();
public
 HashMap<String, VehicleEngineRPM> VehicleEngineRPMMap =
 std::make_unique<HashMap<>>();
public
 ArrayList<Recipe> RecipeMap = std::make_unique<ArrayList<>>();
public
 HashMap<String, Recipe> RecipeByName = std::make_unique<HashMap<>>();
public
 HashMap<String, Recipe> RecipesWithDotInName =
 std::make_unique<HashMap<>>();
public
 ArrayList<EvolvedRecipe> EvolvedRecipeMap =
 std::make_unique<ArrayList<>>();
public
 ArrayList<UniqueRecipe> UniqueRecipeMap =
 std::make_unique<ArrayList<>>();
public
 HashMap<String, Fixing> FixingMap = std::make_unique<HashMap<>>();
public
 ArrayList<String> Imports = std::make_unique<ArrayList<>>();
 bool disabled = false;

 void Load(const std::string &_name, const std::string &strArray) {
 this->name = _name;
 this->value = strArray.trim();
 ScriptManager.instance.CurrentLoadingModule = this;
 this->ParseScriptPP(this->value);
 this->ParseScript(this->value);
 this->value = "";
 }

 std::string GetTokenType(const std::string &string0) {
 int int0 = string0.indexOf(123);
 if (int0 == -1) {
 return nullptr;
 } else {
 std::string string1 = string0.substring(0, int0).trim();
 int int1 = string1.indexOf(32);
 int int2 = string1.indexOf(9);
 if (int1 != -1 && int2 != -1) {
 return string1.substring(0, PZMath.min(int1, int2);
 } else if (int1 != -1) {
 return string1.substring(0, int1);
 } else {
 return int2 != -1 ? string1.substring(0, int2) : string1;
 }
 }
 }

 void CreateFromTokenPP(const std::string &string0) {
 string0 = string0.trim();
 std::string string1 = this->GetTokenType(string0);
 if (string1 != nullptr) {
 if ("item" == string1) {
 String[] strings0 = string0.split("[{}]");
 std::string string2 = strings0[0];
 string2 = string2.replace("item", "");
 string2 = string2.trim();
 Item item = new Item();
 this->ItemMap.put(string2, item);
 }
 else if ("animationsMesh" == string1) {
 String[] strings1 = string0.split("[{}]");
 std::string string3 = strings1[0];
 string3 = string3.replace("animationsMesh", "");
 string3 = string3.trim();
 if (this->AnimationsMeshMap.containsKey(string3) {
 AnimationsMesh animationsMesh0 =
 this->AnimationsMeshMap.get(string3);
 animationsMesh0.reset();
 } else {
 AnimationsMesh animationsMesh1 = new AnimationsMesh();
 this->AnimationsMeshMap.put(string3, animationsMesh1);
 }
 }
 else if ("mannequin" == string1) {
 String[] strings2 = string0.split("[{}]");
 std::string string4 = strings2[0];
 string4 = string4.replace("mannequin", "");
 string4 = string4.trim();
 if (this->MannequinScriptMap.containsKey(string4) {
 MannequinScript mannequinScript0 =
 this->MannequinScriptMap.get(string4);
 mannequinScript0.reset();
 } else {
 MannequinScript mannequinScript1 = new MannequinScript();
 this->MannequinScriptMap.put(string4, mannequinScript1);
 }
 }
 else if ("model" == string1) {
 String[] strings3 = string0.split("[{}]");
 std::string string5 = strings3[0];
 string5 = string5.replace("model", "");
 string5 = string5.trim();
 if (this->ModelScriptMap.containsKey(string5) {
 ModelScript modelScript0 = this->ModelScriptMap.get(string5);
 modelScript0.reset();
 } else {
 ModelScript modelScript1 = new ModelScript();
 this->ModelScriptMap.put(string5, modelScript1);
 }
 }
 else if ("sound" == string1) {
 String[] strings4 = string0.split("[{}]");
 std::string string6 = strings4[0];
 string6 = string6.replace("sound", "");
 string6 = string6.trim();
 if (this->GameSoundMap.containsKey(string6) {
 GameSoundScript gameSoundScript0 = this->GameSoundMap.get(string6);
 gameSoundScript0.reset();
 } else {
 GameSoundScript gameSoundScript1 = new GameSoundScript();
 this->GameSoundMap.put(string6, gameSoundScript1);
 this->GameSoundList.add(gameSoundScript1);
 }
 }
 else if ("soundTimeline" == string1) {
 String[] strings5 = string0.split("[{}]");
 std::string string7 = strings5[0];
 string7 = string7.replace("soundTimeline", "");
 string7 = string7.trim();
 if (this->SoundTimelineMap.containsKey(string7) {
 SoundTimelineScript soundTimelineScript0 =
 this->SoundTimelineMap.get(string7);
 soundTimelineScript0.reset();
 } else {
 SoundTimelineScript soundTimelineScript1 =
 new SoundTimelineScript();
 this->SoundTimelineMap.put(string7, soundTimelineScript1);
 }
 }
 else if ("vehicle" == string1) {
 String[] strings6 = string0.split("[{}]");
 std::string string8 = strings6[0];
 string8 = string8.replace("vehicle", "");
 string8 = string8.trim();
 VehicleScript vehicleScript = new VehicleScript();
 this->VehicleMap.put(string8, vehicleScript);
 }
 else if ("template" == string1) {
 String[] strings7 = string0.split("[{}]");
 std::string string9 = strings7[0];
 string9 = string9.replace("template", "");
 String[] strings8 = string9.trim().split("\\s+");
 if (strings8.length == 2) {
 std::string string10 = strings8[0].trim();
 std::string string11 = strings8[1].trim();
 if ("vehicle" == string10) {
 VehicleTemplate vehicleTemplate =
 new VehicleTemplate(this, string11, string0);
 vehicleTemplate.module = this;
 this->VehicleTemplateMap.put(string11, vehicleTemplate);
 }
 }
 }
 else if ("animation" == string1) {
 String[] strings9 = string0.split("[{}]");
 std::string string12 = strings9[0];
 string12 = string12.replace("animation", "");
 string12 = string12.trim();
 if (this->RuntimeAnimationScriptMap.containsKey(string12) {
 RuntimeAnimationScript runtimeAnimationScript0 =
 this->RuntimeAnimationScriptMap.get(string12);
 runtimeAnimationScript0.reset();
 } else {
 RuntimeAnimationScript runtimeAnimationScript1 =
 new RuntimeAnimationScript();
 this->RuntimeAnimationScriptMap.put(string12,
 runtimeAnimationScript1);
 }
 }
 else if ("vehicleEngineRPM" == string1) {
 String[] strings10 = string0.split("[{}]");
 std::string string13 = strings10[0];
 string13 = string13.replace("vehicleEngineRPM", "");
 string13 = string13.trim();
 if (this->VehicleEngineRPMMap.containsKey(string13) {
 VehicleEngineRPM vehicleEngineRPM0 =
 this->VehicleEngineRPMMap.get(string13);
 vehicleEngineRPM0.reset();
 } else {
 VehicleEngineRPM vehicleEngineRPM1 = new VehicleEngineRPM();
 this->VehicleEngineRPMMap.put(string13, vehicleEngineRPM1);
 }
 }
 }
 }

 void CreateFromToken(const std::string &string0) {
 string0 = string0.trim();
 std::string string1 = this->GetTokenType(string0);
 if (string1 != nullptr) {
 if ("imports" == string1) {
 String[] strings0 = string0.split("[{}]");
 String[] strings1 = strings0[1].split(",");

 for (int int0 = 0; int0 < strings1.length; int0++) {
 if (strings1[int0].trim().length() > 0) {
 std::string string2 = strings1[int0].trim();
 if (string2 == this->getName())) {
 DebugLog.log("ERROR: module \"" + this->getName() +
 "\" imports itself");
 }
 else {
 this->Imports.add(string2);
 }
 }
 }
 }
 else if ("item" == string1) {
 String[] strings2 = string0.split("[{}]");
 std::string string3 = strings2[0];
 string3 = string3.replace("item", "");
 string3 = string3.trim();
 String[] strings3 = strings2[1].split(",");
 Item item = this->ItemMap.get(string3);
 item.module = this;

 try {
 item.Load(string3, strings3);
 } catch (Exception exception0) {
 DebugLog.log(exception0);
 }
 }
 else if ("recipe" == string1) {
 String[] strings4 = string0.split("[{}]");
 std::string string4 = strings4[0];
 string4 = string4.replace("recipe", "");
 string4 = string4.trim();
 String[] strings5 = strings4[1].split(",");
 Recipe recipe = new Recipe();
 this->RecipeMap.add(recipe);
 if (!this->RecipeByName.containsKey(string4) {
 this->RecipeByName.put(string4, recipe);
 }

 if (string4.contains(".")) {
 this->RecipesWithDotInName.put(string4, recipe);
 }

 recipe.module = this;
 recipe.Load(string4, strings5);
 }
 else if ("uniquerecipe" == string1) {
 String[] strings6 = string0.split("[{}]");
 std::string string5 = strings6[0];
 string5 = string5.replace("uniquerecipe", "");
 string5 = string5.trim();
 String[] strings7 = strings6[1].split(",");
 UniqueRecipe uniqueRecipe = new UniqueRecipe(string5);
 this->UniqueRecipeMap.add(uniqueRecipe);
 uniqueRecipe.module = this;
 uniqueRecipe.Load(string5, strings7);
 }
 else if ("evolvedrecipe" == string1) {
 String[] strings8 = string0.split("[{}]");
 std::string string6 = strings8[0];
 string6 = string6.replace("evolvedrecipe", "");
 string6 = string6.trim();
 String[] strings9 = strings8[1].split(",");
 bool boolean0 = false;

 for (EvolvedRecipe evolvedRecipe0 : this->EvolvedRecipeMap) {
 if (evolvedRecipe0.name == string6) {
 evolvedRecipe0.Load(string6, strings9);
 evolvedRecipe0.module = this;
 boolean0 = true;
 }
 }

 if (!boolean0) {
 EvolvedRecipe evolvedRecipe1 = new EvolvedRecipe(string6);
 this->EvolvedRecipeMap.add(evolvedRecipe1);
 evolvedRecipe1.module = this;
 evolvedRecipe1.Load(string6, strings9);
 }
 }
 else if ("fixing" == string1) {
 String[] strings10 = string0.split("[{}]");
 std::string string7 = strings10[0];
 string7 = string7.replace("fixing", "");
 string7 = string7.trim();
 String[] strings11 = strings10[1].split(",");
 Fixing fixing = new Fixing();
 fixing.module = this;
 this->FixingMap.put(string7, fixing);
 fixing.Load(string7, strings11);
 }
 else if ("animationsMesh" == string1) {
 String[] strings12 = string0.split("[{}]");
 std::string string8 = strings12[0];
 string8 = string8.replace("animationsMesh", "");
 string8 = string8.trim();
 AnimationsMesh animationsMesh = this->AnimationsMeshMap.get(string8);
 animationsMesh.module = this;

 try {
 animationsMesh.Load(string8, string0);
 } catch (Throwable throwable0) {
 ExceptionLogger.logException(throwable0);
 }
 }
 else if ("mannequin" == string1) {
 String[] strings13 = string0.split("[{}]");
 std::string string9 = strings13[0];
 string9 = string9.replace("mannequin", "");
 string9 = string9.trim();
 MannequinScript mannequinScript =
 this->MannequinScriptMap.get(string9);
 mannequinScript.module = this;

 try {
 mannequinScript.Load(string9, string0);
 } catch (Throwable throwable1) {
 ExceptionLogger.logException(throwable1);
 }
 }
 else if ("multistagebuild" == string1) {
 String[] strings14 = string0.split("[{}]");
 std::string string10 = strings14[0];
 string10 = string10.replace("multistagebuild", "");
 string10 = string10.trim();
 String[] strings15 = strings14[1].split(",");
 MultiStageBuilding.Stage stage =
 std::make_unique<MultiStageBuilding>().std::make_unique<Stage>();
 stage.Load(string10, strings15);
 MultiStageBuilding.addStage(stage);
 }
 else if ("model" == string1) {
 String[] strings16 = string0.split("[{}]");
 std::string string11 = strings16[0];
 string11 = string11.replace("model", "");
 string11 = string11.trim();
 ModelScript modelScript = this->ModelScriptMap.get(string11);
 modelScript.module = this;

 try {
 modelScript.Load(string11, string0);
 } catch (Throwable throwable2) {
 ExceptionLogger.logException(throwable2);
 }
 }
 else if ("sound" == string1) {
 String[] strings17 = string0.split("[{}]");
 std::string string12 = strings17[0];
 string12 = string12.replace("sound", "");
 string12 = string12.trim();
 GameSoundScript gameSoundScript = this->GameSoundMap.get(string12);
 gameSoundScript.module = this;

 try {
 gameSoundScript.Load(string12, string0);
 } catch (Throwable throwable3) {
 ExceptionLogger.logException(throwable3);
 }
 }
 else if ("soundTimeline" == string1) {
 String[] strings18 = string0.split("[{}]");
 std::string string13 = strings18[0];
 string13 = string13.replace("soundTimeline", "");
 string13 = string13.trim();
 SoundTimelineScript soundTimelineScript =
 this->SoundTimelineMap.get(string13);
 soundTimelineScript.module = this;

 try {
 soundTimelineScript.Load(string13, string0);
 } catch (Throwable throwable4) {
 ExceptionLogger.logException(throwable4);
 }
 }
 else if ("vehicle" == string1) {
 String[] strings19 = string0.split("[{}]");
 std::string string14 = strings19[0];
 string14 = string14.replace("vehicle", "");
 string14 = string14.trim();
 VehicleScript vehicleScript = this->VehicleMap.get(string14);
 vehicleScript.module = this;

 try {
 vehicleScript.Load(string14, string0);
 vehicleScript.Loaded();
 } catch (Exception exception1) {
 ExceptionLogger.logException(exception1);
 }
 }
 else if (!"template" == string1) {
 if ("animation" == string1) {
 String[] strings20 = string0.split("[{}]");
 std::string string15 = strings20[0];
 string15 = string15.replace("animation", "");
 string15 = string15.trim();
 RuntimeAnimationScript runtimeAnimationScript =
 this->RuntimeAnimationScriptMap.get(string15);
 runtimeAnimationScript.module = this;

 try {
 runtimeAnimationScript.Load(string15, string0);
 } catch (Throwable throwable5) {
 ExceptionLogger.logException(throwable5);
 }
 }
 else if ("vehicleEngineRPM" == string1) {
 String[] strings21 = string0.split("[{}]");
 std::string string16 = strings21[0];
 string16 = string16.replace("vehicleEngineRPM", "");
 string16 = string16.trim();
 VehicleEngineRPM vehicleEngineRPM =
 this->VehicleEngineRPMMap.get(string16);
 vehicleEngineRPM.module = this;

 try {
 vehicleEngineRPM.Load(string16, string0);
 } catch (Throwable throwable6) {
 this->VehicleEngineRPMMap.remove(string16);
 ExceptionLogger.logException(throwable6);
 }
 }
 else {
 DebugLog.Script.warn("unknown script object \"%s\"", string1);
 }
 }
 }
 }

 void ParseScript(const std::string &totalFile) {
 std::vector arrayList = ScriptParser.parseTokens(totalFile);

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 std::string string = (String)arrayList.get(int0);
 this->CreateFromToken(string);
 }
 }

 void ParseScriptPP(const std::string &totalFile) {
 std::vector arrayList = ScriptParser.parseTokens(totalFile);

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 std::string string = (String)arrayList.get(int0);
 this->CreateFromTokenPP(string);
 }
 }

 Item getItem(const std::string &_name) {
 if (_name.contains(".")) {
 return ScriptManager.instance.getItem(_name);
 } else if (!this->ItemMap.containsKey(_name) {
 for (int int0 = 0; int0 < this->Imports.size(); int0++) {
 std::string string = this->Imports.get(int0);
 ScriptModule scriptModule = ScriptManager.instance.getModule(string);
 Item item = scriptModule.getItem(_name);
 if (item != nullptr) {
 return item;
 }
 }

 return nullptr;
 } else {
 return this->ItemMap.get(_name);
 }
 }

 ModelScript getModelScript(const std::string &_name) {
 if (_name.contains(".")) {
 return ScriptManager.instance.getModelScript(_name);
 } else {
 ModelScript modelScript = this->ModelScriptMap.get(_name);
 if (modelScript.empty()) {
 for (int int0 = 0; int0 < this->Imports.size(); int0++) {
 std::string string = this->Imports.get(int0);
 ScriptModule scriptModule = ScriptManager.instance.getModule(string);
 modelScript = scriptModule.getModelScript(_name);
 if (modelScript != nullptr) {
 return modelScript;
 }
 }

 return nullptr;
 } else {
 return modelScript;
 }
 }
 }

 Recipe getRecipe(const std::string &_name) {
 if (_name.contains(".") && !this->RecipesWithDotInName.containsKey(_name) {
 return ScriptManager.instance.getRecipe(_name);
 } else {
 Recipe recipe = this->RecipeByName.get(_name);
 if (recipe != nullptr) {
 return recipe;
 } else {
 for (int int0 = 0; int0 < this->Imports.size(); int0++) {
 ScriptModule scriptModule =
 ScriptManager.instance.getModule(this->Imports.get(int0);
 if (scriptModule != nullptr) {
 recipe = scriptModule.getRecipe(_name);
 if (recipe != nullptr) {
 return recipe;
 }
 }
 }

 return nullptr;
 }
 }
 }

 VehicleScript getVehicle(const std::string &_name) {
 if (_name.contains(".")) {
 return ScriptManager.instance.getVehicle(_name);
 } else if (!this->VehicleMap.containsKey(_name) {
 for (int int0 = 0; int0 < this->Imports.size(); int0++) {
 VehicleScript vehicleScript =
 ScriptManager.instance.getModule(this->Imports.get(int0)
 .getVehicle(_name);
 if (vehicleScript != nullptr) {
 return vehicleScript;
 }
 }

 return nullptr;
 } else {
 return this->VehicleMap.get(_name);
 }
 }

 VehicleTemplate getVehicleTemplate(const std::string &_name) {
 if (_name.contains(".")) {
 return ScriptManager.instance.getVehicleTemplate(_name);
 } else if (!this->VehicleTemplateMap.containsKey(_name) {
 for (int int0 = 0; int0 < this->Imports.size(); int0++) {
 VehicleTemplate vehicleTemplate =
 ScriptManager.instance.getModule(this->Imports.get(int0)
 .getVehicleTemplate(_name);
 if (vehicleTemplate != nullptr) {
 return vehicleTemplate;
 }
 }

 return nullptr;
 } else {
 return this->VehicleTemplateMap.get(_name);
 }
 }

 VehicleEngineRPM getVehicleEngineRPM(const std::string &_name) {
 return _name.contains(".")
 ? ScriptManager.instance.getVehicleEngineRPM(_name)
 : this->VehicleEngineRPMMap.get(_name);
 }

 bool CheckExitPoints() { return false; }

 std::string getName() { return this->name; }

 void Reset() {
 this->ItemMap.clear();
 this->GameSoundMap.clear();
 this->GameSoundList.clear();
 this->AnimationsMeshMap.clear();
 this->MannequinScriptMap.clear();
 this->ModelScriptMap.clear();
 this->RuntimeAnimationScriptMap.clear();
 this->SoundTimelineMap.clear();
 this->VehicleMap.clear();
 this->VehicleTemplateMap.clear();
 this->VehicleEngineRPMMap.clear();
 this->RecipeMap.clear();
 this->RecipeByName.clear();
 this->RecipesWithDotInName.clear();
 this->EvolvedRecipeMap.clear();
 this->UniqueRecipeMap.clear();
 this->FixingMap.clear();
 this->Imports.clear();
 }

 Item getSpecificItem(const std::string &_name) {
 return this->ItemMap.get(_name);
 }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
