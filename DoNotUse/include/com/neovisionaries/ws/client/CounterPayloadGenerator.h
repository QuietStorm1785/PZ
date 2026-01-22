#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

class CounterPayloadGenerator {
public:
    long mCount;

   public byte[] generate() {
      return Misc.getBytesUTF8(std::string.valueOf(this.increment()));
   }

    long increment() {
      this.mCount = Math.max(this.mCount + 1L, 1L);
      return this.mCount;
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
