#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/Nullable.h"
#include "com/sun/xml/bind/v2/model/core/ErrorHandler.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class AnnotationReader {
public:
    virtual ~AnnotationReader() = default;
    void setErrorHandler(ErrorHandler var1);

   <A : public Annotation> A getFieldAnnotation(Class<A> var1, F var2, Locatable var3);

    bool hasFieldAnnotation(Class<? extends, F var2);

    bool hasClassAnnotation(C var1, Class<? extends);

   Annotation[] getAllFieldAnnotations(F var1, Locatable var2);

   <A : public Annotation> A getMethodAnnotation(Class<A> var1, M var2, M var3, Locatable var4);

    bool hasMethodAnnotation(Class<? extends, const std::string& var2, M var3, M var4, Locatable var5);

   Annotation[] getAllMethodAnnotations(M var1, Locatable var2);

   <A : public Annotation> A getMethodAnnotation(Class<A> var1, M var2, Locatable var3);

    bool hasMethodAnnotation(Class<? extends, M var2);

   <A : public Annotation> A getMethodParameterAnnotation(Class<A> var1, M var2, int var3, Locatable var4);

   <A : public Annotation> A getClassAnnotation(Class<A> var1, C var2, Locatable var3);

   <A : public Annotation> A getPackageAnnotation(Class<A> var1, C var2, Locatable var3);

    T getClassValue(Annotation var1, const std::string& var2);

   T[] getClassArrayValue(Annotation var1, std::string var2);
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
