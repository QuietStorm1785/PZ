#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/PrivilegedAction.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace util {


class XmlFactory {
public:
    bool run() {
      return bool.getBoolean("com.sun.xml.bind.disableXmlSecurity");
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
