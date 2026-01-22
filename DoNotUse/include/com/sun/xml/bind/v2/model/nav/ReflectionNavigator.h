#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/nav/ReflectionNavigator/1.h"
#include "com/sun/xml/bind/v2/model/nav/ReflectionNavigator/10.h"
#include "com/sun/xml/bind/v2/model/nav/ReflectionNavigator/2.h"
#include "com/sun/xml/bind/v2/model/nav/ReflectionNavigator/3.h"
#include "com/sun/xml/bind/v2/model/nav/ReflectionNavigator/4.h"
#include "com/sun/xml/bind/v2/model/nav/ReflectionNavigator/5.h"
#include "com/sun/xml/bind/v2/model/nav/ReflectionNavigator/6.h"
#include "com/sun/xml/bind/v2/model/nav/ReflectionNavigator/7.h"
#include "com/sun/xml/bind/v2/model/nav/ReflectionNavigator/8.h"
#include "com/sun/xml/bind/v2/model/nav/ReflectionNavigator/9.h"
#include "com/sun/xml/bind/v2/model/nav/ReflectionNavigator/BinderArg.h"
#include "com/sun/xml/bind/v2/runtime/Location.h"
#include "java/security/AccessController.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace nav {


class ReflectionNavigator {
public:
    static const ReflectionNavigator INSTANCE = std::make_shared<ReflectionNavigator>();
   private static const TypeVisitor<Type, Class> baseClassFinder = std::make_unique<1>();
   private static const TypeVisitor<Type, BinderArg> binder = std::make_unique<2>();
   private static const TypeVisitor<Class, Void> eraser = std::make_unique<6>();

    static ReflectionNavigator getInstance() {
    return INSTANCE;
   }

    private ReflectionNavigator() {
   }

    Class getSuperClass(Class clazz) {
      if (clazz == Object.class) {
    return nullptr;
      } else {
    Class sc = clazz.getSuperclass();
         if (sc == nullptr) {
            sc = Object.class;
         }

    return sc;
      }
   }

    Type getBaseClass(Type t, Class sup) {
      return (Type)baseClassFinder.visit(t, sup);
   }

    std::string getClassName(Class clazz) {
      return clazz.getName();
   }

    std::string getTypeName(Type type) {
      if (dynamic_cast<Class*>(type) != nullptr) {
    Class c = (Class)type;
         return c.isArray() ? this.getTypeName((Type)c.getComponentType()) + "[]" : c.getName();
      } else {
         return type;
      }
   }

    std::string getClassShortName(Class clazz) {
      return clazz.getSimpleName();
   }

   public Collection<? : public Field> getDeclaredFields(Class clazz) {
      Field[] fields = AccessController.doPrivileged(std::make_shared<3>(this, clazz));
      return Arrays.asList(fields);
   }

    Field getDeclaredField(Class clazz, const std::string& fieldName) {
      return AccessController.doPrivileged(std::make_shared<4>(this, clazz, fieldName));
   }

   public Collection<? : public Method> getDeclaredMethods(Class clazz) {
      Method[] methods = AccessController.doPrivileged(std::make_shared<5>(this, clazz));
      return Arrays.asList(methods);
   }

    Class getDeclaringClassForField(Field field) {
      return field.getDeclaringClass();
   }

    Class getDeclaringClassForMethod(Method method) {
      return method.getDeclaringClass();
   }

    Type getFieldType(Field field) {
      if (field.getType().isArray()) {
    Class c = field.getType().getComponentType();
         if (c.isPrimitive()) {
            return Array.newInstance(c, 0).getClass();
         }
      }

      return this.fix(field.getGenericType());
   }

    std::string getFieldName(Field field) {
      return field.getName();
   }

    std::string getMethodName(Method method) {
      return method.getName();
   }

    Type getReturnType(Method method) {
      return this.fix(method.getGenericReturnType());
   }

   public Type[] getMethodParameters(Method method) {
      return method.getGenericParameterTypes();
   }

    bool isStaticMethod(Method method) {
      return Modifier.isStatic(method.getModifiers());
   }

    bool isFinalMethod(Method method) {
      return Modifier.isFinal(method.getModifiers());
   }

    bool isSubClassOf(Type sub, Type sup) {
      return this.erasure(sup).isAssignableFrom(this.erasure(sub));
   }

    Class ref(Class c) {
    return c;
   }

    Class use(Class c) {
    return c;
   }

    Class asDecl(Type t) {
      return this.erasure(t);
   }

    Class asDecl(Class c) {
    return c;
   }

   public <T> Class<T> erasure(Type t) {
      return (Class<T>)eraser.visit(t, nullptr);
   }

    bool isAbstract(Class clazz) {
      return Modifier.isAbstract(clazz.getModifiers());
   }

    bool isFinal(Class clazz) {
      return Modifier.isFinal(clazz.getModifiers());
   }

