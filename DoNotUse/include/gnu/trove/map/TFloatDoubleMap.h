#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/iterator/TFloatDoubleIterator.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TFloatDoubleProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TFloatSet.h"

namespace gnu {
namespace trove {
namespace map {


class TFloatDoubleMap {
public:
    virtual ~TFloatDoubleMap() = default;
    float getNoEntryKey();

    double getNoEntryValue();

    double put(float var1, double var2);

    double putIfAbsent(float var1, double var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TFloatDoubleMap var1);

    double get(float var1);

    void clear();

    bool isEmpty();

    double remove(float var1);

    int size();

    TFloatSet keySet();

   float[] keys();

   float[] keys(float[] var1);

    TDoubleCollection valueCollection();

   double[] values();

   double[] values(double[] var1);

    bool containsValue(double var1);

    bool containsKey(float var1);

    TFloatDoubleIterator iterator();

    bool forEachKey(TFloatProcedure var1);

    bool forEachValue(TDoubleProcedure var1);

    bool forEachEntry(TFloatDoubleProcedure var1);

    void transformValues(TDoubleFunction var1);

    bool retainEntries(TFloatDoubleProcedure var1);

    bool increment(float var1);

    bool adjustValue(float var1, double var2);

    double adjustOrPutValue(float var1, double var2, double var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
