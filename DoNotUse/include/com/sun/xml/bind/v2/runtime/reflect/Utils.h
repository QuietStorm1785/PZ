#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Utils/1.h"
#include "java/security/AccessController.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Utils {
public:
    static const Logger LOGGER = Logger.getLogger(Utils.class.getName());
   static const Navigator<Type, Class, Field, Method> REFLECTION_NAVIGATOR;

    private Utils() {
   }

   static {
      try {
    Class refNav = Class.forName("com.sun.xml.bind.v2.model.nav.ReflectionNavigator");
    Method getInstance = AccessController.doPrivileged(std::make_shared<1>(refNav));
         REFLECTION_NAVIGATOR = (Navigator<Type, Class, Field, Method>)getInstance.invoke(nullptr);
      } catch (ClassNotFoundException var2) {
         throw IllegalStateException("Can't find ReflectionNavigator class");
      } catch (InvocationTargetException var3) {
         throw IllegalStateException("ReflectionNavigator.getInstance throws the exception");
      } catch (IllegalAccessException var4) {
         throw IllegalStateException("ReflectionNavigator.getInstance method is inaccessible");
      } catch (SecurityException var5) {
         LOGGER.log(Level.FINE, "Unable to access ReflectionNavigator.getInstance", (Throwable)var5);
    throw var5;
      }
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
