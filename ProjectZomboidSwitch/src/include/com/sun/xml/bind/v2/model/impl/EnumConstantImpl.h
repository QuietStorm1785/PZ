#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/EnumConstant.h"
#include "com/sun/xml/bind/v2/model/core/EnumLeafInfo.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class EnumConstantImpl {
public:
    const std::string lexical;
   protected const EnumLeafInfoImpl<T, C, F, M> owner;
    const std::string name;
   protected const EnumConstantImpl<T, C, F, M> next;

    public EnumConstantImpl(M> owner, const std::string& name, const std::string& lexical, M> next) {
      this.lexical = lexical;
      this.owner = owner;
      this.name = name;
      this.next = next;
   }

   public EnumLeafInfo<T, C> getEnclosingClass() {
      return this.owner;
   }

    std::string getLexicalValue() {
      return this.lexical;
   }

    std::string getName() {
      return this.name;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
