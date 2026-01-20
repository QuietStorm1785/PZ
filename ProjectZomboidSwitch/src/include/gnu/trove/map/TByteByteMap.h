#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/iterator/TByteByteIterator.h"
#include "gnu/trove/procedure/TByteByteProcedure.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/set/TByteSet.h"

namespace gnu {
namespace trove {
namespace map {


class TByteByteMap {
public:
    virtual ~TByteByteMap() = default;
    uint8_t getNoEntryKey();

    uint8_t getNoEntryValue();

    uint8_t put(uint8_t var1, uint8_t var2);

    uint8_t putIfAbsent(uint8_t var1, uint8_t var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TByteByteMap var1);

    uint8_t get(uint8_t var1);

    void clear();

    bool isEmpty();

    uint8_t remove(uint8_t var1);

    int size();

    TByteSet keySet();

   byte[] keys();

   byte[] keys(byte[] var1);

    TByteCollection valueCollection();

   byte[] values();

   byte[] values(byte[] var1);

    bool containsValue(uint8_t var1);

    bool containsKey(uint8_t var1);

    TByteByteIterator iterator();

    bool forEachKey(TByteProcedure var1);

    bool forEachValue(TByteProcedure var1);

    bool forEachEntry(TByteByteProcedure var1);

    void transformValues(TByteFunction var1);

    bool retainEntries(TByteByteProcedure var1);

    bool increment(uint8_t var1);

    bool adjustValue(uint8_t var1, uint8_t var2);

    uint8_t adjustOrPutValue(uint8_t var1, uint8_t var2, uint8_t var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
