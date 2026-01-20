#include <sstream>
#include <string>
#include <vector>
#include "zombie\core\opengl/ShaderUnit.h"

namespace zombie {
namespace core {
namespace opengl {

public ShaderUnit::ShaderUnit(ShaderProgram var1, const std::string& var2, Type var3) {
    // TODO: Implement ShaderUnit
    return nullptr;
}

std::string ShaderUnit::getFileName() {
    // TODO: Implement getFileName
    return "";
}

bool ShaderUnit::isCompiled() {
    // TODO: Implement isCompiled
    return false;
}

bool ShaderUnit::compile() {
    // TODO: Implement compile
    return false;
}

bool ShaderUnit::attach() {
    // TODO: Implement attach
    return false;
}

void ShaderUnit::destroy() {
    // TODO: Implement destroy
}

int ShaderUnit::getGLID() {
    // TODO: Implement getGLID
    return 0;
}

int ShaderUnit::getParentShaderProgramGLID() {
    // TODO: Implement getParentShaderProgramGLID
    return 0;
}

int ShaderUnit::getGlType(Type var0) {
    // TODO: Implement getGlType
    return 0;
}

std::string ShaderUnit::loadShaderFile(const std::string& var1, std::vector<std::string> var2) {
    // TODO: Implement loadShaderFile
    return "";
}

std::string ShaderUnit::preProcessShaderFile(const std::string& var1, std::vector<std::string> var2) {
    // TODO: Implement preProcessShaderFile
    return "";
}

bool ShaderUnit::processIncludeLine(const std::string& var1, std::stringstream var2, const std::string& var3, const std::string& var4, std::vector<std::string> var5) {
    // TODO: Implement processIncludeLine
    return false;
}

std::string ShaderUnit::getParentFolder(const std::string& var1) {
    // TODO: Implement getParentFolder
    return "";
}

} // namespace opengl
} // namespace core
} // namespace zombie
