#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/iterator/TIntLongIterator.h"
#include "gnu/trove/procedure/TIntLongProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TIntSet.h"

namespace gnu {
namespace trove {
namespace map {


class TIntLongMap {
public:
    virtual ~TIntLongMap() = default;
    int getNoEntryKey();

    long getNoEntryValue();

    long put(int var1, long var2);

    long putIfAbsent(int var1, long var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TIntLongMap var1);

    long get(int var1);

    void clear();

    bool isEmpty();

    long remove(int var1);

    int size();

    TIntSet keySet();

   int[] keys();

   int[] keys(int[] var1);

    TLongCollection valueCollection();

   long[] values();

   long[] values(long[] var1);

    bool containsValue(long var1);

    bool containsKey(int var1);

    TIntLongIterator iterator();

    bool forEachKey(TIntProcedure var1);

    bool forEachValue(TLongProcedure var1);

    bool forEachEntry(TIntLongProcedure var1);

    void transformValues(TLongFunction var1);

    bool retainEntries(TIntLongProcedure var1);

    bool increment(int var1);

    bool adjustValue(int var1, long var2);

    long adjustOrPutValue(int var1, long var2, long var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
