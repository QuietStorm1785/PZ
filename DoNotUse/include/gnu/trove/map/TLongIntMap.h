#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/iterator/TLongIntIterator.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/procedure/TLongIntProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TLongSet.h"

namespace gnu {
namespace trove {
namespace map {


class TLongIntMap {
public:
    virtual ~TLongIntMap() = default;
    long getNoEntryKey();

    int getNoEntryValue();

    int put(long var1, int var3);

    int putIfAbsent(long var1, int var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TLongIntMap var1);

    int get(long var1);

    void clear();

    bool isEmpty();

    int remove(long var1);

    int size();

    TLongSet keySet();

   long[] keys();

   long[] keys(long[] var1);

    TIntCollection valueCollection();

   int[] values();

   int[] values(int[] var1);

    bool containsValue(int var1);

    bool containsKey(long var1);

    TLongIntIterator iterator();

    bool forEachKey(TLongProcedure var1);

    bool forEachValue(TIntProcedure var1);

    bool forEachEntry(TLongIntProcedure var1);

    void transformValues(TIntFunction var1);

    bool retainEntries(TLongIntProcedure var1);

    bool increment(long var1);

    bool adjustValue(long var1, int var3);

    int adjustOrPutValue(long var1, int var3, int var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
