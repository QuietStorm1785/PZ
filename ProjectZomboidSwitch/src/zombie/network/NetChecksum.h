#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/NetChecksum/Checksummer.h"
#include "zombie/network/NetChecksum/Comparer.h"

namespace zombie {
namespace network {


class NetChecksum {
public:
    static const Checksummer checksummer = std::make_shared<Checksummer>();
    static const Comparer comparer = std::make_shared<Comparer>();

    static void noise(const std::string& var0) {
      if (!Core.bDebug) {
      }

      DebugLog.log("NetChecksum: " + var0);
   }
}
} // namespace network
} // namespace zombie
