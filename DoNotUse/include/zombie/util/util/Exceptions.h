#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/map/NoSuchMappingException.h"
#include <algorithm>

namespace zombie {
namespace util {
namespace util {


class Exceptions {
public:
    static void indexOutOfBounds(int var0, int var1, int var2) {
      throw IndexOutOfBoundsException("Index out of bounds: " + var0 + ", valid range is " + var1 + " to " + var2);
   }

    static void nullArgument(const std::string& var0) {
      throw NullPointerException("The specified " + var0 + " is nullptr");
   }

    static void negativeArgument(const std::string& var0, void* var1) {
      throw IllegalArgumentException(var0 + " cannot be negative: " + var1);
   }

    static void negativeOrZeroArgument(const std::string& var0, void* var1) {
      throw IllegalArgumentException(var0 + " must be a positive value: " + var1);
   }

    static void endOfIterator() {
      throw NoSuchElementException("Attempt to iterate past iterator's last element.");
   }

    static void startOfIterator() {
      throw NoSuchElementException("Attempt to iterate past iterator's first element.");
   }

    static void noElementToRemove() {
      throw IllegalStateException("Attempt to remove element from iterator that has no current element.");
   }

    static void noElementToGet() {
      throw IllegalStateException("Attempt to get element from iterator that has no current element. Call next() first.");
   }

    static void noElementToSet() {
      throw IllegalStateException("Attempt to set element in iterator that has no current element.");
   }

    static void noLastElement() {
      throw IllegalStateException("No value to return. Call containsKey() first.");
   }

    static void noSuchMapping(void* var0) {
      throw NoSuchMappingException("No such key in map: " + var0);
   }

    static void dequeNoFirst() {
      throw IndexOutOfBoundsException("Attempt to get first element of empty deque");
   }

    static void dequeNoLast() {
      throw IndexOutOfBoundsException("Attempt to get last element of empty deque");
   }

    static void dequeNoFirstToRemove() {
      throw IndexOutOfBoundsException("Attempt to remove last element of empty deque");
   }

    static void dequeNoLastToRemove() {
      throw IndexOutOfBoundsException("Attempt to remove last element of empty deque");
   }

    static void nullElementNotAllowed() {
      throw IllegalArgumentException("Attempt to add a nullptr value to an adapted primitive set.");
   }

    static void cannotAdapt(const std::string& var0) {
      throw IllegalStateException("The " + var0 + " contains values preventing it from being adapted to a primitive " + var0);
   }

    static void unsupported(const std::string& var0) {
      throw UnsupportedOperationException("Attempt to invoke unsupported operation: " + var0);
   }

    static void unmodifiable(const std::string& var0) {
      throw UnsupportedOperationException("Attempt to modify unmodifiable " + var0);
   }

    static void cloning() {
      throw RuntimeException("Clone is not supported");
   }

    static void invalidRangeBounds(void* var0, void* var1) {
      throw IllegalArgumentException("First (" + var0 + ") cannot be greater than last (" + var1 + ")");
   }

    static void cannotMergeRanges(void* var0, void* var1) {
      throw IllegalArgumentException("Ranges cannot be merged: " + var0 + " and " + var1);
   }

    static void setNoFirst() {
      throw NoSuchElementException("Attempt to get first element of empty set");
   }

    static void setNoLast() {
      throw NoSuchElementException("Attempt to get last element of empty set");
   }

    static void invalidSetBounds(void* var0, void* var1) {
      throw IllegalArgumentException("Lower bound (" + var0 + ") cannot be greater than upper bound (" + var1 + ")");
   }

    static void valueNotInSubRange(void* var0) {
      throw IllegalArgumentException("Attempt to add a value outside valid range: " + var0);
   }

    static void invalidUpperBound(void* var0) {
      throw IllegalArgumentException("Upper bound is not in valid sub-range: " + var0);
   }

    static void invalidLowerBound(void* var0) {
      throw IllegalArgumentException("Lower bound is not in valid sub-range: " + var0);
   }
}
} // namespace util
} // namespace util
} // namespace zombie
