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
#include "de/btobastian/javacord/entities/permissions/PermissionsBuilder.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplPermissionsBuilder/1.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {


class ImplPermissionsBuilder {
public:
    int allowed = 0;
    int denied = 0;

    public ImplPermissionsBuilder() {
   }

    public ImplPermissionsBuilder(Permissions permissions) {
      this.allowed = ((ImplPermissions)permissions).getAllowed();
      this.denied = ((ImplPermissions)permissions).getDenied();
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    PermissionsBuilder setState(PermissionType type, PermissionState state) {
      switch (1.$SwitchMap$de$btobastian$javacord$entities$permissions$PermissionState[state.ordinal()]) {
         case 1:
            this.allowed = type.set(this.allowed, true);
            this.denied = type.set(this.denied, false);
            break;
         case 2:
            this.allowed = type.set(this.allowed, false);
            this.denied = type.set(this.denied, true);
            break;
         case 3:
            this.allowed = type.set(this.allowed, false);
            this.denied = type.set(this.denied, false);
      }

    return this;
   }

    PermissionState getState(PermissionType type) {
      if (type.isSet(this.allowed)) {
         return PermissionState.ALLOWED;
      } else {
         return type.isSet(this.denied) ? PermissionState.DENIED : PermissionState.NONE;
      }
   }

    Permissions build() {
      return std::make_shared<ImplPermissions>(this.allowed, this.denied);
   }
}
} // namespace impl
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
