#pragma once
#include "zombie/core/math/PZMath.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/objects/BaseScriptObject.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VehicleEngineRPM : public BaseScriptObject {
public:
  static const int MAX_GEARS = 8;
  static const int VERSION1 = 1;
  static const int VERSION = 1;
  std::string m_name;
public
  final EngineRPMData[] m_rpmData = new EngineRPMData[8];

  std::string getName() { return this.m_name; }

  void Load(const std::string &name, const std::string &totalFile) {
    this.m_name = name;
    int int0 = -1;
    ScriptParser.Block block0 = ScriptParser.parse(totalFile);
    block0 = block0.children.get(0);

    for (ScriptParser.Value value : block0.values) {
      std::string string0 = value.getKey().trim();
      std::string string1 = value.getValue().trim();
      if ("VERSION" == string0)) {
          int0 = PZMath.tryParseInt(string1, -1);
          if (int0 < 0 || int0 > 1) {
            throw new RuntimeException(String.format(
                "unknown vehicleEngineRPM VERSION \"%s\"", string1));
          }
        }
    }

    if (int0 == -1) {
      throw new RuntimeException(String.format(
          "unknown vehicleEngineRPM VERSION \"%s\"", block0.type));
    } else {
      int int1 = 0;

      for (ScriptParser.Block block1 : block0.children) {
        if (!"data" == block1.type)) {
            throw new RuntimeException(String.format(
                "unknown block vehicleEngineRPM.%s", block1.type));
          }

        if (int1 == 8) {
          throw new RuntimeException(String.format(
              "too many vehicleEngineRPM.data blocks, max is %d", 8));
        }

        this.m_rpmData[int1] = std::make_unique<EngineRPMData>();
        this.LoadData(block1, this.m_rpmData[int1]);
        int1++;
      }
    }
  }

  void LoadData(ScriptParser.Block block0, EngineRPMData engineRPMData) {
    for (ScriptParser.Value value : block0.values) {
      std::string string0 = value.getKey().trim();
      std::string string1 = value.getValue().trim();
      if ("afterGearChange" == string0)) {
          engineRPMData.afterGearChange = PZMath.tryParseFloat(string1, 0.0F);
        }
      else {
        if (!"gearChange" == string0)) {
            throw new RuntimeException(String.format(
                "unknown value vehicleEngineRPM.data.%s", value.string));
          }

        engineRPMData.gearChange = PZMath.tryParseFloat(string1, 0.0F);
      }
    }

    for (ScriptParser.Block block1 : block0.children) {
      if (!"xxx" == block1.type)) {
          throw new RuntimeException(String.format(
              "unknown block vehicleEngineRPM.data.%s", block1.type));
        }
    }
  }

  void reset() {
    for (int int0 = 0; int0 < this.m_rpmData.length; int0++) {
      if (this.m_rpmData[int0] != nullptr) {
        this.m_rpmData[int0].reset();
      }
    }
  }
}
} // namespace vehicles
} // namespace zombie
