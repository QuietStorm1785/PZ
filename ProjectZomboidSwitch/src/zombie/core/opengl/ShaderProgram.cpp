#include <string>
#include "zombie\core\opengl/ShaderProgram.h"

namespace zombie {
namespace core {
namespace opengl {

private ShaderProgram::ShaderProgram(const std::string& var1, bool var2) {
    // TODO: Implement ShaderProgram
    return nullptr;
}

std::string ShaderProgram::getName() {
    // TODO: Implement getName
    return "";
}

void ShaderProgram::addCompileListener(IShaderProgramListener var1) {
    // TODO: Implement addCompileListener
}

void ShaderProgram::removeCompileListener(IShaderProgramListener var1) {
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

void ShaderProgram::registerFileWatcherInternal(const std::string& var1, IPredicatedFileWatcherCallback var2) {
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

std::string ShaderProgram::getRootFragFileName(const std::string& var1) {
    // TODO: Implement getRootFragFileName
    return "";
}

ShaderUnit ShaderProgram::addShader(const std::string& var1, Type var2) {
    // TODO: Implement addShader
    return nullptr;
}

ShaderUnit ShaderProgram::findShader(const std::string& var1, Type var2) {
    // TODO: Implement findShader
    return nullptr;
}

ShaderProgram ShaderProgram::createShaderProgram(const std::string& var0, bool var1, bool var2) {
    // TODO: Implement createShaderProgram
    return nullptr;
}

int ShaderProgram::createVertShader(const std::string& var0) {
    // TODO: Implement createVertShader
    return 0;
}

int ShaderProgram::createFragShader(const std::string& var0) {
    // TODO: Implement createFragShader
    return 0;
}

void ShaderProgram::printLogInfo(int var0) {
    // TODO: Implement printLogInfo
}

std::string ShaderProgram::getLogInfo(int var0) {
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

void ShaderProgram::setSamplerUnit(const std::string& var1, int var2) {
    // TODO: Implement setSamplerUnit
}

void ShaderProgram::setValueColor(const std::string& var1, int var2) {
    // TODO: Implement setValueColor
}

void ShaderProgram::setValueColorRGB(const std::string& var1, int var2) {
    // TODO: Implement setValueColorRGB
}

void ShaderProgram::setValue(const std::string& var1, float var2) {
    // TODO: Implement setValue
}

void ShaderProgram::setValue(const std::string& var1, int var2) {
    // TODO: Implement setValue
}

void ShaderProgram::setValue(const std::string& var1, Vector3 var2) {
    // TODO: Implement setValue
}

void ShaderProgram::setValue(const std::string& var1, Vector2 var2) {
    // TODO: Implement setValue
}

void ShaderProgram::setVector2(const std::string& var1, float var2, float var3) {
    // TODO: Implement setVector2
}

void ShaderProgram::setVector3(const std::string& var1, float var2, float var3, float var4) {
    // TODO: Implement setVector3
}

void ShaderProgram::setVector4(const std::string& var1, float var2, float var3, float var4, float var5) {
    // TODO: Implement setVector4
}

Uniform ShaderProgram::getUniform(const std::string& var1, int var2) {
    // TODO: Implement getUniform
    return nullptr;
}

Uniform ShaderProgram::getUniform(const std::string& var1, int var2, bool var3) {
    // TODO: Implement getUniform
    return nullptr;
}

void ShaderProgram::setValue(const std::string& var1, Matrix4f var2) {
    // TODO: Implement setValue
}

void ShaderProgram::setValue(const std::string& var1, Texture var2, int var3) {
    // TODO: Implement setValue
}

void ShaderProgram::setUVScale(int var1, float var2, float var3) {
    // TODO: Implement setUVScale
}

void ShaderProgram::setVector2(int var1, float var2, float var3) {
    // TODO: Implement setVector2
}

void ShaderProgram::setVector3(int var1, float var2, float var3, float var4) {
    // TODO: Implement setVector3
}

void ShaderProgram::setVector4(int var1, float var2, float var3, float var4, float var5) {
    // TODO: Implement setVector4
}

void ShaderProgram::setTransformMatrix(int var1, Matrix4f var2) {
    // TODO: Implement setTransformMatrix
}

} // namespace opengl
} // namespace core
} // namespace zombie
