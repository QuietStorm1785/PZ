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

class PermissionsBuilder {
public:
    virtual ~PermissionsBuilder() = default;
    PermissionsBuilder setState(PermissionType var1, PermissionState var2);

    PermissionState getState(PermissionType var1);

    Permissions build();
}
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
