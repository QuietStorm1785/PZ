#pragma once
#include "org/joml/Matrix4f.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/core/Core.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/util/Pool.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <cstdint>
#include <filesystem>
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

class ModelInstanceRenderData {
public:
 static const Vector3f tempVector3f = new Vector3f();
 Model model;
 Texture tex;
 float depthBias;
 float hue;
 float tintR;
 float tintG;
 float tintB;
 int parentBone;
 FloatBuffer matrixPalette;
 const Matrix4f xfrm = new Matrix4f();
 SoftwareModelMeshInstance softwareMesh;
 ModelInstance modelInstance;
 bool m_muzzleFlash = false;
 ModelInstanceDebugRenderData m_debugRenderData;
private
 static ObjectPool<ModelInstanceRenderData> pool =
 new ObjectPool<>(ModelInstanceRenderData::new);

 ModelInstanceRenderData init(ModelInstance _modelInstance) {
 this->model = _modelInstance.model;
 this->tex = _modelInstance.tex;
 this->depthBias = _modelInstance.depthBias;
 this->hue = _modelInstance.hue;
 this->parentBone = _modelInstance.parentBone;

 assert _modelInstance.character.empty() ||
 _modelInstance.AnimPlayer != nullptr;

 this->m_muzzleFlash = false;
 this->xfrm.identity();
 if (_modelInstance.AnimPlayer != nullptr && !this->model.bStatic) {
 SkinningData skinningData = (SkinningData)this->model.Tag;
 if (Core.bDebug && skinningData.empty()) {
 DebugLog.General.warn(
 "skinningData is nullptr, matrixPalette may be invalid");
 }

 org.lwjgl.util.vector.Matrix4f[] matrix4fs =
 _modelInstance.AnimPlayer.getSkinTransforms(skinningData);
 if (this->matrixPalette.empty() ||
 this->matrixPalette.capacity() < matrix4fs.length * 16) {
 this->matrixPalette =
 BufferUtils.createFloatBuffer(matrix4fs.length * 16);
 }

 this->matrixPalette.clear();

 for (int int0 = 0; int0 < matrix4fs.length; int0++) {
 matrix4fs[int0].store(this->matrixPalette);
 }

 this->matrixPalette.flip();
 }

 VehicleSubModelInstance vehicleSubModelInstance =
 Type.tryCastTo(_modelInstance, VehicleSubModelInstance.class);
 if (_modelInstance instanceof
 VehicleModelInstance || vehicleSubModelInstance != nullptr) {
 if (_modelInstance instanceof VehicleModelInstance) {
 this->xfrm.set(((BaseVehicle)_modelInstance.object).renderTransform);
 } else {
 this->xfrm.set(vehicleSubModelInstance.modelInfo.renderTransform);
 }

 if (_modelInstance.model.Mesh != nullptr &&
 _modelInstance.model.Mesh.isReady() &&
 _modelInstance.model.Mesh.m_transform != nullptr) {
 _modelInstance.model.Mesh.m_transform.transpose();
 this->xfrm.mul(_modelInstance.model.Mesh.m_transform);
 _modelInstance.model.Mesh.m_transform.transpose();
 }
 }

 this->softwareMesh = _modelInstance.softwareMesh;
 this->modelInstance = _modelInstance;
 _modelInstance.renderRefCount++;
 if (_modelInstance.getTextureInitializer() != nullptr) {
 _modelInstance.getTextureInitializer().renderMain();
 }

 return this;
 }

 void renderDebug() {
 if (this->m_debugRenderData != nullptr) {
 this->m_debugRenderData.render();
 }
 }

 void RenderCharacter(ModelSlotRenderData slotData) {
 this->tintR = this->modelInstance.tintR;
 this->tintG = this->modelInstance.tintG;
 this->tintB = this->modelInstance.tintB;
 this->tex = this->modelInstance.tex;
 if (this->tex != nullptr || this->modelInstance.model.tex != nullptr) {
 this->model.DrawChar(slotData, this);
 }
 }

 void RenderVehicle(ModelSlotRenderData slotData) {
 this->tintR = this->modelInstance.tintR;
 this->tintG = this->modelInstance.tintG;
 this->tintB = this->modelInstance.tintB;
 this->tex = this->modelInstance.tex;
 if (this->tex != nullptr || this->modelInstance.model.tex != nullptr) {
 this->model.DrawVehicle(slotData, this);
 }
 }

