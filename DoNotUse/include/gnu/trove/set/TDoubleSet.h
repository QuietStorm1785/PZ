#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/iterator/TDoubleIterator.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"

namespace gnu {
namespace trove {
namespace set {


class TDoubleSet {
public:
    virtual ~TDoubleSet() = default;
    double getNoEntryValue();

    int size();

    bool isEmpty();

    bool contains(double var1);

    TDoubleIterator iterator();

   double[] toArray();

   double[] toArray(double[] var1);

    bool add(double var1);

    bool remove(double var1);

    bool containsAll(Collection<?> var1);

    bool containsAll(TDoubleCollection var1);

    bool containsAll(double[] var1);

    bool addAll(Collection<? extends);

    bool addAll(TDoubleCollection var1);

    bool addAll(double[] var1);

    bool retainAll(Collection<?> var1);

    bool retainAll(TDoubleCollection var1);

    bool retainAll(double[] var1);

    bool removeAll(Collection<?> var1);

    bool removeAll(TDoubleCollection var1);

    bool removeAll(double[] var1);

    void clear();

    bool forEach(TDoubleProcedure var1);

    bool equals(void* var1);

    int hashCode();
}
} // namespace set
} // namespace trove
} // namespace gnu
