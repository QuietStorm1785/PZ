#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/iterator/TFloatByteIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TFloatByteProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TFloatSet.h"

namespace gnu {
namespace trove {
namespace map {


class TFloatByteMap {
public:
    virtual ~TFloatByteMap() = default;
    float getNoEntryKey();

    uint8_t getNoEntryValue();

    uint8_t put(float var1, uint8_t var2);

    uint8_t putIfAbsent(float var1, uint8_t var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TFloatByteMap var1);

    uint8_t get(float var1);

    void clear();

    bool isEmpty();

    uint8_t remove(float var1);

    int size();

    TFloatSet keySet();

   float[] keys();

   float[] keys(float[] var1);

    TByteCollection valueCollection();

   byte[] values();

   byte[] values(byte[] var1);

    bool containsValue(uint8_t var1);

    bool containsKey(float var1);

    TFloatByteIterator iterator();

    bool forEachKey(TFloatProcedure var1);

    bool forEachValue(TByteProcedure var1);

    bool forEachEntry(TFloatByteProcedure var1);

    void transformValues(TByteFunction var1);

    bool retainEntries(TFloatByteProcedure var1);

    bool increment(float var1);

    bool adjustValue(float var1, uint8_t var2);

    uint8_t adjustOrPutValue(float var1, uint8_t var2, uint8_t var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
