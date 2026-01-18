#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoGridSquare.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace utils {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FibonacciHeap {
public:
 private FibonacciHeap.Entry<T> mMin = nullptr;
 int mSize = 0;
 List<FibonacciHeap.Entry<T>> treeTable = new ArrayList<>(300);
 List<FibonacciHeap.Entry<T>> toVisit = new ArrayList<>(300);

 void empty() {
 this->mMin = nullptr;
 this->mSize = 0;
 }

 public FibonacciHeap.Entry<T> enqueue(T object, double double0) {
 this->checkPriority(double0);
 FibonacciHeap.Entry entry = new FibonacciHeap.Entry<>(object, double0);
 this->mMin = mergeLists(this->mMin, entry);
 this->mSize++;
 return entry;
 }

 public FibonacciHeap.Entry<T> min() {
 if (this->isEmpty()) {
 throw NoSuchElementException("Heap is empty.");
 } else {
 return this->mMin;
 }
 }

 bool isEmpty() {
 return this->mMin == nullptr;
 }

 int size() {
 return this->mSize;
 }

 public static <T> FibonacciHeap<T> merge(FibonacciHeap<T> fibonacciHeap2, FibonacciHeap<T> fibonacciHeap1) {
 FibonacciHeap fibonacciHeap0 = new FibonacciHeap();
 fibonacciHeap0.mMin = mergeLists(fibonacciHeap2.mMin, fibonacciHeap1.mMin);
 fibonacciHeap0.mSize = fibonacciHeap2.mSize + fibonacciHeap1.mSize;
 fibonacciHeap2.mSize = fibonacciHeap1.mSize = 0;
 fibonacciHeap2.mMin = nullptr;
 fibonacciHeap1.mMin = nullptr;
 return fibonacciHeap0;
 }

 public FibonacciHeap.Entry<T> dequeueMin() {
 if (this->isEmpty()) {
 throw NoSuchElementException("Heap is empty.");
 } else {
 this->mSize--;
 FibonacciHeap.Entry entry0 = this->mMin;
 if (this->mMin.mNext == this->mMin) {
 this->mMin = nullptr;
 } else {
 this->mMin.mPrev.mNext = this->mMin.mNext;
 this->mMin.mNext.mPrev = this->mMin.mPrev;
 this->mMin = this->mMin.mNext;
 }

 if (entry0.mChild != nullptr) {
 FibonacciHeap.Entry entry1 = entry0.mChild;

 do {
 entry1.mParent = nullptr;
 entry1 = entry1.mNext;
 } while (entry1 != entry0.mChild);
 }

 this->mMin = mergeLists(this->mMin, entry0.mChild);
 if (this->mMin == nullptr) {
 return entry0;
 } else {
 this->treeTable.clear();
 this->toVisit.clear();

 for (FibonacciHeap.Entry entry2 = this->mMin; this->toVisit.empty() || this->toVisit.get(0) != entry2; entry2 = entry2.mNext) {
 this->toVisit.add(entry2);
 }

 label57:
 for (FibonacciHeap.Entry entry3 : this->toVisit) {
 while (true) {
 while (entry3.mDegree < this->treeTable.size()) {
 if (this->treeTable.get(entry3.mDegree) == nullptr) {
 this->treeTable.set(entry3.mDegree, entry3);
 if (entry3.mPriority <= this->mMin.mPriority) {
 this->mMin = entry3;
 }
 continue label57;
 }

 FibonacciHeap.Entry entry4 = this->treeTable.get(entry3.mDegree);
 this->treeTable.set(entry3.mDegree, nullptr);
 FibonacciHeap.Entry entry5 = entry4.mPriority < entry3.mPriority ? entry4 : entry3;
 FibonacciHeap.Entry entry6 = entry4.mPriority < entry3.mPriority ? entry3 : entry4;
 entry6.mNext.mPrev = entry6.mPrev;
 entry6.mPrev.mNext = entry6.mNext;
 entry6.mNext = entry6.mPrev = entry6;
 entry5.mChild = mergeLists(entry5.mChild, entry6);
 entry6.mParent = entry5;
 entry6.mIsMarked = false;
 entry5.mDegree++;
 entry3 = entry5;
 }

 this->treeTable.add(nullptr);
 }
 }

 return entry0;
 }
 }
 }

 void decreaseKey(FibonacciHeap.Entry<T> entry, double double0) {
 this->checkPriority(double0);
 if (double0 > entry.mPriority) {
 throw IllegalArgumentException("New priority exceeds old.");
 } else {
 this->decreaseKeyUnchecked(entry, double0);
 }
 }

 void delete(FibonacciHeap.Entry<T> entry) {
 this->decreaseKeyUnchecked(entry, Double.NEGATIVE_INFINITY);
 this->dequeueMin();
 }

 void delete(int var1, IsoGridSquare var2) {
 }

 void checkPriority(double double0) {
 if (Double.isNaN(double0) {
 throw IllegalArgumentException(double0 + " is invalid.");
 }
 }

 private static <T> FibonacciHeap.Entry<T> mergeLists(FibonacciHeap.Entry<T> entry1, FibonacciHeap.Entry<T> entry0) {
 if (entry1 == nullptr && entry0 == nullptr) {
 return nullptr;
 } else if (entry1 != nullptr && entry0 == nullptr) {
 return entry1;
 } else if (entry1 == nullptr && entry0 != nullptr) {
 return entry0;
 } else {
 FibonacciHeap.Entry entry2 = entry1.mNext;
 entry1.mNext = entry0.mNext;
 entry1.mNext.mPrev = entry1;
 entry0.mNext = entry2;
 entry0.mNext.mPrev = entry0;
 return entry1.mPriority < entry0.mPriority ? entry1 : entry0;
 }
 }

 void decreaseKeyUnchecked(FibonacciHeap.Entry<T> entry, double double0) {
 entry.mPriority = double0;
 if (entry.mParent != nullptr && entry.mPriority <= entry.mParent.mPriority) {
 this->cutNode(entry);
 }

 if (entry.mPriority <= this->mMin.mPriority) {
 this->mMin = entry;
 }
 }

 void decreaseKeyUncheckedNode(FibonacciHeap.Entry<IsoGridSquare> entry, double double0) {
 entry.mPriority = double0;
 if (entry.mParent != nullptr && entry.mPriority <= entry.mParent.mPriority) {
 this->cutNodeNode(entry);
 }

 if (entry.mPriority <= this->mMin.mPriority) {
 this->mMin = entry;
 }
 }

 void cutNode(FibonacciHeap.Entry<T> entry) {
 entry.mIsMarked = false;
 if (entry.mParent != nullptr) {
 if (entry.mNext != entry) {
 entry.mNext.mPrev = entry.mPrev;
 entry.mPrev.mNext = entry.mNext;
 }

 if (entry.mParent.mChild == entry) {
 if (entry.mNext != entry) {
 entry.mParent.mChild = entry.mNext;
 } else {
 entry.mParent.mChild = nullptr;
 }
 }

 entry.mParent.mDegree--;
 entry.mPrev = entry.mNext = entry;
 this->mMin = mergeLists(this->mMin, entry);
 if (entry.mParent.mIsMarked) {
 this->cutNode(entry.mParent);
 } else {
 entry.mParent.mIsMarked = true;
 }

 entry.mParent = nullptr;
 }
 }

 void cutNodeNode(FibonacciHeap.Entry<IsoGridSquare> entry) {
 entry.mIsMarked = false;
 if (entry.mParent != nullptr) {
 if (entry.mNext != entry) {
 entry.mNext.mPrev = entry.mPrev;
 entry.mPrev.mNext = entry.mNext;
 }

 if (entry.mParent.mChild == entry) {
 if (entry.mNext != entry) {
 entry.mParent.mChild = entry.mNext;
 } else {
 entry.mParent.mChild = nullptr;
 }
 }

 entry.mParent.mDegree--;
 entry.mPrev = entry.mNext = entry;
 this->mMin = mergeLists(this->mMin, entry);
 if (entry.mParent.mIsMarked) {
 this->cutNode(entry.mParent);
 } else {
 entry.mParent.mIsMarked = true;
 }

 entry.mParent = nullptr;
 }
 }

 public static class Entry<T> {
 int mDegree = 0;
 bool mIsMarked = false;
 private FibonacciHeap.Entry<T> mNext;
 private FibonacciHeap.Entry<T> mPrev;
 private FibonacciHeap.Entry<T> mParent;
 private FibonacciHeap.Entry<T> mChild;
 T mElem;
 double mPriority;

 T getValue() {
 return this->mElem;
 }

 void setValue(T object) {
 this->mElem = (T)object;
 }

 double getPriority() {
 return this->mPriority;
 }

 private Entry(T object, double double0) {
 this->mNext = this->mPrev = this;
 this->mElem = (T)object;
 this->mPriority = double0;
 }
 }
}
} // namespace utils
} // namespace core
} // namespace zombie
