#include <string>
#include "zombie\text\templating/ReplaceProvider.h"

namespace zombie {
namespace text {
namespace templating {

void ReplaceProvider::addKey(const std::string& var1, const std::string& var2) {
    // TODO: Implement addKey
}

void ReplaceProvider::addKey(const std::string& var1, KahluaTableImpl var2) {
    // TODO: Implement addKey
}

void ReplaceProvider::addReplacer(const std::string& var1, IReplace var2) {
    // TODO: Implement addReplacer
}

bool ReplaceProvider::hasReplacer(const std::string& var1) {
    // TODO: Implement hasReplacer
    return false;
}

IReplace ReplaceProvider::getReplacer(const std::string& var1) {
    // TODO: Implement getReplacer
    return nullptr;
}

} // namespace templating
} // namespace text
} // namespace zombie
