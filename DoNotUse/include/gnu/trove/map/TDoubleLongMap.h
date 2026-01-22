#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/iterator/TDoubleLongIterator.h"
#include "gnu/trove/procedure/TDoubleLongProcedure.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"

namespace gnu {
namespace trove {
namespace map {


class TDoubleLongMap {
public:
    virtual ~TDoubleLongMap() = default;
    double getNoEntryKey();

    long getNoEntryValue();

    long put(double var1, long var3);

    long putIfAbsent(double var1, long var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TDoubleLongMap var1);

    long get(double var1);

    void clear();

    bool isEmpty();

    long remove(double var1);

    int size();

    TDoubleSet keySet();

   double[] keys();

   double[] keys(double[] var1);

    TLongCollection valueCollection();

   long[] values();

   long[] values(long[] var1);

    bool containsValue(long var1);

    bool containsKey(double var1);

    TDoubleLongIterator iterator();

    bool forEachKey(TDoubleProcedure var1);

    bool forEachValue(TLongProcedure var1);

    bool forEachEntry(TDoubleLongProcedure var1);

    void transformValues(TLongFunction var1);

    bool retainEntries(TDoubleLongProcedure var1);

    bool increment(double var1);

    bool adjustValue(double var1, long var3);

    long adjustOrPutValue(double var1, long var3, long var5);
}
} // namespace map
} // namespace trove
} // namespace gnu
