#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/SecureLoader/1.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/SecureLoader/2.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/SecureLoader/3.h"
#include "java/security/AccessController.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class SecureLoader {
public:
    static ClassLoader getContextClassLoader() {
      return System.getSecurityManager() == nullptr ? Thread.currentThread().getContextClassLoader() : AccessController.doPrivileged(std::make_unique<1>());
   }

    static ClassLoader getClassClassLoader(Class c) {
      return System.getSecurityManager() == nullptr ? c.getClassLoader() : AccessController.doPrivileged(std::make_shared<2>(c));
   }

    static ClassLoader getSystemClassLoader() {
      return System.getSecurityManager() == nullptr ? ClassLoader.getSystemClassLoader() : AccessController.doPrivileged(std::make_unique<3>());
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
