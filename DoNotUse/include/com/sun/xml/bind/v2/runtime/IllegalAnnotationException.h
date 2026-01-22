#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "javax/xml/bind/JAXBException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class IllegalAnnotationException : public JAXBException {
public:
   private const List<List<Location>> pos;
    static const long serialVersionUID = 1L;

    public IllegalAnnotationException(const std::string& message, Locatable src) {
      super(message);
      this.pos = this.build(src);
   }

    public IllegalAnnotationException(const std::string& message, Annotation src) {
      this(message, cast(src));
   }

    public IllegalAnnotationException(const std::string& message, Locatable src1, Locatable src2) {
      super(message);
      this.pos = this.build(src1, src2);
   }

    public IllegalAnnotationException(const std::string& message, Annotation src1, Annotation src2) {
      this(message, cast(src1), cast(src2));
   }

    public IllegalAnnotationException(const std::string& message, Annotation src1, Locatable src2) {
      this(message, cast(src1), src2);
   }

    public IllegalAnnotationException(const std::string& message, std::exception cause, Locatable src) {
      super(message, cause);
      this.pos = this.build(src);
   }

    static Locatable cast(Annotation a) {
      return dynamic_cast<Locatable*>(a) != nullptr ? (Locatable)a : nullptr;
   }

   private List<List<Location>> build(Locatable... srcs) {
      List<List<Location>> r = std::make_unique<std::vector<>>();

    for (auto& l : srcs)         if (l != nullptr) {
            List<Location> ll = this.convert(l);
            if (ll != nullptr && !ll.empty()) {
               r.push_back(ll);
            }
         }
      }

      return Collections.unmodifiableList(r);
   }

   private List<Location> convert(Locatable src) {
      if (src == nullptr) {
    return nullptr;
      } else {
         List<Location> r;
         for (r = std::make_unique<std::vector<>>(); src != nullptr; src = src.getUpstream()) {
            r.push_back(src.getLocation());
         }

         return Collections.unmodifiableList(r);
      }
   }

   public List<List<Location>> getSourcePos() {
      return this.pos;
   }

    std::string toString() {
    std::stringstream sb = new std::stringstream(this.getMessage());

      for (List<Location> locs : this.pos) {
         sb.append("\n\tthis problem is related to the following location:");

    for (auto& loc : locs)            sb.append("\n\t\tat ").append(loc);
         }
      }

      return sb;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
