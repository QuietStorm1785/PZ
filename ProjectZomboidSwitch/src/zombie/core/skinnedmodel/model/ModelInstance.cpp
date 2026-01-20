#include <string>
#include "zombie\core\skinnedmodel\model/ModelInstance.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {

ModelInstance ModelInstance::init(Model var1, IsoGameCharacter var2, AnimationPlayer var3) {
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

void ModelInstance::LoadTexture(const std::string& var1) {
    // TODO: Implement LoadTexture
}

void ModelInstance::dismember(int var1) {
    // TODO: Implement dismember
}

void ModelInstance::UpdateDir() {
    // TODO: Implement UpdateDir
}

void ModelInstance::Update() {
    // TODO: Implement Update
}

void ModelInstance::SetForceDir(Vector2 var1) {
    // TODO: Implement SetForceDir
}

void ModelInstance::setInstanceSkip(int var1) {
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

void ModelInstance::setItemVisual(ItemVisual var1) {
    // TODO: Implement setItemVisual
}

void ModelInstance::applyModelScriptScale(const std::string& var1) {
    // TODO: Implement applyModelScriptScale
}

ModelAttachment ModelInstance::getAttachment(int var1) {
    // TODO: Implement getAttachment
    return nullptr;
}

ModelAttachment ModelInstance::getAttachmentById(const std::string& var1) {
    // TODO: Implement getAttachmentById
    return nullptr;
}

Matrix4f ModelInstance::getAttachmentMatrix(ModelAttachment var1, Matrix4f var2) {
    // TODO: Implement getAttachmentMatrix
    return nullptr;
}

Matrix4f ModelInstance::getAttachmentMatrix(int var1, Matrix4f var2) {
    // TODO: Implement getAttachmentMatrix
    return nullptr;
}

Matrix4f ModelInstance::getAttachmentMatrixById(const std::string& var1, Matrix4f var2) {
    // TODO: Implement getAttachmentMatrixById
    return nullptr;
}

void ModelInstance::setOwner(void* var1) {
    // TODO: Implement setOwner
}

void ModelInstance::clearOwner(void* var1) {
    // TODO: Implement clearOwner
}

void* ModelInstance::getOwner() {
    // TODO: Implement getOwner
    return nullptr;
}

void ModelInstance::setTextureInitializer(ModelInstanceTextureInitializer var1) {
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

} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
