#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/iterator/TDoubleDoubleIterator.h"
#include "gnu/trove/procedure/TDoubleDoubleProcedure.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"

namespace gnu {
namespace trove {
namespace map {


class TDoubleDoubleMap {
public:
    virtual ~TDoubleDoubleMap() = default;
    double getNoEntryKey();

    double getNoEntryValue();

    double put(double var1, double var3);

    double putIfAbsent(double var1, double var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TDoubleDoubleMap var1);

    double get(double var1);

    void clear();

    bool isEmpty();

    double remove(double var1);

    int size();

    TDoubleSet keySet();

   double[] keys();

   double[] keys(double[] var1);

    TDoubleCollection valueCollection();

   double[] values();

   double[] values(double[] var1);

    bool containsValue(double var1);

    bool containsKey(double var1);

    TDoubleDoubleIterator iterator();

    bool forEachKey(TDoubleProcedure var1);

    bool forEachValue(TDoubleProcedure var1);

    bool forEachEntry(TDoubleDoubleProcedure var1);

    void transformValues(TDoubleFunction var1);

    bool retainEntries(TDoubleDoubleProcedure var1);

    bool increment(double var1);

    bool adjustValue(double var1, double var3);

    double adjustOrPutValue(double var1, double var3, double var5);
}
} // namespace map
} // namespace trove
} // namespace gnu
