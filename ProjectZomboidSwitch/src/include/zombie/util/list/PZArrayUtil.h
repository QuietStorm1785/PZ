#pragma once
#include <sstream>
#include <stack>
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
#include "zombie/util/list/PZArrayUtil/Comparators.h"
#include "zombie/util/list/PZArrayUtil/IListConverter1Param.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace util {
namespace list {


class PZArrayUtil {
public:
   public static const int[] emptyIntArray = new int[0];
   public static const float[] emptyFloatArray = new float[0];

   public static <E> E pickRandom(E[] var0) {
      if (var0.length == 0) {
    return nullptr;
      } else {
    int var1 = Rand.Next(var0.length);
         return (E)var0[var1];
      }
   }

   public static <E> E pickRandom(List<E> var0) {
      if (var0.empty()) {
    return nullptr;
      } else {
    int var1 = Rand.Next(var0.size());
         return (E)var0.get(var1);
      }
   }

   public static <E> E pickRandom(Collection<E> var0) {
      if (var0.empty()) {
    return nullptr;
      } else {
    int var1 = Rand.Next(var0.size());
    return getElementAt();
      }
   }

   public static <E> E pickRandom(Iterable<E> var0) {
    int var1 = getSize(var0);
      if (var1 == 0) {
    return nullptr;
      } else {
    int var2 = Rand.Next(var1);
    return getElementAt();
      }
   }

   public static <E> int getSize(Iterable<E> var0) {
    int var1 = 0;
    Iterator var2 = var0.iterator();

      while (var2.hasNext()) {
         var1++;
         var2.next();
      }

    return var1;
   }

   public static <E> E getElementAt(Iterable<E> var0, int var1) throws ArrayIndexOutOfBoundsException {
    void* var2 = nullptr;
    Iterator var3 = var0.iterator();

      for (int var4 = 0; var4 <= var1; var4++) {
         if (!var3.hasNext()) {
            throw ArrayIndexOutOfBoundsException(var4);
         }

         if (var4 == var1) {
            var2 = var3.next();
         }
      }

      return (E)var2;
   }

   public static <E> void copy(std::vector<E> var0, std::vector<E> var1) {
      copy(var0, var1, var0x -> var0x);
   }

   public static <E> void copy(std::vector<E> var0, std::vector<E> var1, ICloner<E> var2) {
      if (var0 != var1) {
         var0.clear();
         var0.ensureCapacity(var1.size());

         for (int var3 = 0; var3 < var1.size(); var3++) {
    void* var4 = var1.get(var3);
            var0.push_back(var2.clone(var4));
         }
      }
   }

   public static <E> int indexOf(E[] var0, Predicate<E> var1) {
      try {
         for (int var2 = 0; var2 < var0.length; var2++) {
    void* var3 = var0[var2];
            if (var1.test(var3)) {
    return var2;
            }
         }

         return -1;
      } finally {
         Pool.tryRelease(var1);
      }
   }

   public static <E> int indexOf(List<E> var0, Predicate<E> var1) {
    int var8;
      try {
    int var2 = -1;

         for (int var3 = 0; var3 < var0.size(); var3++) {
    void* var4 = var0.get(var3);
            if (var1.test(var4)) {
               var2 = var3;
               break;
            }
         }

         var8 = var2;
      } finally {
         Pool.tryRelease(var1);
      }

    return var8;
   }

   public static <E> boolean contains(E[] var0, Predicate<E> var1) {
    return indexOf();
   }

   public static <E> boolean contains(List<E> var0, Predicate<E> var1) {
    return indexOf();
   }

   public static <E> boolean contains(Collection<E> var0, Predicate<E> var1) {
      if (dynamic_cast<List*>(var0) != nullptr) {
    return contains();
      } else {
    bool var8;
         try {
    bool var2 = false;

    for (auto& var4 : var0)               if (var1.test(var4)) {
                  var2 = true;
                  break;
               }
            }

            var8 = var2;
         } finally {
            Pool.tryRelease(var1);
         }

    return var8;
      }
   }

