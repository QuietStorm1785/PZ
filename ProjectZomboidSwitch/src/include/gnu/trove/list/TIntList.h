#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {


class TIntList {
public:
    virtual ~TIntList() = default;
    int getNoEntryValue();

    int size();

    bool isEmpty();

    bool add(int var1);

    void add(int[] var1);

    void add(int[] var1, int var2, int var3);

    void insert(int var1, int var2);

    void insert(int var1, int[] var2);

    void insert(int var1, int[] var2, int var3, int var4);

    int get(int var1);

    int set(int var1, int var2);

    void set(int var1, int[] var2);

    void set(int var1, int[] var2, int var3, int var4);

    int replace(int var1, int var2);

    void clear();

    bool remove(int var1);

    int removeAt(int var1);

    void remove(int var1, int var2);

    void transformValues(TIntFunction var1);

    void reverse();

    void reverse(int var1, int var2);

    void shuffle(Random var1);

    TIntList subList(int var1, int var2);

   int[] toArray();

   int[] toArray(int var1, int var2);

   int[] toArray(int[] var1);

   int[] toArray(int[] var1, int var2, int var3);

   int[] toArray(int[] var1, int var2, int var3, int var4);

    bool forEach(TIntProcedure var1);

    bool forEachDescending(TIntProcedure var1);

    void sort();

    void sort(int var1, int var2);

    void fill(int var1);

    void fill(int var1, int var2, int var3);

    int binarySearch(int var1);

    int binarySearch(int var1, int var2, int var3);

    int indexOf(int var1);

    int indexOf(int var1, int var2);

    int lastIndexOf(int var1);

    int lastIndexOf(int var1, int var2);

    bool contains(int var1);

    TIntList grep(TIntProcedure var1);

    TIntList inverseGrep(TIntProcedure var1);

    int max();

    int min();

    int sum();
}
} // namespace list
} // namespace trove
} // namespace gnu
