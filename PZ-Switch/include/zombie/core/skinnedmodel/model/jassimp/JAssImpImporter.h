#pragma once
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
#include "jassimp/JassimpLibraryLoader.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/model/VertexPositionNormalTangentTexture.h"
#include "zombie/core/skinnedmodel/model/VertexPositionNormalTangentTextureSkin.h"
#include "zombie/util/SharedStrings.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
namespace jassimp {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class JAssImpImporter {
public:
private
 static TObjectIntHashMap<String> sharedStringCounts =
 std::make_unique<TObjectIntHashMap<>>();
 static const SharedStrings sharedStrings = new SharedStrings();
private
 static HashMap<String, Integer> tempHashMap =
 std::make_unique<HashMap<>>();

 static void Init() {
 Jassimp.setLibraryLoader(new JAssImpImporter.LibraryLoader());
 }

 static AiNode FindNode(const std::string &string, AiNode aiNode0) {
 std::vector list = aiNode0.getChildren();

 for (int int0 = 0; int0 < list.size(); int0++) {
 AiNode aiNode1 = (AiNode)list.get(int0);
 if (aiNode1.getName() == string) {
 return aiNode1;
 }

 AiNode aiNode2 = FindNode(string, aiNode1);
 if (aiNode2 != nullptr) {
 return aiNode2;
 }
 }

 return nullptr;
 }

