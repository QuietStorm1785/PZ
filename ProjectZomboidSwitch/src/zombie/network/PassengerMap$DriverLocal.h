#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/PassengerMap/PassengerRemote.h"

namespace zombie {
namespace network {


class PassengerMap {
public:
   const PassengerRemote[] passengers = new PassengerRemote[16];

   private PassengerMap$DriverLocal() {
   }
}
} // namespace network
} // namespace zombie
