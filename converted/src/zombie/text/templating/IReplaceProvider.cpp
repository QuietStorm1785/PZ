#include "zombie/text/templating/IReplaceProvider.h"

namespace zombie {
namespace text {
namespace templating {

bool IReplaceProvider::hasReplacer(const std::string &key) {
  // TODO: Implement hasReplacer
  return false;
}

IReplace IReplaceProvider::getReplacer(const std::string &key) {
  // TODO: Implement getReplacer
  return nullptr;
}

} // namespace templating
} // namespace text
} // namespace zombie
