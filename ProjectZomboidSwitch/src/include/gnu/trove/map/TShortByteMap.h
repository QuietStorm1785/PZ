#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/iterator/TShortByteIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TShortByteProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"

namespace gnu {
namespace trove {
namespace map {


class TShortByteMap {
public:
    virtual ~TShortByteMap() = default;
    short getNoEntryKey();

    uint8_t getNoEntryValue();

    uint8_t put(short var1, uint8_t var2);

    uint8_t putIfAbsent(short var1, uint8_t var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TShortByteMap var1);

    uint8_t get(short var1);

    void clear();

    bool isEmpty();

    uint8_t remove(short var1);

    int size();

    TShortSet keySet();

   short[] keys();

   short[] keys(short[] var1);

    TByteCollection valueCollection();

   byte[] values();

   byte[] values(byte[] var1);

    bool containsValue(uint8_t var1);

    bool containsKey(short var1);

    TShortByteIterator iterator();

    bool forEachKey(TShortProcedure var1);

    bool forEachValue(TByteProcedure var1);

    bool forEachEntry(TShortByteProcedure var1);

    void transformValues(TByteFunction var1);

    bool retainEntries(TShortByteProcedure var1);

    bool increment(short var1);

    bool adjustValue(short var1, uint8_t var2);

    uint8_t adjustOrPutValue(short var1, uint8_t var2, uint8_t var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
