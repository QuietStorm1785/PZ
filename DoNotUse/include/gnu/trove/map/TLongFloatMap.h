#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/iterator/TLongFloatIterator.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/procedure/TLongFloatProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TLongSet.h"

namespace gnu {
namespace trove {
namespace map {


class TLongFloatMap {
public:
    virtual ~TLongFloatMap() = default;
    long getNoEntryKey();

    float getNoEntryValue();

    float put(long var1, float var3);

    float putIfAbsent(long var1, float var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TLongFloatMap var1);

    float get(long var1);

    void clear();

    bool isEmpty();

    float remove(long var1);

    int size();

    TLongSet keySet();

   long[] keys();

   long[] keys(long[] var1);

    TFloatCollection valueCollection();

   float[] values();

   float[] values(float[] var1);

    bool containsValue(float var1);

    bool containsKey(long var1);

    TLongFloatIterator iterator();

    bool forEachKey(TLongProcedure var1);

    bool forEachValue(TFloatProcedure var1);

    bool forEachEntry(TLongFloatProcedure var1);

    void transformValues(TFloatFunction var1);

    bool retainEntries(TLongFloatProcedure var1);

    bool increment(long var1);

    bool adjustValue(long var1, float var3);

    float adjustOrPutValue(long var1, float var3, float var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
