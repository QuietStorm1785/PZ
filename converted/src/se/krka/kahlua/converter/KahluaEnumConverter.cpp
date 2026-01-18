#include "se/krka/kahlua/converter/KahluaEnumConverter.h"

namespace se {
namespace krka {
namespace kahlua {
namespace converter {

private
KahluaEnumConverter::KahluaEnumConverter() {
  // TODO: Implement KahluaEnumConverter
  return nullptr;
}

void KahluaEnumConverter::install(
    KahluaConverterManager kahluaConverterManager) {
  // TODO: Implement install
}

void *KahluaEnumConverter::fromJavaToLua(Enum _enum) {
  // TODO: Implement fromJavaToLua
  return nullptr;
}

Enum KahluaEnumConverter::fromLuaToJava(const std::string &string,
                                        Class<Enum> clazz) {
  // TODO: Implement fromLuaToJava
  return nullptr;
}

} // namespace converter
} // namespace kahlua
} // namespace krka
} // namespace se
