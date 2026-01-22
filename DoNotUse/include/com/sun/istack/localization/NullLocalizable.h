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


class NullLocalizable {
public:
    const std::string msg;

    public NullLocalizable(const std::string& msg) {
      if (msg == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         this.msg = msg;
      }
   }

    std::string getKey() {
      return "\u0000";
   }

   public Object[] getArguments() {
      return new Object[]{this.msg};
   }

    std::string getResourceBundleName() {
      return "";
   }

    ResourceBundle getResourceBundle(Locale locale) {
    return nullptr;
   }
}
} // namespace localization
} // namespace istack
} // namespace sun
} // namespace com
