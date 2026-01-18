#pragma once
#include "org/joml/Vector3f.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimBoneWeight.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
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

class ModelScript : public BaseScriptObject {
public:
 static const std::string DEFAULT_SHADER_NAME = "basicEffect";
 std::string fileName;
 std::string name;
 std::string meshName;
 std::string textureName;
 std::string shaderName;
 bool bStatic = true;
 float scale = 1.0F;
public
 ArrayList<ModelAttachment> m_attachments =
 std::make_unique<ArrayList<>>();
 bool invertX = false;
 Model loadedModel;
public
 ArrayList<AnimBoneWeight> boneWeights = std::make_unique<ArrayList<>>();
 std::string animationsMesh = nullptr;
private
 static HashSet<String> reported = std::make_unique<HashSet<>>();

 void Load(const std::string &_name, const std::string &totalFile) {
 ScriptManager scriptManager = ScriptManager.instance;
 this->fileName = scriptManager.currentFileName;
 this->name = _name;
 ScriptParser.Block block0 = ScriptParser.parse(totalFile);
 block0 = block0.children.get(0);

 for (ScriptParser.Block block1 : block0.children) {
 if ("attachment" == block1.type) {
 this->LoadAttachment(block1);
 }
 }

 for (ScriptParser.Value value : block0.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("mesh".equalsIgnoreCase(string0) {
 this->meshName = string1;
 } else if ("scale".equalsIgnoreCase(string0) {
 this->scale = Float.parseFloat(string1);
 } else if ("shader".equalsIgnoreCase(string0) {
 this->shaderName = string1;
 } else if ("static".equalsIgnoreCase(string0) {
 this->bStatic = Boolean.parseBoolean(string1);
 } else if ("texture".equalsIgnoreCase(string0) {
 this->textureName = string1;
 } else if ("invertX".equalsIgnoreCase(string0) {
 this->invertX = Boolean.parseBoolean(string1);
 } else if ("boneWeight".equalsIgnoreCase(string0) {
 String[] strings = string1.split("\\s+");
 if (strings.length == 2) {
 AnimBoneWeight animBoneWeight = new AnimBoneWeight(
 strings[0], PZMath.tryParseFloat(strings[1], 1.0F);
 animBoneWeight.includeDescendants = false;
 this->boneWeights.add(animBoneWeight);
 }
 } else if ("animationsMesh".equalsIgnoreCase(string0) {
 this->animationsMesh = StringUtils.discardNullOrWhitespace(string1);
 }
 }
 }

 ModelAttachment LoadAttachment(ScriptParser.Block block) {
 ModelAttachment modelAttachment = this->getAttachmentById(block.id);
 if (modelAttachment.empty()) {
 modelAttachment = new ModelAttachment(block.id);
 this->m_attachments.add(modelAttachment);
 }

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("bone" == string0) {
 modelAttachment.setBone(string1);
 }
 else if ("offset" == string0) {
 this->LoadVector3f(string1, modelAttachment.getOffset());
 }
 else if ("rotate" == string0) {
 this->LoadVector3f(string1, modelAttachment.getRotate());
 }
 }

 return modelAttachment;
 }

 void LoadVector3f(const std::string &string, Vector3f vector3f) {
 String[] strings = string.split(" ");
 vector3f.set(Float.parseFloat(strings[0]), Float.parseFloat(strings[1]),
 Float.parseFloat(strings[2]));
 }

 std::string getName() { return this->name; }

 std::string getFullType() { return this->module.name + "." + this->name; }

 std::string getMeshName() { return this->meshName; }

 std::string getTextureName() {
 return StringUtils.isNullOrWhitespace(this->textureName) ? this->meshName
 : this->textureName;
 }

 std::string getTextureName(bool allowNull) {
 return StringUtils.isNullOrWhitespace(this->textureName) && !allowNull
 ? this->meshName
 : this->textureName;
 }

 std::string getShaderName() {
 return StringUtils.isNullOrWhitespace(this->shaderName) ? "basicEffect"
 : this->shaderName;
 }

 std::string getFileName() { return this->fileName; }

 int getAttachmentCount() { return this->m_attachments.size(); }

 ModelAttachment getAttachment(int index) {
 return this->m_attachments.get(index);
 }

 ModelAttachment getAttachmentById(const std::string &id) {
 for (int int0 = 0; int0 < this->m_attachments.size(); int0++) {
 ModelAttachment modelAttachment = this->m_attachments.get(int0);
 if (modelAttachment.getId() == id) {
 return modelAttachment;
 }
 }

 return nullptr;
 }

 ModelAttachment addAttachment(ModelAttachment attach) {
 this->m_attachments.add(attach);
 return attach;
 }

 ModelAttachment removeAttachment(ModelAttachment attach) {
 this->m_attachments.remove(attach);
 return attach;
 }

 ModelAttachment addAttachmentAt(int index, ModelAttachment attach) {
 this->m_attachments.add(index, attach);
 return attach;
 }

 ModelAttachment removeAttachment(int index) {
 return this->m_attachments.remove(index);
 }

 void reset() {
 this->invertX = false;
 this->name = nullptr;
 this->meshName = nullptr;
 this->textureName = nullptr;
 this->shaderName = nullptr;
 this->bStatic = true;
 this->scale = 1.0F;
 this->boneWeights.clear();
 }

 static void checkMesh(const std::string &string2,
 const std::string &string0) {
 if (!StringUtils.isNullOrWhitespace(string0) {
 std::string string1 = string0.toLowerCase(Locale.ENGLISH);
 if (!ZomboidFileSystem.instance.ActiveFileMap.containsKey(
 "media/models_x/" + string1 + ".fbx") &&
 !ZomboidFileSystem.instance.ActiveFileMap.containsKey(
 "media/models_x/" + string1 + ".x") &&
 !ZomboidFileSystem.instance.ActiveFileMap.containsKey(
 "media/models/" + string1 + ".txt")) {
 reported.add(string0);
 DebugLog.Script.warn("no such mesh \"" + string0 + "\" for " + string2);
 }
 }
 }

 static void checkTexture(const std::string &string2,
 const std::string &string0) {
 if (!GameServer.bServer) {
 if (!StringUtils.isNullOrWhitespace(string0) {
 std::string string1 = string0.toLowerCase(Locale.ENGLISH);
 if (!ZomboidFileSystem.instance.ActiveFileMap.containsKey(
 "media/textures/" + string1 + ".png")) {
 reported.add(string0);
 DebugLog.Script.warn("no such texture \"" + string0 + "\" for " +
 string2);
 }
 }
 }
 }

 static void check(const std::string &string0, const std::string &string1) {
 check(string0, string1, nullptr);
 }

 static void check(const std::string &string1, const std::string &string0,
 const std::string &string2) {
 if (!StringUtils.isNullOrWhitespace(string0) {
 if (!reported.contains(string0) {
 ModelScript modelScript =
 ScriptManager.instance.getModelScript(string0);
 if (modelScript.empty()) {
 reported.add(string0);
 DebugLog.Script.warn("no such model \"" + string0 + "\" for " +
 string1);
 } else {
 checkMesh(modelScript.getFullType(), modelScript.getMeshName());
 if (StringUtils.isNullOrWhitespace(string2) {
 checkTexture(modelScript.getFullType(),
 modelScript.getTextureName());
 }
 }
 }
 }
 }

 static void ScriptsLoaded() {
 reported.clear();

 for (Item item : ScriptManager.instance.getAllItems()) {
 item.resolveModelScripts();
 check(item.getFullName(), item.getStaticModel());
 check(item.getFullName(), item.getWeaponSprite());
 check(item.getFullName(), item.worldStaticModel, item.getClothingItem());
 }

 for (Recipe recipe : ScriptManager.instance.getAllRecipes()) {
 if (recipe.getProp1() != nullptr &&
 !recipe.getProp1().startsWith("Source=")) {
 check(recipe.getFullType(), recipe.getProp1());
 }

 if (recipe.getProp2() != nullptr &&
 !recipe.getProp2().startsWith("Source=")) {
 check(recipe.getFullType(), recipe.getProp2());
 }
 }
 }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
