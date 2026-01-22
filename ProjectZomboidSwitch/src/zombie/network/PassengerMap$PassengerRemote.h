#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class PassengerMap {
public:
    int wx = -1;
    int wy = -1;
    long loaded = 0L;

   private PassengerMap$PassengerRemote() {
   }

    void setLoaded(int var1, int var2, long var3) {
      this.wx = var1;
      this.wy = var2;
      this.loaded = var3;
   }
}
} // namespace network
} // namespace zombie
