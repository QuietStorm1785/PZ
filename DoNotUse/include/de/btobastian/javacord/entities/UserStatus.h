#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {

enum class UserStatus {
   ONLINE,
   IDLE,
   DO_NOT_DISTURB,
   OFFLINE;

    static UserStatus fromString(const std::string& str) {
      switch (str) {
         case "online":
    return ONLINE;
         case "idle":
    return IDLE;
         case "dnd":
    return DO_NOT_DISTURB;
         default:
    return OFFLINE;
      }
   }
}
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
