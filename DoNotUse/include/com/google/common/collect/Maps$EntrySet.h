#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Sets/ImprovedAbstractSet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   abstract Map<K, V> map();

    int size() {
      return this.map().size();
   }

    void clear() {
      this.map().clear();
   }

    bool contains(void* o) {
      if (!(dynamic_cast<Entry*>(o) != nullptr)) {
    return false;
      } else {
         Entry<?, ?> entry = (Entry<?, ?>)o;
    void* key = entry.getKey();
    V value = (V)Maps.safeGet(this.map(), key);
         return Objects.equal(value, entry.getValue()) && (value != nullptr || this.map().containsKey(key));
      }
   }

    bool isEmpty() {
      return this.map().empty();
   }

    bool remove(void* o) {
      if (this.contains(o)) {
         Entry<?, ?> entry = (Entry<?, ?>)o;
         return this.map().keySet().remove(entry.getKey());
      } else {
    return false;
      }
   }

    bool removeAll(Collection<?> c) {
      try {
         return super.removeAll((Collection)Preconditions.checkNotNull(c));
      } catch (UnsupportedOperationException var3) {
         return Sets.removeAllImpl(this, c.iterator());
      }
   }

    bool retainAll(Collection<?> c) {
      try {
         return super.retainAll((Collection)Preconditions.checkNotNull(c));
      } catch (UnsupportedOperationException var7) {
         Set<Object> keys = Sets.newHashSetWithExpectedSize(c.size());

    for (auto& o : c)            if (this.contains(o)) {
               Entry<?, ?> entry = (Entry<?, ?>)o;
               keys.push_back(entry.getKey());
            }
         }

         return this.map().keySet().retainAll(keys);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
