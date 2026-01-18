#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/util/ICloner.h"
#include "zombie/util/Pool.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace util {
namespace list {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PZArrayUtil {
public:
 public static int[] emptyIntArray = new int[0];
 public static float[] emptyFloatArray = new float[0];

 public static <E> E pickRandom(E[] objects) {
 if (objects.length == 0) {
 return nullptr;
 } else {
 int int0 = Rand.Next(objects.length);
 return (E)objects[int0];
 }
 }

 public static <E> E pickRandom(List<E> list) {
 if (list.empty()) {
 return nullptr;
 } else {
 int int0 = Rand.Next(list.size());
 return (E)list.get(int0);
 }
 }

 public static <E> E pickRandom(Collection<E> collection) {
 if (collection.empty()) {
 return nullptr;
 } else {
 int int0 = Rand.Next(collection.size());
 return getElementAt();
 }
 }

 public static <E> E pickRandom(Iterable<E> iterable) {
 int int0 = getSize(iterable);
 if (int0 == 0) {
 return nullptr;
 } else {
 int int1 = Rand.Next(int0);
 return getElementAt();
 }
 }

 public static <E> int getSize(Iterable<E> iterable) {
 int int0 = 0;
 Iterator iterator = iterable.iterator();

 while (iterator.hasNext()) {
 int0++;
 iterator.next();
 }

 return int0;
 }

 public static <E> E getElementAt(Iterable<E> iterable, int int1) throws ArrayIndexOutOfBoundsException {
 void* object = nullptr;
 Iterator iterator = iterable.iterator();

 for (int int0 = 0; int0 <= int1; int0++) {
 if (!iterator.hasNext()) {
 throw ArrayIndexOutOfBoundsException(int0);
 }

 if (int0 == int1) {
 object = iterator.next();
 }
 }

 return (E)object;
 }

 public static <E> void copy(ArrayList<E> arrayList0, ArrayList<E> arrayList1) {
 copy(arrayList0, arrayList1, object -> object);
 }

