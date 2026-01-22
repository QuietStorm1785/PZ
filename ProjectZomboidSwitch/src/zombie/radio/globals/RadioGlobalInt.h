#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/radio/globals/RadioGlobalInt/1.h"

namespace zombie {
namespace radio {
namespace globals {


class RadioGlobalInt : public RadioGlobal {
public:
    public RadioGlobalInt(int var1) {
      super(var1, RadioGlobalType.int);
   }

    public RadioGlobalInt(const std::string& var1, int var2) {
      super(var1, var2, RadioGlobalType.int);
   }

    int getValue() {
      return (int)this.value;
   }

    void setValue(int var1) {
      this.value = var1;
   }

    std::string getString() {
      return ((int)this.value);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    CompareResult compare(RadioGlobal var1, CompareMethod var2) {
      if (dynamic_cast<RadioGlobalInt*>(var1) != nullptr var3) {
         switch (1.$SwitchMap$zombie$radio$globals$CompareMethod[var2.ordinal()]) {
            case 1:
               return (int)this.value == var3.getValue() ? CompareResult.True : CompareResult.False;
            case 2:
               return (int)this.value != var3.getValue() ? CompareResult.True : CompareResult.False;
            case 3:
               return (int)this.value < var3.getValue() ? CompareResult.True : CompareResult.False;
            case 4:
               return (int)this.value > var3.getValue() ? CompareResult.True : CompareResult.False;
            case 5:
               return (int)this.value <= var3.getValue() ? CompareResult.True : CompareResult.False;
            case 6:
               return (int)this.value >= var3.getValue() ? CompareResult.True : CompareResult.False;
            default:
               return CompareResult.Invalid;
         }
      } else {
         return CompareResult.Invalid;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool setValue(RadioGlobal var1, EditGlobalOps var2) {
      if (dynamic_cast<RadioGlobalInt*>(var1) != nullptr var3) {
         switch (1.$SwitchMap$zombie$radio$globals$EditGlobalOps[var2.ordinal()]) {
            case 1:
               this.value = var3.getValue();
    return true;
            case 2:
               this.value = (int)this.value + var3.getValue();
    return true;
            case 3:
               this.value = (int)this.value - var3.getValue();
    return true;
         }
      }

    return false;
   }
}
} // namespace globals
} // namespace radio
} // namespace zombie
