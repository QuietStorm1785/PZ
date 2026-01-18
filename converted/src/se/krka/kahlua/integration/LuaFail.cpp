#include "se/krka/kahlua/integration/LuaFail.h"

namespace se {
namespace krka {
namespace kahlua {
namespace integration {

bool LuaFail::isSuccess() {
  // TODO: Implement isSuccess
  return false;
}

void *LuaFail::getErrorObject() {
  // TODO: Implement getErrorObject
  return nullptr;
}

std::string LuaFail::getErrorString() {
  // TODO: Implement getErrorString
  return "";
}

std::string LuaFail::getLuaStackTrace() {
  // TODO: Implement getLuaStackTrace
  return "";
}

std::runtime_error LuaFail::getJavaException() {
  // TODO: Implement getJavaException
  return nullptr;
}

int LuaFail::size() {
  // TODO: Implement size
  return 0;
}

std::string LuaFail::toString() {
  // TODO: Implement toString
  return "";
}

} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
