#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Lister {
public:
   private const Class<ItemT> itemType;

   public Lister$Pack(Class<ItemT> itemType) {
      this.itemType = itemType;
   }

   public ItemT[] build() {
      return (ItemT[])super.toArray((Object[])Array.newInstance(this.itemType, this.size()));
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
