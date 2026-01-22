#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/iterator/TShortDoubleIterator.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TShortDoubleProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"

namespace gnu {
namespace trove {
namespace map {


class TShortDoubleMap {
public:
    virtual ~TShortDoubleMap() = default;
    short getNoEntryKey();

    double getNoEntryValue();

    double put(short var1, double var2);

    double putIfAbsent(short var1, double var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TShortDoubleMap var1);

    double get(short var1);

    void clear();

    bool isEmpty();

    double remove(short var1);

    int size();

    TShortSet keySet();

   short[] keys();

   short[] keys(short[] var1);

    TDoubleCollection valueCollection();

   double[] values();

   double[] values(double[] var1);

    bool containsValue(double var1);

    bool containsKey(short var1);

    TShortDoubleIterator iterator();

    bool forEachKey(TShortProcedure var1);

    bool forEachValue(TDoubleProcedure var1);

    bool forEachEntry(TShortDoubleProcedure var1);

    void transformValues(TDoubleFunction var1);

    bool retainEntries(TShortDoubleProcedure var1);

    bool increment(short var1);

    bool adjustValue(short var1, double var2);

    double adjustOrPutValue(short var1, double var2, double var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
