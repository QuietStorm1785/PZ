#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "javax/xml/bind/JAXBException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {


class InternalAccessorFactory {
public:
    virtual ~InternalAccessorFactory() = default;
    Accessor createFieldAccessor(Class var1, Field var2, bool var3, bool var4);
}
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
