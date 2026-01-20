#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/iterator/TIntDoubleIterator.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TIntDoubleProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TIntSet.h"

namespace gnu {
namespace trove {
namespace map {


class TIntDoubleMap {
public:
    virtual ~TIntDoubleMap() = default;
    int getNoEntryKey();

    double getNoEntryValue();

    double put(int var1, double var2);

    double putIfAbsent(int var1, double var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TIntDoubleMap var1);

    double get(int var1);

    void clear();

    bool isEmpty();

    double remove(int var1);

    int size();

    TIntSet keySet();

   int[] keys();

   int[] keys(int[] var1);

    TDoubleCollection valueCollection();

   double[] values();

   double[] values(double[] var1);

    bool containsValue(double var1);

    bool containsKey(int var1);

    TIntDoubleIterator iterator();

    bool forEachKey(TIntProcedure var1);

    bool forEachValue(TDoubleProcedure var1);

    bool forEachEntry(TIntDoubleProcedure var1);

    void transformValues(TDoubleFunction var1);

    bool retainEntries(TIntDoubleProcedure var1);

    bool increment(int var1);

    bool adjustValue(int var1, double var2);

    double adjustOrPutValue(int var1, double var2, double var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
