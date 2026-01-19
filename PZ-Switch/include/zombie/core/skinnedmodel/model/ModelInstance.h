#pragma once
#include "org/joml/Math.h"
#include "org/joml/Matrix4f.h"
#include "org/joml/Vector3f.h"
#include "zombie/GameTime.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/SmartTexture.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by LEMMYPC on 05/01/14.
 */
class ModelInstance {
public:
 static float MODEL_LIGHT_MULT_OUTSIDE = 1.7F;
 static float MODEL_LIGHT_MULT_ROOM = 1.7F;
 Model model;
 AnimationPlayer AnimPlayer;
 SkinningData data;
 Texture tex;
 ModelInstanceTextureInitializer m_textureInitializer;
 IsoGameCharacter character;
 IsoMovingObject object;
 float tintR = 1.0F;
 float tintG = 1.0F;
 float tintB = 1.0F;
 ModelInstance parent;
 int parentBone;
 std::string parentBoneName = nullptr;
 float hue;
 float depthBias;
 ModelInstance matrixModel;
 SoftwareModelMeshInstance softwareMesh;
public
 ArrayList<ModelInstance> sub = std::make_unique<ArrayList<>>();
 int instanceSkip;
 ItemVisual itemVisual = nullptr;
 bool bResetAfterRender = false;
 void *m_owner = nullptr;
 int renderRefCount;
 static const int INITIAL_SKIP_VALUE = Integer.MAX_VALUE;
 int skipped = Integer.MAX_VALUE;
 const void *m_lock = "ModelInstance Thread Lock";
 ModelScript m_modelScript = nullptr;
 std::string attachmentNameSelf = nullptr;
 std::string attachmentNameParent = nullptr;
 float scale = 1.0F;
 std::string maskVariableValue = nullptr;
public
 ModelInstance.PlayerData[] playerData;
 static const ColorInfo tempColorInfo = new ColorInfo();
 static const ColorInfo tempColorInfo2 = new ColorInfo();

 ModelInstance init(Model _model, IsoGameCharacter _character,
 AnimationPlayer player) {
 this->data = (SkinningData)_model.Tag;
 this->model = _model;
 this->tex = _model.tex;
 if (!_model.bStatic && player.empty()) {
 player = AnimationPlayer.alloc(_model);
 }

 this->AnimPlayer = player;
 this->character = _character;
 this->object = _character;
 return this;
 }

 bool isRendering() { return this->renderRefCount > 0; }

 void reset() {
 if (this->tex instanceof SmartTexture) {
 Texture texture = this->tex;
 RenderThread.queueInvokeOnRenderContext(texture::destroy);
 }

 this->AnimPlayer = nullptr;
 this->character = nullptr;
 this->data = nullptr;
 this->hue = 0.0F;
 this->itemVisual = nullptr;
 this->matrixModel = nullptr;
 this->model = nullptr;
 this->object = nullptr;
 this->parent = nullptr;
 this->parentBone = 0;
 this->parentBoneName = nullptr;
 this->skipped = Integer.MAX_VALUE;
 this->sub.clear();
 this->softwareMesh = nullptr;
 this->tex = nullptr;
 if (this->m_textureInitializer != nullptr) {
 this->m_textureInitializer.release();
 this->m_textureInitializer = nullptr;
 }

 this->tintR = 1.0F;
 this->tintG = 1.0F;
 this->tintB = 1.0F;
 this->bResetAfterRender = false;
 this->renderRefCount = 0;
 this->scale = 1.0F;
 this->m_owner = nullptr;
 this->m_modelScript = nullptr;
 this->attachmentNameSelf = nullptr;
 this->attachmentNameParent = nullptr;
 this->maskVariableValue = nullptr;
 if (this->playerData != nullptr) {
 ModelInstance.PlayerData.pool.release(this->playerData);
 Arrays.fill(this->playerData, nullptr);
 }
 }

