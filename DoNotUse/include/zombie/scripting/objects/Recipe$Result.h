#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace scripting {
namespace objects {

class Recipe {
public:
    std::string module = nullptr;
    std::string type;
    int count = 1;
    int drainableCount = 0;

    std::string getType() {
      return this.type;
   }

    void setType(const std::string& var1) {
      this.type = var1;
   }

    int getCount() {
      return this.count;
   }

    void setCount(int var1) {
      this.count = var1;
   }

    std::string getModule() {
      return this.module;
   }

    void setModule(const std::string& var1) {
      this.module = var1;
   }

    std::string getFullType() {
      return this.module + "." + this.type;
   }

    int getDrainableCount() {
      return this.drainableCount;
   }

    void setDrainableCount(int var1) {
      this.drainableCount = var1;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
