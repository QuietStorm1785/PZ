#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableMultiset/EntrySetSerializedForm.h"
#include "com/google/common/collect/ImmutableSet/Indexed.h"
#include "com/google/common/collect/Multiset/Entry.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMultiset {
public:
    static const long serialVersionUID = 0L;

   private ImmutableMultiset$EntrySet(ImmutableMultiset var1) {
      this.this$0 = var1;
   }

    bool isPartialView() {
      return this.this$0.isPartialView();
   }

   Entry<E> get(int index) {
      return this.this$0.getEntry(index);
   }

    int size() {
      return this.this$0.elementSet().size();
   }

    bool contains(void* o) {
      if (dynamic_cast<Entry*>(o) != nullptr) {
         Entry<?> entry = (Entry<?>)o;
         if (entry.getCount() <= 0) {
    return false;
         } else {
    int count = this.this$0.count(entry.getElement());
    return count = = entry.getCount();
         }
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.this$0.hashCode();
   }

    void* writeReplace() {
      return std::make_shared<EntrySetSerializedForm>(this.this$0);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
