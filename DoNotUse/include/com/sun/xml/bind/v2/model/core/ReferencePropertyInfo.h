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


class ReferencePropertyInfo {
public:
    virtual ~ReferencePropertyInfo() = default;
   Set<? : public Element<T, C>> getElements();

   Collection<? : public TypeInfo<T, C>> ref();

    QName getXmlName();

    bool isCollectionNillable();

    bool isCollectionRequired();

    bool isMixed();

    WildcardMode getWildcard();

    C getDOMHandler();

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
