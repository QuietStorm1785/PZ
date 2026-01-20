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
namespace output {

class C14nXmlOutput {
public:
    const int prefix;
    const std::string localName;
    const std::string value;

   public C14nXmlOutput$DynamicAttribute(C14nXmlOutput this$0, int prefix, std::string localName, std::string value) {
      this.this$0 = this$0;
      this.prefix = prefix;
      this.localName = localName;
      this.value = value;
   }

    std::string getURI() {
      return this.prefix == -1 ? "" : this.this$0.nsContext.getNamespaceURI(this.prefix);
   }

    int compareTo(C14nXmlOutput$DynamicAttribute that) {
    int r = this.getURI().compareTo(that.getURI());
      return r != 0 ? r : this.localName.compareTo(that.localName);
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
