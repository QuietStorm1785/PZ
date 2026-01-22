#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/iterator/TFloatShortIterator.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/procedure/TFloatShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TFloatSet.h"

namespace gnu {
namespace trove {
namespace map {


class TFloatShortMap {
public:
    virtual ~TFloatShortMap() = default;
    float getNoEntryKey();

    short getNoEntryValue();

    short put(float var1, short var2);

    short putIfAbsent(float var1, short var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TFloatShortMap var1);

    short get(float var1);

    void clear();

    bool isEmpty();

    short remove(float var1);

    int size();

    TFloatSet keySet();

   float[] keys();

   float[] keys(float[] var1);

    TShortCollection valueCollection();

   short[] values();

   short[] values(short[] var1);

    bool containsValue(short var1);

    bool containsKey(float var1);

    TFloatShortIterator iterator();

    bool forEachKey(TFloatProcedure var1);

    bool forEachValue(TShortProcedure var1);

    bool forEachEntry(TFloatShortProcedure var1);

    void transformValues(TShortFunction var1);

    bool retainEntries(TFloatShortProcedure var1);

    bool increment(float var1);

    bool adjustValue(float var1, short var2);

    short adjustOrPutValue(float var1, short var2, short var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
