#include <string>
#include "zombie\scripting\objects/ModelScript.h"

namespace zombie {
namespace scripting {
namespace objects {

void ModelScript::Load(const std::string& var1, const std::string& var2) {
    // TODO: Implement Load
}

ModelAttachment ModelScript::LoadAttachment(Block var1) {
    // TODO: Implement LoadAttachment
    return nullptr;
}

void ModelScript::LoadVector3f(const std::string& var1, Vector3f var2) {
    // TODO: Implement LoadVector3f
}

std::string ModelScript::getName() {
    // TODO: Implement getName
    return "";
}

std::string ModelScript::getFullType() {
    // TODO: Implement getFullType
    return "";
}

std::string ModelScript::getMeshName() {
    // TODO: Implement getMeshName
    return "";
}

std::string ModelScript::getTextureName() {
    // TODO: Implement getTextureName
    return "";
}

std::string ModelScript::getTextureName(bool var1) {
    // TODO: Implement getTextureName
    return "";
}

std::string ModelScript::getShaderName() {
    // TODO: Implement getShaderName
    return "";
}

std::string ModelScript::getFileName() {
    // TODO: Implement getFileName
    return "";
}

int ModelScript::getAttachmentCount() {
    // TODO: Implement getAttachmentCount
    return 0;
}

ModelAttachment ModelScript::getAttachment(int var1) {
    // TODO: Implement getAttachment
    return nullptr;
}

ModelAttachment ModelScript::getAttachmentById(const std::string& var1) {
    // TODO: Implement getAttachmentById
    return nullptr;
}

ModelAttachment ModelScript::addAttachment(ModelAttachment var1) {
    // TODO: Implement addAttachment
    return nullptr;
}

ModelAttachment ModelScript::removeAttachment(ModelAttachment var1) {
    // TODO: Implement removeAttachment
    return nullptr;
}

ModelAttachment ModelScript::addAttachmentAt(int var1, ModelAttachment var2) {
    // TODO: Implement addAttachmentAt
    return nullptr;
}

ModelAttachment ModelScript::removeAttachment(int var1) {
    // TODO: Implement removeAttachment
    return nullptr;
}

void ModelScript::reset() {
    // TODO: Implement reset
}

void ModelScript::checkMesh(const std::string& var0, const std::string& var1) {
    // TODO: Implement checkMesh
}

void ModelScript::checkTexture(const std::string& var0, const std::string& var1) {
    // TODO: Implement checkTexture
}

void ModelScript::check(const std::string& var0, const std::string& var1) {
    // TODO: Implement check
}

void ModelScript::check(const std::string& var0, const std::string& var1, const std::string& var2) {
    // TODO: Implement check
}

void ModelScript::ScriptsLoaded() {
    // TODO: Implement ScriptsLoaded
}

} // namespace objects
} // namespace scripting
} // namespace zombie
