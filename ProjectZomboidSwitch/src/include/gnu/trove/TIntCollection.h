#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TIntIterator.h"
#include "gnu/trove/procedure/TIntProcedure.h"

namespace gnu {
namespace trove {


class TIntCollection {
public:
    virtual ~TIntCollection() = default;
    long serialVersionUID = 1L;

    int getNoEntryValue();

    int size();

    bool isEmpty();

    bool contains(int var1);

    TIntIterator iterator();

   int[] toArray();

   int[] toArray(int[] var1);

    bool add(int var1);

    bool remove(int var1);

    bool containsAll(Collection<?> var1);

    bool containsAll(TIntCollection var1);

    bool containsAll(int[] var1);

    bool addAll(Collection<? extends);

    bool addAll(TIntCollection var1);

    bool addAll(int[] var1);

    bool retainAll(Collection<?> var1);

    bool retainAll(TIntCollection var1);

    bool retainAll(int[] var1);

    bool removeAll(Collection<?> var1);

    bool removeAll(TIntCollection var1);

    bool removeAll(int[] var1);

    void clear();

    bool forEach(TIntProcedure var1);

    bool equals(void* var1);

    int hashCode();
}
} // namespace trove
} // namespace gnu
