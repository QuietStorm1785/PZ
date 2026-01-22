#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/Key.h"

namespace org {
namespace uncommons {
namespace maths {
namespace random {


class AESCounterRNG {
public:
   private const byte[] keyData;

   private AESCounterRNG$AESKey(byte[] keyData) {
      this.keyData = keyData;
   }

    std::string getAlgorithm() {
      return "AES";
   }

    std::string getFormat() {
      return "RAW";
   }

   public byte[] getEncoded() {
      return this.keyData;
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
