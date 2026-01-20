#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/iterator/TLongCharIterator.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TLongCharProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TLongSet.h"

namespace gnu {
namespace trove {
namespace map {


class TLongCharMap {
public:
    virtual ~TLongCharMap() = default;
    long getNoEntryKey();

    char getNoEntryValue();

    char put(long var1, char var3);

    char putIfAbsent(long var1, char var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TLongCharMap var1);

    char get(long var1);

    void clear();

    bool isEmpty();

    char remove(long var1);

    int size();

    TLongSet keySet();

   long[] keys();

   long[] keys(long[] var1);

    TCharCollection valueCollection();

   char[] values();

   char[] values(char[] var1);

    bool containsValue(char var1);

    bool containsKey(long var1);

    TLongCharIterator iterator();

    bool forEachKey(TLongProcedure var1);

    bool forEachValue(TCharProcedure var1);

    bool forEachEntry(TLongCharProcedure var1);

    void transformValues(TCharFunction var1);

    bool retainEntries(TLongCharProcedure var1);

    bool increment(long var1);

    bool adjustValue(long var1, char var3);

    char adjustOrPutValue(long var1, char var3, char var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
