#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {


class TShortList {
public:
    virtual ~TShortList() = default;
    short getNoEntryValue();

    int size();

    bool isEmpty();

    bool add(short var1);

    void add(short[] var1);

    void add(short[] var1, int var2, int var3);

    void insert(int var1, short var2);

    void insert(int var1, short[] var2);

    void insert(int var1, short[] var2, int var3, int var4);

    short get(int var1);

    short set(int var1, short var2);

    void set(int var1, short[] var2);

    void set(int var1, short[] var2, int var3, int var4);

    short replace(int var1, short var2);

    void clear();

    bool remove(short var1);

    short removeAt(int var1);

    void remove(int var1, int var2);

    void transformValues(TShortFunction var1);

    void reverse();

    void reverse(int var1, int var2);

    void shuffle(Random var1);

    TShortList subList(int var1, int var2);

   short[] toArray();

   short[] toArray(int var1, int var2);

   short[] toArray(short[] var1);

   short[] toArray(short[] var1, int var2, int var3);

   short[] toArray(short[] var1, int var2, int var3, int var4);

    bool forEach(TShortProcedure var1);

    bool forEachDescending(TShortProcedure var1);

    void sort();

    void sort(int var1, int var2);

    void fill(short var1);

    void fill(int var1, int var2, short var3);

    int binarySearch(short var1);

    int binarySearch(short var1, int var2, int var3);

    int indexOf(short var1);

    int indexOf(int var1, short var2);

    int lastIndexOf(short var1);

    int lastIndexOf(int var1, short var2);

    bool contains(short var1);

    TShortList grep(TShortProcedure var1);

    TShortList inverseGrep(TShortProcedure var1);

    short max();

    short min();

    short sum();
}
} // namespace list
} // namespace trove
} // namespace gnu
