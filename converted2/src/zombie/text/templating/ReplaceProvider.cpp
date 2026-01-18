#include "zombie/text/templating/ReplaceProvider.h"

namespace zombie {
namespace text {
namespace templating {

void ReplaceProvider::addKey(const std::string &key, final String) {
  // TODO: Implement addKey
}

std::string ReplaceProvider::getString() {
  // TODO: Implement getString
  return "";
}

void ReplaceProvider::addKey(const std::string &key, KahluaTableImpl table) {
  // TODO: Implement addKey
}

void ReplaceProvider::addReplacer(const std::string &key, IReplace replace) {
  // TODO: Implement addReplacer
}

bool ReplaceProvider::hasReplacer(const std::string &key) {
  // TODO: Implement hasReplacer
  return false;
}

IReplace ReplaceProvider::getReplacer(const std::string &key) {
  // TODO: Implement getReplacer
  return nullptr;
}

} // namespace templating
} // namespace text
} // namespace zombie
