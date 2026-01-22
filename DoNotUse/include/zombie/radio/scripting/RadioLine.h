#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace scripting {

class RadioLine {
public:
    float r = 1.0F;
    float g = 1.0F;
    float b = 1.0F;
    std::string text = "<!text missing!>";
    std::string effects = "";
    float airTime = -1.0F;

    public RadioLine(const std::string& var1, float var2, float var3, float var4) {
      this(var1, var2, var3, var4, nullptr);
   }

    public RadioLine(const std::string& var1, float var2, float var3, float var4, const std::string& var5) {
      this.text = var1 != nullptr ? var1 : this.text;
      this.r = var2;
      this.g = var3;
      this.b = var4;
      this.effects = var5 != nullptr ? var5 : this.effects;
   }

    float getR() {
      return this.r;
   }

    float getG() {
      return this.g;
   }

    float getB() {
      return this.b;
   }

    std::string getText() {
      return this.text;
   }

    std::string getEffectsString() {
      return this.effects;
   }

    bool isCustomAirTime() {
      return this.airTime > 0.0F;
   }

    float getAirTime() {
      return this.airTime;
   }

    void setAirTime(float var1) {
      this.airTime = var1;
   }

    void setText(const std::string& var1) {
      this.text = var1;
   }
}
} // namespace scripting
} // namespace radio
} // namespace zombie
