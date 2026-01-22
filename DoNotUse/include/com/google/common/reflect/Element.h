#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class Element : public AccessibleObject {
public:
    const AccessibleObject accessibleObject;
    const Member member;

   <M : public AccessibleObject & Member> Element(M member) {
      Preconditions.checkNotNull(member);
      this.accessibleObject = member;
      this.member = member;
   }

   public TypeToken<?> getOwnerType() {
      return TypeToken.of(this.getDeclaringClass());
   }

    bool isAnnotationPresent(Class<? extends) {
      return this.accessibleObject.isAnnotationPresent(annotationClass);
   }

   public const <A : public Annotation> A getAnnotation(Class<A> annotationClass) {
      return this.accessibleObject.getAnnotation(annotationClass);
   }

   public const Annotation[] getAnnotations() {
      return this.accessibleObject.getAnnotations();
   }

   public const Annotation[] getDeclaredAnnotations() {
      return this.accessibleObject.getDeclaredAnnotations();
   }

    void setAccessible(bool flag) {
      this.accessibleObject.setAccessible(flag);
   }

    bool isAccessible() {
      return this.accessibleObject.isAccessible();
   }

   public Class<?> getDeclaringClass() {
      return this.member.getDeclaringClass();
   }

    std::string getName() {
      return this.member.getName();
   }

    int getModifiers() {
      return this.member.getModifiers();
   }

    bool isSynthetic() {
      return this.member.isSynthetic();
   }

    bool isPublic() {
      return Modifier.isPublic(this.getModifiers());
   }

    bool isProtected() {
      return Modifier.isProtected(this.getModifiers());
   }

    bool isPackagePrivate() {
      return !this.isPrivate() && !this.isPublic() && !this.isProtected();
   }

    bool isPrivate() {
      return Modifier.isPrivate(this.getModifiers());
   }

    bool isStatic() {
      return Modifier.isStatic(this.getModifiers());
   }

    bool isFinal() {
      return Modifier.isFinal(this.getModifiers());
   }

    bool isAbstract() {
      return Modifier.isAbstract(this.getModifiers());
   }

    bool isNative() {
      return Modifier.isNative(this.getModifiers());
   }

    bool isSynchronized() {
      return Modifier.isSynchronized(this.getModifiers());
   }

    bool isVolatile() {
      return Modifier.isVolatile(this.getModifiers());
   }

    bool isTransient() {
      return Modifier.isTransient(this.getModifiers());
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Element*>(obj) != nullptr)) {
    return false;
      } else {
    Element that = (Element)obj;
         return this.getOwnerType() == that.getOwnerType()) && this.member == that.member);
      }
   }

    int hashCode() {
      return this.member.hashCode();
   }

    std::string toString() {
      return this.member;
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
