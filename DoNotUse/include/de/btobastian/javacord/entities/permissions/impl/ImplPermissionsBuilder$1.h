#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/permissions/PermissionState.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {


// $VF: synthetic class
class ImplPermissionsBuilder {
public:
   static {
      try {
         $SwitchMap$de$btobastian$javacord$entities$permissions$PermissionState[PermissionState.ALLOWED.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$de$btobastian$javacord$entities$permissions$PermissionState[PermissionState.DENIED.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$de$btobastian$javacord$entities$permissions$PermissionState[PermissionState.NONE.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace impl
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
