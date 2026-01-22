#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/FluentIterable.h"
#include "com/google/common/collect/ImmutableList.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class Parameter {
public:
   private const Invokable<?, ?> declaration;
    const int position;
   private const TypeToken<?> type;
   private const ImmutableList<Annotation> annotations;

   Parameter(Invokable<?, ?> declaration, int position, TypeToken<?> type, Annotation[] annotations) {
      this.declaration = declaration;
      this.position = position;
      this.type = type;
      this.annotations = ImmutableList.copyOf(annotations);
   }

   public TypeToken<?> getType() {
      return this.type;
   }

   public Invokable<?, ?> getDeclaringInvokable() {
      return this.declaration;
   }

    bool isAnnotationPresent(Class<? extends) {
      return this.getAnnotation(annotationType) != nullptr;
   }

   public <A : public Annotation> A getAnnotation(Class<A> annotationType) {
      Preconditions.checkNotNull(annotationType);

      for (Annotation annotation : this.annotations) {
         if (annotationType.isInstance(annotation)) {
            return annotationType.cast(annotation);
         }
      }

    return nullptr;
   }

   public Annotation[] getAnnotations() {
      return this.getDeclaredAnnotations();
   }

   public <A : public Annotation> A[] getAnnotationsByType(Class<A> annotationType) {
      return this.getDeclaredAnnotationsByType(annotationType);
   }

   public Annotation[] getDeclaredAnnotations() {
      return (Annotation[])this.annotations.toArray(new Annotation[this.annotations.size()]);
   }

   public <A : public Annotation> A getDeclaredAnnotation(Class<A> annotationType) {
      Preconditions.checkNotNull(annotationType);
      return (A)FluentIterable.from(this.annotations).filter(annotationType).first().orNull();
   }

   public <A : public Annotation> A[] getDeclaredAnnotationsByType(Class<A> annotationType) {
      return (A[])FluentIterable.from(this.annotations).filter(annotationType).toArray(annotationType);
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Parameter*>(obj) != nullptr)) {
    return false;
      } else {
    Parameter that = (Parameter)obj;
         return this.position == that.position && this.declaration == that.declaration);
      }
   }

    int hashCode() {
      return this.position;
   }

    std::string toString() {
      return this.type + " arg" + this.position;
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
