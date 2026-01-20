#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/Location.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace nav {


class Navigator {
public:
    virtual ~Navigator() = default;
    C getSuperClass(C var1);

    T getBaseClass(T var1, C var2);

    std::string getClassName(C var1);

    std::string getTypeName(T var1);

    std::string getClassShortName(C var1);

   Collection<? : public F> getDeclaredFields(C var1);

    F getDeclaredField(C var1, const std::string& var2);

   Collection<? : public M> getDeclaredMethods(C var1);

    C getDeclaringClassForField(F var1);

    C getDeclaringClassForMethod(M var1);

    T getFieldType(F var1);

    std::string getFieldName(F var1);

    std::string getMethodName(M var1);

    T getReturnType(M var1);

   T[] getMethodParameters(M var1);

    bool isStaticMethod(M var1);

    bool isSubClassOf(T var1, T var2);

    T ref(Class var1);

    T use(C var1);

    C asDecl(T var1);

    C asDecl(Class var1);

    bool isArray(T var1);

    bool isArrayButNotByteArray(T var1);

    T getComponentType(T var1);

    T getTypeArgument(T var1, int var2);

    bool isParameterizedType(T var1);

    bool isPrimitive(T var1);

    T getPrimitive(Class var1);

    Location getClassLocation(C var1);

    Location getFieldLocation(F var1);

    Location getMethodLocation(M var1);

    bool hasDefaultConstructor(C var1);

    bool isStaticField(F var1);

    bool isPublicMethod(M var1);

    bool isFinalMethod(M var1);

    bool isPublicField(F var1);

    bool isEnum(C var1);

   <P> T erasure(T var1);

    bool isAbstract(C var1);

    bool isFinal(C var1);

   F[] getEnumConstants(C var1);

    T getVoidType();

    std::string getPackageName(C var1);

    C loadObjectFactory(C var1, const std::string& var2);

    bool isBridgeMethod(M var1);

    bool isOverriding(M var1, C var2);

    bool isInterface(C var1);

    bool isTransient(F var1);

    bool isInnerClass(C var1);

    bool isSameType(T var1, T var2);
}
} // namespace nav
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
