#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {


class TLongList {
public:
    virtual ~TLongList() = default;
    long getNoEntryValue();

    int size();

    bool isEmpty();

    bool add(long var1);

    void add(long[] var1);

    void add(long[] var1, int var2, int var3);

    void insert(int var1, long var2);

    void insert(int var1, long[] var2);

    void insert(int var1, long[] var2, int var3, int var4);

    long get(int var1);

    long set(int var1, long var2);

    void set(int var1, long[] var2);

    void set(int var1, long[] var2, int var3, int var4);

    long replace(int var1, long var2);

    void clear();

    bool remove(long var1);

    long removeAt(int var1);

    void remove(int var1, int var2);

    void transformValues(TLongFunction var1);

    void reverse();

    void reverse(int var1, int var2);

    void shuffle(Random var1);

    TLongList subList(int var1, int var2);

   long[] toArray();

   long[] toArray(int var1, int var2);

   long[] toArray(long[] var1);

   long[] toArray(long[] var1, int var2, int var3);

   long[] toArray(long[] var1, int var2, int var3, int var4);

    bool forEach(TLongProcedure var1);

    bool forEachDescending(TLongProcedure var1);

    void sort();

    void sort(int var1, int var2);

    void fill(long var1);

    void fill(int var1, int var2, long var3);

    int binarySearch(long var1);

    int binarySearch(long var1, int var3, int var4);

    int indexOf(long var1);

    int indexOf(int var1, long var2);

    int lastIndexOf(long var1);

    int lastIndexOf(int var1, long var2);

    bool contains(long var1);

    TLongList grep(TLongProcedure var1);

    TLongList inverseGrep(TLongProcedure var1);

    long max();

    long min();

    long sum();
}
} // namespace list
} // namespace trove
} // namespace gnu
