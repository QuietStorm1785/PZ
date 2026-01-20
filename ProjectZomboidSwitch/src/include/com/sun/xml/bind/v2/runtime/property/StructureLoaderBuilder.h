#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {


class StructureLoaderBuilder {
public:
    virtual ~StructureLoaderBuilder() = default;
    QName TEXT_HANDLER = std::make_shared<QName>("\u0000", "text");
    QName CATCH_ALL = std::make_shared<QName>("\u0000", "catchAll");

    void buildChildElementUnmarshallers(UnmarshallerChain var1, QNameMap<ChildLoader> var2);
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
