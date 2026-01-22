#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace core {
namespace Collections {


class AbstractEntry {
public:
    const TypeK _key;
    TypeV _val;

    public AbstractEntry(TypeK var1, TypeV var2) {
      this._key = (TypeK)var1;
      this._val = (TypeV)var2;
   }

    public AbstractEntry(TypeV> var1) {
      this._key = (TypeK)var1.getKey();
      this._val = (TypeV)var1.getValue();
   }

    std::string toString() {
      return this._key + "=" + this._val;
   }

    TypeK getKey() {
      return this._key;
   }

    TypeV getValue() {
      return this._val;
   }

    bool equals(void* var1) {
      return !(dynamic_cast<Entry*>(var1) != nullptr var2) ? false : eq(this._key, var2.getKey()) && eq(this._val, var2.getValue());
   }

    int hashCode() {
      return (this._key == nullptr ? 0 : this._key.hashCode()) ^ (this._val == nullptr ? 0 : this._val.hashCode());
   }

    static bool eq(void* var0, void* var1) {
    return var0 = = nullptr ? var1 == nullptr : var0 == var1);
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
