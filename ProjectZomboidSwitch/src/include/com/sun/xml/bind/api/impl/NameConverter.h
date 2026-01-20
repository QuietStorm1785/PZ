#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/impl/NameConverter/1.h"
#include "com/sun/xml/bind/api/impl/NameConverter/2.h"
#include "com/sun/xml/bind/api/impl/NameConverter/Standard.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace api {
namespace impl {


class NameConverter {
public:
    virtual ~NameConverter() = default;
    NameConverter standard = std::make_shared<Standard>();
    NameConverter jaxrpcCompatible = std::make_shared<1>();
    NameConverter smart = std::make_shared<2>();

    std::string toClassName(const std::string& var1);

    std::string toInterfaceName(const std::string& var1);

    std::string toPropertyName(const std::string& var1);

    std::string toConstantName(const std::string& var1);

    std::string toVariableName(const std::string& var1);

    std::string toPackageName(const std::string& var1);
}
} // namespace impl
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
