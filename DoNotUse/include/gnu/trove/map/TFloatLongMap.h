#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/iterator/TFloatLongIterator.h"
#include "gnu/trove/procedure/TFloatLongProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TFloatSet.h"

namespace gnu {
namespace trove {
namespace map {


class TFloatLongMap {
public:
    virtual ~TFloatLongMap() = default;
    float getNoEntryKey();

    long getNoEntryValue();

    long put(float var1, long var2);

    long putIfAbsent(float var1, long var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TFloatLongMap var1);

    long get(float var1);

    void clear();

    bool isEmpty();

    long remove(float var1);

    int size();

    TFloatSet keySet();

   float[] keys();

   float[] keys(float[] var1);

    TLongCollection valueCollection();

   long[] values();

   long[] values(long[] var1);

    bool containsValue(long var1);

    bool containsKey(float var1);

    TFloatLongIterator iterator();

    bool forEachKey(TFloatProcedure var1);

    bool forEachValue(TLongProcedure var1);

    bool forEachEntry(TFloatLongProcedure var1);

    void transformValues(TLongFunction var1);

    bool retainEntries(TFloatLongProcedure var1);

    bool increment(float var1);

    bool adjustValue(float var1, long var2);

    long adjustOrPutValue(float var1, long var2, long var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
