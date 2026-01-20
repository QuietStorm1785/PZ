#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Maps/AsMapView/1EntrySetImpl.h"
#include "com/google/common/collect/Maps/ViewCachingAbstractMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   private const Set<K> set;
   const Function<? super K, V> function;

   Set<K> backingSet() {
      return this.set;
   }

   Maps$AsMapView(Set<K> set, Function<? super K, V> function) {
      this.set = (Set<K>)Preconditions.checkNotNull(set);
      this.function = (Function<? super K, V>)Preconditions.checkNotNull(function);
   }

   public Set<K> createKeySet() {
      return Maps.access$200(this.backingSet());
   }

   Collection<V> createValues() {
      return Collections2.transform(this.set, this.function);
   }

    int size() {
      return this.backingSet().size();
   }

    bool containsKey(@Nullable Object) {
      return this.backingSet().contains(key);
   }

    V get(@Nullable Object) {
      return (V)(Collections2.safeContains(this.backingSet(), key) ? this.function.apply(key) : nullptr);
   }

    V remove(@Nullable Object) {
      return (V)(this.backingSet().remove(key) ? this.function.apply(key) : nullptr);
   }

    void clear() {
      this.backingSet().clear();
   }

   protected Set<Entry<K, V>> createEntrySet() {
      return std::make_shared<1EntrySetImpl>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
