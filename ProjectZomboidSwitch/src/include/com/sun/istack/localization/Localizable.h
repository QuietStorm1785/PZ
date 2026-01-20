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


class Localizable {
public:
    virtual ~Localizable() = default;
    std::string NOT_LOCALIZABLE = "\u0000";

    std::string getKey();

   Object[] getArguments();

    std::string getResourceBundleName();

    ResourceBundle getResourceBundle(Locale var1);
}
} // namespace localization
} // namespace istack
} // namespace sun
} // namespace com
