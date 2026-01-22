#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"

namespace zombie {
namespace radio {
namespace StorySounds {


class EventSound {
public:
    std::string name;
    Color color = std::make_shared<Color>(1.0F, 1.0F, 1.0F);
   protected std::vector<DataPoint> dataPoints = std::make_unique<std::vector<>>();
   protected std::vector<StorySound> storySounds = std::make_unique<std::vector<>>();

    public EventSound() {
      this("Unnamed");
   }

    public EventSound(const std::string& var1) {
      this.name = var1;
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

    Color getColor() {
      return this.color;
   }

    void setColor(Color var1) {
      this.color = var1;
   }

   public std::vector<DataPoint> getDataPoints() {
      return this.dataPoints;
   }

    void setDataPoints(std::vector<DataPoint> var1) {
      this.dataPoints = var1;
   }

   public std::vector<StorySound> getStorySounds() {
      return this.storySounds;
   }

    void setStorySounds(std::vector<StorySound> var1) {
      this.storySounds = var1;
   }
}
} // namespace StorySounds
} // namespace radio
} // namespace zombie
