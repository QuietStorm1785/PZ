#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace core {


class ElementPropertyInfo {
public:
    virtual ~ElementPropertyInfo() = default;
   List<? : public TypeRef<T, C>> getTypes();

    QName getXmlName();

    bool isCollectionRequired();

    bool isCollectionNillable();

    bool isValueList();

    bool isRequired();

   Adapter<T, C> getAdapter();
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