 static Matrix4f getMatrixFromAiMatrix(AiMatrix4f aiMatrix4f) {
 return getMatrixFromAiMatrix(new Matrix4f();
 }

 static Matrix4f getMatrixFromAiMatrix(AiMatrix4f aiMatrix4f,
 Matrix4f matrix4f) {
 matrix4f.m00 = aiMatrix4f.get(0, 0);
 matrix4f.m01 = aiMatrix4f.get(0, 1);
 matrix4f.m02 = aiMatrix4f.get(0, 2);
 matrix4f.m03 = aiMatrix4f.get(0, 3);
 matrix4f.m10 = aiMatrix4f.get(1, 0);
 matrix4f.m11 = aiMatrix4f.get(1, 1);
 matrix4f.m12 = aiMatrix4f.get(1, 2);
 matrix4f.m13 = aiMatrix4f.get(1, 3);
 matrix4f.m20 = aiMatrix4f.get(2, 0);
 matrix4f.m21 = aiMatrix4f.get(2, 1);
 matrix4f.m22 = aiMatrix4f.get(2, 2);
 matrix4f.m23 = aiMatrix4f.get(2, 3);
 matrix4f.m30 = aiMatrix4f.get(3, 0);
 matrix4f.m31 = aiMatrix4f.get(3, 1);
 matrix4f.m32 = aiMatrix4f.get(3, 2);
 matrix4f.m33 = aiMatrix4f.get(3, 3);
 return matrix4f;
 }

 static void CollectBoneNodes(ArrayList<AiNode> arrayList, AiNode aiNode) {
 arrayList.add(aiNode);

 for (int int0 = 0; int0 < aiNode.getNumChildren(); int0++) {
 CollectBoneNodes(arrayList, aiNode.getChildren().get(int0);
 }
 }

 static std::string DumpAiMatrix(AiMatrix4f aiMatrix4f) {
 std::string string = "";
 string = string + String.format("%1$.8f, ", aiMatrix4f.get(0, 0);
 string = string + String.format("%1$.8f, ", aiMatrix4f.get(0, 1);
 string = string + String.format("%1$.8f, ", aiMatrix4f.get(0, 2);
 string = string + String.format("%1$.8f\n ", aiMatrix4f.get(0, 3);
 string = string + String.format("%1$.8f, ", aiMatrix4f.get(1, 0);
 string = string + String.format("%1$.8f, ", aiMatrix4f.get(1, 1);
 string = string + String.format("%1$.8f, ", aiMatrix4f.get(1, 2);
 string = string + String.format("%1$.8f\n ", aiMatrix4f.get(1, 3);
 string = string + String.format("%1$.8f, ", aiMatrix4f.get(2, 0);
 string = string + String.format("%1$.8f, ", aiMatrix4f.get(2, 1);
 string = string + String.format("%1$.8f, ", aiMatrix4f.get(2, 2);
 string = string + String.format("%1$.8f\n ", aiMatrix4f.get(2, 3);
 string = string + String.format("%1$.8f, ", aiMatrix4f.get(3, 0);
 string = string + String.format("%1$.8f, ", aiMatrix4f.get(3, 1);
 string = string + String.format("%1$.8f, ", aiMatrix4f.get(3, 2);
 return string + String.format("%1$.8f\n ", aiMatrix4f.get(3, 3);
 }

 static std::string DumpMatrix(Matrix4f matrix4f) {
 std::string string = "";
 string = string + String.format("%1$.8f, ", matrix4f.m00);
 string = string + String.format("%1$.8f, ", matrix4f.m01);
 string = string + String.format("%1$.8f, ", matrix4f.m02);
 string = string + String.format("%1$.8f\n ", matrix4f.m03);
 string = string + String.format("%1$.8f, ", matrix4f.m10);
 string = string + String.format("%1$.8f, ", matrix4f.m11);
 string = string + String.format("%1$.8f, ", matrix4f.m12);
 string = string + String.format("%1$.8f\n ", matrix4f.m13);
 string = string + String.format("%1$.8f, ", matrix4f.m20);
 string = string + String.format("%1$.8f, ", matrix4f.m21);
 string = string + String.format("%1$.8f, ", matrix4f.m22);
 string = string + String.format("%1$.8f\n ", matrix4f.m23);
 string = string + String.format("%1$.8f, ", matrix4f.m30);
 string = string + String.format("%1$.8f, ", matrix4f.m31);
 string = string + String.format("%1$.8f, ", matrix4f.m32);
 return string + String.format("%1$.8f\n ", matrix4f.m33);
 }

 static AiBone FindAiBone(const std::string &string1, List<AiBone> list) {
 int int0 = list.size();

 for (int int1 = 0; int1 < int0; int1++) {
 AiBone aiBone = (AiBone)list.get(int1);
 std::string string0 = aiBone.getName();
 if (string0 == string1) {
 return aiBone;
 }
 }

 return nullptr;
 }

 static void DumpMesh(VertexPositionNormalTangentTextureSkin
 [] vertexPositionNormalTangentTextureSkins) {
 StringBuilder stringBuilder = new StringBuilder();

 for (auto &vertexPositionNormalTangentTextureSkin :
 vertexPositionNormalTangentTextureSkins)
 stringBuilder.append(vertexPositionNormalTangentTextureSkin.Position.x())
 .append('\t')
 .append(vertexPositionNormalTangentTextureSkin.Position.y())
 .append('\t')
 .append(vertexPositionNormalTangentTextureSkin.Position.z())
 .append('\t')
 .append('\n');
 }

 std::string string = stringBuilder.toString();
 string = nullptr;
}

static Vector3f
GetKeyFramePosition(AiNodeAnim aiNodeAnim, float float1) {
 int int0 = -1;

 for (int int1 = 0; int1 < aiNodeAnim.getNumPosKeys(); int1++) {
 float float0 = (float)aiNodeAnim.getPosKeyTime(int1);
 if (float0 > float1) {
 break;
 }

 int0 = int1;
 if (float0 == float1) {
 return new Vector3f(aiNodeAnim.getPosKeyX(int1),
 aiNodeAnim.getPosKeyY(int1),
 aiNodeAnim.getPosKeyZ(int1);
 }
 }

 if (int0 < 0) {
 return std::make_unique<Vector3f>();
 } else if (aiNodeAnim.getNumPosKeys() > int0 + 1) {
 float float2 = (float)aiNodeAnim.getPosKeyTime(int0);
 float float3 = (float)aiNodeAnim.getPosKeyTime(int0 + 1);
 float float4 = float3 - float2;
 float float5 = float1 - float2;
 float5 /= float4;
 float float6 = aiNodeAnim.getPosKeyX(int0);
 float float7 = aiNodeAnim.getPosKeyX(int0 + 1);
 float float8 = float6 + float5 * (float7 - float6);
 float float9 = aiNodeAnim.getPosKeyY(int0);
 float float10 = aiNodeAnim.getPosKeyY(int0 + 1);
 float float11 = float9 + float5 * (float10 - float9);
 float float12 = aiNodeAnim.getPosKeyZ(int0);
 float float13 = aiNodeAnim.getPosKeyZ(int0 + 1);
 float float14 = float12 + float5 * (float13 - float12);
 return new Vector3f(float8, float11, float14);
 } else {
 return new Vector3f(aiNodeAnim.getPosKeyX(int0),
 aiNodeAnim.getPosKeyY(int0),
 aiNodeAnim.getPosKeyZ(int0);
 }
}

static Quaternion GetKeyFrameRotation(AiNodeAnim aiNodeAnim, float float1) {
 bool boolean0 = false;
 Quaternion quaternion = new Quaternion();
 int int0 = -1;

 for (int int1 = 0; int1 < aiNodeAnim.getNumRotKeys(); int1++) {
 float float0 = (float)aiNodeAnim.getRotKeyTime(int1);
 if (float0 > float1) {
 break;
 }

 int0 = int1;
 if (float0 == float1) {
 quaternion.set(aiNodeAnim.getRotKeyX(int1), aiNodeAnim.getRotKeyY(int1),
 aiNodeAnim.getRotKeyZ(int1), aiNodeAnim.getRotKeyW(int1);
 boolean0 = true;
 break;
 }
 }

 if (!boolean0 && int0 < 0) {
 return std::make_unique<Quaternion>();
 } else {
 if (!boolean0 && aiNodeAnim.getNumRotKeys() > int0 + 1) {
 float float2 = (float)aiNodeAnim.getRotKeyTime(int0);
 float float3 = (float)aiNodeAnim.getRotKeyTime(int0 + 1);
 float float4 = float3 - float2;
 float float5 = float1 - float2;
 float5 /= float4;
 float float6 = aiNodeAnim.getRotKeyX(int0);
 float float7 = aiNodeAnim.getRotKeyX(int0 + 1);
 float float8 = float6 + float5 * (float7 - float6);
 float float9 = aiNodeAnim.getRotKeyY(int0);
 float float10 = aiNodeAnim.getRotKeyY(int0 + 1);
 float float11 = float9 + float5 * (float10 - float9);
 float float12 = aiNodeAnim.getRotKeyZ(int0);
 float float13 = aiNodeAnim.getRotKeyZ(int0 + 1);
 float float14 = float12 + float5 * (float13 - float12);
 float float15 = aiNodeAnim.getRotKeyW(int0);
 float float16 = aiNodeAnim.getRotKeyW(int0 + 1);
 float float17 = float15 + float5 * (float16 - float15);
 quaternion.set(float8, float11, float14, float17);
 boolean0 = true;
 }

 if (!boolean0 && aiNodeAnim.getNumRotKeys() > int0) {
 quaternion.set(aiNodeAnim.getRotKeyX(int0), aiNodeAnim.getRotKeyY(int0),
 aiNodeAnim.getRotKeyZ(int0), aiNodeAnim.getRotKeyW(int0);
 boolean0 = true;
 }

 return quaternion;
 }
}

static Vector3f GetKeyFrameScale(AiNodeAnim aiNodeAnim, float float1) {
 int int0 = -1;

 for (int int1 = 0; int1 < aiNodeAnim.getNumScaleKeys(); int1++) {
 float float0 = (float)aiNodeAnim.getScaleKeyTime(int1);
 if (float0 > float1) {
 break;
 }

 int0 = int1;
 if (float0 == float1) {
 return new Vector3f(aiNodeAnim.getScaleKeyX(int1),
 aiNodeAnim.getScaleKeyY(int1),
 aiNodeAnim.getScaleKeyZ(int1);
 }
 }

 if (int0 < 0) {
 return new Vector3f(1.0F, 1.0F, 1.0F);
 } else if (aiNodeAnim.getNumScaleKeys() > int0 + 1) {
 float float2 = (float)aiNodeAnim.getScaleKeyTime(int0);
 float float3 = (float)aiNodeAnim.getScaleKeyTime(int0 + 1);
 float float4 = float3 - float2;
 float float5 = float1 - float2;
 float5 /= float4;
 float float6 = aiNodeAnim.getScaleKeyX(int0);
 float float7 = aiNodeAnim.getScaleKeyX(int0 + 1);
 float float8 = float6 + float5 * (float7 - float6);
 float float9 = aiNodeAnim.getScaleKeyY(int0);
 float float10 = aiNodeAnim.getScaleKeyY(int0 + 1);
 float float11 = float9 + float5 * (float10 - float9);
 float float12 = aiNodeAnim.getScaleKeyZ(int0);
 float float13 = aiNodeAnim.getScaleKeyZ(int0 + 1);
 float float14 = float12 + float5 * (float13 - float12);
 return new Vector3f(float8, float11, float14);
 } else {
 return new Vector3f(aiNodeAnim.getScaleKeyX(int0),
 aiNodeAnim.getScaleKeyY(int0),
 aiNodeAnim.getScaleKeyZ(int0);
 }
}

static void replaceHashMapKeys(Integer > hashMap, const std::string &string1) {
 tempHashMap.clear();
 tempHashMap.putAll(hashMap);
 hashMap.clear();

 for (Entry entry : tempHashMap.entrySet()) {
 std::string string0 = getSharedString((String)entry.getKey(), string1);
 hashMap.put(string0, (Integer)entry.getValue());
 }

 tempHashMap.clear();
}

static std::string getSharedString(const std::string &string1,
 const std::string &string2) {
 std::string string0 = sharedStrings.get(string1);
 if (Core.bDebug && string1 != string0) {
 sharedStringCounts.adjustOrPutValue(string2, 1, 0);
 }

 return string0;
}

static void takeOutTheTrash(
 VertexPositionNormalTangentTexture[] vertexPositionNormalTangentTextures) {
 PZArrayUtil.forEach(vertexPositionNormalTangentTextures,
 JAssImpImporter::takeOutTheTrash);
 Arrays.fill(vertexPositionNormalTangentTextures, nullptr);
}

static void takeOutTheTrash(VertexPositionNormalTangentTextureSkin
 [] vertexPositionNormalTangentTextureSkins) {
 PZArrayUtil.forEach(vertexPositionNormalTangentTextureSkins,
 JAssImpImporter::takeOutTheTrash);
 Arrays.fill(vertexPositionNormalTangentTextureSkins, nullptr);
}

static void takeOutTheTrash(
 VertexPositionNormalTangentTexture vertexPositionNormalTangentTexture) {
 vertexPositionNormalTangentTexture.Normal = nullptr;
 vertexPositionNormalTangentTexture.Position = nullptr;
 vertexPositionNormalTangentTexture.TextureCoordinates = nullptr;
 vertexPositionNormalTangentTexture.Tangent = nullptr;
}

static void takeOutTheTrash(VertexPositionNormalTangentTextureSkin
 vertexPositionNormalTangentTextureSkin) {
 vertexPositionNormalTangentTextureSkin.Normal = nullptr;
 vertexPositionNormalTangentTextureSkin.Position = nullptr;
 vertexPositionNormalTangentTextureSkin.TextureCoordinates = nullptr;
 vertexPositionNormalTangentTextureSkin.Tangent = nullptr;
 vertexPositionNormalTangentTextureSkin.BlendWeights = nullptr;
 vertexPositionNormalTangentTextureSkin.BlendIndices = nullptr;
}

static void takeOutTheTrash(AiScene aiScene) {
 for (AiAnimation aiAnimation : aiScene.getAnimations()) {
 aiAnimation.getChannels().clear();
 }

 aiScene.getAnimations().clear();
 aiScene.getCameras().clear();
 aiScene.getLights().clear();

 for (AiMaterial aiMaterial : aiScene.getMaterials()) {
 aiMaterial.getProperties().clear();
 }

 aiScene.getMaterials().clear();

 for (AiMesh aiMesh : aiScene.getMeshes()) {
 for (AiBone aiBone : aiMesh.getBones()) {
 aiBone.getBoneWeights().clear();
 }

 aiMesh.getBones().clear();
 }

 aiScene.getMeshes().clear();
 AiNode aiNode = aiScene.getSceneRoot(new AiBuiltInWrapperProvider());
 takeOutTheTrash(aiNode);
}

static void takeOutTheTrash(AiNode aiNode1) {
 for (AiNode aiNode0 : aiNode1.getChildren()) {
 takeOutTheTrash(aiNode0);
 }

 aiNode1.getChildren().clear();
}

private
static class LibraryLoader extends JassimpLibraryLoader {
 void loadLibrary() {
 if (System.getProperty("os.name").contains("OS X")) {
 System.loadLibrary("jassimp");
 } else if (System.getProperty("os.name").startsWith("Win")) {
 if (System.getProperty("sun.arch.data.model") == "64")) {
 System.loadLibrary("jassimp64");
 }
 else {
 System.loadLibrary("jassimp32");
 }
 } else if (System.getProperty("sun.arch.data.model") == "64")) {
 System.loadLibrary("jassimp64");
 }
 else {
 System.loadLibrary("jassimp32");
 }
 }
}

public static enum LoadMode {
 Normal, StaticMesh, AnimationOnly;
}
}
} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
