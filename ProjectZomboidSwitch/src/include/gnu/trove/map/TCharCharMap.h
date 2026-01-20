#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/iterator/TCharCharIterator.h"
#include "gnu/trove/procedure/TCharCharProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/set/TCharSet.h"

namespace gnu {
namespace trove {
namespace map {


class TCharCharMap {
public:
    virtual ~TCharCharMap() = default;
    char getNoEntryKey();

    char getNoEntryValue();

    char put(char var1, char var2);

    char putIfAbsent(char var1, char var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TCharCharMap var1);

    char get(char var1);

    void clear();

    bool isEmpty();

    char remove(char var1);

    int size();

    TCharSet keySet();

   char[] keys();

   char[] keys(char[] var1);

    TCharCollection valueCollection();

   char[] values();

   char[] values(char[] var1);

    bool containsValue(char var1);

    bool containsKey(char var1);

    TCharCharIterator iterator();

    bool forEachKey(TCharProcedure var1);

    bool forEachValue(TCharProcedure var1);

    bool forEachEntry(TCharCharProcedure var1);

    void transformValues(TCharFunction var1);

    bool retainEntries(TCharCharProcedure var1);

    bool increment(char var1);

    bool adjustValue(char var1, char var2);

    char adjustOrPutValue(char var1, char var2, char var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
