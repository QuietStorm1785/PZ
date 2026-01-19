#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace shader {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ShaderManager {
public:
 static const ShaderManager instance = new ShaderManager();
private
 ArrayList<Shader> shaders = std::make_unique<ArrayList<>>();

 Shader getShader(std::string_view string, bool boolean0) {
 for (int int0 = 0; int0 < this->shaders.size(); int0++) {
 Shader shader = this->shaders.get(int0);
 if (string == shader.name) && boolean0 == shader.bStatic) {
 return shader;
 }
 }

 return nullptr;
 }

 Shader getOrCreateShader(std::string_view string, bool boolean0) {
 Shader shader0 = this->getShader(string, boolean0);
 if (shader0 != nullptr) {
 return shader0;
 } else {
 for (int int0 = 0; int0 < this->shaders.size(); int0++) {
 Shader shader1 = this->shaders.get(int0);
 if (shader1.name.equalsIgnoreCase(string) && !shader1.name == string) {
 throw IllegalArgumentException(
 "shader filenames are case-sensitive");
 }
 }

 shader0 = new Shader(string, boolean0);
 this->shaders.add(shader0);
 return shader0;
 }
 }
}
} // namespace shader
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
