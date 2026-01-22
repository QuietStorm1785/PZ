#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/iterator/TIntShortIterator.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/procedure/TIntShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TIntSet.h"

namespace gnu {
namespace trove {
namespace map {


class TIntShortMap {
public:
    virtual ~TIntShortMap() = default;
    int getNoEntryKey();

    short getNoEntryValue();

    short put(int var1, short var2);

    short putIfAbsent(int var1, short var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TIntShortMap var1);

    short get(int var1);

    void clear();

    bool isEmpty();

    short remove(int var1);

    int size();

    TIntSet keySet();

   int[] keys();

   int[] keys(int[] var1);

    TShortCollection valueCollection();

   short[] values();

   short[] values(short[] var1);

    bool containsValue(short var1);

    bool containsKey(int var1);

    TIntShortIterator iterator();

    bool forEachKey(TIntProcedure var1);

    bool forEachValue(TShortProcedure var1);

    bool forEachEntry(TIntShortProcedure var1);

    void transformValues(TShortFunction var1);

    bool retainEntries(TIntShortProcedure var1);

    bool increment(int var1);

    bool adjustValue(int var1, short var2);

    short adjustOrPutValue(int var1, short var2, short var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
