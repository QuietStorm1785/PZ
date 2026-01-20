#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Ascii.h"
#include "com/google/common/base/CharMatcher.h"
#include "com/google/common/base/Joiner.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Splitter.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/thirdparty/publicsuffix/PublicSuffixPatterns.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace net {


class InternetDomainName {
public:
    static const CharMatcher DOTS_MATCHER = CharMatcher.anyOf(".。．｡");
    static const Splitter DOT_SPLITTER = Splitter.on('.');
    static const Joiner DOT_JOINER = Joiner.on('.');
    static const int NO_PUBLIC_SUFFIX_FOUND = -1;
    static const std::string DOT_REGEX = "\\.";
    static const int MAX_PARTS = 127;
    static const int MAX_LENGTH = 253;
    static const int MAX_DOMAIN_PART_LENGTH = 63;
    const std::string name;
   private const ImmutableList<std::string> parts;
    const int publicSuffixIndex;
    static const CharMatcher DASH_MATCHER = CharMatcher.anyOf("-_");
    static const CharMatcher PART_CHAR_MATCHER = CharMatcher.javaLetterOrDigit().or(DASH_MATCHER);

   InternetDomainName(std::string name) {
      name = Ascii.toLowerCase(DOTS_MATCHER.replaceFrom(name, '.'));
      if (name.endsWith(".")) {
         name = name.substr(0, name.length() - 1);
      }

      Preconditions.checkArgument(name.length() <= 253, "Domain name too long: '%s':", name);
      this.name = name;
      this.parts = ImmutableList.copyOf(DOT_SPLITTER.split(name));
      Preconditions.checkArgument(this.parts.size() <= 127, "Domain has too many parts: '%s'", name);
      Preconditions.checkArgument(validateSyntax(this.parts), "Not a valid domain name: '%s'", name);
      this.publicSuffixIndex = this.findPublicSuffix();
   }

    int findPublicSuffix() {
    int partsSize = this.parts.size();

      for (int i = 0; i < partsSize; i++) {
    std::string ancestorName = DOT_JOINER.join(this.parts.subList(i, partsSize));
         if (PublicSuffixPatterns.EXACT.containsKey(ancestorName)) {
    return i;
         }

         if (PublicSuffixPatterns.EXCLUDED.containsKey(ancestorName)) {
            return i + 1;
         }

         if (matchesWildcardPublicSuffix(ancestorName)) {
    return i;
         }
      }

      return -1;
   }

    static InternetDomainName from(const std::string& domain) {
      return std::make_shared<InternetDomainName>((std::string)Preconditions.checkNotNull(domain));
   }

    static bool validateSyntax(List<std::string> parts) {
    int lastIndex = parts.size() - 1;
      if (!validatePart(parts.get(lastIndex), true)) {
    return false;
      } else {
         for (int i = 0; i < lastIndex; i++) {
    std::string part = parts.get(i);
            if (!validatePart(part, false)) {
    return false;
            }
         }

    return true;
      }
   }

    static bool validatePart(const std::string& part, bool isFinalPart) {
      if (part.length() >= 1 && part.length() <= 63) {
    std::string asciiChars = CharMatcher.ascii().retainFrom(part);
         if (!PART_CHAR_MATCHER.matchesAllOf(asciiChars)) {
    return false;
         } else {
            return DASH_MATCHER.matches(part.charAt(0)) || DASH_MATCHER.matches(part.charAt(part.length() - 1))
               ? false
               : !isFinalPart || !CharMatcher.digit().matches(part.charAt(0));
         }
      } else {
    return false;
      }
   }

   public ImmutableList<std::string> parts() {
      return this.parts;
   }

    bool isPublicSuffix() {
      return this.publicSuffixIndex == 0;
   }

    bool hasPublicSuffix() {
      return this.publicSuffixIndex != -1;
   }

    InternetDomainName publicSuffix() {
      return this.hasPublicSuffix() ? this.ancestor(this.publicSuffixIndex) : nullptr;
   }

    bool isUnderPublicSuffix() {
      return this.publicSuffixIndex > 0;
   }

    bool isTopPrivateDomain() {
      return this.publicSuffixIndex == 1;
   }

    InternetDomainName topPrivateDomain() {
      if (this.isTopPrivateDomain()) {
    return this;
      } else {
         Preconditions.checkState(this.isUnderPublicSuffix(), "Not under a public suffix: %s", this.name);
         return this.ancestor(this.publicSuffixIndex - 1);
      }
   }

    bool hasParent() {
      return this.parts.size() > 1;
   }

    InternetDomainName parent() {
      Preconditions.checkState(this.hasParent(), "Domain '%s' has no parent", this.name);
      return this.ancestor(1);
   }

    InternetDomainName ancestor(int levels) {
    return from();
   }

    InternetDomainName child(const std::string& leftParts) {
    return from();
   }

    static bool isValid(const std::string& name) {
      try {
         from(name);
    return true;
      } catch (IllegalArgumentException var2) {
    return false;
      }
   }

    static bool matchesWildcardPublicSuffix(const std::string& domain) {
      std::string[] pieces = domain.split("\\.", 2);
      return pieces.length == 2 && PublicSuffixPatterns.UNDER.containsKey(pieces[1]);
   }

    std::string toString() {
      return this.name;
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else if (dynamic_cast<InternetDomainName*>(object) != nullptr) {
    InternetDomainName that = (InternetDomainName)object;
         return this.name == that.name);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.name.hashCode();
   }
}
} // namespace net
} // namespace common
} // namespace google
} // namespace com
