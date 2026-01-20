#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {


class TFloatList {
public:
    virtual ~TFloatList() = default;
    float getNoEntryValue();

    int size();

    bool isEmpty();

    bool add(float var1);

    void add(float[] var1);

    void add(float[] var1, int var2, int var3);

    void insert(int var1, float var2);

    void insert(int var1, float[] var2);

    void insert(int var1, float[] var2, int var3, int var4);

    float get(int var1);

    float set(int var1, float var2);

    void set(int var1, float[] var2);

    void set(int var1, float[] var2, int var3, int var4);

    float replace(int var1, float var2);

    void clear();

    bool remove(float var1);

    float removeAt(int var1);

    void remove(int var1, int var2);

    void transformValues(TFloatFunction var1);

    void reverse();

    void reverse(int var1, int var2);

    void shuffle(Random var1);

    TFloatList subList(int var1, int var2);

   float[] toArray();

   float[] toArray(int var1, int var2);

   float[] toArray(float[] var1);

   float[] toArray(float[] var1, int var2, int var3);

   float[] toArray(float[] var1, int var2, int var3, int var4);

    bool forEach(TFloatProcedure var1);

    bool forEachDescending(TFloatProcedure var1);

    void sort();

    void sort(int var1, int var2);

    void fill(float var1);

    void fill(int var1, int var2, float var3);

    int binarySearch(float var1);

    int binarySearch(float var1, int var2, int var3);

    int indexOf(float var1);

    int indexOf(int var1, float var2);

    int lastIndexOf(float var1);

    int lastIndexOf(int var1, float var2);

    bool contains(float var1);

    TFloatList grep(TFloatProcedure var1);

    TFloatList inverseGrep(TFloatProcedure var1);

    float max();

    float min();

    float sum();
}
} // namespace list
} // namespace trove
} // namespace gnu
