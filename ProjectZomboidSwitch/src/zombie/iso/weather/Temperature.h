#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"

namespace zombie {
namespace iso {
namespace weather {


class Temperature {
public:
    static bool DO_DEFAULT_BASE = false;
    static bool DO_DAYLEN_MOD = true;
    static std::string CELSIUS_POSTFIX = "°C";
    static std::string FAHRENHEIT_POSTFIX = "°F";
    static const float skinCelciusMin = 20.0F;
    static const float skinCelciusFavorable = 33.0F;
    static const float skinCelciusMax = 42.0F;
    static const float homeostasisDefault = 37.0F;
    static const float FavorableNakedTemp = 27.0F;
    static const float FavorableRoomTemp = 22.0F;
    static const float coreCelciusMin = 20.0F;
    static const float coreCelciusMax = 42.0F;
    static const float neutralZone = 27.0F;
    static const float Hypothermia_1 = 36.5F;
    static const float Hypothermia_2 = 35.0F;
    static const float Hypothermia_3 = 30.0F;
    static const float Hypothermia_4 = 25.0F;
    static const float Hyperthermia_1 = 37.5F;
    static const float Hyperthermia_2 = 39.0F;
    static const float Hyperthermia_3 = 40.0F;
    static const float Hyperthermia_4 = 41.0F;
    static const float TrueInsulationMultiplier = 2.0F;
    static const float TrueWindresistMultiplier = 1.0F;
    static const float BodyMinTemp = 20.0F;
    static const float BodyMaxTemp = 42.0F;
    static std::string cacheTempString = "";
    static float cacheTemp = -9000.0F;
    static Color tempColor = std::make_shared<Color>(1.0F, 1.0F, 1.0F, 1.0F);
    static Color col_0 = std::make_shared<Color>(29, 34, 237);
    static Color col_25 = std::make_shared<Color>(0, 255, 234);
    static Color col_50 = std::make_shared<Color>(84, 255, 55);
    static Color col_75 = std::make_shared<Color>(255, 246, 0);
    static Color col_100 = std::make_shared<Color>(255, 0, 0);

    static std::string getCelsiusPostfix() {
    return CELSIUS_POSTFIX;
   }

    static std::string getFahrenheitPostfix() {
    return FAHRENHEIT_POSTFIX;
   }

    static std::string getTemperaturePostfix() {
      return Core.OptionTemperatureDisplayCelsius ? CELSIUS_POSTFIX : FAHRENHEIT_POSTFIX;
   }

    static std::string getTemperatureString(float var0) {
    float var1 = Core.OptionTemperatureDisplayCelsius ? var0 : CelsiusToFahrenheit(var0);
      var1 = Math.round(var1 * 10.0F) / 10.0F;
      if (cacheTemp != var1) {
         cacheTemp = var1;
         cacheTempString = var1 + " " + getTemperaturePostfix();
      }

    return cacheTempString;
   }

    static float CelsiusToFahrenheit(float var0) {
      return var0 * 1.8F + 32.0F;
   }

    static float FahrenheitToCelsius(float var0) {
      return (var0 - 32.0F) / 1.8F;
   }

    static float WindchillCelsiusKph(float var0, float var1) {
    float var2 = 13.12F + 0.6215F * var0 - 11.37F * (float)Math.pow(var1, 0.16F) + 0.3965F * var0 * (float)Math.pow(var1, 0.16F);
      return var2 < var0 ? var2 : var0;
   }

    static float getTrueInsulationValue(float var0) {
      return var0 * 2.0F + 0.5F * var0 * var0 * var0;
   }

    static float getTrueWindresistanceValue(float var0) {
      return var0 * 1.0F + 0.5F * var0 * var0;
   }

    static void reset() {
   }

    static float getFractionForRealTimeRatePerMin(float var0) {
      if (DO_DEFAULT_BASE) {
         return var0 / (1440.0F / SandboxOptions.instance.getDayLengthMinutesDefault());
      } else if (!DO_DAYLEN_MOD) {
         return var0 / (1440.0F / SandboxOptions.instance.getDayLengthMinutes());
      } else {
    float var1 = (float)SandboxOptions.instance.getDayLengthMinutes() / SandboxOptions.instance.getDayLengthMinutesDefault();
         if (var1 < 1.0F) {
            var1 = 0.5F + 0.5F * var1;
         } else if (var1 > 1.0F) {
            var1 = 1.0F + var1 / 16.0F;
         }

         return var0 / (1440.0F / SandboxOptions.instance.getDayLengthMinutes()) * var1;
      }
   }

    static Color getValueColor(float var0) {
      var0 = ClimateManager.clamp(0.0F, 1.0F, var0);
      tempColor.set(0.0F, 0.0F, 0.0F, 1.0F);
    float var1 = 0.0F;
      if (var0 < 0.25F) {
         var1 = var0 / 0.25F;
         col_0.interp(col_25, var1, tempColor);
      } else if (var0 < 0.5F) {
         var1 = (var0 - 0.25F) / 0.25F;
         col_25.interp(col_50, var1, tempColor);
      } else if (var0 < 0.75F) {
         var1 = (var0 - 0.5F) / 0.25F;
         col_50.interp(col_75, var1, tempColor);
      } else {
         var1 = (var0 - 0.75F) / 0.25F;
         col_75.interp(col_100, var1, tempColor);
      }

    return tempColor;
   }

    static float getWindChillAmountForPlayer(IsoPlayer var0) {
      if (var0.getVehicle() == nullptr && (var0.getSquare() == nullptr || !var0.getSquare().isInARoom())) {
    ClimateManager var1 = ClimateManager.getInstance();
    float var2 = var1.getAirTemperatureForCharacter(var0, true);
    float var3 = 0.0F;
         if (var2 < var1.getTemperature()) {
            var3 = var1.getTemperature() - var2;
         }

    return var3;
      } else {
         return 0.0F;
      }
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
