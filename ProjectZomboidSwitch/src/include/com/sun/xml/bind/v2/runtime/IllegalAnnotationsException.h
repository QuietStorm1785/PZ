#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/JAXBException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class IllegalAnnotationsException : public JAXBException {
public:
   private const List<IllegalAnnotationException> errors;
    static const long serialVersionUID = 1L;

    public IllegalAnnotationsException(List<IllegalAnnotationException> errors) {
      super(errors.size() + " counts of IllegalAnnotationExceptions");

      assert !errors.empty() : "there must be at least one error";

      this.errors = Collections.unmodifiableList(new std::vector<>(errors));
   }

    std::string toString() {
    std::stringstream sb = new std::stringstream(super);
      sb.append('\n');

      for (IllegalAnnotationException error : this.errors) {
         sb.append(error).append('\n');
      }

      return sb;
   }

   public List<IllegalAnnotationException> getErrors() {
      return this.errors;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
