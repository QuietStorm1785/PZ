#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/Nullable.h"
#include "com/sun/xml/bind/v2/model/annotation/AnnotationSource.h"
#include "javax/activation/MimeType.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace core {


class PropertyInfo {
public:
    virtual ~PropertyInfo() = default;
   TypeInfo<T, C> parent();

    std::string getName();

    std::string displayName();

    bool isCollection();

   Collection<? : public TypeInfo<T, C>> ref();

    PropertyKind kind();

   Adapter<T, C> getAdapter();

    ID id();

    MimeType getExpectedMimeType();

    bool inlineBinaryData();

    QName getSchemaType();
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
