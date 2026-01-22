#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {

class NameList {
public:
   public const std::string[] namespaceURIs;
   public const boolean[] nsUriCannotBeDefaulted;
   public const std::string[] localNames;
    const int numberOfElementNames;
    const int numberOfAttributeNames;

    public NameList(std::string[] namespaceURIs, boolean[] nsUriCannotBeDefaulted, std::string[] localNames, int numberElementNames, int numberAttributeNames) {
      this.namespaceURIs = namespaceURIs;
      this.nsUriCannotBeDefaulted = nsUriCannotBeDefaulted;
      this.localNames = localNames;
      this.numberOfElementNames = numberElementNames;
      this.numberOfAttributeNames = numberAttributeNames;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
