#pragma once
#include <cstdint>
#include <memory>
#include <string>
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
class StorySoundEvent {
public:
  std::string name;
protected
  ArrayList<EventSound> eventSounds = std::make_unique<ArrayList<>>();

public
  StorySoundEvent() { this("Unnamed"); }

public
  StorySoundEvent(const std::string &_name) { this.name = _name; }

  std::string getName() { return this.name; }

  void setName(const std::string &_name) { this.name = _name; }

public
  ArrayList<EventSound> getEventSounds() { return this.eventSounds; }

  void setEventSounds(ArrayList<EventSound> _eventSounds) {
    this.eventSounds = _eventSounds;
  }
}
} // namespace StorySounds
} // namespace radio
} // namespace zombie
