#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace istack {
namespace localization {


class LocalizableMessageFactory {
public:
    virtual ~LocalizableMessageFactory() = default;
    ResourceBundle getResourceBundle(Locale var1);
}
} // namespace localization
} // namespace istack
} // namespace sun
} // namespace com
