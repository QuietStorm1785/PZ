#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/iterator/TCharLongIterator.h"
#include "gnu/trove/procedure/TCharLongProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TCharSet.h"

namespace gnu {
namespace trove {
namespace map {


class TCharLongMap {
public:
    virtual ~TCharLongMap() = default;
    char getNoEntryKey();

    long getNoEntryValue();

    long put(char var1, long var2);

    long putIfAbsent(char var1, long var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TCharLongMap var1);

    long get(char var1);

    void clear();

    bool isEmpty();

    long remove(char var1);

    int size();

    TCharSet keySet();

   char[] keys();

   char[] keys(char[] var1);

    TLongCollection valueCollection();

   long[] values();

   long[] values(long[] var1);

    bool containsValue(long var1);

    bool containsKey(char var1);

    TCharLongIterator iterator();

    bool forEachKey(TCharProcedure var1);

    bool forEachValue(TLongProcedure var1);

    bool forEachEntry(TCharLongProcedure var1);

    void transformValues(TLongFunction var1);

    bool retainEntries(TCharLongProcedure var1);

    bool increment(char var1);

    bool adjustValue(char var1, long var2);

    long adjustOrPutValue(char var1, long var2, long var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
