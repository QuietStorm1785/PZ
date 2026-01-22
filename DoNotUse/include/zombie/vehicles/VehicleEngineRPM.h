#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"
#include "zombie/scripting/objects/BaseScriptObject.h"

namespace zombie {
namespace vehicles {


class VehicleEngineRPM : public BaseScriptObject {
public:
    static const int MAX_GEARS = 8;
    static const int VERSION1 = 1;
    static const int VERSION = 1;
    std::string m_name;
   public const EngineRPMData[] m_rpmData = new EngineRPMData[8];

    std::string getName() {
      return this.m_name;
   }

    void Load(const std::string& var1, const std::string& var2) {
      this.m_name = var1;
    int var3 = -1;
    Block var4 = ScriptParser.parse(var2);
      var4 = (Block)var4.children.get(0);

      for (Value var6 : var4.values) {
    std::string var7 = var6.getKey().trim();
    std::string var8 = var6.getValue().trim();
         if ("VERSION" == var7)) {
            var3 = PZMath.tryParseInt(var8, -1);
            if (var3 < 0 || var3 > 1) {
               throw RuntimeException(std::string.format("unknown vehicleEngineRPM VERSION \"%s\"", var8));
            }
         }
      }

      if (var3 == -1) {
         throw RuntimeException(std::string.format("unknown vehicleEngineRPM VERSION \"%s\"", var4.type));
      } else {
    int var10 = 0;

         for (Block var12 : var4.children) {
            if (!"data" == var12.type)) {
               throw RuntimeException(std::string.format("unknown block vehicleEngineRPM.%s", var12.type));
            }

            if (var10 == 8) {
               throw RuntimeException(std::string.format("too many vehicleEngineRPM.data blocks, max is %d", 8));
            }

            this.m_rpmData[var10] = std::make_unique<EngineRPMData>();
            this.LoadData(var12, this.m_rpmData[var10]);
            var10++;
         }
      }
   }

    void LoadData(Block var1, EngineRPMData var2) {
      for (Value var4 : var1.values) {
    std::string var5 = var4.getKey().trim();
    std::string var6 = var4.getValue().trim();
         if ("afterGearChange" == var5)) {
            var2.afterGearChange = PZMath.tryParseFloat(var6, 0.0F);
         } else {
            if (!"gearChange" == var5)) {
               throw RuntimeException(std::string.format("unknown value vehicleEngineRPM.data.%s", var4.string));
            }

            var2.gearChange = PZMath.tryParseFloat(var6, 0.0F);
         }
      }

      for (Block var8 : var1.children) {
         if (!"xxx" == var8.type)) {
            throw RuntimeException(std::string.format("unknown block vehicleEngineRPM.data.%s", var8.type));
         }
      }
   }

    void reset() {
      for (int var1 = 0; var1 < this.m_rpmData.length; var1++) {
         if (this.m_rpmData[var1] != nullptr) {
            this.m_rpmData[var1].reset();
         }
      }
   }
}
} // namespace vehicles
} // namespace zombie
