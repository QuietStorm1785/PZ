#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/iterator/TShortObjectIterator.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/procedure/TShortObjectProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"

namespace gnu {
namespace trove {
namespace map {


class TShortObjectMap {
public:
    virtual ~TShortObjectMap() = default;
    short getNoEntryKey();

    int size();

    bool isEmpty();

    bool containsKey(short var1);

    bool containsValue(void* var1);

    V get(short var1);

    V put(short var1, V var2);

    V putIfAbsent(short var1, V var2);

    V remove(short var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TShortObjectMap<? extends);

    void clear();

    TShortSet keySet();

   short[] keys();

   short[] keys(short[] var1);

   Collection<V> valueCollection();

   Object[] values();

   V[] values(V[] var1);

   TShortObjectIterator<V> iterator();

    bool forEachKey(TShortProcedure var1);

    bool forEachValue(TObjectProcedure<? super);

    bool forEachEntry(TShortObjectProcedure<? super);

    void transformValues(V> var1);

    bool retainEntries(TShortObjectProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
