#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/iterator/TLongIterator.h"
#include "gnu/trove/procedure/TLongProcedure.h"

namespace gnu {
namespace trove {
namespace set {


class TLongSet {
public:
    virtual ~TLongSet() = default;
    long getNoEntryValue();

    int size();

    bool isEmpty();

    bool contains(long var1);

    TLongIterator iterator();

   long[] toArray();

   long[] toArray(long[] var1);

    bool add(long var1);

    bool remove(long var1);

    bool containsAll(Collection<?> var1);

    bool containsAll(TLongCollection var1);

    bool containsAll(long[] var1);

    bool addAll(Collection<? extends);

    bool addAll(TLongCollection var1);

    bool addAll(long[] var1);

    bool retainAll(Collection<?> var1);

    bool retainAll(TLongCollection var1);

    bool retainAll(long[] var1);

    bool removeAll(Collection<?> var1);

    bool removeAll(TLongCollection var1);

    bool removeAll(long[] var1);

    void clear();

    bool forEach(TLongProcedure var1);

    bool equals(void* var1);

    int hashCode();
}
} // namespace set
} // namespace trove
} // namespace gnu
