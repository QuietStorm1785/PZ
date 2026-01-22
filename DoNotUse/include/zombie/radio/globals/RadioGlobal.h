#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace globals {

class RadioGlobal {
public:
    std::string name;
    T value;
    RadioGlobalType type = RadioGlobalType.Invalid;

    protected RadioGlobal(T var1, RadioGlobalType var2) {
      this(nullptr, (T)var1, var2);
   }

    protected RadioGlobal(const std::string& var1, T var2, RadioGlobalType var3) {
      this.name = var1;
      this.value = (T)var2;
      this.type = var3;
   }

    RadioGlobalType getType() {
      return this.type;
   }

    std::string getName() {
      return this.name;
   }

   public abstract std::string getString();

   public abstract CompareResult compare(RadioGlobal var1, CompareMethod var2);

   public abstract boolean setValue(RadioGlobal var1, EditGlobalOps var2);
}
} // namespace globals
} // namespace radio
} // namespace zombie
