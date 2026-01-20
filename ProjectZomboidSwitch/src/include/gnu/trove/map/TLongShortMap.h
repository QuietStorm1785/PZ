#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/iterator/TLongShortIterator.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/procedure/TLongShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TLongSet.h"

namespace gnu {
namespace trove {
namespace map {


class TLongShortMap {
public:
    virtual ~TLongShortMap() = default;
    long getNoEntryKey();

    short getNoEntryValue();

    short put(long var1, short var3);

    short putIfAbsent(long var1, short var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TLongShortMap var1);

    short get(long var1);

    void clear();

    bool isEmpty();

    short remove(long var1);

    int size();

    TLongSet keySet();

   long[] keys();

   long[] keys(long[] var1);

    TShortCollection valueCollection();

   short[] values();

   short[] values(short[] var1);

    bool containsValue(short var1);

    bool containsKey(long var1);

    TLongShortIterator iterator();

    bool forEachKey(TLongProcedure var1);

    bool forEachValue(TShortProcedure var1);

    bool forEachEntry(TLongShortProcedure var1);

    void transformValues(TShortFunction var1);

    bool retainEntries(TLongShortProcedure var1);

    bool increment(long var1);

    bool adjustValue(long var1, short var3);

    short adjustOrPutValue(long var1, short var3, short var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
