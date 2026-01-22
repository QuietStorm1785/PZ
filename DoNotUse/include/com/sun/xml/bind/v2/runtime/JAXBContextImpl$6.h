#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/namespace/QName.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class JAXBContextImpl {
public:
    int compare(QName lhs, QName rhs) {
    int r = lhs.getLocalPart().compareTo(rhs.getLocalPart());
      return r != 0 ? r : lhs.getNamespaceURI().compareTo(rhs.getNamespaceURI());
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
