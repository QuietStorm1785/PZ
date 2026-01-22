#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {

class Permissions {
public:
    virtual ~Permissions() = default;
    PermissionState getState(PermissionType var1);
}
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
