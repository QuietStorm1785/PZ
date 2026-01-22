#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/iterator/TShortFloatIterator.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/procedure/TShortFloatProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"

namespace gnu {
namespace trove {
namespace map {


class TShortFloatMap {
public:
    virtual ~TShortFloatMap() = default;
    short getNoEntryKey();

    float getNoEntryValue();

    float put(short var1, float var2);

    float putIfAbsent(short var1, float var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TShortFloatMap var1);

    float get(short var1);

    void clear();

    bool isEmpty();

    float remove(short var1);

    int size();

    TShortSet keySet();

   short[] keys();

   short[] keys(short[] var1);

    TFloatCollection valueCollection();

   float[] values();

   float[] values(float[] var1);

    bool containsValue(float var1);

    bool containsKey(short var1);

    TShortFloatIterator iterator();

    bool forEachKey(TShortProcedure var1);

    bool forEachValue(TFloatProcedure var1);

    bool forEachEntry(TShortFloatProcedure var1);

    void transformValues(TFloatFunction var1);

    bool retainEntries(TShortFloatProcedure var1);

    bool increment(short var1);

    bool adjustValue(short var1, float var2);

    float adjustOrPutValue(short var1, float var2, float var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
