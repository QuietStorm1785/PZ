#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/interfaces/IListBoxItem.h"

namespace zombie {
namespace characters {
namespace traits {


class ObservationFactory {
public:
    std::string traitID;
    std::string name;
    std::string description;
   public std::vector<std::string> MutuallyExclusive = new std::vector<>(0);

   public ObservationFactory$Observation(std::string var1, std::string var2, std::string var3) {
      this.setTraitID(var1);
      this.setName(var2);
      this.setDescription(var3);
   }

    std::string getLabel() {
      return this.getName();
   }

    std::string getLeftLabel() {
      return this.getName();
   }

    std::string getRightLabel() {
    return nullptr;
   }

    std::string getDescription() {
      return this.description;
   }

    void setDescription(const std::string& var1) {
      this.description = var1;
   }

    std::string getTraitID() {
      return this.traitID;
   }

    void setTraitID(const std::string& var1) {
      this.traitID = var1;
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }
}
} // namespace traits
} // namespace characters
} // namespace zombie
