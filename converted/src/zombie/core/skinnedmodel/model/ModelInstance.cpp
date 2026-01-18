#include "zombie/core/skinnedmodel/model/ModelInstance.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {

ModelInstance ModelInstance::init(Model _model, IsoGameCharacter _character, AnimationPlayer player) {
 // TODO: Implement init
 return nullptr;
}

bool ModelInstance::isRendering() {
 // TODO: Implement isRendering
 return false;
}

void ModelInstance::reset() {
 // TODO: Implement reset
}

void ModelInstance::LoadTexture(const std::string& name) {
 // TODO: Implement LoadTexture
}

void ModelInstance::dismember(int bone) {
 // TODO: Implement dismember
}

void ModelInstance::UpdateDir() {
 // TODO: Implement UpdateDir
}

void ModelInstance::Update() {
 // TODO: Implement Update
}

void ModelInstance::SetForceDir(Vector2 dir) {
 // TODO: Implement SetForceDir
}

void ModelInstance::setInstanceSkip(int c) {
 // TODO: Implement setInstanceSkip
}

void ModelInstance::destroySmartTextures() {
 // TODO: Implement destroySmartTextures
}

void ModelInstance::updateLights() {
 // TODO: Implement updateLights
}

ItemVisual ModelInstance::getItemVisual() {
 // TODO: Implement getItemVisual
 return nullptr;
}

void ModelInstance::setItemVisual(ItemVisual _itemVisual) {
 // TODO: Implement setItemVisual
}

void ModelInstance::applyModelScriptScale(const std::string& modelName) {
 // TODO: Implement applyModelScriptScale
}

ModelAttachment ModelInstance::getAttachment(int index) {
 // TODO: Implement getAttachment
 return nullptr;
}

ModelAttachment ModelInstance::getAttachmentById(const std::string& id) {
 // TODO: Implement getAttachmentById
 return nullptr;
}

Matrix4f ModelInstance::getAttachmentMatrix(ModelAttachment attachment, Matrix4f out) {
 // TODO: Implement getAttachmentMatrix
 return nullptr;
}

Matrix4f ModelInstance::getAttachmentMatrix(int index, Matrix4f out) {
 // TODO: Implement getAttachmentMatrix
 return nullptr;
}

Matrix4f ModelInstance::getAttachmentMatrixById(const std::string& id, Matrix4f out) {
 // TODO: Implement getAttachmentMatrixById
 return nullptr;
}

void ModelInstance::setOwner(void* owner) {
 // TODO: Implement setOwner
}

void ModelInstance::clearOwner(void* expectedOwner) {
 // TODO: Implement clearOwner
}

void* ModelInstance::getOwner() {
 // TODO: Implement getOwner
 return nullptr;
}

void ModelInstance::setTextureInitializer(ModelInstanceTextureInitializer textureInitializer) {
 // TODO: Implement setTextureInitializer
}

ModelInstanceTextureInitializer ModelInstance::getTextureInitializer() {
 // TODO: Implement getTextureInitializer
 return nullptr;
}

bool ModelInstance::hasTextureCreator() {
 // TODO: Implement hasTextureCreator
 return false;
}

void ModelInstance::set(float _x, float _y, float _z, float _r, float _g, float _b, int _radius) {
 // TODO: Implement set
}

void ModelInstance::registerFrameLight(IsoGridSquare.ResultLight resultLight) {
 // TODO: Implement registerFrameLight
}

void ModelInstance::initFrameLightsForFrame() {
 // TODO: Implement initFrameLightsForFrame
}

void ModelInstance::completeFrameLightsForFrame() {
 // TODO: Implement completeFrameLightsForFrame
}

void ModelInstance::sortLights(IsoGameCharacter character) {
 // TODO: Implement sortLights
}

void ModelInstance::updateLights(IsoGameCharacter character, bool boolean0) {
 // TODO: Implement updateLights
}

float ModelInstance::lerp(float float0, float float2, float float1) {
 // TODO: Implement lerp
 return 0;
}

void ModelInstance::setCurrentToTarget() {
 // TODO: Implement setCurrentToTarget
}

float ModelInstance::step(float float0, float float1, float float2) {
 // TODO: Implement step
 return 0;
}

} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
