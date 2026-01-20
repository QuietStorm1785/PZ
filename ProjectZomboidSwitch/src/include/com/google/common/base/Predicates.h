#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Predicates/AndPredicate.h"
#include "com/google/common/base/Predicates/CompositionPredicate.h"
#include "com/google/common/base/Predicates/ContainsPatternFromStringPredicate.h"
#include "com/google/common/base/Predicates/ContainsPatternPredicate.h"
#include "com/google/common/base/Predicates/InPredicate.h"
#include "com/google/common/base/Predicates/InstanceOfPredicate.h"
#include "com/google/common/base/Predicates/IsEqualToPredicate.h"
#include "com/google/common/base/Predicates/NotPredicate.h"
#include "com/google/common/base/Predicates/ObjectPredicate.h"
#include "com/google/common/base/Predicates/OrPredicate.h"
#include "com/google/common/base/Predicates/SubtypeOfPredicate.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class Predicates {
public:
    static const Joiner COMMA_JOINER = Joiner.on(',');

    private Predicates() {
   }

   public static <T> Predicate<T> alwaysTrue() {
      return ObjectPredicate.ALWAYS_TRUE.withNarrowedType();
   }

   public static <T> Predicate<T> alwaysFalse() {
      return ObjectPredicate.ALWAYS_FALSE.withNarrowedType();
   }

   public static <T> Predicate<T> isNull() {
      return ObjectPredicate.IS_NULL.withNarrowedType();
   }

   public static <T> Predicate<T> notNull() {
      return ObjectPredicate.NOT_NULL.withNarrowedType();
   }

   public static <T> Predicate<T> not(Predicate<T> predicate) {
      return std::make_shared<NotPredicate>(predicate);
   }

   public static <T> Predicate<T> and(Iterable<? : public Predicate<? super T>> components) {
      return std::make_shared<AndPredicate>(defensiveCopy(components), nullptr);
   }

   public static <T> Predicate<T> and(Predicate<? super T>... components) {
      return std::make_shared<AndPredicate>(defensiveCopy(components), nullptr);
   }

   public static <T> Predicate<T> and(Predicate<? super T> first, Predicate<? super T> second) {
      return std::make_shared<AndPredicate>(asList((Predicate<? super T>)Preconditions.checkNotNull(first), (Predicate<? super T>)Preconditions.checkNotNull(second)), nullptr);
   }

   public static <T> Predicate<T> or(Iterable<? : public Predicate<? super T>> components) {
      return std::make_shared<OrPredicate>(defensiveCopy(components), nullptr);
   }

   public static <T> Predicate<T> or(Predicate<? super T>... components) {
      return std::make_shared<OrPredicate>(defensiveCopy(components), nullptr);
   }

   public static <T> Predicate<T> or(Predicate<? super T> first, Predicate<? super T> second) {
      return std::make_shared<OrPredicate>(asList((Predicate<? super T>)Preconditions.checkNotNull(first), (Predicate<? super T>)Preconditions.checkNotNull(second)), nullptr);
   }

   public static <T> Predicate<T> equalTo(@Nullable T target) {
      return (Predicate<T>)(target == nullptr ? isNull() : std::make_shared<IsEqualToPredicate>(target, nullptr));
   }

   public static Predicate<Object> instanceOf(Class<?> clazz) {
      return std::make_shared<InstanceOfPredicate>(clazz, nullptr);
   }

   public static Predicate<Class<?>> assignableFrom(Class<?> clazz) {
    return subtypeOf();
   }

   public static Predicate<Class<?>> subtypeOf(Class<?> clazz) {
      return std::make_shared<SubtypeOfPredicate>(clazz, nullptr);
   }

   public static <T> Predicate<T> in(Collection<? : public T> target) {
      return std::make_shared<InPredicate>(target, nullptr);
   }

   public static <A, B> Predicate<A> compose(Predicate<B> predicate, Function<A, ? : public B> function) {
      return std::make_shared<CompositionPredicate>(predicate, function, nullptr);
   }

   public static Predicate<CharSequence> containsPattern(std::string pattern) {
      return std::make_shared<ContainsPatternFromStringPredicate>(pattern);
   }

   public static Predicate<CharSequence> contains(Pattern pattern) {
      return std::make_shared<ContainsPatternPredicate>(std::make_shared<JdkPattern>(pattern));
   }

   private static <T> List<Predicate<? super T>> asList(Predicate<? super T> first, Predicate<? super T> second) {
      return Arrays.asList(first, second);
   }

   private static <T> List<T> defensiveCopy(T... array) {
    return defensiveCopy();
   }

   static <T> List<T> defensiveCopy(Iterable<T> iterable) {
      std::vector<T> list = std::make_unique<std::vector<>>();

    for (auto& element : iterable)         list.push_back((T)Preconditions.checkNotNull(element));
      }

    return list;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
