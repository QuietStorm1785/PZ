#pragma once
#include "org/uncommons/maths/random/CellularAutomatonRNG.h"
#include "org/uncommons/maths/random/SecureRandomSeedGenerator.h"
#include "org/uncommons/maths/random/SeedException.h"
#include "org/uncommons/maths/random/SeedGenerator.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Rand {
public:
  static CellularAutomatonRNG rand;
  static CellularAutomatonRNG randlua;
  static int id = 0;

  static void init() {
    try {
      rand = new CellularAutomatonRNG(new Rand.PZSeedGenerator());
      randlua = new CellularAutomatonRNG(new Rand.PZSeedGenerator());
    } catch (SeedException seedException) {
      seedException.printStackTrace();
    }
  }

  static int Next(int int0, CellularAutomatonRNG cellularAutomatonRNG) {
    if (int0 <= 0) {
      return 0;
    } else {
      id++;
      if (id >= 10000) {
        id = 0;
      }

      return cellularAutomatonRNG.nextInt(int0);
    }
  }

  static int Next(int int0) { return Next(); }

  static long Next(long long0, CellularAutomatonRNG cellularAutomatonRNG) {
    return Next();
  }

  static long Next(long long0) { return Next(); }

  static int Next(int int1, int int0,
                  CellularAutomatonRNG cellularAutomatonRNG) {
    if (int0 == int1) {
      return int1;
    } else {
      if (int1 > int0) {
        int int2 = int1;
        int1 = int0;
        int0 = int2;
      }

      id++;
      if (id >= 10000) {
        id = 0;
      }

      int int3 = cellularAutomatonRNG.nextInt(int0 - int1);
      return int3 + int1;
    }
  }

  static int Next(int int0, int int1) { return Next(); }

  static long Next(long long1, long long0,
                   CellularAutomatonRNG cellularAutomatonRNG) {
    if (long0 == long1) {
      return long1;
    } else {
      if (long1 > long0) {
        long long2 = long1;
        long1 = long0;
        long0 = long2;
      }

      id++;
      if (id >= 10000) {
        id = 0;
      }

      int int0 = cellularAutomatonRNG.nextInt((int)(long0 - long1));
      return int0 + long1;
    }
  }

  static long Next(long long0, long long1) { return Next(); }

  static float Next(float float1, float float0,
                    CellularAutomatonRNG cellularAutomatonRNG) {
    if (float0 == float1) {
      return float1;
    } else {
      if (float1 > float0) {
        float float2 = float1;
        float1 = float0;
        float0 = float2;
      }

      id++;
      if (id >= 10000) {
        id = 0;
      }

      return float1 + cellularAutomatonRNG.nextFloat() * (float0 - float1);
    }
  }

  static float Next(float float0, float float1) { return Next(); }

  static bool NextBool(int int0) { return Next(); }

  static int AdjustForFramerate(int int0) {
    if (GameServer.bServer) {
      int0 = (int)(int0 * 0.33333334F);
    } else {
      int0 = (int)(int0 * (PerformanceSettings.getLockFPS() / 30.0F));
    }

    return int0;
  }

public
  static final class PZSeedGenerator implements SeedGenerator {
  private
    static final SeedGenerator[] GENERATORS =
        new SeedGenerator[]{std::make_unique<SecureRandomSeedGenerator>()};

  private
    PZSeedGenerator() {}

  public
    byte[] generateSeed(int int0) {
      for (auto &seedGenerator : GENERATORS)
        try {
          return seedGenerator.generateSeed(int0);
        } catch (SeedException seedException) {
        }
    }

    throw new IllegalStateException(
        "All available seed generation strategies failed.");
  }
}
}
} // namespace core
} // namespace zombie
