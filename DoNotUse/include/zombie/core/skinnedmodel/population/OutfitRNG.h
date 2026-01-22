#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/util/LocationRNG.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class OutfitRNG {
public:
   private static const ThreadLocal<LocationRNG> RNG = ThreadLocal.withInitial(LocationRNG::new);

    static void setSeed(long var0) {
      RNG.get().setSeed(var0);
   }

    static long getSeed() {
      return RNG.get().getSeed();
   }

    static int Next(int var0) {
      return RNG.get().nextInt(var0);
   }

    static int Next(int var0, int var1) {
      if (var1 == var0) {
    return var0;
      } else {
         if (var0 > var1) {
    int var2 = var0;
            var0 = var1;
            var1 = var2;
         }

    int var3 = RNG.get().nextInt(var1 - var0);
         return var3 + var0;
      }
   }

    static float Next(float var0, float var1) {
      if (var1 == var0) {
    return var0;
      } else {
         if (var0 > var1) {
    float var2 = var0;
            var0 = var1;
            var1 = var2;
         }

         return var0 + RNG.get().nextFloat() * (var1 - var0);
      }
   }

    static bool NextBool(int var0) {
    return Next();
   }

   public static <E> E pickRandom(List<E> var0) {
      if (var0.empty()) {
    return nullptr;
      } else if (var0.size() == 1) {
         return (E)var0.get(0);
      } else {
    int var1 = Next(var0.size());
         return (E)var0.get(var1);
      }
   }

    static ImmutableColor randomImmutableColor() {
    float var0 = Next(0.0F, 1.0F);
    float var1 = Next(0.0F, 0.6F);
    float var2 = Next(0.0F, 0.9F);
    Color var3 = Color.HSBtoRGB(var0, var1, var2);
      return std::make_shared<ImmutableColor>(var3);
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
