#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/iterator/TByteShortIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TByteShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TByteSet.h"

namespace gnu {
namespace trove {
namespace map {


class TByteShortMap {
public:
    virtual ~TByteShortMap() = default;
    uint8_t getNoEntryKey();

    short getNoEntryValue();

    short put(uint8_t var1, short var2);

    short putIfAbsent(uint8_t var1, short var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TByteShortMap var1);

    short get(uint8_t var1);

    void clear();

    bool isEmpty();

    short remove(uint8_t var1);

    int size();

    TByteSet keySet();

   byte[] keys();

   byte[] keys(byte[] var1);

    TShortCollection valueCollection();

   short[] values();

   short[] values(short[] var1);

    bool containsValue(short var1);

    bool containsKey(uint8_t var1);

    TByteShortIterator iterator();

    bool forEachKey(TByteProcedure var1);

    bool forEachValue(TShortProcedure var1);

    bool forEachEntry(TByteShortProcedure var1);

    void transformValues(TShortFunction var1);

    bool retainEntries(TByteShortProcedure var1);

    bool increment(uint8_t var1);

    bool adjustValue(uint8_t var1, short var2);

    short adjustOrPutValue(uint8_t var1, short var2, short var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
