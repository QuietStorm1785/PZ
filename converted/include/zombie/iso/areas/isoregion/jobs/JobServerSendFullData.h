#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/raknet/UdpConnection.h"

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace jobs {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class JobServerSendFullData : public RegionJob {
public:
 UdpConnection targetConn;

 protected JobServerSendFullData() {
 super(RegionJobType.ServerSendFullData);
 }

 void reset() {
 this->targetConn = nullptr;
 }

 UdpConnection getTargetConn() {
 return this->targetConn;
 }
}
} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
