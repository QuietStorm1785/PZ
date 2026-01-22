#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/iterator/TLongDoubleIterator.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TLongDoubleProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TLongSet.h"

namespace gnu {
namespace trove {
namespace map {


class TLongDoubleMap {
public:
    virtual ~TLongDoubleMap() = default;
    long getNoEntryKey();

    double getNoEntryValue();

    double put(long var1, double var3);

    double putIfAbsent(long var1, double var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TLongDoubleMap var1);

    double get(long var1);

    void clear();

    bool isEmpty();

    double remove(long var1);

    int size();

    TLongSet keySet();

   long[] keys();

   long[] keys(long[] var1);

    TDoubleCollection valueCollection();

   double[] values();

   double[] values(double[] var1);

    bool containsValue(double var1);

    bool containsKey(long var1);

    TLongDoubleIterator iterator();

    bool forEachKey(TLongProcedure var1);

    bool forEachValue(TDoubleProcedure var1);

    bool forEachEntry(TLongDoubleProcedure var1);

    void transformValues(TDoubleFunction var1);

    bool retainEntries(TLongDoubleProcedure var1);

    bool increment(long var1);

    bool adjustValue(long var1, double var3);

    double adjustOrPutValue(long var1, double var3, double var5);
}
} // namespace map
} // namespace trove
} // namespace gnu
