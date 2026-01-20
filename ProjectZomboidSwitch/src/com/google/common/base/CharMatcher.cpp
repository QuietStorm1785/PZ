#include <sstream>
#include <string>
#include "com\google\common\base/CharMatcher.h"

namespace com {
namespace google {
namespace common {
namespace base {

CharMatcher CharMatcher::any() {
    // TODO: Implement any
    return nullptr;
}

CharMatcher CharMatcher::none() {
    // TODO: Implement none
    return nullptr;
}

CharMatcher CharMatcher::whitespace() {
    // TODO: Implement whitespace
    return nullptr;
}

CharMatcher CharMatcher::breakingWhitespace() {
    // TODO: Implement breakingWhitespace
    return nullptr;
}

CharMatcher CharMatcher::ascii() {
    // TODO: Implement ascii
    return nullptr;
}

CharMatcher CharMatcher::digit() {
    // TODO: Implement digit
    return nullptr;
}

CharMatcher CharMatcher::javaDigit() {
    // TODO: Implement javaDigit
    return nullptr;
}

CharMatcher CharMatcher::javaLetter() {
    // TODO: Implement javaLetter
    return nullptr;
}

CharMatcher CharMatcher::javaLetterOrDigit() {
    // TODO: Implement javaLetterOrDigit
    return nullptr;
}

CharMatcher CharMatcher::javaUpperCase() {
    // TODO: Implement javaUpperCase
    return nullptr;
}

CharMatcher CharMatcher::javaLowerCase() {
    // TODO: Implement javaLowerCase
    return nullptr;
}

CharMatcher CharMatcher::javaIsoControl() {
    // TODO: Implement javaIsoControl
    return nullptr;
}

CharMatcher CharMatcher::invisible() {
    // TODO: Implement invisible
    return nullptr;
}

CharMatcher CharMatcher::singleWidth() {
    // TODO: Implement singleWidth
    return nullptr;
}

CharMatcher CharMatcher::is(char match) {
    // TODO: Implement is
    return nullptr;
}

CharMatcher CharMatcher::isNot(char match) {
    // TODO: Implement isNot
    return nullptr;
}

CharMatcher CharMatcher::anyOf(CharSequence sequence) {
    // TODO: Implement anyOf
    return nullptr;
}

return CharMatcher::none() {
    // TODO: Implement none
    return nullptr;
}

return CharMatcher::is() {
    // TODO: Implement is
    return nullptr;
}

return CharMatcher::isEither() {
    // TODO: Implement isEither
    return nullptr;
}

CharMatcher CharMatcher::noneOf(CharSequence sequence) {
    // TODO: Implement noneOf
    return nullptr;
}

return CharMatcher::anyOf() {
    // TODO: Implement anyOf
    return nullptr;
}

CharMatcher CharMatcher::inRange(char startInclusive, char endInclusive) {
    // TODO: Implement inRange
    return nullptr;
}

CharMatcher CharMatcher::forPredicate(Predicate<? super) {
    // TODO: Implement forPredicate
    return nullptr;
}

protected CharMatcher::CharMatcher() {
    // TODO: Implement CharMatcher
    return nullptr;
}

CharMatcher CharMatcher::negate() {
    // TODO: Implement negate
    return nullptr;
}

CharMatcher CharMatcher::and(CharMatcher other) {
    // TODO: Implement and
    return nullptr;
}

CharMatcher CharMatcher::or(CharMatcher other) {
    // TODO: Implement or
    return nullptr;
}

CharMatcher CharMatcher::precomputed() {
    // TODO: Implement precomputed
    return nullptr;
}

CharMatcher CharMatcher::precomputedInternal() {
    // TODO: Implement precomputedInternal
    return nullptr;
}

return CharMatcher::precomputedPositive() {
    // TODO: Implement precomputedPositive
    return nullptr;
}

CharMatcher CharMatcher::precomputedPositive(int totalCharacters, BitSet table, const std::string& description) {
    // TODO: Implement precomputedPositive
    return nullptr;
}

return CharMatcher::none() {
    // TODO: Implement none
    return nullptr;
}

return CharMatcher::is() {
    // TODO: Implement is
    return nullptr;
}

return CharMatcher::isEither() {
    // TODO: Implement isEither
    return nullptr;
}

bool CharMatcher::isSmall(int totalCharacters, int tableLength) {
    // TODO: Implement isSmall
    return false;
}

void CharMatcher::setBits(BitSet table) {
    // TODO: Implement setBits
}

bool CharMatcher::matchesAnyOf(CharSequence sequence) {
    // TODO: Implement matchesAnyOf
    return false;
}

bool CharMatcher::matchesAllOf(CharSequence sequence) {
    // TODO: Implement matchesAllOf
    return false;
}

bool CharMatcher::matchesNoneOf(CharSequence sequence) {
    // TODO: Implement matchesNoneOf
    return false;
}

int CharMatcher::indexIn(CharSequence sequence) {
    // TODO: Implement indexIn
    return 0;
}

int CharMatcher::indexIn(CharSequence sequence, int start) {
    // TODO: Implement indexIn
    return 0;
}

int CharMatcher::lastIndexIn(CharSequence sequence) {
    // TODO: Implement lastIndexIn
    return 0;
}

int CharMatcher::countIn(CharSequence sequence) {
    // TODO: Implement countIn
    return 0;
}

std::string CharMatcher::removeFrom(CharSequence sequence) {
    // TODO: Implement removeFrom
    return "";
}

std::string CharMatcher::retainFrom(CharSequence sequence) {
    // TODO: Implement retainFrom
    return "";
}

std::string CharMatcher::replaceFrom(CharSequence sequence, char replacement) {
    // TODO: Implement replaceFrom
    return "";
}

std::string CharMatcher::replaceFrom(CharSequence sequence, CharSequence replacement) {
    // TODO: Implement replaceFrom
    return "";
}

std::string CharMatcher::trimFrom(CharSequence sequence) {
    // TODO: Implement trimFrom
    return "";
}

std::string CharMatcher::trimLeadingFrom(CharSequence sequence) {
    // TODO: Implement trimLeadingFrom
    return "";
}

std::string CharMatcher::trimTrailingFrom(CharSequence sequence) {
    // TODO: Implement trimTrailingFrom
    return "";
}

std::string CharMatcher::collapseFrom(CharSequence sequence, char replacement) {
    // TODO: Implement collapseFrom
    return "";
}

std::string CharMatcher::trimAndCollapseFrom(CharSequence sequence, char replacement) {
    // TODO: Implement trimAndCollapseFrom
    return "";
}

std::string CharMatcher::finishCollapseFrom(CharSequence sequence, int start, int end, char replacement, std::stringstream builder, bool inMatchingGroup) {
    // TODO: Implement finishCollapseFrom
    return "";
}

bool CharMatcher::apply(char character) {
    // TODO: Implement apply
    return false;
}

std::string CharMatcher::toString() {
    // TODO: Implement toString
    return "";
}

std::string CharMatcher::showCharacter(char c) {
    // TODO: Implement showCharacter
    return "";
}

IsEither CharMatcher::isEither(char c1, char c2) {
    // TODO: Implement isEither
    return nullptr;
}

} // namespace base
} // namespace common
} // namespace google
} // namespace com
