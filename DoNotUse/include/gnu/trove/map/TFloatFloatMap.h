#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/iterator/TFloatFloatIterator.h"
#include "gnu/trove/procedure/TFloatFloatProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TFloatSet.h"

namespace gnu {
namespace trove {
namespace map {


class TFloatFloatMap {
public:
    virtual ~TFloatFloatMap() = default;
    float getNoEntryKey();

    float getNoEntryValue();

    float put(float var1, float var2);

    float putIfAbsent(float var1, float var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TFloatFloatMap var1);

    float get(float var1);

    void clear();

    bool isEmpty();

    float remove(float var1);

    int size();

    TFloatSet keySet();

   float[] keys();

   float[] keys(float[] var1);

    TFloatCollection valueCollection();

   float[] values();

   float[] values(float[] var1);

    bool containsValue(float var1);

    bool containsKey(float var1);

    TFloatFloatIterator iterator();

    bool forEachKey(TFloatProcedure var1);

    bool forEachValue(TFloatProcedure var1);

    bool forEachEntry(TFloatFloatProcedure var1);

    void transformValues(TFloatFunction var1);

    bool retainEntries(TFloatFloatProcedure var1);

    bool increment(float var1);

    bool adjustValue(float var1, float var2);

    float adjustOrPutValue(float var1, float var2, float var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
