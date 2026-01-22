#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/SecureRandom.h"

namespace org {
namespace uncommons {
namespace maths {
namespace random {


class SecureRandomSeedGenerator {
public:
    static const SecureRandom SOURCE = std::make_shared<SecureRandom>();

   public byte[] generateSeed(int length) throws SeedException {
      return SOURCE.generateSeed(length);
   }

    std::string toString() {
      return "java.security.SecureRandom";
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
