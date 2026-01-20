#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/iterator/TByteCharIterator.h"
#include "gnu/trove/procedure/TByteCharProcedure.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/set/TByteSet.h"

namespace gnu {
namespace trove {
namespace map {


class TByteCharMap {
public:
    virtual ~TByteCharMap() = default;
    uint8_t getNoEntryKey();

    char getNoEntryValue();

    char put(uint8_t var1, char var2);

    char putIfAbsent(uint8_t var1, char var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TByteCharMap var1);

    char get(uint8_t var1);

    void clear();

    bool isEmpty();

    char remove(uint8_t var1);

    int size();

    TByteSet keySet();

   byte[] keys();

   byte[] keys(byte[] var1);

    TCharCollection valueCollection();

   char[] values();

   char[] values(char[] var1);

    bool containsValue(char var1);

    bool containsKey(uint8_t var1);

    TByteCharIterator iterator();

    bool forEachKey(TByteProcedure var1);

    bool forEachValue(TCharProcedure var1);

    bool forEachEntry(TByteCharProcedure var1);

    void transformValues(TCharFunction var1);

    bool retainEntries(TByteCharProcedure var1);

    bool increment(uint8_t var1);

    bool adjustValue(uint8_t var1, char var2);

    char adjustOrPutValue(uint8_t var1, char var2, char var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
