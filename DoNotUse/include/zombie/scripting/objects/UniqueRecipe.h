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


class UniqueRecipe : public BaseScriptObject {
public:
    std::string name = nullptr;
    std::string baseRecipe = nullptr;
   private const std::vector<std::string> items = std::make_unique<std::vector<>>();
    int hungerBonus = 0;
    int hapinessBonus = 0;
    int boredomBonus = 0;

    public UniqueRecipe(const std::string& var1) {
      this.setName(var1);
   }

    void Load(const std::string& var1, std::string[] var2) {
      for (int var3 = 0; var3 < var2.length; var3++) {
         if (!var2[var3].trim().empty() && var2[var3].contains(":")) {
            std::string[] var4 = var2[var3].split(":");
    std::string var5 = var4[0].trim();
    std::string var6 = var4[1].trim();
            if (var5 == "BaseRecipeItem")) {
               this.setBaseRecipe(var6);
            } else if (var5 == "Item")) {
               this.items.push_back(var6);
            } else if (var5 == "Hunger")) {
               this.setHungerBonus(int.parseInt(var6));
            } else if (var5 == "Hapiness")) {
               this.setHapinessBonus(int.parseInt(var6));
            } else if (var5 == "Boredom")) {
               this.setBoredomBonus(int.parseInt(var6));
            }
         }
      }
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

    std::string getBaseRecipe() {
      return this.baseRecipe;
   }

    void setBaseRecipe(const std::string& var1) {
      this.baseRecipe = var1;
   }

    int getHungerBonus() {
      return this.hungerBonus;
   }

    void setHungerBonus(int var1) {
      this.hungerBonus = var1;
   }

    int getHapinessBonus() {
      return this.hapinessBonus;
   }

    void setHapinessBonus(int var1) {
      this.hapinessBonus = var1;
   }

   public std::vector<std::string> getItems() {
      return this.items;
   }

    int getBoredomBonus() {
      return this.boredomBonus;
   }

    void setBoredomBonus(int var1) {
      this.boredomBonus = var1;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
