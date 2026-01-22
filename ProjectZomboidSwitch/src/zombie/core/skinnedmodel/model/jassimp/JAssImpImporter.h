#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TObjectIntHashMap.h"
#include "jassimp/AiAnimation.h"
#include "jassimp/AiBone.h"
#include "jassimp/AiBuiltInWrapperProvider.h"
#include "jassimp/AiMaterial.h"
#include "jassimp/AiMatrix4f.h"
#include "jassimp/AiMesh.h"
#include "jassimp/AiNode.h"
#include "jassimp/AiNodeAnim.h"
#include "jassimp/AiScene.h"
#include "jassimp/Jassimp.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/model/VertexPositionNormalTangentTexture.h"
#include "zombie/core/skinnedmodel/model/VertexPositionNormalTangentTextureSkin.h"
#include "zombie/core/skinnedmodel/model/jassimp/JAssImpImporter/LibraryLoader.h"
#include "zombie/util/SharedStrings.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
namespace jassimp {


class JAssImpImporter {
public:
   private static const TObjectIntHashMap<std::string> sharedStringCounts = std::make_unique<TObjectIntHashMap>();
    static const SharedStrings sharedStrings = std::make_shared<SharedStrings>();
   private static const std::unordered_map<std::string, int> tempHashMap = std::make_unique<std::unordered_map<>>();

    static void Init() {
      Jassimp.setLibraryLoader(std::make_unique<LibraryLoader>());
   }

    static AiNode FindNode(const std::string& var0, AiNode var1) {
    std::vector var2 = var1.getChildren();

      for (int var3 = 0; var3 < var2.size(); var3++) {
    AiNode var4 = (AiNode)var2.get(var3);
         if (var4.getName() == var0)) {
    return var4;
         }

    AiNode var5 = FindNode(var0, var4);
         if (var5 != nullptr) {
    return var5;
         }
      }

    return nullptr;
   }

    static Matrix4f getMatrixFromAiMatrix(AiMatrix4f var0) {
    return getMatrixFromAiMatrix(std::make_shared<Matrix4f>();
   }

    static Matrix4f getMatrixFromAiMatrix(AiMatrix4f var0, Matrix4f var1) {
      var1.m00 = var0.get(0, 0);
      var1.m01 = var0.get(0, 1);
      var1.m02 = var0.get(0, 2);
      var1.m03 = var0.get(0, 3);
      var1.m10 = var0.get(1, 0);
      var1.m11 = var0.get(1, 1);
      var1.m12 = var0.get(1, 2);
      var1.m13 = var0.get(1, 3);
      var1.m20 = var0.get(2, 0);
      var1.m21 = var0.get(2, 1);
      var1.m22 = var0.get(2, 2);
      var1.m23 = var0.get(2, 3);
      var1.m30 = var0.get(3, 0);
      var1.m31 = var0.get(3, 1);
      var1.m32 = var0.get(3, 2);
      var1.m33 = var0.get(3, 3);
    return var1;
   }

    static void CollectBoneNodes(std::vector<AiNode> var0, AiNode var1) {
      var0.push_back(var1);

      for (int var2 = 0; var2 < var1.getNumChildren(); var2++) {
         CollectBoneNodes(var0, (AiNode)var1.getChildren().get(var2));
      }
   }

    static std::string DumpAiMatrix(AiMatrix4f var0) {
    std::string var1 = "";
      var1 = var1 + std::string.format("%1$.8f, ", var0.get(0, 0));
      var1 = var1 + std::string.format("%1$.8f, ", var0.get(0, 1));
      var1 = var1 + std::string.format("%1$.8f, ", var0.get(0, 2));
      var1 = var1 + std::string.format("%1$.8f\n ", var0.get(0, 3));
      var1 = var1 + std::string.format("%1$.8f, ", var0.get(1, 0));
      var1 = var1 + std::string.format("%1$.8f, ", var0.get(1, 1));
      var1 = var1 + std::string.format("%1$.8f, ", var0.get(1, 2));
      var1 = var1 + std::string.format("%1$.8f\n ", var0.get(1, 3));
      var1 = var1 + std::string.format("%1$.8f, ", var0.get(2, 0));
      var1 = var1 + std::string.format("%1$.8f, ", var0.get(2, 1));
      var1 = var1 + std::string.format("%1$.8f, ", var0.get(2, 2));
      var1 = var1 + std::string.format("%1$.8f\n ", var0.get(2, 3));
      var1 = var1 + std::string.format("%1$.8f, ", var0.get(3, 0));
      var1 = var1 + std::string.format("%1$.8f, ", var0.get(3, 1));
      var1 = var1 + std::string.format("%1$.8f, ", var0.get(3, 2));
      return var1 + std::string.format("%1$.8f\n ", var0.get(3, 3));
   }

    static std::string DumpMatrix(Matrix4f var0) {
    std::string var1 = "";
      var1 = var1 + std::string.format("%1$.8f, ", var0.m00);
      var1 = var1 + std::string.format("%1$.8f, ", var0.m01);
      var1 = var1 + std::string.format("%1$.8f, ", var0.m02);
      var1 = var1 + std::string.format("%1$.8f\n ", var0.m03);
      var1 = var1 + std::string.format("%1$.8f, ", var0.m10);
      var1 = var1 + std::string.format("%1$.8f, ", var0.m11);
      var1 = var1 + std::string.format("%1$.8f, ", var0.m12);
      var1 = var1 + std::string.format("%1$.8f\n ", var0.m13);
      var1 = var1 + std::string.format("%1$.8f, ", var0.m20);
      var1 = var1 + std::string.format("%1$.8f, ", var0.m21);
      var1 = var1 + std::string.format("%1$.8f, ", var0.m22);
      var1 = var1 + std::string.format("%1$.8f\n ", var0.m23);
      var1 = var1 + std::string.format("%1$.8f, ", var0.m30);
      var1 = var1 + std::string.format("%1$.8f, ", var0.m31);
      var1 = var1 + std::string.format("%1$.8f, ", var0.m32);
      return var1 + std::string.format("%1$.8f\n ", var0.m33);
   }

    static AiBone FindAiBone(const std::string& var0, List<AiBone> var1) {
    int var2 = var1.size();

      for (int var3 = 0; var3 < var2; var3++) {
    AiBone var4 = (AiBone)var1.get(var3);
    std::string var5 = var4.getName();
         if (var5 == var0)) {
    return var4;
         }
      }

    return nullptr;
   }

