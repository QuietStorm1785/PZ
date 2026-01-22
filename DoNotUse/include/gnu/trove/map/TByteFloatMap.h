#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/iterator/TByteFloatIterator.h"
#include "gnu/trove/procedure/TByteFloatProcedure.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TByteSet.h"

namespace gnu {
namespace trove {
namespace map {


class TByteFloatMap {
public:
    virtual ~TByteFloatMap() = default;
    uint8_t getNoEntryKey();

    float getNoEntryValue();

    float put(uint8_t var1, float var2);

    float putIfAbsent(uint8_t var1, float var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TByteFloatMap var1);

    float get(uint8_t var1);

    void clear();

    bool isEmpty();

    float remove(uint8_t var1);

    int size();

    TByteSet keySet();

   byte[] keys();

   byte[] keys(byte[] var1);

    TFloatCollection valueCollection();

   float[] values();

   float[] values(float[] var1);

    bool containsValue(float var1);

    bool containsKey(uint8_t var1);

    TByteFloatIterator iterator();

    bool forEachKey(TByteProcedure var1);

    bool forEachValue(TFloatProcedure var1);

    bool forEachEntry(TByteFloatProcedure var1);

    void transformValues(TFloatFunction var1);

    bool retainEntries(TByteFloatProcedure var1);

    bool increment(uint8_t var1);

    bool adjustValue(uint8_t var1, float var2);

    float adjustOrPutValue(uint8_t var1, float var2, float var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
