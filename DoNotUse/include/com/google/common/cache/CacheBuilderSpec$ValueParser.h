#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheBuilderSpec {
public:
    virtual ~CacheBuilderSpec() = default;
    void parse(CacheBuilderSpec var1, const std::string& var2, @Nullable std::string);
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
