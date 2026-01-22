#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/iterator/TIntIntIterator.h"
#include "gnu/trove/procedure/TIntIntProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TIntSet.h"

namespace gnu {
namespace trove {
namespace map {


class TIntIntMap {
public:
    virtual ~TIntIntMap() = default;
    int getNoEntryKey();

    int getNoEntryValue();

    int put(int var1, int var2);

    int putIfAbsent(int var1, int var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TIntIntMap var1);

    int get(int var1);

    void clear();

    bool isEmpty();

    int remove(int var1);

    int size();

    TIntSet keySet();

   int[] keys();

   int[] keys(int[] var1);

    TIntCollection valueCollection();

   int[] values();

   int[] values(int[] var1);

    bool containsValue(int var1);

    bool containsKey(int var1);

    TIntIntIterator iterator();

    bool forEachKey(TIntProcedure var1);

    bool forEachValue(TIntProcedure var1);

    bool forEachEntry(TIntIntProcedure var1);

    void transformValues(TIntFunction var1);

    bool retainEntries(TIntIntProcedure var1);

    bool increment(int var1);

    bool adjustValue(int var1, int var2);

    int adjustOrPutValue(int var1, int var2, int var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
