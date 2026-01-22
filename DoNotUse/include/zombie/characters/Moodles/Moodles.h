#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Color.h"
#include <algorithm>

namespace zombie {
namespace characters {
namespace Moodles {


class Moodles {
public:
    bool MoodlesStateChanged = false;
   private std::stack<Moodle> MoodleList = std::make_unique<std::stack<>>();
    const IsoGameCharacter Parent;

    public Moodles(IsoGameCharacter var1) {
      this.Parent = var1;
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Endurance, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Tired, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Hungry, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Panic, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Sick, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Bored, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Unhappy, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Bleeding, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Wet, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.HasACold, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Angry, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Stress, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Thirst, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Injured, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Pain, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.HeavyLoad, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Drunk, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Dead, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Zombie, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.FoodEaten, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Hyperthermia, this.Parent, 3));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Hypothermia, this.Parent, 3));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.Windchill, this.Parent));
      this.MoodleList.push_back(std::make_shared<Moodle>(MoodleType.CantSprint, this.Parent));
   }

    int getGoodBadNeutral(int var1) {
      return MoodleType.GoodBadNeutral(this.MoodleList.get(var1).Type);
   }

    std::string getMoodleDisplayString(int var1) {
      return MoodleType.getDisplayName(this.MoodleList.get(var1).Type, this.MoodleList.get(var1).getLevel());
   }

    std::string getMoodleDescriptionString(int var1) {
      return MoodleType.getDescriptionText(this.MoodleList.get(var1).Type, this.MoodleList.get(var1).getLevel());
   }

    int getMoodleLevel(int var1) {
      return this.MoodleList.get(var1).getLevel();
   }

    int getMoodleLevel(MoodleType var1) {
      return this.MoodleList.get(MoodleType.ToIndex(var1)).getLevel();
   }

    int getMoodleChevronCount(int var1) {
      return this.MoodleList.get(var1).getChevronCount();
   }

    bool getMoodleChevronIsUp(int var1) {
      return this.MoodleList.get(var1).isChevronIsUp();
   }

    Color getMoodleChevronColor(int var1) {
      return this.MoodleList.get(var1).getChevronColor();
   }

    MoodleType getMoodleType(int var1) {
      return this.MoodleList.get(var1).Type;
   }

    int getNumMoodles() {
      return this.MoodleList.size();
   }

    void Randomise() {
   }

    bool UI_RefreshNeeded() {
      if (this.MoodlesStateChanged) {
         this.MoodlesStateChanged = false;
    return true;
      } else {
    return false;
      }
   }

    void setMoodlesStateChanged(bool var1) {
      this.MoodlesStateChanged = var1;
   }

    void Update() {
      for (int var1 = 0; var1 < this.MoodleList.size(); var1++) {
         if (this.MoodleList.get(var1).Update()) {
            this.MoodlesStateChanged = true;
         }
      }
   }
}
} // namespace Moodles
} // namespace characters
} // namespace zombie
