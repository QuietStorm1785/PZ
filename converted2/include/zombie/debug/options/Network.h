#pragma once
#include "zombie/debug/BooleanDebugOption.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace debug {
namespace options {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Network : public OptionGroup {
public:
public
  final Network.Client Client = new Network.Client(this.Group);
public
  final Network.Server Server = new Network.Server(this.Group);
public
  final Network.PublicServerUtil PublicServerUtil =
      new Network.PublicServerUtil(this.Group);

public
  Network() { super("Network"); }

public
  final class Client extends OptionGroup {
    const BooleanDebugOption MainLoop =
        newDebugOnlyOption(this.Group, "MainLoop", true);
    const BooleanDebugOption UpdateZombiesFromPacket =
        newDebugOnlyOption(this.Group, "UpdateZombiesFromPacket", true);
    const BooleanDebugOption SyncIsoObject =
        newDebugOnlyOption(this.Group, "SyncIsoObject", true);

  public
    Client(IDebugOptionGroup iDebugOptionGroup) {
      super(iDebugOptionGroup, "Client");
    }
  }

  public final class PublicServerUtil extends OptionGroup {
    const BooleanDebugOption Enabled =
        newDebugOnlyOption(this.Group, "Enabled", true);

  public
    PublicServerUtil(IDebugOptionGroup iDebugOptionGroup) {
      super(iDebugOptionGroup, "PublicServerUtil");
    }
  }

  public final class Server extends OptionGroup {
    const BooleanDebugOption SyncIsoObject =
        newDebugOnlyOption(this.Group, "SyncIsoObject", true);

  public
    Server(IDebugOptionGroup iDebugOptionGroup) {
      super(iDebugOptionGroup, "Server");
    }
  }
}
} // namespace options
} // namespace debug
} // namespace zombie
