#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/GameServerWorkshopItems/WorkshopInstallState.h"

namespace zombie {
namespace network {


// $VF: synthetic class
class GameServerWorkshopItems {
public:
   static {
      try {
         $SwitchMap$zombie$network$GameServerWorkshopItems$WorkshopInstallState[WorkshopInstallState.CheckItemState.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$network$GameServerWorkshopItems$WorkshopInstallState[WorkshopInstallState.DownloadPending.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$network$GameServerWorkshopItems$WorkshopInstallState[WorkshopInstallState.Ready.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace network
} // namespace zombie
