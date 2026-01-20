#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"
#include "java/security/AccessController.h"
#include "java/security/PrivilegedActionException.h"
#include "javax/activation/SecuritySupport/1.h"
#include "javax/activation/SecuritySupport/2.h"
#include "javax/activation/SecuritySupport/3.h"
#include "javax/activation/SecuritySupport/4.h"
#include "javax/activation/SecuritySupport/5.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class SecuritySupport {
public:
    private SecuritySupport() {
   }

    static ClassLoader getContextClassLoader() {
      return AccessController.doPrivileged(std::make_unique<1>());
   }

    static InputStream getResourceAsStream(Class c, const std::string& name) {
      try {
         return AccessController.doPrivileged(std::make_shared<2>(c, name));
      } catch (PrivilegedActionException var3) {
         throw (IOException)var3.getException();
      }
   }

   public static URL[] getResources(ClassLoader cl, std::string name) {
      return AccessController.doPrivileged(std::make_shared<3>(cl, name));
   }

   public static URL[] getSystemResources(std::string name) {
      return AccessController.doPrivileged(std::make_shared<4>(name));
   }

    static InputStream openStream(URL url) {
      try {
         return AccessController.doPrivileged(std::make_shared<5>(url));
      } catch (PrivilegedActionException var2) {
         throw (IOException)var2.getException();
      }
   }
}
} // namespace activation
} // namespace javax