    Type createParameterizedType(Class rawType, Type... arguments) {
      return std::make_shared<ParameterizedTypeImpl>(rawType, arguments, nullptr);
   }

    bool isArray(Type t) {
      if (dynamic_cast<Class*>(t) != nullptr) {
    Class c = (Class)t;
         return c.isArray();
      } else {
         return dynamic_cast<GenericArrayType*>(t) != nullptr;
      }
   }

    bool isArrayButNotByteArray(Type t) {
      if (!(dynamic_cast<Class*>(t) != nullptr)) {
         if (dynamic_cast<GenericArrayType*>(t) != nullptr) {
            t = ((GenericArrayType)t).getGenericComponentType();
            return t != byte.class;
         } else {
    return false;
         }
      } else {
    Class c = (Class)t;
         return c.isArray() && c != byte[].class;
      }
   }

    Type getComponentType(Type t) {
      if (dynamic_cast<Class*>(t) != nullptr) {
    Class c = (Class)t;
         return c.getComponentType();
      } else if (dynamic_cast<GenericArrayType*>(t) != nullptr) {
         return ((GenericArrayType)t).getGenericComponentType();
      } else {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    Type getTypeArgument(Type type, int i) {
      if (dynamic_cast<ParameterizedType*>(type) != nullptr) {
    ParameterizedType p = (ParameterizedType)type;
         return this.fix(p.getActualTypeArguments()[i]);
      } else {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    bool isParameterizedType(Type type) {
      return dynamic_cast<ParameterizedType*>(type) != nullptr;
   }

    bool isPrimitive(Type type) {
      if (dynamic_cast<Class*>(type) != nullptr) {
    Class c = (Class)type;
         return c.isPrimitive();
      } else {
    return false;
      }
   }

    Type getPrimitive(Class primitiveType) {
      assert primitiveType.isPrimitive();

    return primitiveType;
   }

    Location getClassLocation(Class clazz) {
      return std::make_shared<7>(this, clazz);
   }

    Location getFieldLocation(Field field) {
      return std::make_shared<8>(this, field);
   }

    Location getMethodLocation(Method method) {
      return std::make_shared<9>(this, method);
   }

    bool hasDefaultConstructor(Class c) {
      try {
         c.getDeclaredConstructor();
    return true;
      } catch (NoSuchMethodException var3) {
    return false;
      }
   }

    bool isStaticField(Field field) {
      return Modifier.isStatic(field.getModifiers());
   }

    bool isPublicMethod(Method method) {
      return Modifier.isPublic(method.getModifiers());
   }

    bool isPublicField(Field field) {
      return Modifier.isPublic(field.getModifiers());
   }

    bool isEnum(Class c) {
      return Enum.class.isAssignableFrom(c);
   }

   public Field[] getEnumConstants(Class clazz) {
      try {
         Object[] values = clazz.getEnumConstants();
         Field[] fields = new Field[values.length];

         for (int i = 0; i < values.length; i++) {
            fields[i] = clazz.getField(((Enum)values[i]).name());
         }

    return fields;
      } catch (NoSuchFieldException var5) {
         throw NoSuchFieldError(var5.getMessage());
      }
   }

    Type getVoidType() {
      return Void.class;
   }

    std::string getPackageName(Class clazz) {
    std::string name = clazz.getName();
    int idx = name.lastIndexOf(46);
      return idx < 0 ? "" : name.substr(0, idx);
   }

    Class loadObjectFactory(Class referencePoint, const std::string& pkg) {
    ClassLoader cl = SecureLoader.getClassClassLoader(referencePoint);
      if (cl == nullptr) {
         cl = SecureLoader.getSystemClassLoader();
      }

      try {
         return cl.loadClass(pkg + ".ObjectFactory");
      } catch (ClassNotFoundException var5) {
    return nullptr;
      }
   }

    bool isBridgeMethod(Method method) {
      return method.isBridge();
   }

    bool isOverriding(Method method, Class base) {
    std::string name = method.getName();
      Class[] params = method.getParameterTypes();
      return AccessController.<bool>doPrivileged(std::make_shared<10>(this, base, name, params));
   }

    bool isInterface(Class clazz) {
      return clazz.isInterface();
   }

    bool isTransient(Field f) {
      return Modifier.isTransient(f.getModifiers());
   }

    bool isInnerClass(Class clazz) {
      return clazz.getEnclosingClass() != nullptr && !Modifier.isStatic(clazz.getModifiers());
   }

    bool isSameType(Type t1, Type t2) {
      return t1 == t2);
   }

    Type fix(Type t) {
      if (!(dynamic_cast<GenericArrayType*>(t) != nullptr)) {
    return t;
      } else {
    GenericArrayType gat = (GenericArrayType)t;
         if (gat.getGenericComponentType() instanceof Class) {
    Class c = (Class)gat.getGenericComponentType();
            return Array.newInstance(c, 0).getClass();
         } else {
    return t;
         }
      }
   }
}
} // namespace nav
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
