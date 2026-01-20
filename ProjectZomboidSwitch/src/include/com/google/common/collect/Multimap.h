#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimap {
public:
    virtual ~Multimap() = default;
    int size();

    bool isEmpty();

    bool containsKey(@Nullable Object);

    bool containsValue(@Nullable Object);

    bool containsEntry(@Nullable Object, @Nullable Object);

    bool put(@Nullable K, @Nullable V);

    bool remove(@Nullable Object, @Nullable Object);

    bool putAll(@Nullable K, Iterable<? extends);

    bool putAll(Multimap<? extends, ? extends);

   Collection<V> replaceValues(@Nullable K var1, Iterable<? : public V> var2);

   Collection<V> removeAll(@Nullable Object var1);

    void clear();

   Collection<V> get(@Nullable K var1);

   Set<K> keySet();

   Multiset<K> keys();

   Collection<V> values();

   Collection<Entry<K, V>> entries();

   Map<K, Collection<V>> asMap();

    bool equals(@Nullable Object);

    int hashCode();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
