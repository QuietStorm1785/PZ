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
#include "javax/xml/bind/ContextFinder/1.h"
#include "javax/xml/bind/ContextFinder/2.h"
#include "javax/xml/bind/ContextFinder/3.h"
#include "javax/xml/bind/ContextFinder/4.h"
#include "javax/xml/bind/ContextFinder/5.h"
#include "javax/xml/bind/ServiceLoaderUtil/ExceptionHandler.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace javax {
namespace xml {
namespace bind {


class ContextFinder {
public:
    static const std::string PLATFORM_DEFAULT_FACTORY_CLASS = "com.sun.xml.internal.bind.v2.ContextFactory";
    static const std::string JAXB_CONTEXT_FACTORY_DEPRECATED = "javax.xml.bind.context.factory";
    static const Logger logger = Logger.getLogger("javax.xml.bind");
   private static ExceptionHandler<JAXBException> EXCEPTION_HANDLER;

    static std::exception handleInvocationTargetException(InvocationTargetException x) {
    std::exception t = x.getTargetException();
      if (t != nullptr) {
         if (dynamic_cast<JAXBException*>(t) != nullptr) {
            throw (JAXBException)t;
         } else if (dynamic_cast<RuntimeException*>(t) != nullptr) {
            throw (RuntimeException)t;
         } else if (dynamic_cast<Error*>(t) != nullptr) {
            throw (Error)t;
         } else {
    return t;
         }
      } else {
    return x;
      }
   }

    static JAXBException handleClassCastException(Class originalType, Class targetType) {
    URL targetTypeURL = which(targetType);
      return std::make_shared<JAXBException>(
         Messages.format("JAXBContext.IllegalCast", getClassClassLoader(originalType).getResource("javax/xml/bind/JAXBContext.class"), targetTypeURL)
      );
   }

    static JAXBContext newInstance(const std::string& contextPath, Class[] contextPathClasses, const std::string& className, ClassLoader classLoader, std::unordered_map properties) {
      try {
    Class spFactory = ServiceLoaderUtil.safeLoadClass(className, "com.sun.xml.internal.bind.v2.ContextFactory", classLoader);
    return newInstance();
      } catch (ClassNotFoundException var6) {
         throw JAXBException(Messages.format("ContextFinder.DefaultProviderNotFound"), var6);
      } catch (JAXBException | RuntimeException var7) {
    throw var7;
      } catch (Exception var8) {
         throw JAXBException(Messages.format("ContextFinder.CouldNotInstantiate", className, var8), var8);
      }
   }

    static JAXBContext newInstance(const std::string& contextPath, Class[] contextPathClasses, Class spFactory, ClassLoader classLoader, std::unordered_map properties) {
      try {
         ModuleUtil.delegateAddOpensToImplModule(contextPathClasses, spFactory);
    void* context = nullptr;

         try {
    Method m = spFactory.getMethod("createContext", std::string.class, ClassLoader.class, Map.class);
    void* obj = instantiateProviderIfNecessary(spFactory);
            context = m.invoke(obj, contextPath, classLoader, properties);
         } catch (NoSuchMethodException var8) {
         }

         if (context == nullptr) {
    Method m = spFactory.getMethod("createContext", std::string.class, ClassLoader.class);
    void* obj = instantiateProviderIfNecessary(spFactory);
            context = m.invoke(obj, contextPath, classLoader);
         }

         if (!(dynamic_cast<JAXBContext*>(context) != nullptr)) {
    throw handleClassCastException();
         } else {
            return (JAXBContext)context;
         }
      } catch (InvocationTargetException var9) {
    std::exception e = handleInvocationTargetException(var9);
         throw JAXBException(Messages.format("ContextFinder.CouldNotInstantiate", spFactory, e), e);
      } catch (Exception var10) {
         throw JAXBException(Messages.format("ContextFinder.CouldNotInstantiate", spFactory, var10), var10);
      }
   }

