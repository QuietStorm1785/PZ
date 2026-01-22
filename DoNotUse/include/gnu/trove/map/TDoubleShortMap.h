#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/iterator/TDoubleShortIterator.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TDoubleShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"

namespace gnu {
namespace trove {
namespace map {


class TDoubleShortMap {
public:
    virtual ~TDoubleShortMap() = default;
    double getNoEntryKey();

    short getNoEntryValue();

    short put(double var1, short var3);

    short putIfAbsent(double var1, short var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TDoubleShortMap var1);

    short get(double var1);

    void clear();

    bool isEmpty();

    short remove(double var1);

    int size();

    TDoubleSet keySet();

   double[] keys();

   double[] keys(double[] var1);

    TShortCollection valueCollection();

   short[] values();

   short[] values(short[] var1);

    bool containsValue(short var1);

    bool containsKey(double var1);

    TDoubleShortIterator iterator();

    bool forEachKey(TDoubleProcedure var1);

    bool forEachValue(TShortProcedure var1);

    bool forEachEntry(TDoubleShortProcedure var1);

    void transformValues(TShortFunction var1);

    bool retainEntries(TDoubleShortProcedure var1);

    bool increment(double var1);

    bool adjustValue(double var1, short var3);

    short adjustOrPutValue(double var1, short var3, short var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
