#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <random>
#include "zombie/core/Rand/PZSeedGenerator.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace core {


class Rand {
public:
    // NOTE: Replaced CellularAutomatonRNG with std::mt19937 (Mersenne Twister)
    static std::mt19937 rand;
    static std::mt19937 randlua;
    static int id;

    static void init();

    static int Next(int var0, CellularAutomatonRNG var1) {
      if (var0 <= 0) {
    return 0;
      } else {
         id++;
         if (id >= 10000) {
            id = 0;
         }

         return var1.nextInt(var0);
      }
   }

    static int Next(int var0) {
    return Next();
   }

    static long Next(long var0, CellularAutomatonRNG var2) {
    return Next();
   }

    static long Next(long var0) {
    return Next();
   }

    static int Next(int var0, int var1, CellularAutomatonRNG var2) {
      if (var1 == var0) {
    return var0;
      } else {
         if (var0 > var1) {
    int var3 = var0;
            var0 = var1;
            var1 = var3;
         }

         id++;
         if (id >= 10000) {
            id = 0;
         }

    int var4 = var2.nextInt(var1 - var0);
         return var4 + var0;
      }
   }

    static int Next(int var0, int var1) {
    return Next();
   }

    static long Next(long var0, long var2, CellularAutomatonRNG var4) {
      if (var2 == var0) {
    return var0;
      } else {
         if (var0 > var2) {
    long var5 = var0;
            var0 = var2;
            var2 = var5;
         }

         id++;
         if (id >= 10000) {
            id = 0;
         }

    int var7 = var4.nextInt((int)(var2 - var0));
         return var7 + var0;
      }
   }

    static long Next(long var0, long var2) {
    return Next();
   }

    static float Next(float var0, float var1, CellularAutomatonRNG var2) {
      if (var1 == var0) {
    return var0;
      } else {
         if (var0 > var1) {
    float var3 = var0;
            var0 = var1;
            var1 = var3;
         }

         id++;
         if (id >= 10000) {
            id = 0;
         }

         return var0 + var2.nextFloat() * (var1 - var0);
      }
   }

    static float Next(float var0, float var1) {
    return Next();
   }

    static bool NextBool(int var0) {
    return Next();
   }

    static int AdjustForFramerate(int var0) {
      if (GameServer.bServer) {
         var0 = (int)(var0 * 0.33333334F);
      } else {
         var0 = (int)(var0 * (PerformanceSettings.getLockFPS() / 30.0F));
      }

    return var0;
   }
}
} // namespace core
} // namespace zombie