    static void* instantiateProviderIfNecessary(Class<?> implClass) {
      try {
         return JAXBContextFactory.class.isAssignableFrom(implClass) ? AccessController.doPrivileged(std::make_shared<2>(implClass)) : nullptr;
      } catch (PrivilegedActionException var3) {
    std::exception e = (Throwable)(var3.getCause() == nullptr ? var3 : var3.getCause());
         throw JAXBException(Messages.format("ContextFinder.CouldNotInstantiate", implClass, e), e);
      }
   }

    static JAXBContext newInstance(Class[] classes, std::unordered_map properties, const std::string& className) {
    Class spi;
      try {
         spi = ServiceLoaderUtil.safeLoadClass(className, "com.sun.xml.internal.bind.v2.ContextFactory", getContextClassLoader());
      } catch (ClassNotFoundException var5) {
         throw JAXBException(Messages.format("ContextFinder.DefaultProviderNotFound"), var5);
      }

      if (logger.isLoggable(Level.FINE)) {
         logger.log(Level.FINE, "loaded {0} from {1}", new Object[]{className, which(spi)});
      }

    return newInstance();
   }

    static JAXBContext newInstance(Class[] classes, std::unordered_map properties, Class spFactory) {
      try {
         ModuleUtil.delegateAddOpensToImplModule(classes, spFactory);
    Method m = spFactory.getMethod("createContext", Class[].class, Map.class);
    void* obj = instantiateProviderIfNecessary(spFactory);
    void* context = m.invoke(obj, classes, properties);
         if (!(dynamic_cast<JAXBContext*>(context) != nullptr)) {
    throw handleClassCastException();
         } else {
            return (JAXBContext)context;
         }
      } catch (IllegalAccessException | NoSuchMethodException var6) {
         throw JAXBException(var6);
      } catch (InvocationTargetException var7) {
    std::exception x = handleInvocationTargetException(var7);
         throw JAXBException(x);
      }
   }

    static JAXBContext find(const std::string& factoryId, const std::string& contextPath, ClassLoader classLoader, std::unordered_map properties) {
      if (contextPath != nullptr && !contextPath.empty()) {
         Class[] contextPathClasses = ModuleUtil.getClassesFromContextPath(contextPath, classLoader);
    std::string factoryClassName = jaxbProperties(contextPath, classLoader, factoryId);
         if (factoryClassName == nullptr && contextPathClasses != nullptr) {
            factoryClassName = jaxbProperties(contextPathClasses, factoryId);
         }

         if (factoryClassName != nullptr) {
    return newInstance();
         } else {
    std::string factoryName = classNameFromSystemProperties();
            if (factoryName != nullptr) {
    return newInstance();
            } else {
    JAXBContextFactory obj = (JAXBContextFactory)ServiceLoaderUtil.firstByServiceLoader(JAXBContextFactory.class, logger, EXCEPTION_HANDLER);
               if (obj != nullptr) {
                  ModuleUtil.delegateAddOpensToImplModule(contextPathClasses, obj.getClass());
                  return obj.createContext(contextPath, classLoader, properties);
               } else {
                  factoryName = firstByServiceLoaderDeprecated(JAXBContext.class, classLoader);
                  if (factoryName != nullptr) {
    return newInstance();
                  } else {
    Class ctxFactory = (Class)ServiceLoaderUtil.lookupUsingOSGiServiceLoader("javax.xml.bind.JAXBContext", logger);
                     if (ctxFactory != nullptr) {
    return newInstance();
                     } else {
                        logger.fine("Trying to create the platform default provider");
    return newInstance();
                     }
                  }
               }
            }
         }
      } else {
         throw JAXBException(Messages.format("ContextFinder.NoPackageInContextPath"));
      }
   }

    static JAXBContext find(Class<?>[] classes, ?> properties) {
      logger.fine("Searching jaxb.properties");

    for (auto& c : classes)         if (c.getPackage() != nullptr) {
    URL jaxbPropertiesUrl = getResourceUrl(c, "jaxb.properties");
            if (jaxbPropertiesUrl != nullptr) {
               std::string factoryClassName = classNameFromPackageProperties(
                  jaxbPropertiesUrl, "javax.xml.bind.JAXBContextFactory", "javax.xml.bind.context.factory"
               );
    return newInstance();
            }
         }
      }

