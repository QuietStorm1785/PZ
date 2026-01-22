#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Translator.h"

namespace zombie {
namespace network {
namespace packets {


enum class RequestDataPacket {
   ConnectionDetails,
   Descriptors,
   MetaGrid,
   MapZone,
   PlayerZombieDescriptors,
   RadioData;

    std::string getDescriptor() {
      return Translator.getText("IGUI_RequestID_" + this.name());
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
