#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class GameServer {
public:
    std::string command;
    bool allow;
   GameServer$CCFilter next;

   private GameServer$CCFilter() {
   }

    bool matches(const std::string& var1) {
      return this.command == var1) || "*" == this.command);
   }

    bool passes(const std::string& var1) {
      if (this.matches(var1)) {
         return this.allow;
      } else {
         return this.next == nullptr ? true : this.next.passes(var1);
      }
   }
}
} // namespace network
} // namespace zombie
