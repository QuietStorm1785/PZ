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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * TurboTuTone.
 */
class Temperature {
public:
 static bool DO_DEFAULT_BASE = false;
 static bool DO_DAYLEN_MOD = true;
 static std::string CELSIUS_POSTFIX = "\u00b0C";
 static std::string FAHRENHEIT_POSTFIX = "\u00b0F";
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
 static Color tempColor = new Color(1.0F, 1.0F, 1.0F, 1.0F);
 static Color col_0 = new Color(29, 34, 237);
 static Color col_25 = new Color(0, 255, 234);
 static Color col_50 = new Color(84, 255, 55);
 static Color col_75 = new Color(255, 246, 0);
 static Color col_100 = new Color(255, 0, 0);

 static std::string getCelsiusPostfix() {
 return CELSIUS_POSTFIX;
 }

 static std::string getFahrenheitPostfix() {
 return FAHRENHEIT_POSTFIX;
 }

 static std::string getTemperaturePostfix() {
 return Core.OptionTemperatureDisplayCelsius ? CELSIUS_POSTFIX : FAHRENHEIT_POSTFIX;
 }

 static std::string getTemperatureString(float celsius) {
 float float0 = Core.OptionTemperatureDisplayCelsius ? celsius : CelsiusToFahrenheit(celsius);
 float0 = Math.round(float0 * 10.0F) / 10.0F;
 if (cacheTemp != float0) {
 cacheTemp = float0;
 cacheTempString = float0 + " " + getTemperaturePostfix();
 }

 return cacheTempString;
 }

 static float CelsiusToFahrenheit(float celsius) {
 return celsius * 1.8F + 32.0F;
 }

 static float FahrenheitToCelsius(float fahrenheit) {
 return (fahrenheit - 32.0F) / 1.8F;
 }

 static float WindchillCelsiusKph(float t, float v) {
 float float0 = 13.12F + 0.6215F * t - 11.37F * (float)Math.pow(v, 0.16F) + 0.3965F * t * (float)Math.pow(v, 0.16F);
 return float0 < t ? float0 : t;
 }

 static float getTrueInsulationValue(float insulation) {
 return insulation * 2.0F + 0.5F * insulation * insulation * insulation;
 }

 static float getTrueWindresistanceValue(float windresist) {
 return windresist * 1.0F + 0.5F * windresist * windresist;
 }

 static void reset() {
 }

 static float getFractionForRealTimeRatePerMin(float rate) {
 if (DO_DEFAULT_BASE) {
 return rate / (1440.0F / SandboxOptions.instance.getDayLengthMinutesDefault());
 } else if (!DO_DAYLEN_MOD) {
 return rate / (1440.0F / SandboxOptions.instance.getDayLengthMinutes());
 } else {
 float float0 = (float)SandboxOptions.instance.getDayLengthMinutes() / SandboxOptions.instance.getDayLengthMinutesDefault();
 if (float0 < 1.0F) {
 float0 = 0.5F + 0.5F * float0;
 } else if (float0 > 1.0F) {
 float0 = 1.0F + float0 / 16.0F;
 }

 return rate / (1440.0F / SandboxOptions.instance.getDayLengthMinutes()) * float0;
 }
 }

 static Color getValueColor(float val) {
 val = ClimateManager.clamp(0.0F, 1.0F, val);
 tempColor.set(0.0F, 0.0F, 0.0F, 1.0F);
 float float0 = 0.0F;
 if (val < 0.25F) {
 float0 = val / 0.25F;
 col_0.interp(col_25, float0, tempColor);
 } else if (val < 0.5F) {
 float0 = (val - 0.25F) / 0.25F;
 col_25.interp(col_50, float0, tempColor);
 } else if (val < 0.75F) {
 float0 = (val - 0.5F) / 0.25F;
 col_50.interp(col_75, float0, tempColor);
 } else {
 float0 = (val - 0.75F) / 0.25F;
 col_75.interp(col_100, float0, tempColor);
 }

 return tempColor;
 }

 static float getWindChillAmountForPlayer(IsoPlayer player) {
 if (player.getVehicle() == nullptr && (player.getSquare() == nullptr || !player.getSquare().isInARoom())) {
 ClimateManager climateManager = ClimateManager.getInstance();
 float float0 = climateManager.getAirTemperatureForCharacter(player, true);
 float float1 = 0.0F;
 if (float0 < climateManager.getTemperature()) {
 float1 = climateManager.getTemperature() - float0;
 }

 return float1;
 } else {
 return 0.0F;
 }
 }
}
} // namespace weather
} // namespace iso
} // namespace zombie
