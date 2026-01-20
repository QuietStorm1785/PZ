#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/iterator/TObjectDoubleIterator.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TObjectDoubleProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"

namespace gnu {
namespace trove {
namespace map {


class TObjectDoubleMap {
public:
    virtual ~TObjectDoubleMap() = default;
    double getNoEntryValue();

    int size();

    bool isEmpty();

    bool containsKey(void* var1);

    bool containsValue(double var1);

    double get(void* var1);

    double put(K var1, double var2);

    double putIfAbsent(K var1, double var2);

    double remove(void* var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TObjectDoubleMap<? extends);

    void clear();

   Set<K> keySet();

   Object[] keys();

   K[] keys(K[] var1);

    TDoubleCollection valueCollection();

   double[] values();

   double[] values(double[] var1);

   TObjectDoubleIterator<K> iterator();

    bool increment(K var1);

    bool adjustValue(K var1, double var2);

    double adjustOrPutValue(K var1, double var2, double var4);

    bool forEachKey(TObjectProcedure<? super);

    bool forEachValue(TDoubleProcedure var1);

    bool forEachEntry(TObjectDoubleProcedure<? super);

    void transformValues(TDoubleFunction var1);

    bool retainEntries(TObjectDoubleProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
