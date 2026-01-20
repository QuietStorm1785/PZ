#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/iterator/TCharShortIterator.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TCharShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TCharSet.h"

namespace gnu {
namespace trove {
namespace map {


class TCharShortMap {
public:
    virtual ~TCharShortMap() = default;
    char getNoEntryKey();

    short getNoEntryValue();

    short put(char var1, short var2);

    short putIfAbsent(char var1, short var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TCharShortMap var1);

    short get(char var1);

    void clear();

    bool isEmpty();

    short remove(char var1);

    int size();

    TCharSet keySet();

   char[] keys();

   char[] keys(char[] var1);

    TShortCollection valueCollection();

   short[] values();

   short[] values(short[] var1);

    bool containsValue(short var1);

    bool containsKey(char var1);

    TCharShortIterator iterator();

    bool forEachKey(TCharProcedure var1);

    bool forEachValue(TShortProcedure var1);

    bool forEachEntry(TCharShortProcedure var1);

    void transformValues(TShortFunction var1);

    bool retainEntries(TCharShortProcedure var1);

    bool increment(char var1);

    bool adjustValue(char var1, short var2);

    short adjustOrPutValue(char var1, short var2, short var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
