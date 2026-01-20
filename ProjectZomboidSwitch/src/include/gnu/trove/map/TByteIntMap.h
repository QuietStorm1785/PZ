#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/iterator/TByteIntIterator.h"
#include "gnu/trove/procedure/TByteIntProcedure.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TByteSet.h"

namespace gnu {
namespace trove {
namespace map {


class TByteIntMap {
public:
    virtual ~TByteIntMap() = default;
    uint8_t getNoEntryKey();

    int getNoEntryValue();

    int put(uint8_t var1, int var2);

    int putIfAbsent(uint8_t var1, int var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TByteIntMap var1);

    int get(uint8_t var1);

    void clear();

    bool isEmpty();

    int remove(uint8_t var1);

    int size();

    TByteSet keySet();

   byte[] keys();

   byte[] keys(byte[] var1);

    TIntCollection valueCollection();

   int[] values();

   int[] values(int[] var1);

    bool containsValue(int var1);

    bool containsKey(uint8_t var1);

    TByteIntIterator iterator();

    bool forEachKey(TByteProcedure var1);

    bool forEachValue(TIntProcedure var1);

    bool forEachEntry(TByteIntProcedure var1);

    void transformValues(TIntFunction var1);

    bool retainEntries(TByteIntProcedure var1);

    bool increment(uint8_t var1);

    bool adjustValue(uint8_t var1, int var2);

    int adjustOrPutValue(uint8_t var1, int var2, int var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
