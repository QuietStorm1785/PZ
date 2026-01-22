#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace erosion {

class ErosionConfig {
public:
    bool enabled = false;
    int startday = 26;
    int startmonth = 11;

    bool getEnabled() {
      return this.enabled;
   }

    int getStartDay() {
      return this.startday;
   }

    int getStartMonth() {
      return this.startmonth;
   }
}
} // namespace erosion
} // namespace zombie
