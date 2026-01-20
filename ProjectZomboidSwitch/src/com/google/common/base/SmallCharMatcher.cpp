#include <string>
#include "com\google\common\base/SmallCharMatcher.h"

namespace com {
namespace google {
namespace common {
namespace base {

private SmallCharMatcher::SmallCharMatcher(char[] table, long filter, bool containsZero, const std::string& description) {
    // TODO: Implement SmallCharMatcher
    return nullptr;
}

int SmallCharMatcher::smear(int hashCode) {
    // TODO: Implement smear
    return 0;
}

bool SmallCharMatcher::checkFilter(int c) {
    // TODO: Implement checkFilter
    return false;
}

int SmallCharMatcher::chooseTableSize(int setSize) {
    // TODO: Implement chooseTableSize
    return 0;
}

CharMatcher SmallCharMatcher::from(BitSet chars, const std::string& description) {
    // TODO: Implement from
    return nullptr;
}

bool SmallCharMatcher::matches(char c) {
    // TODO: Implement matches
    return false;
}

void SmallCharMatcher::setBits(BitSet table) {
    // TODO: Implement setBits
}

} // namespace base
} // namespace common
} // namespace google
} // namespace com
