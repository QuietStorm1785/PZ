#include "se/krka/kahlua/integration/LuaSuccess.h"

namespace se {
namespace krka {
namespace kahlua {
namespace integration {

bool LuaSuccess::isSuccess() {
 // TODO: Implement isSuccess
 return false;
}

void *LuaSuccess::getErrorObject() {
 // TODO: Implement getErrorObject
 return nullptr;
}

std::string LuaSuccess::getErrorString() {
 // TODO: Implement getErrorString
 return "";
}

std::string LuaSuccess::getLuaStackTrace() {
 // TODO: Implement getLuaStackTrace
 return "";
}

std::runtime_error LuaSuccess::getJavaException() {
 // TODO: Implement getJavaException
 return nullptr;
}

} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
