#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/iterator/TFloatIntIterator.h"
#include "gnu/trove/procedure/TFloatIntProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TFloatSet.h"

namespace gnu {
namespace trove {
namespace map {


class TFloatIntMap {
public:
    virtual ~TFloatIntMap() = default;
    float getNoEntryKey();

    int getNoEntryValue();

    int put(float var1, int var2);

    int putIfAbsent(float var1, int var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TFloatIntMap var1);

    int get(float var1);

    void clear();

    bool isEmpty();

    int remove(float var1);

    int size();

    TFloatSet keySet();

   float[] keys();

   float[] keys(float[] var1);

    TIntCollection valueCollection();

   int[] values();

   int[] values(int[] var1);

    bool containsValue(int var1);

    bool containsKey(float var1);

    TFloatIntIterator iterator();

    bool forEachKey(TFloatProcedure var1);

    bool forEachValue(TIntProcedure var1);

    bool forEachEntry(TFloatIntProcedure var1);

    void transformValues(TIntFunction var1);

    bool retainEntries(TFloatIntProcedure var1);

    bool increment(float var1);

    bool adjustValue(float var1, int var2);

    int adjustOrPutValue(float var1, int var2, int var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
