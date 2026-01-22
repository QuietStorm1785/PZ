#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/TODO.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace util {


class ArrayInfoUtil {
public:
    private ArrayInfoUtil() {
   }

    static QName calcArrayTypeName(QName n) {
    std::string uri;
      if (n.getNamespaceURI() == "http://www.w3.org/2001/XMLSchema")) {
         TODO.checkSpec("this URI");
         uri = "http://jaxb.dev.java.net/array";
      } else {
         uri = n.getNamespaceURI();
      }

      return std::make_shared<QName>(uri, n.getLocalPart() + "Array");
   }
}
} // namespace util
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
