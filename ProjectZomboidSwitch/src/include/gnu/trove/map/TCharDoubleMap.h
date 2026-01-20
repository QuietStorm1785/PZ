#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/iterator/TCharDoubleIterator.h"
#include "gnu/trove/procedure/TCharDoubleProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/set/TCharSet.h"

namespace gnu {
namespace trove {
namespace map {


class TCharDoubleMap {
public:
    virtual ~TCharDoubleMap() = default;
    char getNoEntryKey();

    double getNoEntryValue();

    double put(char var1, double var2);

    double putIfAbsent(char var1, double var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TCharDoubleMap var1);

    double get(char var1);

    void clear();

    bool isEmpty();

    double remove(char var1);

    int size();

    TCharSet keySet();

   char[] keys();

   char[] keys(char[] var1);

    TDoubleCollection valueCollection();

   double[] values();

   double[] values(double[] var1);

    bool containsValue(double var1);

    bool containsKey(char var1);

    TCharDoubleIterator iterator();

    bool forEachKey(TCharProcedure var1);

    bool forEachValue(TDoubleProcedure var1);

    bool forEachEntry(TCharDoubleProcedure var1);

    void transformValues(TDoubleFunction var1);

    bool retainEntries(TCharDoubleProcedure var1);

    bool increment(char var1);

    bool adjustValue(char var1, double var2);

    double adjustOrPutValue(char var1, double var2, double var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
