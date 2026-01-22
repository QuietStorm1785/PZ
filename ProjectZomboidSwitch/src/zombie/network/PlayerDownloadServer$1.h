#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/PlayerDownloadServer/EThreadCommand.h"

namespace zombie {
namespace network {


// $VF: synthetic class
class PlayerDownloadServer {
public:
   static {
      try {
         $SwitchMap$zombie$network$PlayerDownloadServer$EThreadCommand[EThreadCommand.RequestLargeArea.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$network$PlayerDownloadServer$EThreadCommand[EThreadCommand.RequestZipArray.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$network$PlayerDownloadServer$EThreadCommand[EThreadCommand.Quit.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace network
} // namespace zombie
