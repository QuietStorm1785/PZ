#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TByteIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"

namespace gnu {
namespace trove {


class TByteCollection {
public:
    virtual ~TByteCollection() = default;
    long serialVersionUID = 1L;

    uint8_t getNoEntryValue();

    int size();

    bool isEmpty();

    bool contains(uint8_t var1);

    TByteIterator iterator();

   byte[] toArray();

   byte[] toArray(byte[] var1);

    bool add(uint8_t var1);

    bool remove(uint8_t var1);

    bool containsAll(Collection<?> var1);

    bool containsAll(TByteCollection var1);

    bool containsAll(byte[] var1);

    bool addAll(Collection<? extends);

    bool addAll(TByteCollection var1);

    bool addAll(byte[] var1);

    bool retainAll(Collection<?> var1);

    bool retainAll(TByteCollection var1);

    bool retainAll(byte[] var1);

    bool removeAll(Collection<?> var1);

    bool removeAll(TByteCollection var1);

    bool removeAll(byte[] var1);

    void clear();

    bool forEach(TByteProcedure var1);

    bool equals(void* var1);

    int hashCode();
}
} // namespace trove
} // namespace gnu