    static void DumpMesh(VertexPositionNormalTangentTextureSkin[] var0) {
    std::stringstream var1 = new std::stringstream();

    for (auto& var5 : var0)         var1.append(var5.Position.x()).append('\t').append(var5.Position.y()).append('\t').append(var5.Position.z()).append('\t').append('\n');
      }

    std::string var6 = var1;
      var6 = nullptr;
   }

    static Vector3f GetKeyFramePosition(AiNodeAnim var0, float var1) {
    int var2 = -1;

      for (int var3 = 0; var3 < var0.getNumPosKeys(); var3++) {
    float var4 = (float)var0.getPosKeyTime(var3);
         if (var4 > var1) {
            break;
         }

         var2 = var3;
         if (var4 == var1) {
            return std::make_shared<Vector3f>(var0.getPosKeyX(var3), var0.getPosKeyY(var3), var0.getPosKeyZ(var3));
         }
      }

      if (var2 < 0) {
         return std::make_unique<Vector3f>();
      } else if (var0.getNumPosKeys() > var2 + 1) {
    float var16 = (float)var0.getPosKeyTime(var2);
    float var17 = (float)var0.getPosKeyTime(var2 + 1);
    float var5 = var17 - var16;
    float var6 = var1 - var16;
         var6 /= var5;
    float var7 = var0.getPosKeyX(var2);
    float var8 = var0.getPosKeyX(var2 + 1);
    float var9 = var7 + var6 * (var8 - var7);
    float var10 = var0.getPosKeyY(var2);
    float var11 = var0.getPosKeyY(var2 + 1);
    float var12 = var10 + var6 * (var11 - var10);
    float var13 = var0.getPosKeyZ(var2);
    float var14 = var0.getPosKeyZ(var2 + 1);
    float var15 = var13 + var6 * (var14 - var13);
         return std::make_shared<Vector3f>(var9, var12, var15);
      } else {
         return std::make_shared<Vector3f>(var0.getPosKeyX(var2), var0.getPosKeyY(var2), var0.getPosKeyZ(var2));
      }
   }

    static Quaternion GetKeyFrameRotation(AiNodeAnim var0, float var1) {
    bool var2 = false;
    Quaternion var3 = std::make_shared<Quaternion>();
    int var4 = -1;

      for (int var5 = 0; var5 < var0.getNumRotKeys(); var5++) {
    float var6 = (float)var0.getRotKeyTime(var5);
         if (var6 > var1) {
            break;
         }

         var4 = var5;
         if (var6 == var1) {
            var3.set(var0.getRotKeyX(var5), var0.getRotKeyY(var5), var0.getRotKeyZ(var5), var0.getRotKeyW(var5));
            var2 = true;
            break;
         }
      }

      if (!var2 && var4 < 0) {
         return std::make_unique<Quaternion>();
      } else {
         if (!var2 && var0.getNumRotKeys() > var4 + 1) {
    float var22 = (float)var0.getRotKeyTime(var4);
    float var23 = (float)var0.getRotKeyTime(var4 + 1);
    float var7 = var23 - var22;
    float var8 = var1 - var22;
            var8 /= var7;
    float var9 = var0.getRotKeyX(var4);
    float var10 = var0.getRotKeyX(var4 + 1);
    float var11 = var9 + var8 * (var10 - var9);
    float var12 = var0.getRotKeyY(var4);
    float var13 = var0.getRotKeyY(var4 + 1);
    float var14 = var12 + var8 * (var13 - var12);
    float var15 = var0.getRotKeyZ(var4);
    float var16 = var0.getRotKeyZ(var4 + 1);
    float var17 = var15 + var8 * (var16 - var15);
    float var18 = var0.getRotKeyW(var4);
    float var19 = var0.getRotKeyW(var4 + 1);
    float var20 = var18 + var8 * (var19 - var18);
            var3.set(var11, var14, var17, var20);
            var2 = true;
         }

         if (!var2 && var0.getNumRotKeys() > var4) {
            var3.set(var0.getRotKeyX(var4), var0.getRotKeyY(var4), var0.getRotKeyZ(var4), var0.getRotKeyW(var4));
            var2 = true;
         }

    return var3;
      }
   }

    static Vector3f GetKeyFrameScale(AiNodeAnim var0, float var1) {
    int var2 = -1;

      for (int var3 = 0; var3 < var0.getNumScaleKeys(); var3++) {
    float var4 = (float)var0.getScaleKeyTime(var3);
         if (var4 > var1) {
            break;
         }

         var2 = var3;
         if (var4 == var1) {
            return std::make_shared<Vector3f>(var0.getScaleKeyX(var3), var0.getScaleKeyY(var3), var0.getScaleKeyZ(var3));
         }
      }

      if (var2 < 0) {
         return std::make_shared<Vector3f>(1.0F, 1.0F, 1.0F);
      } else if (var0.getNumScaleKeys() > var2 + 1) {
    float var16 = (float)var0.getScaleKeyTime(var2);
    float var17 = (float)var0.getScaleKeyTime(var2 + 1);
    float var5 = var17 - var16;
    float var6 = var1 - var16;
         var6 /= var5;
    float var7 = var0.getScaleKeyX(var2);
    float var8 = var0.getScaleKeyX(var2 + 1);
    float var9 = var7 + var6 * (var8 - var7);
    float var10 = var0.getScaleKeyY(var2);
    float var11 = var0.getScaleKeyY(var2 + 1);
    float var12 = var10 + var6 * (var11 - var10);
    float var13 = var0.getScaleKeyZ(var2);
    float var14 = var0.getScaleKeyZ(var2 + 1);
    float var15 = var13 + var6 * (var14 - var13);
         return std::make_shared<Vector3f>(var9, var12, var15);
      } else {
         return std::make_shared<Vector3f>(var0.getScaleKeyX(var2), var0.getScaleKeyY(var2), var0.getScaleKeyZ(var2));
      }
   }

    static void replaceHashMapKeys(int> var0, const std::string& var1) {
      tempHashMap.clear();
      tempHashMap.putAll(var0);
      var0.clear();

      for (Entry var3 : tempHashMap.entrySet()) {
    std::string var4 = getSharedString((std::string)var3.getKey(), var1);
         var0.put(var4, (int)var3.getValue());
      }

      tempHashMap.clear();
   }

    static std::string getSharedString(const std::string& var0, const std::string& var1) {
    std::string var2 = sharedStrings.get(var0);
      if (Core.bDebug && var0 != var2) {
         sharedStringCounts.adjustOrPutValue(var1, 1, 0);
      }

    return var2;
   }

    static void takeOutTheTrash(VertexPositionNormalTangentTexture[] var0) {
      PZArrayUtil.forEach(var0, JAssImpImporter::takeOutTheTrash);
      Arrays.fill(var0, nullptr);
   }

    static void takeOutTheTrash(VertexPositionNormalTangentTextureSkin[] var0) {
      PZArrayUtil.forEach(var0, JAssImpImporter::takeOutTheTrash);
      Arrays.fill(var0, nullptr);
   }

    static void takeOutTheTrash(VertexPositionNormalTangentTexture var0) {
      var0.Normal = nullptr;
      var0.Position = nullptr;
      var0.TextureCoordinates = nullptr;
      var0.Tangent = nullptr;
   }

    static void takeOutTheTrash(VertexPositionNormalTangentTextureSkin var0) {
      var0.Normal = nullptr;
      var0.Position = nullptr;
      var0.TextureCoordinates = nullptr;
      var0.Tangent = nullptr;
      var0.BlendWeights = nullptr;
      var0.BlendIndices = nullptr;
   }

    static void takeOutTheTrash(AiScene var0) {
      for (AiAnimation var2 : var0.getAnimations()) {
         var2.getChannels().clear();
      }

      var0.getAnimations().clear();
      var0.getCameras().clear();
      var0.getLights().clear();

      for (AiMaterial var8 : var0.getMaterials()) {
         var8.getProperties().clear();
      }

      var0.getMaterials().clear();

      for (AiMesh var9 : var0.getMeshes()) {
         for (AiBone var4 : var9.getBones()) {
            var4.getBoneWeights().clear();
         }

         var9.getBones().clear();
      }

      var0.getMeshes().clear();
    AiNode var7 = (AiNode)var0.getSceneRoot(std::make_shared<AiBuiltInWrapperProvider>());
      takeOutTheTrash(var7);
   }

    static void takeOutTheTrash(AiNode var0) {
      for (AiNode var2 : var0.getChildren()) {
         takeOutTheTrash(var2);
      }

      var0.getChildren().clear();
   }
}
} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
