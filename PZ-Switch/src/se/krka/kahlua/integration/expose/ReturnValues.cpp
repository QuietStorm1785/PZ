#include "se/krka/kahlua/integration/expose/ReturnValues.h"

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace expose {

ReturnValues ReturnValues::get(KahluaConverterManager kahluaConverterManager,
 LuaCallFrame luaCallFrame) {
 // TODO: Implement get
 return nullptr;
}

void ReturnValues::put(ReturnValues returnValues) {
 // TODO: Implement put
}

ReturnValues ReturnValues::push(void *object) {
 // TODO: Implement push
 return nullptr;
}

ReturnValues ReturnValues::push(Object... objects) {
 // TODO: Implement push
 return nullptr;
}

int ReturnValues::getNArguments() {
 // TODO: Implement getNArguments
 return 0;
}

} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
