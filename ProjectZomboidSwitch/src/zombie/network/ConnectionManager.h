#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/SimpleDateFormat.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>

namespace zombie {
namespace network {


class ConnectionManager {
public:
    static const SimpleDateFormat s_logSdf = std::make_shared<SimpleDateFormat>("dd-MM-yy HH:mm:ss.SSS");

    static void log(const std::string& var0, const std::string& var1, UdpConnection var2) {
      DebugLog.Network
         .println(
            "[%s] > ConnectionManager: [%s] \"%s\" connection: %s",
            s_logSdf.format(Calendar.getInstance().getTime()),
            var0,
            var1,
            GameClient.bClient ? GameClient.connection : var2
         );
   }
}
} // namespace network
} // namespace zombie
