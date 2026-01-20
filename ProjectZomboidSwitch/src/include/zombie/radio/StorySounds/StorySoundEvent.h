#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace StorySounds {


class StorySoundEvent {
public:
    std::string name;
   protected std::vector<EventSound> eventSounds = std::make_unique<std::vector<>>();

    public StorySoundEvent() {
      this("Unnamed");
   }

    public StorySoundEvent(const std::string& var1) {
      this.name = var1;
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

   public std::vector<EventSound> getEventSounds() {
      return this.eventSounds;
   }

    void setEventSounds(std::vector<EventSound> var1) {
      this.eventSounds = var1;
   }
}
} // namespace StorySounds
} // namespace radio
} // namespace zombie
