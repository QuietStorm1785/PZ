#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Preconditions.h"
#include "java/net/Inet4Address.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace net {


class InetAddresses {
public:
    const Inet4Address server;
    const Inet4Address client;
    const int port;
    const int flags;

   public InetAddresses$TeredoInfo(@Nullable Inet4Address server, @Nullable Inet4Address client, int port, int flags) {
      Preconditions.checkArgument(port >= 0 && port <= 65535, "port '%s' is out of range (0 <= port <= 0xffff)", port);
      Preconditions.checkArgument(flags >= 0 && flags <= 65535, "flags '%s' is out of range (0 <= flags <= 0xffff)", flags);
      this.server = (Inet4Address)MoreObjects.firstNonNull(server, InetAddresses.access$000());
      this.client = (Inet4Address)MoreObjects.firstNonNull(client, InetAddresses.access$000());
      this.port = port;
      this.flags = flags;
   }

    Inet4Address getServer() {
      return this.server;
   }

    Inet4Address getClient() {
      return this.client;
   }

    int getPort() {
      return this.port;
   }

    int getFlags() {
      return this.flags;
   }
}
} // namespace net
} // namespace common
} // namespace google
} // namespace com
