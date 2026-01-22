#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/BasicPermission.h"

namespace javax {
namespace xml {
namespace bind {


class JAXBPermission : public BasicPermission {
public:
    static const long serialVersionUID = 1L;

    public JAXBPermission(const std::string& name) {
      super(name);
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
