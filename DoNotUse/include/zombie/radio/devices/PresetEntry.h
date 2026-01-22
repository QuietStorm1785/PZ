#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace devices {

class PresetEntry {
public:
    std::string name = "New preset";
    int frequency = 93200;

    public PresetEntry() {
   }

    public PresetEntry(const std::string& var1, int var2) {
      this.name = var1;
      this.frequency = var2;
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

    int getFrequency() {
      return this.frequency;
   }

    void setFrequency(int var1) {
      this.frequency = var1;
   }
}
} // namespace devices
} // namespace radio
} // namespace zombie
