#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/AnnotationSource.h"
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class PropertySeed {
public:
    virtual ~PropertySeed() = default;
    std::string getName();

    T getRawType();
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
