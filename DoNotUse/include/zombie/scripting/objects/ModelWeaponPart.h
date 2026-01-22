#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace scripting {
namespace objects {

class ModelWeaponPart {
public:
    std::string partType;
    std::string modelName;
    std::string attachmentNameSelf;
    std::string attachmentParent;
}
} // namespace objects
} // namespace scripting
} // namespace zombie