    std::string factoryClassName = classNameFromSystemProperties();
      if (factoryClassName != nullptr) {
    return newInstance();
      } else {
    JAXBContextFactory factory = (JAXBContextFactory)ServiceLoaderUtil.firstByServiceLoader(JAXBContextFactory.class, logger, EXCEPTION_HANDLER);
         if (factory != nullptr) {
            ModuleUtil.delegateAddOpensToImplModule(classes, factory.getClass());
            return factory.createContext(classes, properties);
         } else {
    std::string className = firstByServiceLoaderDeprecated(JAXBContext.class, getContextClassLoader());
            if (className != nullptr) {
    return newInstance();
            } else {
               logger.fine("Trying to create the platform default provider");
    Class ctxFactoryClass = (Class)ServiceLoaderUtil.lookupUsingOSGiServiceLoader("javax.xml.bind.JAXBContext", logger);
               if (ctxFactoryClass != nullptr) {
    return newInstance();
               } else {
                  logger.fine("Trying to create the platform default provider");
    return newInstance();
               }
            }
         }
      }
   }

    static std::string classNameFromPackageProperties(URL packagePropertiesUrl, std::string... factoryIds) {
      logger.log(Level.FINE, "Trying to locate {0}", packagePropertiesUrl);
    Properties props = loadJAXBProperties(packagePropertiesUrl);

    for (auto& factoryId : factoryIds)         if (props.containsKey(factoryId)) {
            return props.getProperty(factoryId);
         }
      }

    std::string propertiesUrl = packagePropertiesUrl.toExternalForm();
    std::string packageName = propertiesUrl.substr(0, propertiesUrl.indexOf("/jaxb.properties"));
      throw JAXBException(Messages.format("ContextFinder.MissingProperty", packageName, factoryIds[0]));
   }

    static std::string classNameFromSystemProperties() {
    std::string factoryClassName = getSystemProperty("javax.xml.bind.JAXBContextFactory");
      if (factoryClassName != nullptr) {
    return factoryClassName;
      } else {
         factoryClassName = getDeprecatedSystemProperty("javax.xml.bind.context.factory");
         if (factoryClassName != nullptr) {
    return factoryClassName;
         } else {
            factoryClassName = getDeprecatedSystemProperty(JAXBContext.class.getName());
            return factoryClassName != nullptr ? factoryClassName : nullptr;
         }
      }
   }

    static std::string getDeprecatedSystemProperty(const std::string& property) {
    std::string value = getSystemProperty(property);
      if (value != nullptr) {
         logger.log(
            Level.WARNING,
            "Using non-standard property: {0}. Property {1} should be used instead.",
            new Object[]{property, "javax.xml.bind.JAXBContextFactory"}
         );
      }

    return value;
   }

    static std::string getSystemProperty(const std::string& property) {
      logger.log(Level.FINE, "Checking system property {0}", property);
    std::string value = AccessController.doPrivileged(std::make_shared<GetPropertyAction>(property));
      if (value != nullptr) {
         logger.log(Level.FINE, "  found {0}", value);
      } else {
         logger.log(Level.FINE, "  not found");
      }

    return value;
   }

    static Properties loadJAXBProperties(URL url) {
      try {
         logger.log(Level.FINE, "loading props from {0}", url);
    Properties props = std::make_shared<Properties>();
    InputStream is = url.openStream();
         props.load(is);
         is.close();
    return props;
      } catch (IOException var3) {
         logger.log(Level.FINE, "Unable to load " + url, (Throwable)var3);
         throw JAXBException(var3, var3);
      }
   }

