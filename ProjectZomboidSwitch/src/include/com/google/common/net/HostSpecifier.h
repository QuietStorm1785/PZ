#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "java/net/InetAddress.h"
#include "java/text/ParseException.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace net {


class HostSpecifier {
public:
    const std::string canonicalForm;

    private HostSpecifier(const std::string& canonicalForm) {
      this.canonicalForm = canonicalForm;
   }

    static HostSpecifier fromValid(const std::string& specifier) {
    HostAndPort parsedHost = HostAndPort.fromString(specifier);
      Preconditions.checkArgument(!parsedHost.hasPort());
    std::string host = parsedHost.getHost();
    InetAddress addr = nullptr;

      try {
         addr = InetAddresses.forString(host);
      } catch (IllegalArgumentException var5) {
      }

      if (addr != nullptr) {
         return std::make_shared<HostSpecifier>(InetAddresses.toUriString(addr));
      } else {
    InternetDomainName domain = InternetDomainName.from(host);
         if (domain.hasPublicSuffix()) {
            return std::make_shared<HostSpecifier>(domain);
         } else {
            throw IllegalArgumentException("Domain name does not have a recognized public suffix: " + host);
         }
      }
   }

    static HostSpecifier from(const std::string& specifier) {
      try {
    return fromValid();
      } catch (IllegalArgumentException var3) {
    ParseException parseException = std::make_shared<ParseException>("Invalid host specifier: " + specifier, 0);
         parseException.initCause(var3);
    throw parseException;
      }
   }

    static bool isValid(const std::string& specifier) {
      try {
         fromValid(specifier);
    return true;
      } catch (IllegalArgumentException var2) {
    return false;
      }
   }

    bool equals(@Nullable Object) {
      if (this == other) {
    return true;
      } else if (dynamic_cast<HostSpecifier*>(other) != nullptr) {
    HostSpecifier that = (HostSpecifier)other;
         return this.canonicalForm == that.canonicalForm);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.canonicalForm.hashCode();
   }

    std::string toString() {
      return this.canonicalForm;
   }
}
} // namespace net
} // namespace common
} // namespace google
} // namespace com
