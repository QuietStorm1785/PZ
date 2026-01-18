#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

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
 + this->bConnectionActive
 + "\" connecting=\""
 + this->bConnecting
 + "\" relay=\""
 + this->bUsingRelay
 + "\" error=\""
 + this->eP2PSessionError
 + "\" bytes=\""
 + this->bytesQueuedForSend
 + "\" packets=\""
 + this->packetsQueuedForSend
 + "\" ip=\""
 + (255L & this->remoteIP >> 24)
 + "."
 + (255L & this->remoteIP >> 16)
 + "."
 + (255L & this->remoteIP >> 8)
 + "."
 + (255L & this->remoteIP)
 + "\" port=\""
 + this->remotePort
 + "\"";
 }
}
} // namespace znet
} // namespace core
} // namespace zombie