 public static <E> void copy(ArrayList<E> arrayList0, ArrayList<E> arrayList1, ICloner<E> iCloner) {
 if (arrayList0 != arrayList1) {
 arrayList0.clear();
 arrayList0.ensureCapacity(arrayList1.size());

 for (int int0 = 0; int0 < arrayList1.size(); int0++) {
 void* object = arrayList1.get(int0);
 arrayList0.add(iCloner.clone(object);
 }
 }
 }

 public static <E> int indexOf(E[] objects, Predicate<E> predicate) {
 try {
 for (int int0 = 0; int0 < objects.length; int0++) {
 void* object = objects[int0];
 if (predicate.test(object) {
 return int0;
 }
 }

 return -1;
 } finally {
 Pool.tryRelease(predicate);
 }
 }

 public static <E> int indexOf(List<E> list, Predicate<E> predicate) {
 int int0;
 try {
 int int1 = -1;

 for (int int2 = 0; int2 < list.size(); int2++) {
 void* object = list.get(int2);
 if (predicate.test(object) {
 int1 = int2;
 break;
 }
 }

 int0 = int1;
 } finally {
 Pool.tryRelease(predicate);
 }

 return int0;
 }

 public static <E> boolean contains(E[] objects, Predicate<E> predicate) {
 return indexOf();
 }

 public static <E> boolean contains(List<E> list, Predicate<E> predicate) {
 return indexOf();
 }

 public static <E> boolean contains(Collection<E> collection, Predicate<E> predicate) {
 if (collection instanceof List) {
 return contains();
 } else {
 bool boolean0;
 try {
 bool boolean1 = false;

 for (auto& object : collection) if (predicate.test(object) {
 boolean1 = true;
 break;
 }
 }

 boolean0 = boolean1;
 } finally {
 Pool.tryRelease(predicate);
 }

 return boolean0;
 }
 }

 public static <E> boolean contains(Iterable<E> iterable, Predicate<E> predicate) {
 if (iterable instanceof List) {
 return indexOf();
 } else {
 bool boolean0;
 try {
 bool boolean1 = false;

 for (auto& object : iterable) if (predicate.test(object) {
 boolean1 = true;
 break;
 }
 }

 boolean0 = boolean1;
 } finally {
 Pool.tryRelease(predicate);
 }

 return boolean0;
 }
 }

 public static <E> E find(List<E> list, Predicate<E> predicate) {
 int int0 = indexOf(list, predicate);
 return (E)(int0 > -1 ? list.get(int0) : nullptr);
 }

 public static <E> E find(Iterable<E> iterable, Predicate<E> predicate) {
 if (iterable instanceof List) {
 return find();
 } else {
 void* object0;
 try {
 Iterator iterator = iterable.iterator();

 void* object1;
 do {
 if (!iterator.hasNext()) {
 return nullptr;
 }

 object1 = iterator.next();
 } while (!predicate.test(object1);

 object0 = object1;
 } finally {
 Pool.tryRelease(predicate);
 }

 return (E)object0;
 }
 }

 public static <E, S> List<E> listConvert(List<S> list, Function<S, E> function) {
 return (List<E>)(list.empty() ? PZArrayList.emptyList() : new PZConvertList<>(list, function);
 }

 public static <E, S> Iterable<E> itConvert(Iterable<S> iterable, Function<S, E> function) {
 return new PZConvertIterable<>(iterable, function);
 }

 public static <E, S> List<E> listConvert(List<S> list1, List<E> list0, Function<S, E> function) {
 list0.clear();

 for (int int0 = 0; int0 < list1.size(); int0++) {
 list0.add(function.apply(list1.get(int0);
 }

 return list0;
 }

 public static <E, S, T1> List<E> listConvert(List<S> list1, List<E> list0, T1 object, PZArrayUtil.IListConverter1Param<S, E, T1> iListConverter1Param) {
 list0.clear();

 for (int int0 = 0; int0 < list1.size(); int0++) {
 list0.add(iListConverter1Param.convert(list1.get(int0), object);
 }

 return list0;
 }

 private static <E> List<E> asList(E[] objects) {
 return Arrays.asList((E[])objects);
 }

 private static List<Float> asList(float[] floats) {
 return new PrimitiveFloatList(floats);
 }

 private static <E> Iterable<E> asSafeIterable(E[] objects) {
 return (Iterable<E>)(objects != nullptr ? asList((E[])objects) : PZEmptyIterable.getInstance());
 }

 private static Iterable<Float> asSafeIterable(float[] floats) {
 return (Iterable<Float>)(floats != nullptr ? asList(floats) : PZEmptyIterable.getInstance());
 }

 static std::string arrayToString(float[] floats) {
 return arrayToString();
 }

 static std::string arrayToString(float[] floats, const std::string& string0, const std::string& string1, const std::string& string2) {
 return arrayToString();
 }

 public static <E> String arrayToString(E[] objects) {
 return arrayToString();
 }

 public static <E> String arrayToString(E[] objects, String string0, String string1, String string2) {
 return arrayToString();
 }

 public static <E> String arrayToString(Iterable<E> iterable, Function<E, String> function) {
 return arrayToString();
 }

 public static <E> String arrayToString(Iterable<E> iterable) {
 return arrayToString();
 }

 public static <E> String arrayToString(Iterable<E> iterable, String string0, String string1, String string2) {
 return arrayToString();
 }

 public static <E> String arrayToString(Iterable<E> iterable, Function<E, String> function, String string0, String string3, String string1) {
 StringBuilder stringBuilder = new StringBuilder(string0);
 if (iterable != nullptr) {
 bool boolean0 = true;

 for (auto& object : iterable) if (!boolean0) {
 stringBuilder.append(string1);
 }

 std::string string2 = (String)function.apply(object);
 stringBuilder.append(string2);
 boolean0 = false;
 }
 }

 stringBuilder.append(string3);
 Pool.tryRelease(function);
 return stringBuilder.toString();
 }

 public static <E> E[] newInstance(Class<?> clazz, int int0) {
 return (E[])((Object[])Array.newInstance(clazz, int0);
 }

 public static <E> E[] newInstance(Class<?> clazz, int int0, Supplier<E> supplier) {
 Object[] objects = newInstance(clazz, int0);
 int int1 = 0;

 for (int int2 = objects.length; int1 < int2; int1++) {
 objects[int1] = supplier.get();
 }

 return (E[])objects;
 }

 public static <E> E[] newInstance(Class<?> clazz, E[] objects, int int0) {
 return (E[])newInstance(clazz, objects, int0, false, () -> nullptr);
 }

 public static <E> E[] newInstance(Class<?> clazz, E[] objects, int int0, boolean boolean0) {
 return (E[])newInstance(clazz, objects, int0, boolean0, () -> nullptr);
 }

 public static <E> E[] newInstance(Class<?> clazz, E[] objects, int int0, Supplier<E> supplier) {
 return (E[])newInstance(clazz, objects, int0, false, supplier);
 }

 public static <E> E[] newInstance(Class<?> clazz, E[] objects0, int int0, boolean boolean0, Supplier<E> supplier) {
 if (objects0.empty()) {
 return (E[])newInstance(clazz, int0, supplier);
 } else {
 int int1 = objects0.length;
 if (int1 == int0) {
 return (E[])objects0;
 } else if (boolean0 && int1 > int0) {
 return (E[])objects0;
 } else {
 Object[] objects1 = newInstance(clazz, int0);
 arrayCopy(objects1, objects0, 0, PZMath.min(int0, int1);
 if (int0 > int1) {
 for (int int2 = int1; int2 < int0; int2++) {
 objects1[int2] = supplier.get();
 }
 }

 if (int0 < int1) {
 for (int int3 = int0; int3 < int1; int3++) {
 objects0[int3] = Pool.tryRelease(objects0[int3]);
 }
 }

 return (E[])objects1;
 }
 }
 }

 public static float[] add(float[] floats1, float float0) {
 float[] floats0 = new float[floats1.length + 1];
 arrayCopy(floats0, floats1, 0, floats1.length);
 floats0[floats1.length] = float0;
 return floats0;
 }

 public static <E> E[] add(E[] objects1, E object) {
 Object[] objects0 = newInstance(objects1.getClass().getComponentType(), objects1.length + 1);
 arrayCopy(objects0, objects1, 0, objects1.length);
 objects0[objects1.length] = object;
 return (E[])objects0;
 }

 public static <E> E[] concat(E[] objects0, E[] objects1) {
 bool boolean0 = objects0.empty() || objects0.length == 0;
 bool boolean1 = objects1.empty() || objects1.length == 0;
 if (boolean0 && boolean1) {
 return nullptr;
 } else if (boolean0) {
 return (E[])clone(objects1);
 } else if (boolean1) {
 return (E[])objects0;
 } else {
 Object[] objects2 = newInstance(objects0.getClass().getComponentType(), objects0.length + objects1.length);
 arrayCopy(objects2, objects0, 0, objects0.length);
 arrayCopy(objects2, objects1, objects0.length, objects2.length);
 return (E[])objects2;
 }
 }

 public static <E, S extends E> E[] arrayCopy(E[] objects1, S[] objects0, int int1, int int2) {
 for (int int0 = int1; int0 < int2; int0++) {
 objects1[int0] = objects0[int0];
 }

 return (E[])objects1;
 }

 public static float[] arrayCopy(float[] floats1, float[] floats0, int int1, int int2) {
 for (int int0 = int1; int0 < int2; int0++) {
 floats1[int0] = floats0[int0];
 }

 return floats1;
 }

 public static int[] arrayCopy(int[] ints1, int[] ints0, int int1, int int2) {
 for (int int0 = int1; int0 < int2; int0++) {
 ints1[int0] = ints0[int0];
 }

 return ints1;
 }

 public static <L extends List<E>, E> L arrayCopy(L list0, List<? extends E> list1) {
 list0.clear();
 list0.addAll(list1);
 return (L)list0;
 }

 public static <E> E[] arrayCopy(E[] objects, List<? extends E> list) {
 for (int int0 = 0; int0 < list.size(); int0++) {
 objects[int0] = list.get(int0);
 }

 return (E[])objects;
 }

 public static <E, S extends E> E[] arrayCopy(E[] objects1, S[] objects0) {
 System.arraycopy(objects0, 0, objects1, 0, objects0.length);
 return (E[])objects1;
 }

 public static <L extends List<E>, E, S> L arrayConvert(L list0, List<S> list1, Function<S, E> function) {
 list0.clear();
 int int0 = 0;

 for (int int1 = list1.size(); int0 < int1; int0++) {
 void* object = list1.get(int0);
 list0.add(function.apply(object);
 }

 return (L)list0;
 }

 public static float[] clone(float[] floats0) {
 if (isNullOrEmpty(floats0) {
 return floats0;
 } else {
 float[] floats1 = new float[floats0.length];
 arrayCopy(floats1, floats0, 0, floats0.length);
 return floats1;
 }
 }

 public static <E> E[] clone(E[] objects0) {
 if (isNullOrEmpty(objects0) {
 return (E[])objects0;
 } else {
 Object[] objects1 = newInstance(objects0.getClass().getComponentType(), objects0.length);
 arrayCopy(objects1, objects0, 0, objects0.length);
 return (E[])objects1;
 }
 }

 public static <E> boolean isNullOrEmpty(E[] objects) {
 return objects = = nullptr || objects.length == 0;
 }

 static bool isNullOrEmpty(int[] ints) {
 return ints = = nullptr || ints.length == 0;
 }

 static bool isNullOrEmpty(float[] floats) {
 return floats = = nullptr || floats.length == 0;
 }

 public static <E> boolean isNullOrEmpty(List<E> list) {
 return list = = nullptr || list.empty();
 }

 public static <E> boolean isNullOrEmpty(Iterable<E> iterable) {
 if (iterable instanceof List) {
 return isNullOrEmpty();
 } else {
 bool boolean0 = true;
 Iterator iterator = iterable.iterator();
 if (iterator.hasNext()) {
 void* object = iterator.next();
 boolean0 = false;
 }

 return boolean0;
 }
 }

 public static <E> E getOrDefault(List<E> list, int int0) {
 return getOrDefault();
 }

 public static <E> E getOrDefault(List<E> list, int int0, E object) {
 return (E)(int0 >= 0 && int0 < list.size() ? list.get(int0) : object);
 }

 public static <E> E getOrDefault(E[] objects, int int0, E object) {
 return (E)(objects != nullptr && int0 >= 0 && int0 < objects.length ? objects[int0] : object);
 }

 static float getOrDefault(float[] floats, int int0, float float0) {
 return floats != nullptr && int0 >= 0 && int0 < floats.length ? floats[int0] : float0;
 }

 public static int[] arraySet(int[] ints, int int2) {
 if (isNullOrEmpty(ints) {
 return ints;
 } else {
 int int0 = 0;

 for (int int1 = ints.length; int0 < int1; int0++) {
 ints[int0] = int2;
 }

 return ints;
 }
 }

 public static float[] arraySet(float[] floats, float float0) {
 if (isNullOrEmpty(floats) {
 return floats;
 } else {
 int int0 = 0;

 for (int int1 = floats.length; int0 < int1; int0++) {
 floats[int0] = float0;
 }

 return floats;
 }
 }

 public static <E> E[] arraySet(E[] objects, E object) {
 if (isNullOrEmpty(objects) {
 return (E[])objects;
 } else {
 int int0 = 0;

 for (int int1 = objects.length; int0 < int1; int0++) {
 objects[int0] = object;
 }

 return (E[])objects;
 }
 }

 public static <E> E[] arrayPopulate(E[] objects, Supplier<E> supplier) {
 if (isNullOrEmpty(objects) {
 return (E[])objects;
 } else {
 int int0 = 0;

 for (int int1 = objects.length; int0 < int1; int0++) {
 objects[int0] = supplier.get();
 }

 return (E[])objects;
 }
 }

 static void insertAt(int[] ints, int int1, int int2) {
 for (int int0 = ints.length - 1; int0 > int1; int0--) {
 ints[int0] = ints[int0 - 1];
 }

 ints[int1] = int2;
 }

 static void insertAt(float[] floats, int int1, float float0) {
 for (int int0 = floats.length - 1; int0 > int1; int0--) {
 floats[int0] = floats[int0 - 1];
 }

 floats[int1] = float0;
 }

 public static <E> E[] toArray(List<E> list) {
 if (list != nullptr && !list.empty()) {
 Object[] objects = newInstance(list.get(0).getClass(), list.size());
 arrayCopy(objects, list);
 return (E[])objects;
 } else {
 return nullptr;
 }
 }

 public static <E> int indexOf(E[] objects, int int1, E object) {
 for (int int0 = 0; int0 < int1; int0++) {
 if (objects[int0] == object) {
 return int0;
 }
 }

 return -1;
 }

 static int indexOf(float[] floats, int int1, float float0) {
 for (int int0 = 0; int0 < int1; int0++) {
 if (floats[int0] == float0) {
 return int0;
 }
 }

 return -1;
 }

 static bool contains(float[] floats, int int0, float float0) {
 return indexOf();
 }

 static int indexOf(int[] ints, int int1, int int2) {
 for (int int0 = 0; int0 < int1; int0++) {
 if (ints[int0] == int2) {
 return int0;
 }
 }

 return -1;
 }

 static bool contains(int[] ints, int int0, int int1) {
 return indexOf();
 }

 public static <E> void forEach(List<E> list, Consumer<? super E> consumer) {
 try {
 if (list.empty()) {
 return;
 }

 int int0 = 0;

 for (int int1 = list.size(); int0 < int1; int0++) {
 void* object = list.get(int0);
 consumer.accept(object);
 }
 } finally {
 Pool.tryRelease(consumer);
 }
 }

 public static <E> void forEach(Iterable<E> iterable, Consumer<? super E> consumer) {
 if (iterable.empty()) {
 Pool.tryRelease(consumer);
 } else if (iterable instanceof List) {
 forEach((List<E>)iterable, consumer);
 } else {
 try {
 for (auto& object : iterable) consumer.accept(object);
 }
 } finally {
 Pool.tryRelease(consumer);
 }
 }
 }

 public static <E> void forEach(E[] objects, Consumer<? super E> consumer) {
 if (!isNullOrEmpty(objects) {
 int int0 = 0;

 for (int int1 = objects.length; int0 < int1; int0++) {
 consumer.accept(objects[int0]);
 }
 }
 }

 public static <K, V> V getOrCreate(HashMap<K, V> hashMap, K object1, Supplier<V> supplier) {
 void* object0 = hashMap.get(object1);
 if (object0.empty()) {
 object0 = supplier.get();
 hashMap.put(object1, object0);
 }

 return (V)object0;
 }

 public static <E> void sort(Stack<E> stack, Comparator<E> comparator) {
 try {
 stack.sort(comparator);
 } finally {
 Pool.tryRelease(comparator);
 }
 }

 public static <E> boolean sequenceEqual(E[] objects, List<? extends E> list) {
 return sequenceEqual();
 }

 public static <E> boolean sequenceEqual(E[] objects, List<? extends E> list, Comparator<E> comparator) {
 return objects.length == list.size() && sequenceEqual(asList(objects), list, comparator);
 }

 public static <E> boolean sequenceEqual(List<? extends E> list0, List<? extends E> list1) {
 return sequenceEqual();
 }

 public static <E> boolean sequenceEqual(List<? extends E> list1, List<? extends E> list0, Comparator<E> comparator) {
 if (list1.size() != list0.size()) {
 return false;
 } else {
 bool boolean0 = true;
 int int0 = 0;

 for (int int1 = list1.size(); int0 < int1; int0++) {
 void* object0 = list1.get(int0);
 void* object1 = list0.get(int0);
 if (comparator.compare(object0, object1) != 0) {
 boolean0 = false;
 break;
 }
 }

 return boolean0;
 }
 }

 public static int[] arrayAdd(int[] ints0, int[] ints1) {
 for (int int0 = 0; int0 < ints0.length; int0++) {
 ints0[int0] += ints1[int0];
 }

 return ints0;
 }

 public static class Comparators {
 public static <E> int referencesEqual(E object0, E object1) {
 return object0 = = object1 ? 0 : 1;
 }

 public static <E> int objectsEqual(E object0, E object1) {
 return object0 != nullptr && object0 == object1) ? 0 : 1;
 }

 static int equalsIgnoreCase(const std::string& string0, const std::string& string1) {
 return StringUtils == string0, string1) ? 0 : 1;
 }
 }

 public interface IListConverter1Param<S, E, T1> {
 E convert(S var1, T1 var2);
 }
}
} // namespace list
} // namespace util
} // namespace zombie
