#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/iterator/TShortCharIterator.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TShortCharProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"

namespace gnu {
namespace trove {
namespace map {


class TShortCharMap {
public:
    virtual ~TShortCharMap() = default;
    short getNoEntryKey();

    char getNoEntryValue();

    char put(short var1, char var2);

    char putIfAbsent(short var1, char var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TShortCharMap var1);

    char get(short var1);

    void clear();

    bool isEmpty();

    char remove(short var1);

    int size();

    TShortSet keySet();

   short[] keys();

   short[] keys(short[] var1);

    TCharCollection valueCollection();

   char[] values();

   char[] values(char[] var1);

    bool containsValue(char var1);

    bool containsKey(short var1);

    TShortCharIterator iterator();

    bool forEachKey(TShortProcedure var1);

    bool forEachValue(TCharProcedure var1);

    bool forEachEntry(TShortCharProcedure var1);

    void transformValues(TCharFunction var1);

    bool retainEntries(TShortCharProcedure var1);

    bool increment(short var1);

    bool adjustValue(short var1, char var2);

    char adjustOrPutValue(short var1, char var2, char var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
