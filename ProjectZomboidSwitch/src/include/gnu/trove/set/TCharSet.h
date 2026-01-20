#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/iterator/TCharIterator.h"
#include "gnu/trove/procedure/TCharProcedure.h"

namespace gnu {
namespace trove {
namespace set {


class TCharSet {
public:
    virtual ~TCharSet() = default;
    char getNoEntryValue();

    int size();

    bool isEmpty();

    bool contains(char var1);

    TCharIterator iterator();

   char[] toArray();

   char[] toArray(char[] var1);

    bool add(char var1);

    bool remove(char var1);

    bool containsAll(Collection<?> var1);

    bool containsAll(TCharCollection var1);

    bool containsAll(char[] var1);

    bool addAll(Collection<? extends);

    bool addAll(TCharCollection var1);

    bool addAll(char[] var1);

    bool retainAll(Collection<?> var1);

    bool retainAll(TCharCollection var1);

    bool retainAll(char[] var1);

    bool removeAll(Collection<?> var1);

    bool removeAll(TCharCollection var1);

    bool removeAll(char[] var1);

    void clear();

    bool forEach(TCharProcedure var1);

    bool equals(void* var1);

    int hashCode();
}
} // namespace set
} // namespace trove
} // namespace gnu
