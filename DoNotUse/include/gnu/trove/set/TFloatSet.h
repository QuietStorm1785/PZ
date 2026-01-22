#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/iterator/TFloatIterator.h"
#include "gnu/trove/procedure/TFloatProcedure.h"

namespace gnu {
namespace trove {
namespace set {


class TFloatSet {
public:
    virtual ~TFloatSet() = default;
    float getNoEntryValue();

    int size();

    bool isEmpty();

    bool contains(float var1);

    TFloatIterator iterator();

   float[] toArray();

   float[] toArray(float[] var1);

    bool add(float var1);

    bool remove(float var1);

    bool containsAll(Collection<?> var1);

    bool containsAll(TFloatCollection var1);

    bool containsAll(float[] var1);

    bool addAll(Collection<? extends);

    bool addAll(TFloatCollection var1);

    bool addAll(float[] var1);

    bool retainAll(Collection<?> var1);

    bool retainAll(TFloatCollection var1);

    bool retainAll(float[] var1);

    bool removeAll(Collection<?> var1);

    bool removeAll(TFloatCollection var1);

    bool removeAll(float[] var1);

    void clear();

    bool forEach(TFloatProcedure var1);

    bool equals(void* var1);

    int hashCode();
}
} // namespace set
} // namespace trove
} // namespace gnu
