#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/iterator/TDoubleFloatIterator.h"
#include "gnu/trove/procedure/TDoubleFloatProcedure.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"

namespace gnu {
namespace trove {
namespace map {


class TDoubleFloatMap {
public:
    virtual ~TDoubleFloatMap() = default;
    double getNoEntryKey();

    float getNoEntryValue();

    float put(double var1, float var3);

    float putIfAbsent(double var1, float var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TDoubleFloatMap var1);

    float get(double var1);

    void clear();

    bool isEmpty();

    float remove(double var1);

    int size();

    TDoubleSet keySet();

   double[] keys();

   double[] keys(double[] var1);

    TFloatCollection valueCollection();

   float[] values();

   float[] values(float[] var1);

    bool containsValue(float var1);

    bool containsKey(double var1);

    TDoubleFloatIterator iterator();

    bool forEachKey(TDoubleProcedure var1);

    bool forEachValue(TFloatProcedure var1);

    bool forEachEntry(TDoubleFloatProcedure var1);

    void transformValues(TFloatFunction var1);

    bool retainEntries(TDoubleFloatProcedure var1);

    bool increment(double var1);

    bool adjustValue(double var1, float var3);

    float adjustOrPutValue(double var1, float var3, float var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
