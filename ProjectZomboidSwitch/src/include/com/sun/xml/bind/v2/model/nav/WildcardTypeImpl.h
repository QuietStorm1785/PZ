#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace nav {


class WildcardTypeImpl {
public:
   private const Type[] ub;
   private const Type[] lb;

    public WildcardTypeImpl(Type[] ub, Type[] lb) {
      this.ub = ub;
      this.lb = lb;
   }

   public Type[] getUpperBounds() {
      return this.ub;
   }

   public Type[] getLowerBounds() {
      return this.lb;
   }

    int hashCode() {
      return Arrays.hashCode((Object[])this.lb) ^ Arrays.hashCode((Object[])this.ub);
   }

    bool equals(void* obj) {
      if (!(dynamic_cast<WildcardType*>(obj) != nullptr)) {
    return false;
      } else {
    WildcardType that = (WildcardType)obj;
         return Arrays == (Object[])that.getLowerBounds(), (Object[])this.lb) && Arrays == (Object[])that.getUpperBounds(), (Object[])this.ub);
      }
   }
}
} // namespace nav
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
