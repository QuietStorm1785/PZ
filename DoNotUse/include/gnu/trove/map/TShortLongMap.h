#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/iterator/TShortLongIterator.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/procedure/TShortLongProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"

namespace gnu {
namespace trove {
namespace map {


class TShortLongMap {
public:
    virtual ~TShortLongMap() = default;
    short getNoEntryKey();

    long getNoEntryValue();

    long put(short var1, long var2);

    long putIfAbsent(short var1, long var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TShortLongMap var1);

    long get(short var1);

    void clear();

    bool isEmpty();

    long remove(short var1);

    int size();

    TShortSet keySet();

   short[] keys();

   short[] keys(short[] var1);

    TLongCollection valueCollection();

   long[] values();

   long[] values(long[] var1);

    bool containsValue(long var1);

    bool containsKey(short var1);

    TShortLongIterator iterator();

    bool forEachKey(TShortProcedure var1);

    bool forEachValue(TLongProcedure var1);

    bool forEachEntry(TShortLongProcedure var1);

    void transformValues(TLongFunction var1);

    bool retainEntries(TShortLongProcedure var1);

    bool increment(short var1);

    bool adjustValue(short var1, long var2);

    long adjustOrPutValue(short var1, long var2, long var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
