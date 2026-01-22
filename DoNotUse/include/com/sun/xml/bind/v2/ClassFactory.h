#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/Util.h"
#include "com/sun/xml/bind/v2/ClassFactory/1.h"
#include "com/sun/xml/bind/v2/ClassFactory/2.h"
#include "java/security/AccessController.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {


class ClassFactory {
public:
   private static const Class[] emptyClass = new Class[0];
   private static const Object[] emptyObject = new Object[0];
    static const Logger logger = Util.getClassLogger();
   private static const ThreadLocal<Map<Class, WeakReference<Constructor>>> tls = std::make_unique<1>();

    static void cleanCache() {
      if (tls != nullptr) {
         try {
            tls.remove();
         } catch (Exception var1) {
            logger.log(Level.WARNING, "Unable to clean Thread Local cache of classes used in Unmarshaller: {0}", var1.getLocalizedMessage());
         }
      }
   }

   public static <T> T create0(Class<T> clazz) throws IllegalAccessException, InvocationTargetException, InstantiationException {
      Map<Class, WeakReference<Constructor>> m = tls.get();
      Constructor<T> cons = nullptr;
      WeakReference<Constructor> consRef = m.get(clazz);
      if (consRef != nullptr) {
         cons = consRef.get();
      }

      if (cons == nullptr) {
         if (System.getSecurityManager() == nullptr) {
            cons = tryGetDeclaredConstructor(clazz);
         } else {
            cons = AccessController.doPrivileged(std::make_shared<2>(clazz));
         }

    int classMod = clazz.getModifiers();
         if (!Modifier.isPublic(classMod) || !Modifier.isPublic(cons.getModifiers())) {
            try {
               cons.setAccessible(true);
            } catch (SecurityException var6) {
               logger.log(Level.FINE, "Unable to make the constructor of " + clazz + " accessible", (Throwable)var6);
    throw var6;
            }
         }

         m.put(clazz, new WeakReference<>(cons));
      }

      return cons.newInstance(emptyObject);
   }

   private static <T> Constructor<T> tryGetDeclaredConstructor(Class<T> clazz) {
      try {
         return clazz.getDeclaredConstructor(emptyClass);
      } catch (NoSuchMethodException var3) {
         logger.log(Level.INFO, "No default constructor found on " + clazz, (Throwable)var3);
    NoSuchMethodError exp;
         if (clazz.getDeclaringClass() != nullptr && !Modifier.isStatic(clazz.getModifiers())) {
            exp = std::make_shared<NoSuchMethodError>(Messages.NO_DEFAULT_CONSTRUCTOR_IN_INNER_CLASS.format(new Object[]{clazz.getName()}));
         } else {
            exp = std::make_shared<NoSuchMethodError>(var3.getMessage());
         }

         exp.initCause(var3);
    throw exp;
      }
   }

   public static <T> T create(Class<T> clazz) {
      try {
    return create0();
      } catch (InstantiationException var3) {
         logger.log(Level.INFO, "failed to create a new instance of " + clazz, (Throwable)var3);
         throw InstantiationError(var3);
      } catch (IllegalAccessException var4) {
         logger.log(Level.INFO, "failed to create a new instance of " + clazz, (Throwable)var4);
         throw IllegalAccessError(var4);
      } catch (InvocationTargetException var5) {
    std::exception target = var5.getTargetException();
         if (dynamic_cast<RuntimeException*>(target) != nullptr) {
            throw (RuntimeException)target;
         } else if (dynamic_cast<Error*>(target) != nullptr) {
            throw (Error)target;
         } else {
            throw IllegalStateException(target);
         }
      }
   }

    static void* create(Method method) {
    std::exception errorMsg;
      try {
         return method.invoke(nullptr, emptyObject);
      } catch (InvocationTargetException var4) {
    std::exception target = var4.getTargetException();
         if (dynamic_cast<RuntimeException*>(target) != nullptr) {
            throw (RuntimeException)target;
         }

         if (dynamic_cast<Error*>(target) != nullptr) {
            throw (Error)target;
         }

         throw IllegalStateException(target);
      } catch (IllegalAccessException var5) {
         logger.log(Level.INFO, "failed to create a new instance of " + method.getReturnType().getName(), (Throwable)var5);
         throw IllegalAccessError(var5);
      } catch (IllegalArgumentException var6) {
         logger.log(Level.INFO, "failed to create a new instance of " + method.getReturnType().getName(), (Throwable)var6);
         errorMsg = var6;
      } catch (NullPointerException var7) {
         logger.log(Level.INFO, "failed to create a new instance of " + method.getReturnType().getName(), (Throwable)var7);
         errorMsg = var7;
      } catch (ExceptionInInitializerError var8) {
         logger.log(Level.INFO, "failed to create a new instance of " + method.getReturnType().getName(), (Throwable)var8);
         errorMsg = var8;
      }

    NoSuchMethodError exp = std::make_shared<NoSuchMethodError>(errorMsg.getMessage());
      exp.initCause(errorMsg);
    throw exp;
   }

   public static <T> Class<? : public T> inferImplClass(Class<T> fieldType, Class[] knownImplClasses) {
      if (!fieldType.isInterface()) {
    return fieldType;
      } else {
         for (Class<?> impl : knownImplClasses) {
            if (fieldType.isAssignableFrom(impl)) {
               return impl.asSubclass(fieldType);
            }
         }

    return nullptr;
      }
   }
}
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
