#pragma once
#include "zombie/core/Color.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace StorySounds {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Turbo
 */
class EventSound {
public:
 std::string name;
 Color color = new Color(1.0F, 1.0F, 1.0F);
protected
 ArrayList<DataPoint> dataPoints = std::make_unique<ArrayList<>>();
protected
 ArrayList<StorySound> storySounds = std::make_unique<ArrayList<>>();

public
 EventSound() { this("Unnamed"); }

public
 EventSound(std::string_view _name) { this->name = _name; }

 std::string getName() { return this->name; }

 void setName(std::string_view _name) { this->name = _name; }

 Color getColor() { return this->color; }

 void setColor(Color _color) { this->color = _color; }

public
 ArrayList<DataPoint> getDataPoints() { return this->dataPoints; }

 void setDataPoints(ArrayList<DataPoint> _dataPoints) {
 this->dataPoints = _dataPoints;
 }

public
 ArrayList<StorySound> getStorySounds() { return this->storySounds; }

 void setStorySounds(ArrayList<StorySound> _storySounds) {
 this->storySounds = _storySounds;
 }
}
} // namespace StorySounds
} // namespace radio
} // namespace zombie
