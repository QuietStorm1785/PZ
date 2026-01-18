#include "zombie/iso/weather/Temperature.h"

namespace zombie {
namespace iso {
namespace weather {

std::string Temperature::getCelsiusPostfix() {
  // TODO: Implement getCelsiusPostfix
  return "";
}

std::string Temperature::getFahrenheitPostfix() {
  // TODO: Implement getFahrenheitPostfix
  return "";
}

std::string Temperature::getTemperaturePostfix() {
  // TODO: Implement getTemperaturePostfix
  return "";
}

std::string Temperature::getTemperatureString(float celsius) {
  // TODO: Implement getTemperatureString
  return "";
}

float Temperature::CelsiusToFahrenheit(float celsius) {
  // TODO: Implement CelsiusToFahrenheit
  return 0;
}

float Temperature::FahrenheitToCelsius(float fahrenheit) {
  // TODO: Implement FahrenheitToCelsius
  return 0;
}

float Temperature::WindchillCelsiusKph(float t, float v) {
  // TODO: Implement WindchillCelsiusKph
  return 0;
}

float Temperature::getTrueInsulationValue(float insulation) {
  // TODO: Implement getTrueInsulationValue
  return 0;
}

float Temperature::getTrueWindresistanceValue(float windresist) {
  // TODO: Implement getTrueWindresistanceValue
  return 0;
}

void Temperature::reset() {
  // TODO: Implement reset
}

float Temperature::getFractionForRealTimeRatePerMin(float rate) {
  // TODO: Implement getFractionForRealTimeRatePerMin
  return 0;
}

Color Temperature::getValueColor(float val) {
  // TODO: Implement getValueColor
  return nullptr;
}

float Temperature::getWindChillAmountForPlayer(IsoPlayer player) {
  // TODO: Implement getWindChillAmountForPlayer
  return 0;
}

} // namespace weather
} // namespace iso
} // namespace zombie
