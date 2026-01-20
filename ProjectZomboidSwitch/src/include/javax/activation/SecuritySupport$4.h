#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"
#include "java/security/PrivilegedAction.h"
#include <fstream>
#include <iostream>
#include <iterator>

namespace javax {
namespace activation {


class SecuritySupport {
public:
   SecuritySupport$4(std::string var1) {
      this.val$name = var1;
   }

    void* run() {
      URL[] ret = nullptr;

      try {
    std::vector v = new std::vector();
    Enumeration e = ClassLoader.getSystemResources(this.val$name);

         while (e != nullptr && e.hasMoreElements()) {
    URL url = (URL)e.nextElement();
            if (url != nullptr) {
               v.push_back(url);
            }
         }

         if (v.size() > 0) {
            ret = new URL[v.size()];
            ret = v.toArray(ret);
         }
      } catch (IOException var5) {
      } catch (SecurityException var6) {
      }

    return ret;
   }
}
} // namespace activation
} // namespace javax
