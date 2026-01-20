#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/iterator/TCharByteIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TCharByteProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/set/TCharSet.h"

namespace gnu {
namespace trove {
namespace map {


class TCharByteMap {
public:
    virtual ~TCharByteMap() = default;
    char getNoEntryKey();

    uint8_t getNoEntryValue();

    uint8_t put(char var1, uint8_t var2);

    uint8_t putIfAbsent(char var1, uint8_t var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TCharByteMap var1);

    uint8_t get(char var1);

    void clear();

    bool isEmpty();

    uint8_t remove(char var1);

    int size();

    TCharSet keySet();

   char[] keys();

   char[] keys(char[] var1);

    TByteCollection valueCollection();

   byte[] values();

   byte[] values(byte[] var1);

    bool containsValue(uint8_t var1);

    bool containsKey(char var1);

    TCharByteIterator iterator();

    bool forEachKey(TCharProcedure var1);

    bool forEachValue(TByteProcedure var1);

    bool forEachEntry(TCharByteProcedure var1);

    void transformValues(TByteFunction var1);

    bool retainEntries(TCharByteProcedure var1);

    bool increment(char var1);

    bool adjustValue(char var1, uint8_t var2);

    uint8_t adjustOrPutValue(char var1, uint8_t var2, uint8_t var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
