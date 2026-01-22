#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/radio/globals/RadioGlobalString/1.h"

namespace zombie {
namespace radio {
namespace globals {


class RadioGlobalString : public RadioGlobal {
public:
    public RadioGlobalString(const std::string& var1) {
      super(var1, RadioGlobalType.std::string);
   }

    public RadioGlobalString(const std::string& var1, const std::string& var2) {
      super(var1, var2, RadioGlobalType.std::string);
   }

    std::string getValue() {
      return (std::string)this.value;
   }

    void setValue(const std::string& var1) {
      this.value = var1;
   }

    std::string getString() {
      return (std::string)this.value;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    CompareResult compare(RadioGlobal var1, CompareMethod var2) {
      if (dynamic_cast<RadioGlobalString*>(var1) != nullptr var3) {
         switch (1.$SwitchMap$zombie$radio$globals$CompareMethod[var2.ordinal()]) {
            case 1:
               return ((std::string)this.value) == var3.getValue()) ? CompareResult.True : CompareResult.False;
            case 2:
               return !((std::string)this.value) == var3.getValue()) ? CompareResult.True : CompareResult.False;
            default:
               return CompareResult.Invalid;
         }
      } else {
         return CompareResult.Invalid;
      }
   }

    bool setValue(RadioGlobal var1, EditGlobalOps var2) {
      if (var2 == EditGlobalOps.set) && dynamic_cast<RadioGlobalString*>(var1) != nullptr) {
         this.value = ((RadioGlobalString)var1).getValue();
    return true;
      } else {
    return false;
      }
   }
}
} // namespace globals
} // namespace radio
} // namespace zombie
