#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/iterator/TIntObjectIterator.h"
#include "gnu/trove/procedure/TIntObjectProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/TIntSet.h"

namespace gnu {
namespace trove {
namespace map {


class TIntObjectMap {
public:
    virtual ~TIntObjectMap() = default;
    int getNoEntryKey();

    int size();

    bool isEmpty();

    bool containsKey(int var1);

    bool containsValue(void* var1);

    V get(int var1);

    V put(int var1, V var2);

    V putIfAbsent(int var1, V var2);

    V remove(int var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TIntObjectMap<? extends);

    void clear();

    TIntSet keySet();

   int[] keys();

   int[] keys(int[] var1);

   Collection<V> valueCollection();

   Object[] values();

   V[] values(V[] var1);

   TIntObjectIterator<V> iterator();

    bool forEachKey(TIntProcedure var1);

    bool forEachValue(TObjectProcedure<? super);

    bool forEachEntry(TIntObjectProcedure<? super);

    void transformValues(V> var1);

    bool retainEntries(TIntObjectProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
