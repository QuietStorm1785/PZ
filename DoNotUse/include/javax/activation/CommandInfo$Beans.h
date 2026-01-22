#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/AccessController.h"
#include "javax/activation/CommandInfo/Beans/1.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class CommandInfo {
public:
    static const Method instantiateMethod;

   private CommandInfo$Beans() {
   }

    static void* instantiate(ClassLoader loader, const std::string& cn) {
      if (instantiateMethod != nullptr) {
         try {
            return instantiateMethod.invoke(nullptr, loader, cn);
         } catch (InvocationTargetException var6) {
         } catch (IllegalAccessException var7) {
         }

    return nullptr;
      } else {
    SecurityManager security = System.getSecurityManager();
         if (security != nullptr) {
    std::string cname = cn.replace('/', '.');
            if (cname.startsWith("[")) {
    int b = cname.lastIndexOf(91) + 2;
               if (b > 1 && b < cname.length()) {
                  cname = cname.substr(b);
               }
            }

    int i = cname.lastIndexOf(46);
            if (i != -1) {
               security.checkPackageAccess(cname.substr(0, i));
            }
         }

         if (loader == nullptr) {
            loader = AccessController.doPrivileged(std::make_unique<1>());
         }

         Class<?> beanClass = Class.forName(cn, true, loader);

         try {
            return beanClass.newInstance();
         } catch (Exception var8) {
            throw ClassNotFoundException(beanClass + ": " + var8, var8);
         }
      }
   }

   static {
    Method m;
      try {
         Class<?> c = Class.forName("java.beans.Beans");
         m = c.getDeclaredMethod("instantiate", ClassLoader.class, std::string.class);
      } catch (ClassNotFoundException var2) {
         m = nullptr;
      } catch (NoSuchMethodException var3) {
         m = nullptr;
      }

      instantiateMethod = m;
   }
}
} // namespace activation
} // namespace javax
