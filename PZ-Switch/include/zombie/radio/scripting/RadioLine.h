#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace scripting {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Turbo
 */
class RadioLine {
public:
 float r = 1.0F;
 float g = 1.0F;
 float b = 1.0F;
 std::string text = "<!text missing!>";
 std::string effects = "";
 float airTime = -1.0F;

public
 RadioLine(const std::string &txt, float red, float green, float blue) {
 this(txt, red, green, blue, nullptr);
 }

public
 RadioLine(const std::string &txt, float red, float green, float blue,
 const std::string &fx) {
 this->text = txt != nullptr ? txt : this->text;
 this->r = red;
 this->g = green;
 this->b = blue;
 this->effects = fx != nullptr ? fx : this->effects;
 }

 float getR() { return this->r; }

 float getG() { return this->g; }

 float getB() { return this->b; }

 std::string getText() { return this->text; }

 std::string getEffectsString() { return this->effects; }

 bool isCustomAirTime() { return this->airTime > 0.0F; }

 float getAirTime() { return this->airTime; }

 void setAirTime(float _airTime) { this->airTime = _airTime; }

 void setText(const std::string &_text) { this->text = _text; }
}
} // namespace scripting
} // namespace radio
} // namespace zombie
