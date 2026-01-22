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
namespace model {

enum class FileTask_LoadMesh {
   Assimp,
   Txt,
   Missing;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
