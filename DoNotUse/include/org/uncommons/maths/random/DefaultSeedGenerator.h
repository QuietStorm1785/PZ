#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/uncommons/maths/binary/BinaryUtils.h"

namespace org {
namespace uncommons {
namespace maths {
namespace random {


class DefaultSeedGenerator {
public:
    static const std::string DEBUG_PROPERTY = "org.uncommons.maths.random.debug";
    static const DefaultSeedGenerator INSTANCE = std::make_shared<DefaultSeedGenerator>();
   private static const SeedGenerator[] GENERATORS = new SeedGenerator[]{
    std::make_shared<DevRandomSeedGenerator>();
   };

    private DefaultSeedGenerator() {
   }

    static DefaultSeedGenerator getInstance() {
    return INSTANCE;
   }

   public byte[] generateSeed(int length) {
    for (auto& generator : GENERATORS)         try {
            byte[] seed = generator.generateSeed(length);

            try {
    bool debug = System.getProperty("org.uncommons.maths.random.debug", "false") == "true");
               if (debug) {
    std::string seedString = BinaryUtils.convertBytesToHexString(seed);
                  System.out.println(seed.length + " bytes of seed data acquired from " + generator + ":");
                  System.out.println("  " + seedString);
               }
            } catch (SecurityException var9) {
            }

    return seed;
         } catch (SeedException var10) {
         }
      }

      throw IllegalStateException("All available seed generation strategies failed.");
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
