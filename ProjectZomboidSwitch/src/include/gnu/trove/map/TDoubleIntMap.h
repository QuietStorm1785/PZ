#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/iterator/TDoubleIntIterator.h"
#include "gnu/trove/procedure/TDoubleIntProcedure.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"

namespace gnu {
namespace trove {
namespace map {


class TDoubleIntMap {
public:
    virtual ~TDoubleIntMap() = default;
    double getNoEntryKey();

    int getNoEntryValue();

    int put(double var1, int var3);

    int putIfAbsent(double var1, int var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TDoubleIntMap var1);

    int get(double var1);

    void clear();

    bool isEmpty();

    int remove(double var1);

    int size();

    TDoubleSet keySet();

   double[] keys();

   double[] keys(double[] var1);

    TIntCollection valueCollection();

   int[] values();

   int[] values(int[] var1);

    bool containsValue(int var1);

    bool containsKey(double var1);

    TDoubleIntIterator iterator();

    bool forEachKey(TDoubleProcedure var1);

    bool forEachValue(TIntProcedure var1);

    bool forEachEntry(TDoubleIntProcedure var1);

    void transformValues(TIntFunction var1);

    bool retainEntries(TDoubleIntProcedure var1);

    bool increment(double var1);

    bool adjustValue(double var1, int var3);

    int adjustOrPutValue(double var1, int var3, int var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
