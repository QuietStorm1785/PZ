#include "zombie/core/opengl/ShaderProgram.h"

namespace zombie {
namespace core {
namespace opengl {

private
ShaderProgram::ShaderProgram(const std::string &string, bool boolean0) {
  // TODO: Implement ShaderProgram
  return nullptr;
}

std::string ShaderProgram::getName() {
  // TODO: Implement getName
  return "";
}

void ShaderProgram::addCompileListener(IShaderProgramListener listener) {
  // TODO: Implement addCompileListener
}

void ShaderProgram::removeCompileListener(IShaderProgramListener listener) {
  // TODO: Implement removeCompileListener
}

void ShaderProgram::invokeProgramCompiledEvent() {
  // TODO: Implement invokeProgramCompiledEvent
}

void ShaderProgram::compile() {
  // TODO: Implement compile
}

void ShaderProgram::onCompileSuccess() {
  // TODO: Implement onCompileSuccess
}

void ShaderProgram::registerFileWatchers() {
  // TODO: Implement registerFileWatchers
}

void ShaderProgram::registerFileWatcherInternal(
    const std::string &string,
    PredicatedFileWatcher
        .IPredicatedFileWatcherCallback iPredicatedFileWatcherCallback) {
  // TODO: Implement registerFileWatcherInternal
}

void ShaderProgram::onShaderFileChanged() {
  // TODO: Implement onShaderFileChanged
}

bool ShaderProgram::compileAllShaderUnits() {
  // TODO: Implement compileAllShaderUnits
  return false;
}

bool ShaderProgram::attachAllShaderUnits() {
  // TODO: Implement attachAllShaderUnits
  return false;
}

std::string ShaderProgram::getRootVertFileName() {
  // TODO: Implement getRootVertFileName
  return "";
}

std::string ShaderProgram::getRootFragFileName(const std::string &string) {
  // TODO: Implement getRootFragFileName
  return "";
}

ShaderUnit ShaderProgram::addShader(const std::string &fileName,
                                    ShaderUnit.Type unitType) {
  // TODO: Implement addShader
  return nullptr;
}

ShaderUnit ShaderProgram::findShader(const std::string &string,
                                     ShaderUnit.Type type) {
  // TODO: Implement findShader
  return nullptr;
}

ShaderProgram ShaderProgram::createShaderProgram(const std::string &name,
                                                 bool isStatic, bool compile) {
  // TODO: Implement createShaderProgram
  return nullptr;
}

int ShaderProgram::createVertShader(const std::string &fileName) {
  // TODO: Implement createVertShader
  return 0;
}

int ShaderProgram::createFragShader(const std::string &fileName) {
  // TODO: Implement createFragShader
  return 0;
}

void ShaderProgram::printLogInfo(int obj) {
  // TODO: Implement printLogInfo
}

std::string ShaderProgram::getLogInfo(int obj) {
  // TODO: Implement getLogInfo
  return "";
}

bool ShaderProgram::isCompiled() {
  // TODO: Implement isCompiled
  return false;
}

void ShaderProgram::destroy() {
  // TODO: Implement destroy
}

int ShaderProgram::getShaderID() {
  // TODO: Implement getShaderID
  return 0;
}

void ShaderProgram::Start() {
  // TODO: Implement Start
}

void ShaderProgram::End() {
  // TODO: Implement End
}

void ShaderProgram::setSamplerUnit(const std::string &loc, int textureUnit) {
  // TODO: Implement setSamplerUnit
}

void ShaderProgram::setValueColor(const std::string &loc, int rgba) {
  // TODO: Implement setValueColor
}

void ShaderProgram::setValueColorRGB(const std::string &loc, int rgb) {
  // TODO: Implement setValueColorRGB
}

void ShaderProgram::setValue(const std::string &loc, float val) {
  // TODO: Implement setValue
}

void ShaderProgram::setValue(const std::string &loc, int val) {
  // TODO: Implement setValue
}

void ShaderProgram::setValue(const std::string &loc, Vector3 val) {
  // TODO: Implement setValue
}

void ShaderProgram::setValue(const std::string &loc, Vector2 val) {
  // TODO: Implement setValue
}

void ShaderProgram::setVector2(const std::string &loc, float val_x,
                               float val_y) {
  // TODO: Implement setVector2
}

void ShaderProgram::setVector3(const std::string &loc, float val_x, float val_y,
                               float val_z) {
  // TODO: Implement setVector3
}

void ShaderProgram::setVector4(const std::string &loc, float val_x, float val_y,
                               float val_z, float val_w) {
  // TODO: Implement setVector4
}

void ShaderProgram::setValue(const std::string &loc, Matrix4f matrix4f) {
  // TODO: Implement setValue
}

void ShaderProgram::setValue(const std::string &loc, Texture tex,
                             int samplerUnit) {
  // TODO: Implement setValue
}

void ShaderProgram::setUVScale(int int0, float float0, float float1) {
  // TODO: Implement setUVScale
}

void ShaderProgram::setVector2(int id, float x, float y) {
  // TODO: Implement setVector2
}

void ShaderProgram::setVector3(int id, float x, float y, float z) {
  // TODO: Implement setVector3
}

void ShaderProgram::setVector4(int id, float x, float y, float z, float w) {
  // TODO: Implement setVector4
}

void ShaderProgram::setTransformMatrix(int int0, Matrix4f matrix4f) {
  // TODO: Implement setTransformMatrix
}

} // namespace opengl
} // namespace core
} // namespace zombie
