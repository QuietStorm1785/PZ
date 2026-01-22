#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/iterator/TByteLongIterator.h"
#include "gnu/trove/procedure/TByteLongProcedure.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TByteSet.h"

namespace gnu {
namespace trove {
namespace map {


class TByteLongMap {
public:
    virtual ~TByteLongMap() = default;
    uint8_t getNoEntryKey();

    long getNoEntryValue();

    long put(uint8_t var1, long var2);

    long putIfAbsent(uint8_t var1, long var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TByteLongMap var1);

    long get(uint8_t var1);

    void clear();

    bool isEmpty();

    long remove(uint8_t var1);

    int size();

    TByteSet keySet();

   byte[] keys();

   byte[] keys(byte[] var1);

    TLongCollection valueCollection();

   long[] values();

   long[] values(long[] var1);

    bool containsValue(long var1);

    bool containsKey(uint8_t var1);

    TByteLongIterator iterator();

    bool forEachKey(TByteProcedure var1);

    bool forEachValue(TLongProcedure var1);

    bool forEachEntry(TByteLongProcedure var1);

    void transformValues(TLongFunction var1);

    bool retainEntries(TByteLongProcedure var1);

    bool increment(uint8_t var1);

    bool adjustValue(uint8_t var1, long var2);

    long adjustOrPutValue(uint8_t var1, long var2, long var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
