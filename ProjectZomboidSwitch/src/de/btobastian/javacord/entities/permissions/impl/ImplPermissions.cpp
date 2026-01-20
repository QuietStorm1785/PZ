#include <string>
#include "de\btobastian\javacord\entities\permissions\impl/ImplPermissions.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {

public ImplPermissions::ImplPermissions(int allow, int deny) {
    // TODO: Implement ImplPermissions
    return nullptr;
}

public ImplPermissions::ImplPermissions(int allow) {
    // TODO: Implement ImplPermissions
    return nullptr;
}

PermissionState ImplPermissions::getState(PermissionType type) {
    // TODO: Implement getState
    return nullptr;
}

int ImplPermissions::getAllowed() {
    // TODO: Implement getAllowed
    return 0;
}

int ImplPermissions::getDenied() {
    // TODO: Implement getDenied
    return 0;
}

std::string ImplPermissions::toString() {
    // TODO: Implement toString
    return "";
}

bool ImplPermissions::equals(void* obj) {
    // TODO: Implement equals
    return false;
}

} // namespace impl
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
