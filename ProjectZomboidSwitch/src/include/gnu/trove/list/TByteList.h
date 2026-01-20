#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {


class TByteList {
public:
    virtual ~TByteList() = default;
    uint8_t getNoEntryValue();

    int size();

    bool isEmpty();

    bool add(uint8_t var1);

    void add(byte[] var1);

    void add(byte[] var1, int var2, int var3);

    void insert(int var1, uint8_t var2);

    void insert(int var1, byte[] var2);

    void insert(int var1, byte[] var2, int var3, int var4);

    uint8_t get(int var1);

    uint8_t set(int var1, uint8_t var2);

    void set(int var1, byte[] var2);

    void set(int var1, byte[] var2, int var3, int var4);

    uint8_t replace(int var1, uint8_t var2);

    void clear();

    bool remove(uint8_t var1);

    uint8_t removeAt(int var1);

    void remove(int var1, int var2);

    void transformValues(TByteFunction var1);

    void reverse();

    void reverse(int var1, int var2);

    void shuffle(Random var1);

    TByteList subList(int var1, int var2);

   byte[] toArray();

   byte[] toArray(int var1, int var2);

   byte[] toArray(byte[] var1);

   byte[] toArray(byte[] var1, int var2, int var3);

   byte[] toArray(byte[] var1, int var2, int var3, int var4);

    bool forEach(TByteProcedure var1);

    bool forEachDescending(TByteProcedure var1);

    void sort();

    void sort(int var1, int var2);

    void fill(uint8_t var1);

    void fill(int var1, int var2, uint8_t var3);

    int binarySearch(uint8_t var1);

    int binarySearch(uint8_t var1, int var2, int var3);

    int indexOf(uint8_t var1);

    int indexOf(int var1, uint8_t var2);

    int lastIndexOf(uint8_t var1);

    int lastIndexOf(int var1, uint8_t var2);

    bool contains(uint8_t var1);

    TByteList grep(TByteProcedure var1);

    TByteList inverseGrep(TByteProcedure var1);

    uint8_t max();

    uint8_t min();

    uint8_t sum();
}
} // namespace list
} // namespace trove
} // namespace gnu
