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
#include "zombie/core/PerformanceSettings.h"


namespace zombie {
namespace core {


class Rand {
public:
    // NOTE: Replaced CellularAutomatonRNG with std::mt19937 (Mersenne Twister)
    static std::mt19937 rand;
    static std::mt19937 randlua;
    static int id;

   static void init();


   static int Next(int var0, std::mt19937& rng) {
      if (var0 <= 0) return 0;
      std::uniform_int_distribution<int> dist(0, var0 - 1);
      return dist(rng);
   }

   static int Next(int var0) {
      return Next(var0, rand);
   }

   static long Next(long var0, std::mt19937& rng) {
      if (var0 <= 0) return 0;
      std::uniform_int_distribution<long> dist(0, var0 - 1);
      return dist(rng);
   }

   static long Next(long var0) {
      return Next(var0, rand);
   }

   static int Next(int var0, int var1, std::mt19937& rng) {
      if (var1 == var0) return var0;
      if (var0 > var1) std::swap(var0, var1);
      std::uniform_int_distribution<int> dist(var0, var1 - 1);
      return dist(rng);
   }

   static int Next(int var0, int var1) {
      return Next(var0, var1, rand);
   }

   static long Next(long var0, long var2, std::mt19937& rng) {
      if (var2 == var0) return var0;
      if (var0 > var2) std::swap(var0, var2);
      std::uniform_int_distribution<long> dist(var0, var2 - 1);
      return dist(rng);
   }

   static long Next(long var0, long var2) {
      return Next(var0, var2, rand);
   }

   static float Next(float var0, float var1, std::mt19937& rng) {
      if (var1 == var0) return var0;
      if (var0 > var1) std::swap(var0, var1);
      std::uniform_real_distribution<float> dist(var0, var1);
      return dist(rng);
   }

   static float Next(float var0, float var1) {
      return Next(var0, var1, rand);
   }

   static bool NextBool(int var0) {
      if (var0 <= 0) return false;
      std::uniform_int_distribution<int> dist(0, var0 - 1);
      return dist(rand) == 0;
   }

    static int AdjustForFramerate(int var0) {
      if (zombie::network::GameServer::bServer) {
         var0 = (int)(var0 * 0.33333334F);
      } else {
         var0 = (int)(var0 * (zombie::core::PerformanceSettings::getLockFPS() / 30.0F));
      }
      return var0;
   }
};
} // namespace core
} // namespace zombie
