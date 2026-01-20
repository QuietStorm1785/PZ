#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {

enum class AddCoopPlayer {
   Init,
   ReceiveClientConnect,
   StartMapLoading,
   CheckMapLoading,
   SendPlayerConnect,
   ReceivePlayerConnect,
   AddToWorld,
   Finished;
}
} // namespace util
} // namespace zombie
