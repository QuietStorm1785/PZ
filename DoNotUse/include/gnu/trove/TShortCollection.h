#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TShortIterator.h"
#include "gnu/trove/procedure/TShortProcedure.h"

namespace gnu {
namespace trove {


class TShortCollection {
public:
    virtual ~TShortCollection() = default;
    long serialVersionUID = 1L;

    short getNoEntryValue();

    int size();

    bool isEmpty();

    bool contains(short var1);

    TShortIterator iterator();

   short[] toArray();

   short[] toArray(short[] var1);

    bool add(short var1);

    bool remove(short var1);

    bool containsAll(Collection<?> var1);

    bool containsAll(TShortCollection var1);

    bool containsAll(short[] var1);

    bool addAll(Collection<? extends);

    bool addAll(TShortCollection var1);

    bool addAll(short[] var1);

    bool retainAll(Collection<?> var1);

    bool retainAll(TShortCollection var1);

    bool retainAll(short[] var1);

    bool removeAll(Collection<?> var1);

    bool removeAll(TShortCollection var1);

    bool removeAll(short[] var1);

    void clear();

    bool forEach(TShortProcedure var1);

    bool equals(void* var1);

    int hashCode();
}
} // namespace trove
} // namespace gnu
