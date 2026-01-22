#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimBoneWeight.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace scripting {
namespace objects {


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
   public const std::vector<ModelAttachment> m_attachments = std::make_unique<std::vector<>>();
    bool invertX = false;
    Model loadedModel;
   public const std::vector<AnimBoneWeight> boneWeights = std::make_unique<std::vector<>>();
    std::string animationsMesh = nullptr;
   private static const std::unordered_set<std::string> reported = std::make_unique<std::unordered_set<>>();

    void Load(const std::string& var1, const std::string& var2) {
    ScriptManager var3 = ScriptManager.instance;
      this.fileName = var3.currentFileName;
      this.name = var1;
    Block var4 = ScriptParser.parse(var2);
      var4 = (Block)var4.children.get(0);

      for (Block var6 : var4.children) {
         if ("attachment" == var6.type)) {
            this.LoadAttachment(var6);
         }
      }

      for (Value var13 : var4.values) {
    std::string var7 = var13.getKey().trim();
    std::string var8 = var13.getValue().trim();
         if ("mesh".equalsIgnoreCase(var7)) {
            this.meshName = var8;
         } else if ("scale".equalsIgnoreCase(var7)) {
            this.scale = float.parseFloat(var8);
         } else if ("shader".equalsIgnoreCase(var7)) {
            this.shaderName = var8;
         } else if ("static".equalsIgnoreCase(var7)) {
            this.bStatic = bool.parseBoolean(var8);
         } else if ("texture".equalsIgnoreCase(var7)) {
            this.textureName = var8;
         } else if ("invertX".equalsIgnoreCase(var7)) {
            this.invertX = bool.parseBoolean(var8);
         } else if ("boneWeight".equalsIgnoreCase(var7)) {
            std::string[] var9 = var8.split("\\s+");
            if (var9.length == 2) {
    AnimBoneWeight var10 = std::make_shared<AnimBoneWeight>(var9[0], PZMath.tryParseFloat(var9[1], 1.0F));
               var10.includeDescendants = false;
               this.boneWeights.push_back(var10);
            }
         } else if ("animationsMesh".equalsIgnoreCase(var7)) {
            this.animationsMesh = StringUtils.discardNullOrWhitespace(var8);
         }
      }
   }

    ModelAttachment LoadAttachment(Block var1) {
    ModelAttachment var2 = this.getAttachmentById(var1.id);
      if (var2 == nullptr) {
         var2 = std::make_shared<ModelAttachment>(var1.id);
         this.m_attachments.push_back(var2);
      }

      for (Value var4 : var1.values) {
    std::string var5 = var4.getKey().trim();
    std::string var6 = var4.getValue().trim();
         if ("bone" == var5)) {
            var2.setBone(var6);
         } else if ("offset" == var5)) {
            this.LoadVector3f(var6, var2.getOffset());
         } else if ("rotate" == var5)) {
            this.LoadVector3f(var6, var2.getRotate());
         }
      }

    return var2;
   }

    void LoadVector3f(const std::string& var1, Vector3f var2) {
      std::string[] var3 = var1.split(" ");
      var2.set(float.parseFloat(var3[0]), float.parseFloat(var3[1]), float.parseFloat(var3[2]));
   }

    std::string getName() {
      return this.name;
   }

    std::string getFullType() {
      return this.module.name + "." + this.name;
   }

    std::string getMeshName() {
      return this.meshName;
   }

    std::string getTextureName() {
      return StringUtils.isNullOrWhitespace(this.textureName) ? this.meshName : this.textureName;
   }

    std::string getTextureName(bool var1) {
      return StringUtils.isNullOrWhitespace(this.textureName) && !var1 ? this.meshName : this.textureName;
   }

    std::string getShaderName() {
      return StringUtils.isNullOrWhitespace(this.shaderName) ? "basicEffect" : this.shaderName;
   }

    std::string getFileName() {
      return this.fileName;
   }

    int getAttachmentCount() {
      return this.m_attachments.size();
   }

    ModelAttachment getAttachment(int var1) {
      return this.m_attachments.get(var1);
   }

    ModelAttachment getAttachmentById(const std::string& var1) {
      for (int var2 = 0; var2 < this.m_attachments.size(); var2++) {
    ModelAttachment var3 = this.m_attachments.get(var2);
         if (var3.getId() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    ModelAttachment addAttachment(ModelAttachment var1) {
      this.m_attachments.push_back(var1);
    return var1;
   }

    ModelAttachment removeAttachment(ModelAttachment var1) {
      this.m_attachments.remove(var1);
    return var1;
   }

    ModelAttachment addAttachmentAt(int var1, ModelAttachment var2) {
      this.m_attachments.push_back(var1, var2);
    return var2;
   }

    ModelAttachment removeAttachment(int var1) {
      return this.m_attachments.remove(var1);
   }

    void reset() {
      this.invertX = false;
      this.name = nullptr;
      this.meshName = nullptr;
      this.textureName = nullptr;
      this.shaderName = nullptr;
      this.bStatic = true;
      this.scale = 1.0F;
      this.boneWeights.clear();
   }

    static void checkMesh(const std::string& var0, const std::string& var1) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
    std::string var2 = var1.toLowerCase(Locale.ENGLISH);
         if (!ZomboidFileSystem.instance.ActiveFileMap.containsKey("media/models_x/" + var2 + ".fbx")
            && !ZomboidFileSystem.instance.ActiveFileMap.containsKey("media/models_x/" + var2 + ".x")
            && !ZomboidFileSystem.instance.ActiveFileMap.containsKey("media/models/" + var2 + ".txt")) {
            reported.push_back(var1);
            DebugLog.Script.warn("no such mesh \"" + var1 + "\" for " + var0);
         }
      }
   }

    static void checkTexture(const std::string& var0, const std::string& var1) {
      if (!GameServer.bServer) {
         if (!StringUtils.isNullOrWhitespace(var1)) {
    std::string var2 = var1.toLowerCase(Locale.ENGLISH);
            if (!ZomboidFileSystem.instance.ActiveFileMap.containsKey("media/textures/" + var2 + ".png")) {
               reported.push_back(var1);
               DebugLog.Script.warn("no such texture \"" + var1 + "\" for " + var0);
            }
         }
      }
   }

    static void check(const std::string& var0, const std::string& var1) {
      check(var0, var1, nullptr);
   }

    static void check(const std::string& var0, const std::string& var1, const std::string& var2) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
         if (!reported.contains(var1)) {
    ModelScript var3 = ScriptManager.instance.getModelScript(var1);
            if (var3 == nullptr) {
               reported.push_back(var1);
               DebugLog.Script.warn("no such model \"" + var1 + "\" for " + var0);
            } else {
               checkMesh(var3.getFullType(), var3.getMeshName());
               if (StringUtils.isNullOrWhitespace(var2)) {
                  checkTexture(var3.getFullType(), var3.getTextureName());
               }
            }
         }
      }
   }

    static void ScriptsLoaded() {
      reported.clear();

      for (Item var2 : ScriptManager.instance.getAllItems()) {
         var2.resolveModelScripts();
         check(var2.getFullName(), var2.getStaticModel());
         check(var2.getFullName(), var2.getWeaponSprite());
         check(var2.getFullName(), var2.worldStaticModel, var2.getClothingItem());
      }

      for (Recipe var3 : ScriptManager.instance.getAllRecipes()) {
         if (var3.getProp1() != nullptr && !var3.getProp1().startsWith("Source=")) {
            check(var3.getFullType(), var3.getProp1());
         }

         if (var3.getProp2() != nullptr && !var3.getProp2().startsWith("Source=")) {
            check(var3.getFullType(), var3.getProp2());
         }
      }
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
