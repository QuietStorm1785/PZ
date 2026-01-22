#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace znet {

class ZNetSessionState {
public:
    bool bConnectionActive;
    bool bConnecting;
    bool bUsingRelay;
    long eP2PSessionError;
    long bytesQueuedForSend;
    long packetsQueuedForSend;
    long remoteIP;
    long remotePort;

    std::string getDescription() {
      return "session active=\""
         + this.bConnectionActive
         + "\" connecting=\""
         + this.bConnecting
         + "\" relay=\""
         + this.bUsingRelay
         + "\" error=\""
         + this.eP2PSessionError
         + "\" bytes=\""
         + this.bytesQueuedForSend
         + "\" packets=\""
         + this.packetsQueuedForSend
         + "\" ip=\""
         + (255L & this.remoteIP >> 24)
         + "."
         + (255L & this.remoteIP >> 16)
         + "."
         + (255L & this.remoteIP >> 8)
         + "."
         + (255L & this.remoteIP)
         + "\" port=\""
         + this.remotePort
         + "\"";
   }
}
} // namespace znet
} // namespace core
} // namespace zombie
