#include <string>
#include "zombie/text/templating/IReplaceProvider.h"

namespace zombie {
namespace text {
namespace templating {

bool IReplaceProvider::hasReplacer(const std::string& var1) {
    // TODO: Implement hasReplacer
    return false;
}

IReplace IReplaceProvider::getReplacer(const std::string& var1) {
    // TODO: Implement getReplacer
    return nullptr;
}

} // namespace templating
} // namespace text
} // namespace zombie
