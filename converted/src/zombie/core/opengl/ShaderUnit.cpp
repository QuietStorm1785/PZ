#include "zombie/core/opengl/ShaderUnit.h"

namespace zombie {
namespace core {
namespace opengl {

public
ShaderUnit::ShaderUnit(ShaderProgram parent, const std::string &fileName,
                       ShaderUnit.Type unitType) {
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

int ShaderUnit::getGlType(ShaderUnit.Type type) {
  // TODO: Implement getGlType
  return 0;
}

std::string ShaderUnit::loadShaderFile(const std::string &string1,
                                       ArrayList<String> arrayList) {
  // TODO: Implement loadShaderFile
  return "";
}

std::string ShaderUnit::preProcessShaderFile(const std::string &string0,
                                             ArrayList<String> arrayList) {
  // TODO: Implement preProcessShaderFile
  return "";
}

bool ShaderUnit::processIncludeLine(const std::string &string3,
                                    StringBuilder stringBuilder1,
                                    const std::string &string1,
                                    const std::string &string9,
                                    ArrayList<String> arrayList1) {
  // TODO: Implement processIncludeLine
  return false;
}

std::string ShaderUnit::getParentFolder(const std::string &string) {
  // TODO: Implement getParentFolder
  return "";
}

} // namespace opengl
} // namespace core
} // namespace zombie
