#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class FakeClientManager {
public:
    const uint8_t flags;
    const uint8_t text;
    const std::string name;

   FakeClientManager$Player$Clothes(byte var1, byte var2, std::string var3) {
      this.flags = var1;
      this.text = var2;
      this.name = var3;
   }
}
} // namespace network
} // namespace zombie
