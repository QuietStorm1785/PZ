#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/ErrorHandler.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class AbstractInlineAnnotationReaderImpl {
public:
    ErrorHandler errorHandler;

    void setErrorHandler(ErrorHandler errorHandler) {
      if (errorHandler == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         this.errorHandler = errorHandler;
      }
   }

    ErrorHandler getErrorHandler() {
      assert this.errorHandler != nullptr : "error handler must be set before use";

      return this.errorHandler;
   }

   public const <A : public Annotation> A getMethodAnnotation(Class<A> annotation, M getter, M setter, Locatable srcPos) {
    A a1 = (A)(getter == nullptr ? nullptr : this.getMethodAnnotation(annotation, getter, srcPos));
    A a2 = (A)(setter == nullptr ? nullptr : this.getMethodAnnotation(annotation, setter, srcPos));
      if (a1 == nullptr) {
    return a2 = = nullptr ? nullptr : a2;
      } else if (a2 == nullptr) {
    return a1;
      } else {
         this.getErrorHandler()
            .error(
               std::make_shared<IllegalAnnotationException>(
                  Messages.DUPLICATE_ANNOTATIONS.format(new Object[]{annotation.getName(), this.fullName(getter), this.fullName(setter)}), a1, a2
               )
            );
    return a1;
      }
   }

    bool hasMethodAnnotation(Class<? extends, const std::string& propertyName, M getter, M setter, Locatable srcPos) {
    bool x = getter != nullptr && this.hasMethodAnnotation(annotation, getter);
    bool y = setter != nullptr && this.hasMethodAnnotation(annotation, setter);
      if (x && y) {
         this.getMethodAnnotation(annotation, getter, setter, srcPos);
      }

      return x || y;
   }

   protected abstract std::string fullName(M var1);
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
