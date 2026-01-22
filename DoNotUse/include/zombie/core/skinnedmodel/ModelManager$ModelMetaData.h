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

class ModelManager {
public:
    std::string meshName;
    std::string textureName;
    std::string shaderName;
    bool bStatic;

   private ModelManager$ModelMetaData() {
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
