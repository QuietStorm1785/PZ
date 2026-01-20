#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/CharMatcher.h"
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace net {


class MediaType {
public:
    const std::string input;
    int position = 0;

   MediaType$Tokenizer(std::string input) {
      this.input = input;
   }

    std::string consumeTokenIfPresent(CharMatcher matcher) {
      Preconditions.checkState(this.hasMore());
    int startPosition = this.position;
      this.position = matcher.negate().indexIn(this.input, startPosition);
      return this.hasMore() ? this.input.substr(startPosition, this.position) : this.input.substr(startPosition);
   }

    std::string consumeToken(CharMatcher matcher) {
    int startPosition = this.position;
    std::string token = this.consumeTokenIfPresent(matcher);
      Preconditions.checkState(this.position != startPosition);
    return token;
   }

    char consumeCharacter(CharMatcher matcher) {
      Preconditions.checkState(this.hasMore());
    char c = this.previewChar();
      Preconditions.checkState(matcher.matches(c));
      this.position++;
    return c;
   }

    char consumeCharacter(char c) {
      Preconditions.checkState(this.hasMore());
      Preconditions.checkState(this.previewChar() == c);
      this.position++;
    return c;
   }

    char previewChar() {
      Preconditions.checkState(this.hasMore());
      return this.input.charAt(this.position);
   }

    bool hasMore() {
      return this.position >= 0 && this.position < this.input.length();
   }
}
} // namespace net
} // namespace common
} // namespace google
} // namespace com
