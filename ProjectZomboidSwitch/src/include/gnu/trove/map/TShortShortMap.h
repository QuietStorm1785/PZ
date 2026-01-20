#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/iterator/TShortShortIterator.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/procedure/TShortShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"

namespace gnu {
namespace trove {
namespace map {


class TShortShortMap {
public:
    virtual ~TShortShortMap() = default;
    short getNoEntryKey();

    short getNoEntryValue();

    short put(short var1, short var2);

    short putIfAbsent(short var1, short var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TShortShortMap var1);

    short get(short var1);

    void clear();

    bool isEmpty();

    short remove(short var1);

    int size();

    TShortSet keySet();

   short[] keys();

   short[] keys(short[] var1);

    TShortCollection valueCollection();

   short[] values();

   short[] values(short[] var1);

    bool containsValue(short var1);

    bool containsKey(short var1);

    TShortShortIterator iterator();

    bool forEachKey(TShortProcedure var1);

    bool forEachValue(TShortProcedure var1);

    bool forEachEntry(TShortShortProcedure var1);

    void transformValues(TShortFunction var1);

    bool retainEntries(TShortShortProcedure var1);

    bool increment(short var1);

    bool adjustValue(short var1, short var2);

    short adjustOrPutValue(short var1, short var2, short var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
