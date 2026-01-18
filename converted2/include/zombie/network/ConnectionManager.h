#pragma once
#include "java/text/SimpleDateFormat.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ConnectionManager {
public:
  static const SimpleDateFormat s_logSdf =
      new SimpleDateFormat("dd-MM-yy HH:mm:ss.SSS");

  static void log(const std::string &string0, const std::string &string1,
                  UdpConnection udpConnection) {
    DebugLog.Network.println(
        "[%s] > ConnectionManager: [%s] \"%s\" connection: %s",
        s_logSdf.format(Calendar.getInstance().getTime()), string0, string1,
        GameClient.bClient ? GameClient.connection : udpConnection);
  }
}
} // namespace network
} // namespace zombie
