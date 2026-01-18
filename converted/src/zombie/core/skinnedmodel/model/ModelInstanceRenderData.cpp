#include "zombie/core/skinnedmodel/model/ModelInstanceRenderData.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {

ModelInstanceRenderData ModelInstanceRenderData::init(ModelInstance _modelInstance) {
 // TODO: Implement init
 return nullptr;
}

void ModelInstanceRenderData::renderDebug() {
 // TODO: Implement renderDebug
}

void ModelInstanceRenderData::RenderCharacter(ModelSlotRenderData slotData) {
 // TODO: Implement RenderCharacter
}

void ModelInstanceRenderData::RenderVehicle(ModelSlotRenderData slotData) {
 // TODO: Implement RenderVehicle
}

Matrix4f ModelInstanceRenderData::makeAttachmentTransform(ModelAttachment attachment, Matrix4f attachmentXfrm) {
 // TODO: Implement makeAttachmentTransform
 return nullptr;
}

void ModelInstanceRenderData::applyBoneTransform(ModelInstance parentInstance, const std::string& boneName, Matrix4f transform) {
 // TODO: Implement applyBoneTransform
}

ModelInstanceRenderData ModelInstanceRenderData::transformToParent(ModelInstanceRenderData parentData) {
 // TODO: Implement transformToParent
 return nullptr;
}

void ModelInstanceRenderData::testOnBackItem(ModelInstance modelInstancex) {
 // TODO: Implement testOnBackItem
}

ModelInstanceRenderData ModelInstanceRenderData::alloc() {
 // TODO: Implement alloc
 return nullptr;
}

void ModelInstanceRenderData::release(ArrayList<ModelInstanceRenderData> objs) {
 // TODO: Implement release
}

} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
