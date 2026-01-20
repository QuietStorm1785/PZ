#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "javax/xml/namespace/NamespaceContext.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class NamespaceContext2 {
public:
    virtual ~NamespaceContext2() = default;
    std::string declareNamespace(const std::string& var1, const std::string& var2, bool var3);

    int force(@NotNull std::string, @NotNull std::string);
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
