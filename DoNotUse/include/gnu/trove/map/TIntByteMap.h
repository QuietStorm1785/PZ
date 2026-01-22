#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/iterator/TIntByteIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TIntByteProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TIntSet.h"

namespace gnu {
namespace trove {
namespace map {


class TIntByteMap {
public:
    virtual ~TIntByteMap() = default;
    int getNoEntryKey();

    uint8_t getNoEntryValue();

    uint8_t put(int var1, uint8_t var2);

    uint8_t putIfAbsent(int var1, uint8_t var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TIntByteMap var1);

    uint8_t get(int var1);

    void clear();

    bool isEmpty();

    uint8_t remove(int var1);

    int size();

    TIntSet keySet();

   int[] keys();

   int[] keys(int[] var1);

    TByteCollection valueCollection();

   byte[] values();

   byte[] values(byte[] var1);

    bool containsValue(uint8_t var1);

    bool containsKey(int var1);

    TIntByteIterator iterator();

    bool forEachKey(TIntProcedure var1);

    bool forEachValue(TByteProcedure var1);

    bool forEachEntry(TIntByteProcedure var1);

    void transformValues(TByteFunction var1);

    bool retainEntries(TIntByteProcedure var1);

    bool increment(int var1);

    bool adjustValue(int var1, uint8_t var2);

    uint8_t adjustOrPutValue(int var1, uint8_t var2, uint8_t var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
