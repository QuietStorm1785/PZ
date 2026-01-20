#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/iterator/TLongLongIterator.h"
#include "gnu/trove/procedure/TLongLongProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TLongSet.h"

namespace gnu {
namespace trove {
namespace map {


class TLongLongMap {
public:
    virtual ~TLongLongMap() = default;
    long getNoEntryKey();

    long getNoEntryValue();

    long put(long var1, long var3);

    long putIfAbsent(long var1, long var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TLongLongMap var1);

    long get(long var1);

    void clear();

    bool isEmpty();

    long remove(long var1);

    int size();

    TLongSet keySet();

   long[] keys();

   long[] keys(long[] var1);

    TLongCollection valueCollection();

   long[] values();

   long[] values(long[] var1);

    bool containsValue(long var1);

    bool containsKey(long var1);

    TLongLongIterator iterator();

    bool forEachKey(TLongProcedure var1);

    bool forEachValue(TLongProcedure var1);

    bool forEachEntry(TLongLongProcedure var1);

    void transformValues(TLongFunction var1);

    bool retainEntries(TLongLongProcedure var1);

    bool increment(long var1);

    bool adjustValue(long var1, long var3);

    long adjustOrPutValue(long var1, long var3, long var5);
}
} // namespace map
} // namespace trove
} // namespace gnu
