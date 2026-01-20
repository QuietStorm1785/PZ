#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/iterator/TCharIntIterator.h"
#include "gnu/trove/procedure/TCharIntProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TCharSet.h"

namespace gnu {
namespace trove {
namespace map {


class TCharIntMap {
public:
    virtual ~TCharIntMap() = default;
    char getNoEntryKey();

    int getNoEntryValue();

    int put(char var1, int var2);

    int putIfAbsent(char var1, int var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TCharIntMap var1);

    int get(char var1);

    void clear();

    bool isEmpty();

    int remove(char var1);

    int size();

    TCharSet keySet();

   char[] keys();

   char[] keys(char[] var1);

    TIntCollection valueCollection();

   int[] values();

   int[] values(int[] var1);

    bool containsValue(int var1);

    bool containsKey(char var1);

    TCharIntIterator iterator();

    bool forEachKey(TCharProcedure var1);

    bool forEachValue(TIntProcedure var1);

    bool forEachEntry(TCharIntProcedure var1);

    void transformValues(TIntFunction var1);

    bool retainEntries(TCharIntProcedure var1);

    bool increment(char var1);

    bool adjustValue(char var1, int var2);

    int adjustOrPutValue(char var1, int var2, int var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