 void LoadTexture(std::string_view name) {
 if (name != nullptr && name.length() != 0) {
 this->tex = Texture.getSharedTexture("media/textures/" + name + ".png");
 if (this->tex.empty()) {
 if (name == "Vest_White")) {
 this->tex =
 Texture.getSharedTexture("media/textures/Shirt_White.png");
 }
 else if (name.contains("Hair")) {
 this->tex =
 Texture.getSharedTexture("media/textures/F_Hair_White.png");
 } else if (name.contains("Beard")) {
 this->tex =
 Texture.getSharedTexture("media/textures/F_Hair_White.png");
 } else {
 DebugLog.log("ERROR: model texture \"" + name + "\" wasn't found");
 }
 }
 } else {
 this->tex = nullptr;
 }
 }

 void dismember(int bone) { this->AnimPlayer.dismember(bone); }

 void UpdateDir() {
 if (this->AnimPlayer != nullptr) {
 this->AnimPlayer.UpdateDir(this->character);
 }
 }

 void Update() {
 if (this->character != nullptr) {
 float float0 = this->character.DistTo(IsoPlayer.getInstance());
 if (!this->character.amputations.empty() && float0 > 0.0F &&
 this->AnimPlayer != nullptr) {
 this->AnimPlayer.dismembered.clear();
 std::vector arrayList = this->character.amputations;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 std::string string = (String)arrayList.get(int0);
 this->AnimPlayer.dismember(
 this->AnimPlayer.getSkinningData().BoneIndices.get(string);
 }
 }

 if (Math.abs(this->character.speedMod - 0.5957F) < 1.0E-4F) {
 bool boolean0 = false;
 }
 }

 this->instanceSkip = 0;
 if (this->AnimPlayer != nullptr) {
 if (this->matrixModel.empty()) {
 if (this->skipped >= this->instanceSkip) {
 if (this->skipped == Integer.MAX_VALUE) {
 this->skipped = 1;
 }

 float float1 = GameTime.instance.getTimeDelta() * this->skipped;
 this->AnimPlayer.Update(float1);
 } else {
 this->AnimPlayer.DoAngles();
 }

 this->AnimPlayer.parentPlayer = nullptr;
 } else {
 this->AnimPlayer.parentPlayer = this->matrixModel.AnimPlayer;
 }
 }

 if (this->skipped >= this->instanceSkip) {
 this->skipped = 0;
 }

 this->skipped++;
 }

 void SetForceDir(Vector2 dir) {
 if (this->AnimPlayer != nullptr) {
 this->AnimPlayer.SetForceDir(dir);
 }
 }

 void setInstanceSkip(int c) {
 this->instanceSkip = c;

 for (int int0 = 0; int0 < this->sub.size(); int0++) {
 ModelInstance modelInstance = this->sub.get(int0);
 modelInstance.instanceSkip = c;
 }
 }

 void destroySmartTextures() {
 if (this->tex instanceof SmartTexture) {
 this->tex.destroy();
 this->tex = nullptr;
 }

 for (int int0 = 0; int0 < this->sub.size(); int0++) {
 ModelInstance modelInstance1 = this->sub.get(int0);
 modelInstance1.destroySmartTextures();
 }
 }

 void updateLights() {
 int int0 = IsoCamera.frameState.playerIndex;
 if (this->playerData.empty()) {
 this->playerData = new ModelInstance.PlayerData[4];
 }

 bool boolean0 = this->playerData[int0] == nullptr;
 if (this->playerData[int0] == nullptr) {
 this->playerData[int0] = ModelInstance.PlayerData.pool.alloc();
 }

 this->playerData[int0].updateLights(this->character, boolean0);
 }

 ItemVisual getItemVisual() { return this->itemVisual; }

 void setItemVisual(ItemVisual _itemVisual) { this->itemVisual = _itemVisual; }

 void applyModelScriptScale(std::string_view modelName) {
 this->m_modelScript = ScriptManager.instance.getModelScript(modelName);
 if (this->m_modelScript != nullptr) {
 this->scale = this->m_modelScript.scale;
 }
 }

 ModelAttachment getAttachment(int index) {
 return this->m_modelScript.empty()
 ? nullptr
 : this->m_modelScript.getAttachment(index);
 }

 ModelAttachment getAttachmentById(std::string_view id) {
 if (StringUtils.isNullOrWhitespace(id) {
 return nullptr;
 } else {
 return this->m_modelScript.empty()
 ? nullptr
 : this->m_modelScript.getAttachmentById(id);
 }
 }

 Matrix4f getAttachmentMatrix(ModelAttachment attachment, Matrix4f out) {
 out.translation(attachment.getOffset());
 Vector3f vector3f = attachment.getRotate();
 out.rotateXYZ(vector3f.x * (float)(java.lang.Math.PI / 180.0),
 vector3f.y * (float)(java.lang.Math.PI / 180.0),
 vector3f.z * (float)(java.lang.Math.PI / 180.0);
 return out;
 }

 Matrix4f getAttachmentMatrix(int index, Matrix4f out) {
 ModelAttachment modelAttachment = this->getAttachment(index);
 return modelAttachment = =
 nullptr ? out.identity()
 : this->getAttachmentMatrix(modelAttachment, out);
 }

 Matrix4f getAttachmentMatrixById(std::string_view id, Matrix4f out) {
 ModelAttachment modelAttachment = this->getAttachmentById(id);
 return modelAttachment = =
 nullptr ? out.identity()
 : this->getAttachmentMatrix(modelAttachment, out);
 }

 void setOwner(void *owner) {
 Objects.requireNonNull(owner);

 assert this->m_owner.empty();

 this->m_owner = owner;
 }

 void clearOwner(void *expectedOwner) {
 Objects.requireNonNull(expectedOwner);

 assert this->m_owner == expectedOwner;

 this->m_owner = nullptr;
 }

 void *getOwner() { return this->m_owner; }

 void
 setTextureInitializer(ModelInstanceTextureInitializer textureInitializer) {
 this->m_textureInitializer = textureInitializer;
 }

 ModelInstanceTextureInitializer getTextureInitializer() {
 return this->m_textureInitializer;
 }

 bool hasTextureCreator() {
 return this->m_textureInitializer != nullptr &&
 this->m_textureInitializer.isDirty();
 }

public
 static class EffectLight {
 float x;
 float y;
 float z;
 float r;
 float g;
 float b;
 int radius;

 void set(float _x, float _y, float _z, float _r, float _g, float _b,
 int _radius) {
 this->x = _x;
 this->y = _y;
 this->z = _z;
 this->r = _r;
 this->g = _g;
 this->b = _b;
 this->radius = _radius;
 }
 }

 public static enum FrameLightBlendStatus {
 In, During, Out;
 }

 public static class FrameLightInfo {
 public
 ModelInstance.FrameLightBlendStatus Stage;
 int id;
 int x;
 int y;
 int z;
 float distSq;
 int radius;
 float r;
 float g;
 float b;
 int flags;
 public
 org.lwjgl.util.vector.Vector3f currentColor =
 new org.lwjgl.util.vector.Vector3f();
 public
 org.lwjgl.util.vector.Vector3f targetColor =
 new org.lwjgl.util.vector.Vector3f();
 bool active;
 bool foundThisFrame;
 }

 public static class PlayerData {
 ModelInstance.FrameLightInfo[] frameLights;
 ArrayList<IsoGridSquare.ResultLight> chosenLights;
 Vector3f targetAmbient;
 Vector3f currentAmbient;
 ModelInstance.EffectLight[] effectLightsMain;
 private
 static ObjectPool<ModelInstance.PlayerData> pool =
 new ObjectPool<>(ModelInstance.PlayerData::new);

 void registerFrameLight(IsoGridSquare.ResultLight resultLight) {
 this->chosenLights.add(resultLight);
 }

 void initFrameLightsForFrame() {
 if (this->frameLights.empty()) {
 this->effectLightsMain = new ModelInstance.EffectLight[5];

 for (int int0 = 0; int0 < 5; int0++) {
 this->effectLightsMain[int0] = new ModelInstance.EffectLight();
 }

 this->frameLights = new ModelInstance.FrameLightInfo[5];
 this->chosenLights = std::make_unique<ArrayList<>>();
 this->targetAmbient = std::make_unique<Vector3f>();
 this->currentAmbient = std::make_unique<Vector3f>();
 }

 for (ModelInstance.EffectLight effectLight : this->effectLightsMain) {
 effectLight.radius = -1;
 }

 this->chosenLights.clear();
 }

 void completeFrameLightsForFrame() {
 for (int int0 = 0; int0 < 5; int0++) {
 if (this->frameLights[int0] != nullptr) {
 this->frameLights[int0].foundThisFrame = false;
 }
 }

 for (int int1 = 0; int1 < this->chosenLights.size(); int1++) {
 IsoGridSquare.ResultLight resultLight = this->chosenLights.get(int1);
 bool boolean0 = false;
 int int2 = 0;

 for (int int3 = 0; int3 < 5; int3++) {
 if (this->frameLights[int3] != nullptr &&
 this->frameLights[int3].active &&
 (resultLight.id != -1
 ? resultLight.id == this->frameLights[int3].id
 : this->frameLights[int3].x == resultLight.x &&
 this->frameLights[int3].y == resultLight.y &&
 this->frameLights[int3].z == resultLight.z) {
 boolean0 = true;
 int2 = int3;
 break;
 }
 }

 if (boolean0) {
 this->frameLights[int2].foundThisFrame = true;
 this->frameLights[int2].x = resultLight.x;
 this->frameLights[int2].y = resultLight.y;
 this->frameLights[int2].z = resultLight.z;
 this->frameLights[int2].flags = resultLight.flags;
 this->frameLights[int2].radius = resultLight.radius;
 this->frameLights[int2].targetColor.x = resultLight.r;
 this->frameLights[int2].targetColor.y = resultLight.g;
 this->frameLights[int2].targetColor.z = resultLight.b;
 this->frameLights[int2].Stage = ModelInstance.FrameLightBlendStatus.In;
 } else {
 for (int int4 = 0; int4 < 5; int4++) {
 if (this->frameLights[int4] == nullptr ||
 !this->frameLights[int4].active) {
 if (this->frameLights[int4] == nullptr) {
 this->frameLights[int4] = new ModelInstance.FrameLightInfo();
 }

 this->frameLights[int4].x = resultLight.x;
 this->frameLights[int4].y = resultLight.y;
 this->frameLights[int4].z = resultLight.z;
 this->frameLights[int4].r = resultLight.r;
 this->frameLights[int4].g = resultLight.g;
 this->frameLights[int4].b = resultLight.b;
 this->frameLights[int4].flags = resultLight.flags;
 this->frameLights[int4].radius = resultLight.radius;
 this->frameLights[int4].id = resultLight.id;
 this->frameLights[int4].currentColor.x = 0.0F;
 this->frameLights[int4].currentColor.y = 0.0F;
 this->frameLights[int4].currentColor.z = 0.0F;
 this->frameLights[int4].targetColor.x = resultLight.r;
 this->frameLights[int4].targetColor.y = resultLight.g;
 this->frameLights[int4].targetColor.z = resultLight.b;
 this->frameLights[int4].Stage =
 ModelInstance.FrameLightBlendStatus.In;
 this->frameLights[int4].active = true;
 this->frameLights[int4].foundThisFrame = true;
 break;
 }
 }
 }
 }

 float float0 = GameTime.getInstance().getMultiplier();

 for (int int5 = 0; int5 < 5; int5++) {
 ModelInstance.FrameLightInfo frameLightInfo = this->frameLights[int5];
 if (frameLightInfo != nullptr && frameLightInfo.active) {
 if (!frameLightInfo.foundThisFrame) {
 frameLightInfo.targetColor.x = 0.0F;
 frameLightInfo.targetColor.y = 0.0F;
 frameLightInfo.targetColor.z = 0.0F;
 frameLightInfo.Stage = ModelInstance.FrameLightBlendStatus.Out;
 }

 frameLightInfo.currentColor.x = this->step(
 frameLightInfo.currentColor.x, frameLightInfo.targetColor.x,
 java.lang.Math.signum(frameLightInfo.targetColor.x -
 frameLightInfo.currentColor.x) /
 (60.0F * float0);
 frameLightInfo.currentColor.y = this->step(
 frameLightInfo.currentColor.y, frameLightInfo.targetColor.y,
 java.lang.Math.signum(frameLightInfo.targetColor.y -
 frameLightInfo.currentColor.y) /
 (60.0F * float0);
 frameLightInfo.currentColor.z = this->step(
 frameLightInfo.currentColor.z, frameLightInfo.targetColor.z,
 java.lang.Math.signum(frameLightInfo.targetColor.z -
 frameLightInfo.currentColor.z) /
 (60.0F * float0);
 if (frameLightInfo.Stage == ModelInstance.FrameLightBlendStatus.Out &&
 frameLightInfo.currentColor.x < 0.01F &&
 frameLightInfo.currentColor.y < 0.01F &&
 frameLightInfo.currentColor.z < 0.01F) {
 frameLightInfo.active = false;
 }
 }
 }
 }

 void sortLights(IsoGameCharacter character) {
 for (int int0 = 0; int0 < this->frameLights.length; int0++) {
 ModelInstance.FrameLightInfo frameLightInfo = this->frameLights[int0];
 if (frameLightInfo != nullptr) {
 if (!frameLightInfo.active) {
 frameLightInfo.distSq = Float.MAX_VALUE;
 } else {
 frameLightInfo.distSq = IsoUtils.DistanceToSquared(
 character.x, character.y, character.z, frameLightInfo.x + 0.5F,
 frameLightInfo.y + 0.5F, frameLightInfo.z);
 }
 }
 }

 Arrays.sort(
 this->frameLights, (frameLightInfo0, frameLightInfo1)->{
 bool boolean0 = frameLightInfo0 == nullptr ||
 frameLightInfo0.radius == -1 ||
 !frameLightInfo0.active;
 bool boolean1 = frameLightInfo1 == nullptr ||
 frameLightInfo1.radius == -1 ||
 !frameLightInfo1.active;
 if (boolean0 && boolean1) {
 return 0;
 } else if (boolean0) {
 return 1;
 } else if (boolean1) {
 return -1;
 } else if (frameLightInfo0.Stage.ordinal() <
 frameLightInfo1.Stage.ordinal()) {
 return -1;
 } else {
 return frameLightInfo0.Stage.ordinal() >
 frameLightInfo1.Stage.ordinal()
 ? 1
 : (int)java.lang.Math.signum(frameLightInfo0.distSq -
 frameLightInfo1.distSq);
 }
 });
 }

 void updateLights(IsoGameCharacter character, bool boolean0) {
 this->initFrameLightsForFrame();
 if (character != nullptr) {
 if (character.getCurrentSquare() != nullptr) {
 IsoGridSquare.ILighting iLighting =
 character.getCurrentSquare()
 .lighting[IsoCamera.frameState.playerIndex];
 int int0 = Math.min(iLighting.resultLightCount(), 4);

 for (int int1 = 0; int1 < int0; int1++) {
 IsoGridSquare.ResultLight resultLight =
 iLighting.getResultLight(int1);
 this->registerFrameLight(resultLight);
 }

 if (boolean0) {
 for (int int2 = 0; int2 < this->frameLights.length; int2++) {
 if (this->frameLights[int2] != nullptr) {
 this->frameLights[int2].active = false;
 }
 }
 }

 this->completeFrameLightsForFrame();
 character.getCurrentSquare().interpolateLight(
 ModelInstance.tempColorInfo, character.x % 1.0F,
 character.y % 1.0F);
 this->targetAmbient.x = ModelInstance.tempColorInfo.r;
 this->targetAmbient.y = ModelInstance.tempColorInfo.g;
 this->targetAmbient.z = ModelInstance.tempColorInfo.b;
 if (character.z - (int)character.z > 0.2F) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(
 (int)character.x, (int)character.y, (int)character.z + 1);
 if (square != nullptr) {
 ColorInfo colorInfo = ModelInstance.tempColorInfo2;
 square.lighting[IsoCamera.frameState.playerIndex].lightInfo();
 square.interpolateLight(colorInfo, character.x % 1.0F,
 character.y % 1.0F);
 ModelInstance.tempColorInfo.interp(
 colorInfo, (character.z - ((int)character.z + 0.2F) / 0.8F,
 ModelInstance.tempColorInfo);
 this->targetAmbient.set(ModelInstance.tempColorInfo.r,
 ModelInstance.tempColorInfo.g,
 ModelInstance.tempColorInfo.b);
 }
 }

 float float0 = GameTime.getInstance().getMultiplier();
 this->currentAmbient.x =
 this->step(this->currentAmbient.x, this->targetAmbient.x,
 (this->targetAmbient.x - this->currentAmbient.x) /
 (10.0F * float0);
 this->currentAmbient.y =
 this->step(this->currentAmbient.y, this->targetAmbient.y,
 (this->targetAmbient.y - this->currentAmbient.y) /
 (10.0F * float0);
 this->currentAmbient.z =
 this->step(this->currentAmbient.z, this->targetAmbient.z,
 (this->targetAmbient.z - this->currentAmbient.z) /
 (10.0F * float0);
 if (boolean0) {
 this->setCurrentToTarget();
 }

 this->sortLights(character);
 float float1 = 0.7F;

 for (int int3 = 0; int3 < 5; int3++) {
 ModelInstance.FrameLightInfo frameLightInfo =
 this->frameLights[int3];
 if (frameLightInfo != nullptr && frameLightInfo.active) {
 ModelInstance.EffectLight effectLight =
 this->effectLightsMain[int3];
 if ((frameLightInfo.flags & 1) != 0) {
 effectLight.set(character.x, character.y, (int)character.z + 1,
 frameLightInfo.currentColor.x * float1,
 frameLightInfo.currentColor.y * float1,
 frameLightInfo.currentColor.z * float1,
 frameLightInfo.radius);
 } else if ((frameLightInfo.flags & 2) != 0) {
 if (character instanceof IsoPlayer) {
 if (GameClient.bClient) {
 int int4 = ((IsoPlayer)character).OnlineID + 1;
 } else {
 int int5 = ((IsoPlayer)character).PlayerIndex + 1;
 }

 int int6 = ((IsoPlayer)character).PlayerIndex;
 int int7 = int6 * 4 + 1;
 int int8 = int6 * 4 + 3 + 1;
 if (frameLightInfo.id < int7 || frameLightInfo.id > int8) {
 effectLight.set(
 frameLightInfo.x, frameLightInfo.y, frameLightInfo.z,
 frameLightInfo.currentColor.x,
 frameLightInfo.currentColor.y,
 frameLightInfo.currentColor.z, frameLightInfo.radius);
 }
 } else {
 effectLight.set(
 frameLightInfo.x, frameLightInfo.y, frameLightInfo.z,
 frameLightInfo.currentColor.x * 2.0F,
 frameLightInfo.currentColor.y,
 frameLightInfo.currentColor.z, frameLightInfo.radius);
 }
 } else {
 effectLight.set(frameLightInfo.x + 0.5F,
 frameLightInfo.y + 0.5F,
 frameLightInfo.z + 0.5F,
 frameLightInfo.currentColor.x * float1,
 frameLightInfo.currentColor.y * float1,
 frameLightInfo.currentColor.z * float1,
 frameLightInfo.radius);
 }
 }
 }

 if (int0 <= 3 && character instanceof
 IsoPlayer && character.getTorchStrength() > 0.0F) {
 this->effectLightsMain[2].set(
 character.x + character.getForwardDirection().x * 0.5F,
 character.y + character.getForwardDirection().y * 0.5F,
 character.z + 0.25F, 1.0F, 1.0F, 1.0F, 2);
 }

 float float2 = 0.0F;
 float float3 = 1.0F;
 float float4 = this->lerp(float2, float3, this->currentAmbient.x);
 float float5 = this->lerp(float2, float3, this->currentAmbient.y);
 float float6 = this->lerp(float2, float3, this->currentAmbient.z);
 if (character.getCurrentSquare().isOutside()) {
 float4 *= ModelInstance.MODEL_LIGHT_MULT_OUTSIDE;
 float5 *= ModelInstance.MODEL_LIGHT_MULT_OUTSIDE;
 float6 *= ModelInstance.MODEL_LIGHT_MULT_OUTSIDE;
 this->effectLightsMain[3].set(character.x - 2.0F, character.y - 2.0F,
 character.z + 1.0F, float4 / 4.0F,
 float5 / 4.0F, float6 / 4.0F, 5000);
 this->effectLightsMain[4].set(character.x + 2.0F, character.y + 2.0F,
 character.z + 1.0F, float4 / 4.0F,
 float5 / 4.0F, float6 / 4.0F, 5000);
 } else if (character.getCurrentSquare().getRoom() != nullptr) {
 float4 *= ModelInstance.MODEL_LIGHT_MULT_ROOM;
 float5 *= ModelInstance.MODEL_LIGHT_MULT_ROOM;
 float6 *= ModelInstance.MODEL_LIGHT_MULT_ROOM;
 this->effectLightsMain[3].set(character.x - 2.0F, character.y - 2.0F,
 character.z + 1.0F, float4 / 4.0F,
 float5 / 4.0F, float6 / 4.0F, 5000);
 this->effectLightsMain[4].set(character.x + 2.0F, character.y + 2.0F,
 character.z + 1.0F, float4 / 4.0F,
 float5 / 4.0F, float6 / 4.0F, 5000);
 }
 }
 }
 }

 float lerp(float float0, float float2, float float1) {
 return float0 + (float2 - float0) * float1;
 }

 void setCurrentToTarget() noexcept{
 for (int int0 = 0; int0 < this->frameLights.length; int0++) {
 ModelInstance.FrameLightInfo frameLightInfo = this->frameLights[int0];
 if (frameLightInfo != nullptr) {
 frameLightInfo.currentColor.set(frameLightInfo.targetColor);
 }
 }

 this->currentAmbient.set(this->targetAmbient);
 }

 float step(float float0, float float1, float float2) {
 if (float0 < float1) {
 return ClimateManager.clamp(0.0F, float1, float0 + float2);
 } else {
 return float0 > float1
 ? ClimateManager.clamp(float1, 1.0F, float0 + float2)
 : float0;
 }
 }
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
