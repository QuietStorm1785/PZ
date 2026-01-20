#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/iterator/TShortIntIterator.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/procedure/TShortIntProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"

namespace gnu {
namespace trove {
namespace map {


class TShortIntMap {
public:
    virtual ~TShortIntMap() = default;
    short getNoEntryKey();

    int getNoEntryValue();

    int put(short var1, int var2);

    int putIfAbsent(short var1, int var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TShortIntMap var1);

    int get(short var1);

    void clear();

    bool isEmpty();

    int remove(short var1);

    int size();

    TShortSet keySet();

   short[] keys();

   short[] keys(short[] var1);

    TIntCollection valueCollection();

   int[] values();

   int[] values(int[] var1);

    bool containsValue(int var1);

    bool containsKey(short var1);

    TShortIntIterator iterator();

    bool forEachKey(TShortProcedure var1);

    bool forEachValue(TIntProcedure var1);

    bool forEachEntry(TShortIntProcedure var1);

    void transformValues(TIntFunction var1);

    bool retainEntries(TShortIntProcedure var1);

    bool increment(short var1);

    bool adjustValue(short var1, int var2);

    int adjustOrPutValue(short var1, int var2, int var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
