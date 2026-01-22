#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/PlayerDownloadServer/EThreadCommand.h"

namespace zombie {
namespace network {


class PlayerDownloadServer {
public:
    EThreadCommand e;
    ClientChunkRequest ccr;

   private PlayerDownloadServer$WorkerThreadCommand() {
   }
}
} // namespace network
} // namespace zombie
