#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/PrivilegedAction.h"

namespace javax {
namespace xml {
namespace bind {


class GetPropertyAction {
public:
    const std::string propertyName;

    public GetPropertyAction(const std::string& propertyName) {
      this.propertyName = propertyName;
   }

    std::string run() {
      return System.getProperty(this.propertyName);
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
