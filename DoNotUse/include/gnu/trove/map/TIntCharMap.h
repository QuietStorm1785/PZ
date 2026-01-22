#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/iterator/TIntCharIterator.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TIntCharProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TIntSet.h"

namespace gnu {
namespace trove {
namespace map {


class TIntCharMap {
public:
    virtual ~TIntCharMap() = default;
    int getNoEntryKey();

    char getNoEntryValue();

    char put(int var1, char var2);

    char putIfAbsent(int var1, char var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TIntCharMap var1);

    char get(int var1);

    void clear();

    bool isEmpty();

    char remove(int var1);

    int size();

    TIntSet keySet();

   int[] keys();

   int[] keys(int[] var1);

    TCharCollection valueCollection();

   char[] values();

   char[] values(char[] var1);

    bool containsValue(char var1);

    bool containsKey(int var1);

    TIntCharIterator iterator();

    bool forEachKey(TIntProcedure var1);

    bool forEachValue(TCharProcedure var1);

    bool forEachEntry(TIntCharProcedure var1);

    void transformValues(TCharFunction var1);

    bool retainEntries(TIntCharProcedure var1);

    bool increment(int var1);

    bool adjustValue(int var1, char var2);

    char adjustOrPutValue(int var1, char var2, char var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
