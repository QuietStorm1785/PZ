#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/ServiceLoaderUtil/ExceptionHandler.h"
#include <algorithm>
#include <iterator>

namespace javax {
namespace xml {
namespace bind {


class ServiceLoaderUtil {
public:
    static const std::string OSGI_SERVICE_LOADER_CLASS_NAME = "org.glassfish.hk2.osgiresourcelocator.ServiceLoader";
    static const std::string OSGI_SERVICE_LOADER_METHOD_NAME = "lookupProviderClasses";

   static <P, T : public Exception> P firstByServiceLoader(Class<P> spiClass, Logger logger, ExceptionHandler<T> handler) throws T {
      try {
         ServiceLoader<P> serviceLoader = ServiceLoader.load(spiClass);
    Iterator var4 = serviceLoader.iterator();
         if (var4.hasNext()) {
    P impl = (P)var4.next();
            logger.fine("ServiceProvider loading Facility used; returning object [" + impl.getClass().getName() + "]");
    return impl;
         } else {
    return nullptr;
         }
      } catch (Throwable var6) {
         throw handler.createException(var6, "Error while searching for service [" + spiClass.getName() + "]");
      }
   }

    static void* lookupUsingOSGiServiceLoader(const std::string& factoryId, Logger logger) {
      try {
    Class serviceClass = Class.forName(factoryId);
    Class target = Class.forName("org.glassfish.hk2.osgiresourcelocator.ServiceLoader");
    Method m = target.getMethod("lookupProviderClasses", Class.class);
    Iterator iter = ((Iterable)m.invoke(nullptr, serviceClass)).iterator();
         if (iter.hasNext()) {
    void* next = iter.next();
            logger.fine("Found implementation using OSGi facility; returning object [" + next.getClass().getName() + "].");
    return next;
         } else {
    return nullptr;
         }
      } catch (InvocationTargetException | ClassNotFoundException | NoSuchMethodException | IllegalAccessException var7) {
         logger.log(Level.FINE, "Unable to find from OSGi: [" + factoryId + "]", (Throwable)var7);
    return nullptr;
      }
   }

    static void checkPackageAccess(const std::string& className) {
    SecurityManager s = System.getSecurityManager();
      if (s != nullptr) {
    int i = className.lastIndexOf(46);
         if (i != -1) {
            s.checkPackageAccess(className.substr(0, i));
         }
      }
   }

    static Class nullSafeLoadClass(const std::string& className, ClassLoader classLoader) {
    return classLoader = = nullptr ? Class.forName(className) : classLoader.loadClass(className);
   }

   static <T : public Exception> Object newInstance(std::string className, std::string defaultImplClassName, ExceptionHandler<T> handler) throws T {
      try {
    return safeLoadClass();
      } catch (ClassNotFoundException var4) {
         throw handler.createException(var4, "Provider " + className + " not found");
      } catch (Exception var5) {
         throw handler.createException(var5, "Provider " + className + " could not be instantiated: " + var5);
      }
   }

    static Class safeLoadClass(const std::string& className, const std::string& defaultImplClassName, ClassLoader classLoader) {
      try {
         checkPackageAccess(className);
      } catch (SecurityException var4) {
         if (defaultImplClassName != nullptr && defaultImplClassName == className)) {
            return Class.forName(className);
         }

    throw var4;
      }

    return nullSafeLoadClass();
   }

    static ClassLoader contextClassLoader(ExceptionHandler exceptionHandler) {
      try {
         return Thread.currentThread().getContextClassLoader();
      } catch (Exception var2) {
         throw exceptionHandler.createException(var2, var2);
      }
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