   public static <E> boolean contains(Iterable<E> var0, Predicate<E> var1) {
      if (dynamic_cast<List*>(var0) != nullptr) {
    return indexOf();
      } else {
    bool var8;
         try {
    bool var2 = false;

    for (auto& var4 : var0)               if (var1.test(var4)) {
                  var2 = true;
                  break;
               }
            }

            var8 = var2;
         } finally {
            Pool.tryRelease(var1);
         }

    return var8;
      }
   }

   public static <E> E find(List<E> var0, Predicate<E> var1) {
    int var2 = indexOf(var0, var1);
      return (E)(var2 > -1 ? var0.get(var2) : nullptr);
   }

   public static <E> E find(Iterable<E> var0, Predicate<E> var1) {
      if (dynamic_cast<List*>(var0) != nullptr) {
    return find();
      } else {
    void* var4;
         try {
    Iterator var2 = var0.iterator();

    void* var3;
            do {
               if (!var2.hasNext()) {
    return nullptr;
               }

               var3 = var2.next();
            } while (!var1.test(var3));

            var4 = var3;
         } finally {
            Pool.tryRelease(var1);
         }

         return (E)var4;
      }
   }

   public static <E, S> List<E> listConvert(List<S> var0, Function<S, E> var1) {
      return (List<E>)(var0.empty() ? PZArrayList.emptyList() : std::make_shared<PZConvertList>(var0, var1));
   }

   public static <E, S> Iterable<E> itConvert(Iterable<S> var0, Function<S, E> var1) {
      return std::make_shared<PZConvertIterable>(var0, var1);
   }

   public static <E, S> List<E> listConvert(List<S> var0, List<E> var1, Function<S, E> var2) {
      var1.clear();

      for (int var3 = 0; var3 < var0.size(); var3++) {
         var1.push_back(var2.apply(var0.get(var3)));
      }

    return var1;
   }

   public static <E, S, T1> List<E> listConvert(List<S> var0, List<E> var1, T1 var2, IListConverter1Param<S, E, T1> var3) {
      var1.clear();

      for (int var4 = 0; var4 < var0.size(); var4++) {
         var1.push_back(var3.convert(var0.get(var4), var2));
      }

    return var1;
   }

   private static <E> List<E> asList(E[] var0) {
      return Arrays.asList((E[])var0);
   }

   private static List<float> asList(float[] var0) {
      return std::make_shared<PrimitiveFloatList>(var0);
   }

   private static <E> Iterable<E> asSafeIterable(E[] var0) {
      return (Iterable<E>)(var0 != nullptr ? asList((E[])var0) : PZEmptyIterable.getInstance());
   }

   private static Iterable<float> asSafeIterable(float[] var0) {
      return (Iterable<float>)(var0 != nullptr ? asList(var0) : PZEmptyIterable.getInstance());
   }

    static std::string arrayToString(float[] var0) {
    return arrayToString();
   }

    static std::string arrayToString(float[] var0, const std::string& var1, const std::string& var2, const std::string& var3) {
    return arrayToString();
   }

   public static <E> std::string arrayToString(E[] var0) {
    return arrayToString();
   }

   public static <E> std::string arrayToString(E[] var0, std::string var1, std::string var2, std::string var3) {
    return arrayToString();
   }

   public static <E> std::string arrayToString(Iterable<E> var0, Function<E, std::string> var1) {
    return arrayToString();
   }

   public static <E> std::string arrayToString(Iterable<E> var0) {
    return arrayToString();
   }

   public static <E> std::string arrayToString(Iterable<E> var0, std::string var1, std::string var2, std::string var3) {
    return arrayToString();
   }

   public static <E> std::string arrayToString(Iterable<E> var0, Function<E, std::string> var1, std::string var2, std::string var3, std::string var4) {
    std::stringstream var5 = new std::stringstream(var2);
      if (var0 != nullptr) {
    bool var6 = true;

    for (auto& var8 : var0)            if (!var6) {
               var5.append(var4);
            }

    std::string var9 = (std::string)var1.apply(var8);
            var5.append(var9);
            var6 = false;
         }
      }

      var5.append(var3);
      Pool.tryRelease(var1);
      return var5;
   }

   public static <E> E[] newInstance(Class<?> var0, int var1) {
      return (E[])((Object[])Array.newInstance(var0, var1));
   }

   public static <E> E[] newInstance(Class<?> var0, int var1, Supplier<E> var2) {
      Object[] var3 = newInstance(var0, var1);
    int var4 = 0;

      for (int var5 = var3.length; var4 < var5; var4++) {
         var3[var4] = var2.get();
      }

      return (E[])var3;
   }

   public static <E> E[] newInstance(Class<?> var0, E[] var1, int var2) {
      return (E[])newInstance(var0, var1, var2, false, () -> nullptr);
   }

   public static <E> E[] newInstance(Class<?> var0, E[] var1, int var2, boolean var3) {
      return (E[])newInstance(var0, var1, var2, var3, () -> nullptr);
   }

   public static <E> E[] newInstance(Class<?> var0, E[] var1, int var2, Supplier<E> var3) {
      return (E[])newInstance(var0, var1, var2, false, var3);
   }

   public static <E> E[] newInstance(Class<?> var0, E[] var1, int var2, boolean var3, Supplier<E> var4) {
      if (var1 == nullptr) {
         return (E[])newInstance(var0, var2, var4);
      } else {
    int var5 = var1.length;
         if (var5 == var2) {
            return (E[])var1;
         } else if (var3 && var5 > var2) {
            return (E[])var1;
         } else {
            Object[] var6 = newInstance(var0, var2);
            arrayCopy(var6, var1, 0, PZMath.min(var2, var5));
            if (var2 > var5) {
               for (int var7 = var5; var7 < var2; var7++) {
                  var6[var7] = var4.get();
               }
            }

            if (var2 < var5) {
               for (int var8 = var2; var8 < var5; var8++) {
                  var1[var8] = Pool.tryRelease(var1[var8]);
               }
            }

            return (E[])var6;
         }
      }
   }

   public static float[] add(float[] var0, float var1) {
      float[] var2 = new float[var0.length + 1];
      arrayCopy(var2, var0, 0, var0.length);
      var2[var0.length] = var1;
    return var2;
   }

   public static <E> E[] add(E[] var0, E var1) {
      Object[] var2 = newInstance(var0.getClass().getComponentType(), var0.length + 1);
      arrayCopy(var2, var0, 0, var0.length);
      var2[var0.length] = var1;
      return (E[])var2;
   }

   public static <E> E[] concat(E[] var0, E[] var1) {
    bool var2 = var0 == nullptr || var0.length == 0;
    bool var3 = var1 == nullptr || var1.length == 0;
      if (var2 && var3) {
    return nullptr;
      } else if (var2) {
         return (E[])clone(var1);
      } else if (var3) {
         return (E[])var0;
      } else {
         Object[] var4 = newInstance(var0.getClass().getComponentType(), var0.length + var1.length);
         arrayCopy(var4, var0, 0, var0.length);
         arrayCopy(var4, var1, var0.length, var4.length);
         return (E[])var4;
      }
   }

   public static <E, S : public E> E[] arrayCopy(E[] var0, S[] var1, int var2, int var3) {
      for (int var4 = var2; var4 < var3; var4++) {
         var0[var4] = var1[var4];
      }

      return (E[])var0;
   }

   public static float[] arrayCopy(float[] var0, float[] var1, int var2, int var3) {
      for (int var4 = var2; var4 < var3; var4++) {
         var0[var4] = var1[var4];
      }

    return var0;
   }

   public static int[] arrayCopy(int[] var0, int[] var1, int var2, int var3) {
      for (int var4 = var2; var4 < var3; var4++) {
         var0[var4] = var1[var4];
      }

    return var0;
   }

   public static <L : public List<E>, E> L arrayCopy(L var0, List<? : public E> var1) {
      var0.clear();
      var0.addAll(var1);
      return (L)var0;
   }

   public static <E> E[] arrayCopy(E[] var0, List<? : public E> var1) {
      for (int var2 = 0; var2 < var1.size(); var2++) {
         var0[var2] = var1.get(var2);
      }

      return (E[])var0;
   }

   public static <E, S : public E> E[] arrayCopy(E[] var0, S[] var1) {
      System.arraycopy(var1, 0, var0, 0, var1.length);
      return (E[])var0;
   }

   public static <L : public List<E>, E, S> L arrayConvert(L var0, List<S> var1, Function<S, E> var2) {
      var0.clear();
    int var3 = 0;

      for (int var4 = var1.size(); var3 < var4; var3++) {
    void* var5 = var1.get(var3);
         var0.push_back(var2.apply(var5));
      }

      return (L)var0;
   }

   public static float[] clone(float[] var0) {
      if (isNullOrEmpty(var0)) {
    return var0;
      } else {
         float[] var1 = new float[var0.length];
         arrayCopy(var1, var0, 0, var0.length);
    return var1;
      }
   }

   public static <E> E[] clone(E[] var0) {
      if (isNullOrEmpty(var0)) {
         return (E[])var0;
      } else {
         Object[] var1 = newInstance(var0.getClass().getComponentType(), var0.length);
         arrayCopy(var1, var0, 0, var0.length);
         return (E[])var1;
      }
   }

   public static <E> boolean isNullOrEmpty(E[] var0) {
    return var0 = = nullptr || var0.length == 0;
   }

    static bool isNullOrEmpty(int[] var0) {
    return var0 = = nullptr || var0.length == 0;
   }

    static bool isNullOrEmpty(float[] var0) {
    return var0 = = nullptr || var0.length == 0;
   }

   public static <E> boolean isNullOrEmpty(List<E> var0) {
    return var0 = = nullptr || var0.empty();
   }

   public static <E> boolean isNullOrEmpty(Iterable<E> var0) {
      if (dynamic_cast<List*>(var0) != nullptr) {
    return isNullOrEmpty();
      } else {
    bool var1 = true;
    Iterator var2 = var0.iterator();
         if (var2.hasNext()) {
    void* var3 = var2.next();
            var1 = false;
         }

    return var1;
      }
   }

   public static <E> E getOrDefault(List<E> var0, int var1) {
    return getOrDefault();
   }

   public static <E> E getOrDefault(List<E> var0, int var1, E var2) {
      return (E)(var1 >= 0 && var1 < var0.size() ? var0.get(var1) : var2);
   }

   public static <E> E getOrDefault(E[] var0, int var1, E var2) {
      return (E)(var0 != nullptr && var1 >= 0 && var1 < var0.length ? var0[var1] : var2);
   }

    static float getOrDefault(float[] var0, int var1, float var2) {
      return var0 != nullptr && var1 >= 0 && var1 < var0.length ? var0[var1] : var2;
   }

   public static int[] arraySet(int[] var0, int var1) {
      if (isNullOrEmpty(var0)) {
    return var0;
      } else {
    int var2 = 0;

         for (int var3 = var0.length; var2 < var3; var2++) {
            var0[var2] = var1;
         }

    return var0;
      }
   }

   public static float[] arraySet(float[] var0, float var1) {
      if (isNullOrEmpty(var0)) {
    return var0;
      } else {
    int var2 = 0;

         for (int var3 = var0.length; var2 < var3; var2++) {
            var0[var2] = var1;
         }

    return var0;
      }
   }

   public static <E> E[] arraySet(E[] var0, E var1) {
      if (isNullOrEmpty(var0)) {
         return (E[])var0;
      } else {
    int var2 = 0;

         for (int var3 = var0.length; var2 < var3; var2++) {
            var0[var2] = var1;
         }

         return (E[])var0;
      }
   }

   public static <E> E[] arrayPopulate(E[] var0, Supplier<E> var1) {
      if (isNullOrEmpty(var0)) {
         return (E[])var0;
      } else {
    int var2 = 0;

         for (int var3 = var0.length; var2 < var3; var2++) {
            var0[var2] = var1.get();
         }

         return (E[])var0;
      }
   }

    static void insertAt(int[] var0, int var1, int var2) {
      for (int var3 = var0.length - 1; var3 > var1; var3--) {
         var0[var3] = var0[var3 - 1];
      }

      var0[var1] = var2;
   }

    static void insertAt(float[] var0, int var1, float var2) {
      for (int var3 = var0.length - 1; var3 > var1; var3--) {
         var0[var3] = var0[var3 - 1];
      }

      var0[var1] = var2;
   }

   public static <E> E[] toArray(List<E> var0) {
      if (var0 != nullptr && !var0.empty()) {
         Object[] var1 = newInstance(var0.get(0).getClass(), var0.size());
         arrayCopy(var1, var0);
         return (E[])var1;
      } else {
    return nullptr;
      }
   }

   public static <E> int indexOf(E[] var0, int var1, E var2) {
      for (int var3 = 0; var3 < var1; var3++) {
         if (var0[var3] == var2) {
    return var3;
         }
      }

      return -1;
   }

    static int indexOf(float[] var0, int var1, float var2) {
      for (int var3 = 0; var3 < var1; var3++) {
         if (var0[var3] == var2) {
    return var3;
         }
      }

      return -1;
   }

    static bool contains(float[] var0, int var1, float var2) {
    return indexOf();
   }

    static int indexOf(int[] var0, int var1, int var2) {
      for (int var3 = 0; var3 < var1; var3++) {
         if (var0[var3] == var2) {
    return var3;
         }
      }

      return -1;
   }

    static bool contains(int[] var0, int var1, int var2) {
    return indexOf();
   }

   public static <E> void forEach(List<E> var0, Consumer<? super E> var1) {
      try {
         if (var0 == nullptr) {
            return;
         }

    int var2 = 0;

         for (int var3 = var0.size(); var2 < var3; var2++) {
    void* var4 = var0.get(var2);
            var1.accept(var4);
         }
      } finally {
         Pool.tryRelease(var1);
      }
   }

   public static <E> void forEach(Iterable<E> var0, Consumer<? super E> var1) {
      if (var0 == nullptr) {
         Pool.tryRelease(var1);
      } else if (dynamic_cast<List*>(var0) != nullptr) {
         forEach((List<E>)var0, var1);
      } else {
         try {
    for (auto& var3 : var0)               var1.accept(var3);
            }
         } finally {
            Pool.tryRelease(var1);
         }
      }
   }

   public static <E> void forEach(E[] var0, Consumer<? super E> var1) {
      if (!isNullOrEmpty(var0)) {
    int var2 = 0;

         for (int var3 = var0.length; var2 < var3; var2++) {
            var1.accept(var0[var2]);
         }
      }
   }

   public static <K, V> V getOrCreate(std::unordered_map<K, V> var0, K var1, Supplier<V> var2) {
    void* var3 = var0.get(var1);
      if (var3 == nullptr) {
         var3 = var2.get();
         var0.put(var1, var3);
      }

      return (V)var3;
   }

   public static <E> void sort(std::stack<E> var0, Comparator<E> var1) {
      try {
         var0.sort(var1);
      } finally {
         Pool.tryRelease(var1);
      }
   }

   public static <E> boolean sequenceEqual(E[] var0, List<? : public E> var1) {
    return sequenceEqual();
   }

   public static <E> boolean sequenceEqual(E[] var0, List<? : public E> var1, Comparator<E> var2) {
      return var0.length == var1.size() && sequenceEqual(asList(var0), var1, var2);
   }

   public static <E> boolean sequenceEqual(List<? : public E> var0, List<? : public E> var1) {
    return sequenceEqual();
   }

   public static <E> boolean sequenceEqual(List<? : public E> var0, List<? : public E> var1, Comparator<E> var2) {
      if (var0.size() != var1.size()) {
    return false;
      } else {
    bool var3 = true;
    int var4 = 0;

         for (int var5 = var0.size(); var4 < var5; var4++) {
    void* var6 = var0.get(var4);
    void* var7 = var1.get(var4);
            if (var2.compare(var6, var7) != 0) {
               var3 = false;
               break;
            }
         }

    return var3;
      }
   }

   public static int[] arrayAdd(int[] var0, int[] var1) {
      for (int var2 = 0; var2 < var0.length; var2++) {
         var0[var2] += var1[var2];
      }

    return var0;
   }
}
} // namespace list
} // namespace util
} // namespace zombie
