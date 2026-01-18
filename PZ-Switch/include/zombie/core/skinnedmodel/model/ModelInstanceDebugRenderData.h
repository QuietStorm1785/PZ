#pragma once
#include "org/joml/Matrix4f.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include "zombie/vehicles/BaseVehicle.h"
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ModelInstanceDebugRenderData : public PooledObject {
public:
private
 static Pool<ModelInstanceDebugRenderData> s_pool =
 new Pool<>(ModelInstanceDebugRenderData::new);
private
 ArrayList<Matrix4f> m_attachmentMatrices =
 std::make_unique<ArrayList<>>();

 static ModelInstanceDebugRenderData alloc() { return s_pool.alloc(); }

 ModelInstanceDebugRenderData init(ModelSlotRenderData slotData,
 ModelInstanceRenderData instData) {
 this->initAttachments(slotData, instData);
 return this;
 }

 void render() {
 this->renderAttachments();
 if (DebugOptions.instance.ModelRenderAxis.getValue()) {
 Model.debugDrawAxis(0.0F, 0.0F, 0.0F, 1.0F, 1.0F);
 }
 }

 void initAttachments(ModelSlotRenderData modelSlotRenderData,
 ModelInstanceRenderData modelInstanceRenderData) {
 BaseVehicle.Matrix4fObjectPool matrix4fObjectPool =
 BaseVehicle.TL_matrix4f_pool.get();
 matrix4fObjectPool.release(this->m_attachmentMatrices);
 this->m_attachmentMatrices.clear();
 if (DebugOptions.instance.ModelRenderAttachments.getValue()) {
 ModelScript modelScript =
 modelInstanceRenderData.modelInstance.m_modelScript;
 if (modelScript != nullptr) {
 Matrix4f matrix4f0 =
 matrix4fObjectPool.alloc().set(modelInstanceRenderData.xfrm);
 Matrix4f matrix4f1 = matrix4fObjectPool.alloc();
 matrix4f0.transpose();

 for (int int0 = 0; int0 < modelScript.getAttachmentCount(); int0++) {
 ModelAttachment modelAttachment = modelScript.getAttachment(int0);
 Matrix4f matrix4f2 = matrix4fObjectPool.alloc();
 modelInstanceRenderData.modelInstance.getAttachmentMatrix(
 modelAttachment, matrix4f2);
 if (modelInstanceRenderData.model.bStatic ||
 modelAttachment.getBone() == nullptr) {
 matrix4f0.mul(matrix4f2, matrix4f2);
 } else if (modelSlotRenderData.animPlayer != nullptr &&
 modelSlotRenderData.animPlayer.hasSkinningData()) {
 int int1 = modelSlotRenderData.animPlayer.getSkinningBoneIndex(
 modelAttachment.getBone(), 0);
 org.lwjgl.util.vector.Matrix4f matrix4f3 =
 modelSlotRenderData.animPlayer.modelTransforms[int1];
 PZMath.convertMatrix(matrix4f3, matrix4f1);
 matrix4f1.transpose();
 matrix4f1.mul(matrix4f2, matrix4f2);
 matrix4f0.mul(matrix4f2, matrix4f2);
 }

 this->m_attachmentMatrices.add(matrix4f2);
 }

 matrix4fObjectPool.release(matrix4f1);
 matrix4fObjectPool.release(matrix4f0);
 }
 }
 }

 void renderAttachments() {
 for (int int0 = 0; int0 < this->m_attachmentMatrices.size(); int0++) {
 Matrix4f matrix4f = this->m_attachmentMatrices.get(int0);
 PZGLUtil.pushAndMultMatrix(5888, matrix4f);
 Model.debugDrawAxis(0.0F, 0.0F, 0.0F, 0.05F, 1.0F);
 PZGLUtil.popMatrix(5888);
 }
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
