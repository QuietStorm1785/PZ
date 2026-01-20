#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/iterator/TLongByteIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TLongByteProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TLongSet.h"

namespace gnu {
namespace trove {
namespace map {


class TLongByteMap {
public:
    virtual ~TLongByteMap() = default;
    long getNoEntryKey();

    uint8_t getNoEntryValue();

    uint8_t put(long var1, uint8_t var3);

    uint8_t putIfAbsent(long var1, uint8_t var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TLongByteMap var1);

    uint8_t get(long var1);

    void clear();

    bool isEmpty();

    uint8_t remove(long var1);

    int size();

    TLongSet keySet();

   long[] keys();

   long[] keys(long[] var1);

    TByteCollection valueCollection();

   byte[] values();

   byte[] values(byte[] var1);

    bool containsValue(uint8_t var1);

    bool containsKey(long var1);

    TLongByteIterator iterator();

    bool forEachKey(TLongProcedure var1);

    bool forEachValue(TByteProcedure var1);

    bool forEachEntry(TLongByteProcedure var1);

    void transformValues(TByteFunction var1);

    bool retainEntries(TLongByteProcedure var1);

    bool increment(long var1);

    bool adjustValue(long var1, uint8_t var3);

    uint8_t adjustOrPutValue(long var1, uint8_t var3, uint8_t var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
