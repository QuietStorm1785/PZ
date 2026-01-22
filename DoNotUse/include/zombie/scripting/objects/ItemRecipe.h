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

class ItemRecipe {
public:
    std::string name;
    int use = -1;
    bool cooked = false;
    std::string module = nullptr;

    int getUse() {
      return this.use;
   }

    public ItemRecipe(const std::string& var1, const std::string& var2, int var3) {
      this.name = var1;
      this.use = var3;
      this.setModule(var2);
   }

    std::string getName() {
      return this.name;
   }

    std::string getModule() {
      return this.module;
   }

    void setModule(const std::string& var1) {
      this.module = var1;
   }

    std::string getFullType() {
      return this.module + "." + this.name;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
