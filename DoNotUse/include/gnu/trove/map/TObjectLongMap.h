#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/iterator/TObjectLongIterator.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/procedure/TObjectLongProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"

namespace gnu {
namespace trove {
namespace map {


class TObjectLongMap {
public:
    virtual ~TObjectLongMap() = default;
    long getNoEntryValue();

    int size();

    bool isEmpty();

    bool containsKey(void* var1);

    bool containsValue(long var1);

    long get(void* var1);

    long put(K var1, long var2);

    long putIfAbsent(K var1, long var2);

    long remove(void* var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TObjectLongMap<? extends);

    void clear();

   Set<K> keySet();

   Object[] keys();

   K[] keys(K[] var1);

    TLongCollection valueCollection();

   long[] values();

   long[] values(long[] var1);

   TObjectLongIterator<K> iterator();

    bool increment(K var1);

    bool adjustValue(K var1, long var2);

    long adjustOrPutValue(K var1, long var2, long var4);

    bool forEachKey(TObjectProcedure<? super);

    bool forEachValue(TLongProcedure var1);

    bool forEachEntry(TObjectLongProcedure<? super);

    void transformValues(TLongFunction var1);

    bool retainEntries(TObjectLongProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
