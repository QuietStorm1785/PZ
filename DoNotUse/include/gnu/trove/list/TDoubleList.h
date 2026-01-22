#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {


class TDoubleList {
public:
    virtual ~TDoubleList() = default;
    double getNoEntryValue();

    int size();

    bool isEmpty();

    bool add(double var1);

    void add(double[] var1);

    void add(double[] var1, int var2, int var3);

    void insert(int var1, double var2);

    void insert(int var1, double[] var2);

    void insert(int var1, double[] var2, int var3, int var4);

    double get(int var1);

    double set(int var1, double var2);

    void set(int var1, double[] var2);

    void set(int var1, double[] var2, int var3, int var4);

    double replace(int var1, double var2);

    void clear();

    bool remove(double var1);

    double removeAt(int var1);

    void remove(int var1, int var2);

    void transformValues(TDoubleFunction var1);

    void reverse();

    void reverse(int var1, int var2);

    void shuffle(Random var1);

    TDoubleList subList(int var1, int var2);

   double[] toArray();

   double[] toArray(int var1, int var2);

   double[] toArray(double[] var1);

   double[] toArray(double[] var1, int var2, int var3);

   double[] toArray(double[] var1, int var2, int var3, int var4);

    bool forEach(TDoubleProcedure var1);

    bool forEachDescending(TDoubleProcedure var1);

    void sort();

    void sort(int var1, int var2);

    void fill(double var1);

    void fill(int var1, int var2, double var3);

    int binarySearch(double var1);

    int binarySearch(double var1, int var3, int var4);

    int indexOf(double var1);

    int indexOf(int var1, double var2);

    int lastIndexOf(double var1);

    int lastIndexOf(int var1, double var2);

    bool contains(double var1);

    TDoubleList grep(TDoubleProcedure var1);

    TDoubleList inverseGrep(TDoubleProcedure var1);

    double max();

    double min();

    double sum();
}
} // namespace list
} // namespace trove
} // namespace gnu
