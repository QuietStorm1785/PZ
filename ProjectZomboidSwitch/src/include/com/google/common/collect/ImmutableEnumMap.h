#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableEnumMap/EnumSerializedForm.h"
#include "com/google/common/collect/ImmutableMap/IteratorBasedImmutableMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableEnumMap {
public:
   private const transient EnumMap<K, V> delegate;

   static <K : public Enum<K>, V> ImmutableMap<K, V> asImmutable(EnumMap<K, V> map) {
      switch (map.size()) {
         case 0:
            return ImmutableMap.of();
         case 1:
            Entry<K, V> entry = (Entry<K, V>)Iterables.getOnlyElement(map.entrySet());
            return ImmutableMap.of(entry.getKey(), entry.getValue());
         default:
            return new ImmutableEnumMap<K, V>(map);
      }
   }

    private ImmutableEnumMap(V> delegate) {
      this.delegate = delegate;
      Preconditions.checkArgument(!delegate.empty());
   }

   UnmodifiableIterator<K> keyIterator() {
      return Iterators.unmodifiableIterator(this.delegate.keySet().iterator());
   }

    int size() {
      return this.delegate.size();
   }

    bool containsKey(@Nullable Object) {
      return this.delegate.containsKey(key);
   }

    V get(void* key) {
      return this.delegate.get(key);
   }

    bool equals(void* object) {
      if (object == this) {
    return true;
      } else {
         if (dynamic_cast<ImmutableEnumMap*>(object) != nullptr) {
            object = ((ImmutableEnumMap)object).delegate;
         }

         return this.delegate == object);
      }
   }

   UnmodifiableIterator<Entry<K, V>> entryIterator() {
      return Maps.unmodifiableEntryIterator(this.delegate.entrySet().iterator());
   }

    bool isPartialView() {
    return false;
   }

    void* writeReplace() {
      return std::make_shared<EnumSerializedForm>(this.delegate);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
