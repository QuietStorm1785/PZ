#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/permissions/PermissionState.h"
#include "de/btobastian/javacord/entities/permissions/PermissionType.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {


class ImplPermissions {
public:
    const int allowed;
    int denied;

    public ImplPermissions(int allow, int deny) {
      this.allowed = allow;
      this.denied = deny;
   }

    public ImplPermissions(int allow) {
      this.allowed = allow;

      for (PermissionType type : PermissionType.values()) {
         if (!type.isSet(allow)) {
            this.denied = type.set(this.denied, true);
         }
      }
   }

    PermissionState getState(PermissionType type) {
      if (type.isSet(this.allowed)) {
         return PermissionState.ALLOWED;
      } else {
         return type.isSet(this.denied) ? PermissionState.DENIED : PermissionState.NONE;
      }
   }

    int getAllowed() {
      return this.allowed;
   }

    int getDenied() {
      return this.denied;
   }

    std::string toString() {
      return "Permissions (allowed: " + this.getAllowed() + ", denied: " + this.getDenied() + ")";
   }

    bool equals(void* obj) {
      if (!(dynamic_cast<ImplPermissions*>(obj) != nullptr)) {
    return false;
      } else {
    ImplPermissions other = (ImplPermissions)obj;
         return other.allowed == this.allowed && other.denied == this.denied;
      }
   }
}
} // namespace impl
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
