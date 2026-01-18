#include "zombie/scripting/objects/ModelScript.h"

namespace zombie {
namespace scripting {
namespace objects {

void ModelScript::Load(const std::string &_name, const std::string &totalFile) {
  // TODO: Implement Load
}

ModelAttachment ModelScript::LoadAttachment(ScriptParser.Block block) {
  // TODO: Implement LoadAttachment
  return nullptr;
}

void ModelScript::LoadVector3f(const std::string &string, Vector3f vector3f) {
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

std::string ModelScript::getTextureName(bool allowNull) {
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

ModelAttachment ModelScript::getAttachment(int index) {
  // TODO: Implement getAttachment
  return nullptr;
}

ModelAttachment ModelScript::getAttachmentById(const std::string &id) {
  // TODO: Implement getAttachmentById
  return nullptr;
}

ModelAttachment ModelScript::addAttachment(ModelAttachment attach) {
  // TODO: Implement addAttachment
  return nullptr;
}

ModelAttachment ModelScript::removeAttachment(ModelAttachment attach) {
  // TODO: Implement removeAttachment
  return nullptr;
}

ModelAttachment ModelScript::addAttachmentAt(int index,
                                             ModelAttachment attach) {
  // TODO: Implement addAttachmentAt
  return nullptr;
}

ModelAttachment ModelScript::removeAttachment(int index) {
  // TODO: Implement removeAttachment
  return nullptr;
}

void ModelScript::reset() {
  // TODO: Implement reset
}

void ModelScript::checkMesh(const std::string &string2,
                            const std::string &string0) {
  // TODO: Implement checkMesh
}

void ModelScript::checkTexture(const std::string &string2,
                               const std::string &string0) {
  // TODO: Implement checkTexture
}

void ModelScript::check(const std::string &string0,
                        const std::string &string1) {
  // TODO: Implement check
}

void ModelScript::check(const std::string &string1, const std::string &string0,
                        const std::string &string2) {
  // TODO: Implement check
}

void ModelScript::ScriptsLoaded() {
  // TODO: Implement ScriptsLoaded
}

} // namespace objects
} // namespace scripting
} // namespace zombie
