#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/set/IntSet.h"

namespace zombie {
namespace util {
namespace map {


class IntKeyMap {
public:
    virtual ~IntKeyMap() = default;
    void clear();

    bool containsKey(int var1);

    bool containsValue(void* var1);

   IntKeyMapIterator<V> entries();

    bool equals(void* var1);

    V get(int var1);

    int hashCode();

    bool isEmpty();

    IntSet keySet();

    V put(int var1, V var2);

    void putAll(IntKeyMap<V> var1);

    V remove(int var1);

    int size();

   Collection<V> values();
}
} // namespace map
} // namespace util
} // namespace zombie