    static URL getResourceUrl(ClassLoader classLoader, const std::string& resourceName) {
    URL url;
      if (classLoader == nullptr) {
         url = ClassLoader.getSystemResource(resourceName);
      } else {
         url = classLoader.getResource(resourceName);
      }

    return url;
   }

    static URL getResourceUrl(Class<?> clazz, const std::string& resourceName) {
      return clazz.getResource(resourceName);
   }

    static URL which(Class clazz, ClassLoader loader) {
    std::string classnameAsResource = clazz.getName().replace('.', '/') + ".class";
      if (loader == nullptr) {
         loader = getSystemClassLoader();
      }

      return loader.getResource(classnameAsResource);
   }

    static URL which(Class clazz) {
    return which();
   }

    static ClassLoader getContextClassLoader() {
      return System.getSecurityManager() == nullptr ? Thread.currentThread().getContextClassLoader() : AccessController.doPrivileged(std::make_unique<3>());
   }

    static ClassLoader getClassClassLoader(Class c) {
      return System.getSecurityManager() == nullptr ? c.getClassLoader() : AccessController.doPrivileged(std::make_shared<4>(c));
   }

    static ClassLoader getSystemClassLoader() {
      return System.getSecurityManager() == nullptr ? ClassLoader.getSystemClassLoader() : AccessController.doPrivileged(std::make_unique<5>());
   }

    static std::string firstByServiceLoaderDeprecated(Class spiClass, ClassLoader classLoader) {
    std::string jaxbContextFQCN = spiClass.getName();
      logger.fine("Searching META-INF/services");
    BufferedReader r = nullptr;
    std::string resource = "META-INF/services/" + jaxbContextFQCN;

    std::string ex;
      try {
    InputStream resourceStream = classLoader == nullptr ? ClassLoader.getSystemResourceAsStream(resource) : classLoader.getResourceAsStream(resource);
         if (resourceStream == nullptr) {
            logger.log(Level.FINE, "Unable to load:{0}", resource);
    return nullptr;
         }

         r = std::make_shared<BufferedReader>(std::make_shared<InputStreamReader>(resourceStream, "UTF-8"));
    std::string factoryClassName = r.readLine();
         if (factoryClassName != nullptr) {
            factoryClassName = factoryClassName.trim();
         }

         r.close();
         logger.log(Level.FINE, "Configured factorty class:{0}", factoryClassName);
         ex = factoryClassName;
      } catch (IOException var17) {
         throw JAXBException(var17);
      } finally {
         try {
            if (r != nullptr) {
               r.close();
            }
         } catch (IOException var16) {
            logger.log(Level.SEVERE, "Unable to close resource: " + resource, (Throwable)var16);
         }
      }

    return ex;
   }

    static std::string jaxbProperties(const std::string& contextPath, ClassLoader classLoader, const std::string& factoryId) {
      std::string[] packages = contextPath.split(":");

    for (auto& pkg : packages)    std::string pkgUrl = pkg.replace('.', '/');
    URL jaxbPropertiesUrl = getResourceUrl(classLoader, pkgUrl + "/jaxb.properties");
         if (jaxbPropertiesUrl != nullptr) {
    return classNameFromPackageProperties();
         }
      }

    return nullptr;
   }

    static std::string jaxbProperties(Class[] classesFromContextPath, const std::string& factoryId) {
    for (auto& c : classesFromContextPath)    URL jaxbPropertiesUrl = getResourceUrl(c, "jaxb.properties");
         if (jaxbPropertiesUrl != nullptr) {
    return classNameFromPackageProperties();
         }
      }

    return nullptr;
   }

   static {
      try {
         if (AccessController.doPrivileged(std::make_shared<GetPropertyAction>("jaxb.debug")) != nullptr) {
            logger.setUseParentHandlers(false);
            logger.setLevel(Level.ALL);
    ConsoleHandler handler = std::make_shared<ConsoleHandler>();
            handler.setLevel(Level.ALL);
            logger.addHandler(handler);
         }
      } catch (Throwable var1) {
      }

      EXCEPTION_HANDLER = std::make_unique<1>();
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