 static Matrix4f makeAttachmentTransform(ModelAttachment attachment,
 Matrix4f attachmentXfrm) {
 attachmentXfrm.translation(attachment.getOffset());
 org.joml.Vector3f vector3f = attachment.getRotate();
 attachmentXfrm.rotateXYZ(vector3f.x * (float)(Math.PI / 180.0),
 vector3f.y * (float)(Math.PI / 180.0),
 vector3f.z * (float)(Math.PI / 180.0);
 return attachmentXfrm;
 }

 static void applyBoneTransform(ModelInstance parentInstance,
 std::string_view boneName,
 Matrix4f transform) {
 if (parentInstance != nullptr && parentInstance.AnimPlayer != nullptr) {
 if (!StringUtils.isNullOrWhitespace(boneName) {
 int int0 = parentInstance.AnimPlayer.getSkinningBoneIndex(boneName, -1);
 if (int0 != -1) {
 org.lwjgl.util.vector.Matrix4f matrix4f0 =
 parentInstance.AnimPlayer.GetPropBoneMatrix(int0);
 Matrix4f matrix4f1 = BaseVehicle.TL_matrix4f_pool.get().alloc();
 PZMath.convertMatrix(matrix4f0, matrix4f1);
 matrix4f1.transpose();
 transform.mul(matrix4f1);
 BaseVehicle.TL_matrix4f_pool.get().release(matrix4f1);
 }
 }
 }
 }

 ModelInstanceRenderData
 transformToParent(ModelInstanceRenderData parentData) {
 if (this->modelInstance instanceof
 VehicleModelInstance || this->modelInstance instanceof
 VehicleSubModelInstance) {
 return this;
 } else if (parentData.empty()) {
 return this;
 } else {
 this->xfrm.set(parentData.xfrm);
 this->xfrm.transpose();
 Matrix4f matrix4f = BaseVehicle.TL_matrix4f_pool.get().alloc();
 ModelAttachment modelAttachment0 =
 parentData.modelInstance.getAttachmentById(
 this->modelInstance.attachmentNameParent);
 if (modelAttachment0.empty()) {
 if (this->modelInstance.parentBoneName != nullptr &&
 parentData.modelInstance.AnimPlayer != nullptr) {
 applyBoneTransform(parentData.modelInstance,
 this->modelInstance.parentBoneName, this->xfrm);
 }
 } else {
 applyBoneTransform(parentData.modelInstance, modelAttachment0.getBone(),
 this->xfrm);
 makeAttachmentTransform(modelAttachment0, matrix4f);
 this->xfrm.mul(matrix4f);
 }

 ModelAttachment modelAttachment1 = this->modelInstance.getAttachmentById(
 this->modelInstance.attachmentNameSelf);
 if (modelAttachment1 != nullptr) {
 makeAttachmentTransform(modelAttachment1, matrix4f);
 matrix4f.invert();
 this->xfrm.mul(matrix4f);
 }

 if (this->modelInstance.model.Mesh != nullptr &&
 this->modelInstance.model.Mesh.isReady() &&
 this->modelInstance.model.Mesh.m_transform != nullptr) {
 this->xfrm.mul(this->modelInstance.model.Mesh.m_transform);
 }

 if (this->modelInstance.scale != 1.0F) {
 this->xfrm.scale(this->modelInstance.scale);
 }

 this->xfrm.transpose();
 BaseVehicle.TL_matrix4f_pool.get().release(matrix4f);
 return this;
 }
 }

 void testOnBackItem(ModelInstance modelInstancex) {
 if (modelInstancex.parent != nullptr &&
 modelInstancex.parent.m_modelScript != nullptr) {
 AnimationPlayer animationPlayer = modelInstancex.parent.AnimPlayer;
 ModelAttachment modelAttachment0 = nullptr;

 for (int int0 = 0;
 int0 < modelInstancex.parent.m_modelScript.getAttachmentCount();
 int0++) {
 ModelAttachment modelAttachment1 =
 modelInstancex.parent.getAttachment(int0);
 if (modelAttachment1.getBone() != nullptr &&
 this->parentBone == animationPlayer.getSkinningBoneIndex(
 modelAttachment1.getBone(), 0) {
 modelAttachment0 = modelAttachment1;
 break;
 }
 }

 if (modelAttachment0 != nullptr) {
 Matrix4f matrix4f = BaseVehicle.TL_matrix4f_pool.get().alloc();
 makeAttachmentTransform(modelAttachment0, matrix4f);
 this->xfrm.transpose();
 this->xfrm.mul(matrix4f);
 this->xfrm.transpose();
 ModelAttachment modelAttachment2 =
 modelInstancex.getAttachmentById(modelAttachment0.getId());
 if (modelAttachment2 != nullptr) {
 makeAttachmentTransform(modelAttachment2, matrix4f);
 matrix4f.invert();
 this->xfrm.transpose();
 this->xfrm.mul(matrix4f);
 this->xfrm.transpose();
 }

 BaseVehicle.TL_matrix4f_pool.get().release(matrix4f);
 }
 }
 }

 static ModelInstanceRenderData alloc() { return pool.alloc(); }

 static void release(ArrayList<ModelInstanceRenderData> objs) {
 for (int int0 = 0; int0 < objs.size(); int0++) {
 ModelInstanceRenderData modelInstanceRenderData =
 (ModelInstanceRenderData)objs.get(int0);
 if (modelInstanceRenderData.modelInstance.getTextureInitializer() !=
 nullptr) {
 modelInstanceRenderData.modelInstance.getTextureInitializer()
 .postRender();
 }

 ModelManager.instance.derefModelInstance(
 modelInstanceRenderData.modelInstance);
 modelInstanceRenderData.modelInstance = nullptr;
 modelInstanceRenderData.model = nullptr;
 modelInstanceRenderData.tex = nullptr;
 modelInstanceRenderData.softwareMesh = nullptr;
 modelInstanceRenderData.m_debugRenderData =
 Pool.tryRelease(modelInstanceRenderData.m_debugRenderData);
 }

 pool.release(objs);
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
