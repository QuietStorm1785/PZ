#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace shader {


class ShaderManager {
public:
    static const ShaderManager instance = std::make_shared<ShaderManager>();
   private const std::vector<Shader> shaders = std::make_unique<std::vector<>>();

    Shader getShader(const std::string& var1, bool var2) {
      for (int var3 = 0; var3 < this.shaders.size(); var3++) {
    Shader var4 = this.shaders.get(var3);
         if (var1 == var4.name) && var2 == var4.bStatic) {
    return var4;
         }
      }

    return nullptr;
   }

    Shader getOrCreateShader(const std::string& var1, bool var2) {
    Shader var3 = this.getShader(var1, var2);
      if (var3 != nullptr) {
    return var3;
      } else {
         for (int var4 = 0; var4 < this.shaders.size(); var4++) {
    Shader var5 = this.shaders.get(var4);
            if (var5.name.equalsIgnoreCase(var1) && !var5.name == var1)) {
               throw IllegalArgumentException("shader filenames are case-sensitive");
            }
         }

         var3 = std::make_shared<Shader>(var1, var2);
         this.shaders.push_back(var3);
    return var3;
      }
   }
}
} // namespace shader
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
