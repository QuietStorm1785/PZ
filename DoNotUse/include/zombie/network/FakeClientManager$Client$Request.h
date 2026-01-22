#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace network {


class FakeClientManager {
public:
    const int id;
    const int wx;
    const int wy;
    const long crc;

   private FakeClientManager$Client$Request(int var1, int var2, int var3) {
      this.id = var3;
      this.wx = var1;
      this.wy = var2;
    CRC32 var4 = std::make_shared<CRC32>();
      var4.reset();
      var4.update(std::string.format("map_%d_%d.bin", var1, var2).getBytes());
      this.crc = var4.getValue();
   }
}
} // namespace network
} // namespace zombie
