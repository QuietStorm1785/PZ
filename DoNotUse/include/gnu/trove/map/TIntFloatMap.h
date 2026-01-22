#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/iterator/TIntFloatIterator.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/procedure/TIntFloatProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TIntSet.h"

namespace gnu {
namespace trove {
namespace map {


class TIntFloatMap {
public:
    virtual ~TIntFloatMap() = default;
    int getNoEntryKey();

    float getNoEntryValue();

    float put(int var1, float var2);

    float putIfAbsent(int var1, float var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TIntFloatMap var1);

    float get(int var1);

    void clear();

    bool isEmpty();

    float remove(int var1);

    int size();

    TIntSet keySet();

   int[] keys();

   int[] keys(int[] var1);

    TFloatCollection valueCollection();

   float[] values();

   float[] values(float[] var1);

    bool containsValue(float var1);

    bool containsKey(int var1);

    TIntFloatIterator iterator();

    bool forEachKey(TIntProcedure var1);

    bool forEachValue(TFloatProcedure var1);

    bool forEachEntry(TIntFloatProcedure var1);

    void transformValues(TFloatFunction var1);

    bool retainEntries(TIntFloatProcedure var1);

    bool increment(int var1);

    bool adjustValue(int var1, float var2);

    float adjustOrPutValue(int var1, float var2, float var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
