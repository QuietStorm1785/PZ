#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace reflect {


class Types {
public:
   static const boolean NATIVE_TYPE_VARIABLE_ONLY = !Types$NativeTypeVariableEquals.class.getTypeParameters()[0]
       == Types.newArtificialTypeVariable(Types$NativeTypeVariableEquals.class, "X", new Type[0]));
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
