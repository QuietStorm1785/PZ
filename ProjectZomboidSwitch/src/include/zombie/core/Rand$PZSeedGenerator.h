#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <random>

namespace zombie {
namespace core {


class Rand {
public:
   private static const SeedGenerator[] GENERATORS = new SeedGenerator[]{std::make_unique<SecureRandomSeedGenerator>()};

   private Rand$PZSeedGenerator() {
   }

   public byte[] generateSeed(int var1) {
    for (auto& var5 : GENERATORS)         try {
            return var5.generateSeed(var1);
         } catch (SeedException var7) {
         }
      }

      throw IllegalStateException("All available seed generation strategies failed.");
   }
}
} // namespace core
} // namespace zombie
