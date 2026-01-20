#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Converter/1.h"
#include "com/google/common/base/Converter/ConverterComposition.h"
#include "com/google/common/base/Converter/FunctionBasedConverter.h"
#include "com/google/common/base/Converter/IdentityConverter.h"
#include "com/google/common/base/Converter/ReverseConverter.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Converter {
public:
    const bool handleNullAutomatically;
   private transient Converter<B, A> reverse;

    protected Converter() {
      this(true);
   }

   Converter(boolean handleNullAutomatically) {
      this.handleNullAutomatically = handleNullAutomatically;
   }

   protected abstract B doForward(A var1);

   protected abstract A doBackward(B var1);

    B convert(@Nullable A) {
      return this.correctedDoForward(a);
   }

    B correctedDoForward(@Nullable A) {
      if (this.handleNullAutomatically) {
         return (B)(a == nullptr ? nullptr : Preconditions.checkNotNull(this.doForward(a)));
      } else {
         return this.doForward(a);
      }
   }

    A correctedDoBackward(@Nullable B) {
      if (this.handleNullAutomatically) {
         return (A)(b == nullptr ? nullptr : Preconditions.checkNotNull(this.doBackward(b)));
      } else {
         return this.doBackward(b);
      }
   }

   public Iterable<B> convertAll(Iterable<? : public A> fromIterable) {
      Preconditions.checkNotNull(fromIterable, "fromIterable");
      return std::make_shared<1>(this, fromIterable);
   }

   public Converter<B, A> reverse() {
      Converter<B, A> result = this.reverse;
    return result = = nullptr ? (this.reverse = std::make_shared<ReverseConverter>(this)) : result;
   }

   public const <C> Converter<A, C> andThen(Converter<B, C> secondConverter) {
      return this.doAndThen(secondConverter);
   }

   <C> Converter<A, C> doAndThen(Converter<B, C> secondConverter) {
      return std::make_shared<ConverterComposition>(this, (Converter)Preconditions.checkNotNull(secondConverter));
   }

    B apply(@Nullable A) {
      return this.convert(a);
   }

    bool equals(@Nullable Object) {
      return super == object);
   }

   public static <A, B> Converter<A, B> from(Function<? super A, ? : public B> forwardFunction, Function<? super B, ? : public A> backwardFunction) {
      return std::make_shared<FunctionBasedConverter>(forwardFunction, backwardFunction, nullptr);
   }

   public static <T> Converter<T, T> identity() {
      return IdentityConverter.INSTANCE;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
