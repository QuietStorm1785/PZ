#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL13.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/GameProfiler.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/particle/MuzzleFlash.h"
#include "zombie/core/skinnedmodel/ModelCamera.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/core/skinnedmodel/shader/ShaderManager.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/Vector3.h"
#include "zombie/iso/sprite/SkyBox.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Model : public Asset {
public:
 std::string Name;
 const ModelMesh Mesh;
 Shader Effect;
 void* Tag;
 bool bStatic = false;
 Texture tex = nullptr;
 SoftwareModelMesh softwareMesh;
 static const FloatBuffer m_staticReusableFloatBuffer = BufferUtils.createFloatBuffer(128);
 static const Matrix4f IDENTITY = new Matrix4f();
 public static Color[] debugDrawColours = new Color[]{
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 new Color();
 };
 public Model.ModelAssetParams assetParams;
 static Vector3 tempo = std::make_unique<Vector3>();
 static const AssetType ASSET_TYPE = new AssetType("Model");

 public Model(AssetPath path, AssetManager manager, Model.ModelAssetParams params) {
 super(path, manager);
 this->assetParams = params;
 this->bStatic = this->assetParams != nullptr && this->assetParams.bStatic;
 ModelMesh.MeshAssetParams meshAssetParams = new ModelMesh.MeshAssetParams();
 meshAssetParams.bStatic = this->bStatic;
 meshAssetParams.animationsMesh = this->assetParams.empty() ? nullptr : this->assetParams.animationsModel;
 this->Mesh = (ModelMesh)MeshAssetManager.instance.load(new AssetPath(params.meshName), meshAssetParams);
 if (!StringUtils.isNullOrWhitespace(params.textureName) {
 if (params.textureName.contains("media/")) {
 this->tex = Texture.getSharedTexture(params.textureName, params.textureFlags);
 } else {
 this->tex = Texture.getSharedTexture("media/textures/" + params.textureName + ".png", params.textureFlags);
 }
 }

 if (!StringUtils.isNullOrWhitespace(params.shaderName) {
 this->CreateShader(params.shaderName);
 }

 this->onCreated(this->Mesh.getState());
 this->addDependency(this->Mesh);
 if (this->isReady()) {
 this->Tag = this->Mesh.skinningData;
 this->softwareMesh = this->Mesh.softwareMesh;
 this->assetParams = nullptr;
 }
 }

 static void VectorToWorldCoords(IsoGameCharacter character, Vector3 vec) {
 AnimationPlayer animationPlayer = character.getAnimationPlayer();
 float float0 = animationPlayer.getRenderedAngle();
 vec.x = -vec.x;
 vec.rotatey(float0);
 float float1 = vec.y;
 vec.y = vec.z;
 vec.z = float1 * 0.6F;
 vec.x *= 1.5F;
 vec.y *= 1.5F;
 vec.x = vec.x + character.x;
 vec.y = vec.y + character.y;
 vec.z = vec.z + character.z;
 }

 static void BoneToWorldCoords(IsoGameCharacter character, int boneIndex, Vector3 vec) {
 AnimationPlayer animationPlayer = character.getAnimationPlayer();
 vec.x = animationPlayer.modelTransforms[boneIndex].m03;
 vec.y = animationPlayer.modelTransforms[boneIndex].m13;
 vec.z = animationPlayer.modelTransforms[boneIndex].m23;
 VectorToWorldCoords(character, vec);
 }

 static void BoneYDirectionToWorldCoords(IsoGameCharacter character, int boneIndex, Vector3 vec, float length) {
 AnimationPlayer animationPlayer = character.getAnimationPlayer();
 vec.x = animationPlayer.modelTransforms[boneIndex].m01 * length;
 vec.y = animationPlayer.modelTransforms[boneIndex].m11 * length;
 vec.z = animationPlayer.modelTransforms[boneIndex].m21 * length;
 vec.x = vec.x + animationPlayer.modelTransforms[boneIndex].m03;
 vec.y = vec.y + animationPlayer.modelTransforms[boneIndex].m13;
 vec.z = vec.z + animationPlayer.modelTransforms[boneIndex].m23;
 VectorToWorldCoords(character, vec);
 }

 static void VectorToWorldCoords(ModelSlotRenderData slotData, Vector3 vec) {
 float float0 = slotData.animPlayerAngle;
 vec.x = -vec.x;
 vec.rotatey(float0);
 float float1 = vec.y;
 vec.y = vec.z;
 vec.z = float1 * 0.6F;
 vec.x *= 1.5F;
 vec.y *= 1.5F;
 vec.x = vec.x + slotData.x;
 vec.y = vec.y + slotData.y;
 vec.z = vec.z + slotData.z;
 }

 static void BoneToWorldCoords(ModelSlotRenderData slotData, int boneIndex, Vector3 vec) {
 AnimationPlayer animationPlayer = slotData.animPlayer;
 vec.x = animationPlayer.modelTransforms[boneIndex].m03;
 vec.y = animationPlayer.modelTransforms[boneIndex].m13;
 vec.z = animationPlayer.modelTransforms[boneIndex].m23;
 VectorToWorldCoords(slotData, vec);
 }

 static void CharacterModelCameraBegin(ModelSlotRenderData slotData) {
 ModelCamera.instance.Begin();
 if (slotData.bInVehicle) {
 GL11.glMatrixMode(5888);
 GL11.glTranslatef(0.0F, slotData.centerOfMassY, 0.0F);
 GL11.glMatrixMode(5888);
 GL11.glRotatef(slotData.vehicleAngleZ, 0.0F, 0.0F, 1.0F);
 GL11.glRotatef(slotData.vehicleAngleY, 0.0F, 1.0F, 0.0F);
 GL11.glRotatef(slotData.vehicleAngleX, 1.0F, 0.0F, 0.0F);
 GL11.glRotatef(180.0F, 0.0F, 1.0F, 0.0F);
 uint8_t byte0 = -1;
 GL11.glTranslatef(slotData.inVehicleX, slotData.inVehicleY, slotData.inVehicleZ * byte0);
 GL11.glScalef(1.5F, 1.5F, 1.5F);
 }
 }

 static void CharacterModelCameraEnd() {
 ModelCamera.instance.End();
 }

 void DrawChar(ModelSlotRenderData slotData, ModelInstanceRenderData instData) {
 if (!DebugOptions.instance.Character.Debug.Render.SkipCharacters.getValue()) {
 if (slotData.character == IsoPlayer.getInstance()) {
 bool boolean0 = false;
 }

 if (!(slotData.alpha < 0.01F) {
 if (slotData.animPlayer != nullptr) {
 if (Core.bDebug && GameKeyboard.isKeyDown(199) {
 this->Effect = nullptr;
 }

 if (this->Effect.empty()) {
 this->CreateShader("basicEffect");
 }

 Shader shader0 = this->Effect;
 GL11.glEnable(2884);
 GL11.glCullFace(1028);
 GL11.glEnable(2929);
 GL11.glEnable(3008);
 GL11.glDepthFunc(513);
 GL11.glAlphaFunc(516, 0.01F);
 GL11.glBlendFunc(770, 771);
 if (Core.bDebug && DebugOptions.instance.ModelRenderWireframe.getValue()) {
 GL11.glPolygonMode(1032, 6913);
 GL11.glEnable(2848);
 GL11.glLineWidth(0.75F);
 Shader shader1 = ShaderManager.instance.getOrCreateShader("vehicle_wireframe", this->bStatic);
 if (shader1 != nullptr) {
 shader1.Start();
 if (this->bStatic) {
 shader1.setTransformMatrix(instData.xfrm, true);
 } else {
 shader1.setMatrixPalette(instData.matrixPalette, true);
 }

 this->Mesh.Draw(shader1);
 shader1.End();
 }

 GL11.glPolygonMode(1032, 6914);
 GL11.glDisable(2848);
 } else {
 if (shader0 != nullptr) {
 shader0.Start();
 shader0.startCharacter(slotData, instData);
 }

 if (!DebugOptions.instance.DebugDraw_SkipDrawNonSkinnedModel.getValue()) {
 GameProfiler.getInstance().invokeAndMeasure("Mesh.Draw.Call", shader0, this->Mesh, (shader, modelMesh) -> modelMesh.Draw(shader);
 }

 if (shader0 != nullptr) {
 shader0.End();
 }

 this->drawMuzzleFlash(instData);
 }
 }
 }
 }
 }

 void drawMuzzleFlash(ModelInstanceRenderData modelInstanceRenderData) {
 if (modelInstanceRenderData.m_muzzleFlash) {
 ModelAttachment modelAttachment = modelInstanceRenderData.modelInstance.getAttachmentById("muzzle");
 if (modelAttachment != nullptr) {
 BaseVehicle.Matrix4fObjectPool matrix4fObjectPool = BaseVehicle.TL_matrix4f_pool.get();
 Matrix4f matrix4f0 = matrix4fObjectPool.alloc().set(modelInstanceRenderData.xfrm);
 matrix4f0.transpose();
 Matrix4f matrix4f1 = modelInstanceRenderData.modelInstance.getAttachmentMatrix(modelAttachment, matrix4fObjectPool.alloc());
 matrix4f0.mul(matrix4f1, matrix4f1);
 MuzzleFlash.render(matrix4f1);
 matrix4fObjectPool.release(matrix4f0);
 matrix4fObjectPool.release(matrix4f1);
 }
 }
 }

 void drawVehicleLights(ModelSlotRenderData modelSlotRenderData) {
 for (int int0 = 7; int0 >= 0; int0--) {
 GL13.glActiveTexture(33984 + int0);
 GL11.glDisable(3553);
 }

 GL11.glLineWidth(1.0F);
 GL11.glColor3f(1.0F, 1.0F, 0.0F);
 GL11.glDisable(2929);

 for (int int1 = 0; int1 < 3; int1++) {
 ModelInstance.EffectLight effectLight = modelSlotRenderData.effectLights[int1];
 if (!(effectLight.radius <= 0.0F) {
 float float0 = effectLight.x;
 float float1 = effectLight.y;
 float float2 = effectLight.z;
 float0 *= -54.0F;
 float float3 = float2 * 54.0F;
 float2 = float1 * 54.0F;
 GL11.glBegin(1);
 GL11.glVertex3f(float0, float3, float2);
 GL11.glVertex3f(0.0F, 0.0F, 0.0F);
 GL11.glEnd();
 }
 }

 GL11.glColor3f(1.0F, 1.0F, 1.0F);
 GL11.glEnable(3553);
 GL11.glEnable(2929);
 }

 static void drawBoneMtx(org.lwjgl.util.vector.Matrix4f boneMtx) {
 GL11.glDisable(2929);
 GL11.glDisable(3553);
 GL11.glBegin(1);
 drawBoneMtxInternal(boneMtx);
 GL11.glEnd();
 GL11.glColor3f(1.0F, 1.0F, 1.0F);
 GL11.glEnable(2929);
 }

 static void drawBoneMtxInternal(org.lwjgl.util.vector.Matrix4f matrix4f) {
 float float0 = 0.5F;
 float float1 = 0.15F;
 float float2 = 0.1F;
 float float3 = matrix4f.m03;
 float float4 = matrix4f.m13;
 float float5 = matrix4f.m23;
 float float6 = matrix4f.m00;
 float float7 = matrix4f.m10;
 float float8 = matrix4f.m20;
 float float9 = matrix4f.m01;
 float float10 = matrix4f.m11;
 float float11 = matrix4f.m21;
 float float12 = matrix4f.m02;
 float float13 = matrix4f.m12;
 float float14 = matrix4f.m22;
 drawArrowInternal(float3, float4, float5, float6, float7, float8, float12, float13, float14, float0, float1, float2, 1.0F, 0.0F, 0.0F);
 drawArrowInternal(float3, float4, float5, float9, float10, float11, float12, float13, float14, float0, float1, float2, 0.0F, 1.0F, 0.0F);
 drawArrowInternal(float3, float4, float5, float12, float13, float14, float6, float7, float8, float0, float1, float2, 0.0F, 0.0F, 1.0F);
 }

 private static void drawArrowInternal(
 float float5,
 float float6,
 float float7,
 float float11,
 float float10,
 float float8,
 float float15,
 float float14,
 float float12,
 float float9,
 float float1,
 float float13,
 float float2,
 float float3,
 float float4
 ) {
 float float0 = 1.0F - float1;
 GL11.glColor3f(float2, float3, float4);
 GL11.glVertex3f(float5, float6, float7);
 GL11.glVertex3f(float5 + float11 * float9, float6 + float10 * float9, float7 + float8 * float9);
 GL11.glVertex3f(float5 + float11 * float9, float6 + float10 * float9, float7 + float8 * float9);
 GL11.glVertex3f(
 float5 + (float11 * float0 + float15 * float13) * float9,
 float6 + (float10 * float0 + float14 * float13) * float9,
 float7 + (float8 * float0 + float12 * float13) * float9
 );
 GL11.glVertex3f(float5 + float11 * float9, float6 + float10 * float9, float7 + float8 * float9);
 GL11.glVertex3f(
 float5 + (float11 * float0 - float15 * float13) * float9,
 float6 + (float10 * float0 - float14 * float13) * float9,
 float7 + (float8 * float0 - float12 * float13) * float9
 );
 }

 void debugDrawLightSource(IsoLightSource ls, float cx, float cy, float cz, float radians) {
 debugDrawLightSource(ls.x, ls.y, ls.z, cx, cy, cz, radians);
 }

 static void debugDrawLightSource(float lx, float ly, float lz, float cx, float cy, float cz, float radians) {
 float float0 = lx - cx + 0.5F;
 float float1 = ly - cy + 0.5F;
 float float2 = lz - cz + 0.0F;
 float0 *= 0.67F;
 float1 *= 0.67F;
 float float3 = (float)(float0 * Math.cos(radians) - float1 * Math.sin(radians);
 float1 = (float)(float0 * Math.sin(radians) + float1 * Math.cos(radians);
 float0 = float3 * -1.0F;
 GL11.glDisable(3553);
 GL11.glDisable(2929);
 GL11.glBegin(1);
 GL11.glColor3f(1.0F, 1.0F, 0.0F);
 GL11.glVertex3f(float0, float2, float1);
 GL11.glVertex3f(0.0F, 0.0F, 0.0F);
 GL11.glVertex3f(float0, float2, float1);
 GL11.glVertex3f(float0 + 0.1F, float2, float1);
 GL11.glVertex3f(float0, float2, float1);
 GL11.glVertex3f(float0, float2 + 0.1F, float1);
 GL11.glVertex3f(float0, float2, float1);
 GL11.glVertex3f(float0, float2, float1 + 0.1F);
 GL11.glEnd();
 GL11.glColor3f(1.0F, 1.0F, 1.0F);
 GL11.glEnable(3553);
 GL11.glEnable(2929);
 }

 void DrawVehicle(ModelSlotRenderData slotData, ModelInstanceRenderData instData) {
 if (!DebugOptions.instance.ModelRenderSkipVehicles.getValue()) {
 ModelInstance modelInstance = instData.modelInstance;
 float float0 = slotData.ambientR;
 Texture texture = instData.tex;
 float float1 = instData.tintR;
 float float2 = instData.tintG;
 float float3 = instData.tintB;
 PZGLUtil.checkGLErrorThrow("Model.drawVehicle Enter inst: %s, instTex: %s, slotData: %s", modelInstance, texture, slotData);
 GL11.glEnable(2884);
 GL11.glCullFace(modelInstance.m_modelScript != nullptr && modelInstance.m_modelScript.invertX ? 1029 : 1028);
 GL11.glEnable(2929);
 GL11.glDepthFunc(513);
 ModelCamera.instance.Begin();
 GL11.glMatrixMode(5888);
 GL11.glTranslatef(0.0F, slotData.centerOfMassY, 0.0F);
 Shader shader = this->Effect;
 PZGLUtil.pushAndMultMatrix(5888, instData.xfrm);
 if (Core.bDebug && DebugOptions.instance.ModelRenderWireframe.getValue()) {
 GL11.glPolygonMode(1032, 6913);
 GL11.glEnable(2848);
 GL11.glLineWidth(0.75F);
 shader = ShaderManager.instance.getOrCreateShader("vehicle_wireframe", this->bStatic);
 if (shader != nullptr) {
 shader.Start();
 if (this->bStatic) {
 shader.setTransformMatrix(IDENTITY, false);
 } else {
 shader.setMatrixPalette(instData.matrixPalette, true);
 }

 this->Mesh.Draw(shader);
 shader.End();
 }

 GL11.glDisable(2848);
 PZGLUtil.popMatrix(5888);
 ModelCamera.instance.End();
 } else {
 if (shader != nullptr) {
 shader.Start();
 this->setLights(slotData, 3);
 if (shader.isVehicleShader()) {
 VehicleModelInstance vehicleModelInstance = Type.tryCastTo(modelInstance, VehicleModelInstance.class);
 if (modelInstance instanceof VehicleSubModelInstance) {
 vehicleModelInstance = Type.tryCastTo(modelInstance.parent, VehicleModelInstance.class);
 }

 shader.setTexture(vehicleModelInstance.tex, "Texture0", 0);
 GL11.glTexEnvi(8960, 8704, 7681);
 shader.setTexture(vehicleModelInstance.textureRust, "TextureRust", 1);
 GL11.glTexEnvi(8960, 8704, 7681);
 shader.setTexture(vehicleModelInstance.textureMask, "TextureMask", 2);
 GL11.glTexEnvi(8960, 8704, 7681);
 shader.setTexture(vehicleModelInstance.textureLights, "TextureLights", 3);
 GL11.glTexEnvi(8960, 8704, 7681);
 shader.setTexture(vehicleModelInstance.textureDamage1Overlay, "TextureDamage1Overlay", 4);
 GL11.glTexEnvi(8960, 8704, 7681);
 shader.setTexture(vehicleModelInstance.textureDamage1Shell, "TextureDamage1Shell", 5);
 GL11.glTexEnvi(8960, 8704, 7681);
 shader.setTexture(vehicleModelInstance.textureDamage2Overlay, "TextureDamage2Overlay", 6);
 GL11.glTexEnvi(8960, 8704, 7681);
 shader.setTexture(vehicleModelInstance.textureDamage2Shell, "TextureDamage2Shell", 7);
 GL11.glTexEnvi(8960, 8704, 7681);

 try {
 if (Core.getInstance().getPerfReflectionsOnLoad()) {
 shader.setTexture((Texture)SkyBox.getInstance().getTextureCurrent(), "TextureReflectionA", 8);
 GL11.glTexEnvi(8960, 8704, 7681);
 GL11.glGetError();
 }
 } catch (Throwable throwable0) {
 }

 try {
 if (Core.getInstance().getPerfReflectionsOnLoad()) {
 shader.setTexture((Texture)SkyBox.getInstance().getTexturePrev(), "TextureReflectionB", 9);
 GL11.glTexEnvi(8960, 8704, 7681);
 GL11.glGetError();
 }
 } catch (Throwable throwable1) {
 }

 shader.setReflectionParam(SkyBox.getInstance().getTextureShift(), vehicleModelInstance.refWindows, vehicleModelInstance.refBody);
 shader.setTextureUninstall1(vehicleModelInstance.textureUninstall1);
 shader.setTextureUninstall2(vehicleModelInstance.textureUninstall2);
 shader.setTextureLightsEnables1(vehicleModelInstance.textureLightsEnables1);
 shader.setTextureLightsEnables2(vehicleModelInstance.textureLightsEnables2);
 shader.setTextureDamage1Enables1(vehicleModelInstance.textureDamage1Enables1);
 shader.setTextureDamage1Enables2(vehicleModelInstance.textureDamage1Enables2);
 shader.setTextureDamage2Enables1(vehicleModelInstance.textureDamage2Enables1);
 shader.setTextureDamage2Enables2(vehicleModelInstance.textureDamage2Enables2);
 shader.setMatrixBlood1(vehicleModelInstance.matrixBlood1Enables1, vehicleModelInstance.matrixBlood1Enables2);
 shader.setMatrixBlood2(vehicleModelInstance.matrixBlood2Enables1, vehicleModelInstance.matrixBlood2Enables2);
 shader.setTextureRustA(vehicleModelInstance.textureRustA);
 shader.setTexturePainColor(vehicleModelInstance.painColor, slotData.alpha);
 if (this->bStatic) {
 shader.setTransformMatrix(IDENTITY, false);
 } else {
 shader.setMatrixPalette(instData.matrixPalette, true);
 }
 } else if (modelInstance instanceof VehicleSubModelInstance) {
 GL13.glActiveTexture(33984);
 shader.setTexture(texture, "Texture", 0);
 shader.setShaderAlpha(slotData.alpha);
 if (this->bStatic) {
 shader.setTransformMatrix(IDENTITY, false);
 }
 } else {
 GL13.glActiveTexture(33984);
 shader.setTexture(texture, "Texture", 0);
 }

 shader.setAmbient(float0);
 shader.setTint(float1, float2, float3);
 this->Mesh.Draw(shader);
 shader.End();
 }

 if (Core.bDebug && DebugOptions.instance.ModelRenderLights.getValue() && instData == slotData.modelData.get(0) {
 this->drawVehicleLights(slotData);
 }

 PZGLUtil.popMatrix(5888);
 ModelCamera.instance.End();
 PZGLUtil.checkGLErrorThrow("Model.drawVehicle Exit inst: %s, instTex: %s, slotData: %s", modelInstance, texture, slotData);
 }
 }
 }

 static void debugDrawAxis(float x, float y, float z, float length, float thickness) {
 for (int int0 = 0; int0 < 8; int0++) {
 GL13.glActiveTexture(33984 + int0);
 GL11.glDisable(3553);
 }

 GL11.glDisable(2929);
 GL11.glLineWidth(thickness);
 GL11.glBegin(1);
 GL11.glColor3f(1.0F, 0.0F, 0.0F);
 GL11.glVertex3f(x, y, z);
 GL11.glVertex3f(x + length, y, z);
 GL11.glColor3f(0.0F, 1.0F, 0.0F);
 GL11.glVertex3f(x, y, z);
 GL11.glVertex3f(x, y + length, z);
 GL11.glColor3f(0.0F, 0.0F, 1.0F);
 GL11.glVertex3f(x, y, z);
 GL11.glVertex3f(x, y, z + length);
 GL11.glEnd();
 GL11.glColor3f(1.0F, 1.0F, 1.0F);
 GL11.glEnable(2929);
 GL13.glActiveTexture(33984);
 GL11.glEnable(3553);
 }

 void setLights(ModelSlotRenderData modelSlotRenderData, int int1) {
 for (int int0 = 0; int0 < int1; int0++) {
 ModelInstance.EffectLight effectLight = modelSlotRenderData.effectLights[int0];
 this->Effect
 .setLight(
 int0,
 effectLight.x,
 effectLight.y,
 effectLight.z,
 effectLight.r,
 effectLight.g,
 effectLight.b,
 effectLight.radius,
 modelSlotRenderData.animPlayerAngle,
 modelSlotRenderData.x,
 modelSlotRenderData.y,
 modelSlotRenderData.z,
 modelSlotRenderData.object
 );
 }
 }

 void CreateShader(const std::string& name) {
 if (!ModelManager.NoOpenGL) {
 Lambda.invoke(
 RenderThread::invokeOnRenderContext,
 this,
 name,
 (model, string) -> model.Effect = ShaderManager.instance.getOrCreateShader(string, model.bStatic)
 );
 }
 }

 AssetType getType() {
 return ASSET_TYPE;
 }

 void onBeforeReady() {
 super.onBeforeReady();
 this->Tag = this->Mesh.skinningData;
 this->softwareMesh = this->Mesh.softwareMesh;
 this->assetParams = nullptr;
 }

 public static class ModelAssetParams extends AssetManager.AssetParams {
 std::string meshName;
 std::string textureName;
 int textureFlags;
 std::string shaderName;
 bool bStatic = false;
 ModelMesh animationsModel;
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
