#pragma once
#include "zombie/util/map/NoSuchMappingException.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Exceptions {
public:
 static void indexOutOfBounds(int int2, int int1, int int0) {
 throw IndexOutOfBoundsException("Index out of bounds: " + int2 +
 ", valid range is " + int1 + " to " +
 int0);
 }

 static void nullArgument(std::string_view string) {
 throw NullPointerException("The specified " + string + " is nullptr");
 }

 static void negativeArgument(std::string_view string, void *object) {
 throw IllegalArgumentException(string +
 " cannot be negative: " + object);
 }

 static void negativeOrZeroArgument(std::string_view string, void *object) {
 throw IllegalArgumentException(string +
 " must be a positive value: " + object);
 }

 static void endOfIterator() {
 throw NoSuchElementException(
 "Attempt to iterate past iterator's last element.");
 }

 static void startOfIterator() {
 throw NoSuchElementException(
 "Attempt to iterate past iterator's first element.");
 }

 static void noElementToRemove() {
 throw IllegalStateException(
 "Attempt to remove element from iterator that has no current element.");
 }

 static void noElementToGet() noexcept{
 throw IllegalStateException(
 "Attempt to get element from iterator that has no current element. "
 "Call next() first.");
 }

 static void noElementToSet() {
 throw IllegalStateException(
 "Attempt to set element in iterator that has no current element.");
 }

 static void noLastElement() {
 throw IllegalStateException(
 "No value to return. Call containsKey() first.");
 }

 static void noSuchMapping(void *object) {
 throw NoSuchMappingException("No such key in map: " + object);
 }

 static void dequeNoFirst() {
 throw IndexOutOfBoundsException(
 "Attempt to get first element of empty deque");
 }

 static void dequeNoLast() {
 throw IndexOutOfBoundsException(
 "Attempt to get last element of empty deque");
 }

 static void dequeNoFirstToRemove() {
 throw IndexOutOfBoundsException(
 "Attempt to remove last element of empty deque");
 }

 static void dequeNoLastToRemove() {
 throw IndexOutOfBoundsException(
 "Attempt to remove last element of empty deque");
 }

 static void nullElementNotAllowed() {
 throw IllegalArgumentException(
 "Attempt to add a nullptr value to an adapted primitive set.");
 }

 static void cannotAdapt(std::string_view string) {
 throw IllegalStateException(
 "The " + string +
 " contains values preventing it from being adapted to a primitive " +
 string);
 }

 static void unsupported(std::string_view string) {
 throw UnsupportedOperationException(
 "Attempt to invoke unsupported operation: " + string);
 }

 static void unmodifiable(std::string_view string) {
 throw UnsupportedOperationException("Attempt to modify unmodifiable " +
 string);
 }

 static void cloning() {
 throw RuntimeException("Clone is not supported");
 }

 static void invalidRangeBounds(void *object1, void *object0) {
 throw IllegalArgumentException("First (" + object1 +
 ") cannot be greater than last (" +
 object0 + ")");
 }

 static void cannotMergeRanges(void *object1, void *object0) {
 throw IllegalArgumentException(
 "Ranges cannot be merged: " + object1.toString() + " and " +
 object0.toString());
 }

 static void setNoFirst() {
 throw NoSuchElementException(
 "Attempt to get first element of empty set");
 }

 static void setNoLast() {
 throw NoSuchElementException(
 "Attempt to get last element of empty set");
 }

 static void invalidSetBounds(void *object1, void *object0) {
 throw IllegalArgumentException(
 "Lower bound (" + object1 + ") cannot be greater than upper bound (" +
 object0 + ")");
 }

 static void valueNotInSubRange(void *object) {
 throw IllegalArgumentException(
 "Attempt to add a value outside valid range: " + object);
 }

 static void invalidUpperBound(void *object) {
 throw IllegalArgumentException(
 "Upper bound is not in valid sub-range: " + object);
 }

 static void invalidLowerBound(void *object) {
 throw IllegalArgumentException(
 "Lower bound is not in valid sub-range: " + object);
 }
}
} // namespace util
} // namespace util
} // namespace zombie
