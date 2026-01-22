#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/iterator/TLongObjectIterator.h"
#include "gnu/trove/procedure/TLongObjectProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/TLongSet.h"

namespace gnu {
namespace trove {
namespace map {


class TLongObjectMap {
public:
    virtual ~TLongObjectMap() = default;
    long getNoEntryKey();

    int size();

    bool isEmpty();

    bool containsKey(long var1);

    bool containsValue(void* var1);

    V get(long var1);

    V put(long var1, V var3);

    V putIfAbsent(long var1, V var3);

    V remove(long var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TLongObjectMap<? extends);

    void clear();

    TLongSet keySet();

   long[] keys();

   long[] keys(long[] var1);

   Collection<V> valueCollection();

   Object[] values();

   V[] values(V[] var1);

   TLongObjectIterator<V> iterator();

    bool forEachKey(TLongProcedure var1);

    bool forEachValue(TObjectProcedure<? super);

    bool forEachEntry(TLongObjectProcedure<? super);

    void transformValues(V> var1);

    bool retainEntries(TLongObjectProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
