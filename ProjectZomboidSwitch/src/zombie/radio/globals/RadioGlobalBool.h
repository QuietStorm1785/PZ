#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/radio/globals/RadioGlobalBool/1.h"

namespace zombie {
namespace radio {
namespace globals {


class RadioGlobalBool : public RadioGlobal {
public:
    public RadioGlobalBool(bool var1) {
      super(var1, RadioGlobalType.bool);
   }

    public RadioGlobalBool(const std::string& var1, bool var2) {
      super(var1, var2, RadioGlobalType.bool);
   }

    bool getValue() {
      return (bool)this.value;
   }

    void setValue(bool var1) {
      this.value = var1;
   }

    std::string getString() {
      return ((bool)this.value);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    CompareResult compare(RadioGlobal var1, CompareMethod var2) {
      if (dynamic_cast<RadioGlobalBool*>(var1) != nullptr var3) {
         switch (1.$SwitchMap$zombie$radio$globals$CompareMethod[var2.ordinal()]) {
            case 1:
               return ((bool)this.value) == var3.getValue()) ? CompareResult.True : CompareResult.False;
            case 2:
               return !((bool)this.value) == var3.getValue()) ? CompareResult.True : CompareResult.False;
            default:
               return CompareResult.Invalid;
         }
      } else {
         return CompareResult.Invalid;
      }
   }

    bool setValue(RadioGlobal var1, EditGlobalOps var2) {
      if (var2 == EditGlobalOps.set) && dynamic_cast<RadioGlobalBool*>(var1) != nullptr) {
         this.value = ((RadioGlobalBool)var1).getValue();
    return true;
      } else {
    return false;
      }
   }
}
} // namespace globals
} // namespace radio
} // namespace zombie
