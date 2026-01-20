#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/output/C14nXmlOutput/DynamicAttribute.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class C14nXmlOutput {
public:
    Name name;
    std::string value;

   C14nXmlOutput$StaticAttribute(C14nXmlOutput this$0) {
      this.this$0 = this$0;
   }

    void set(Name name, const std::string& value) {
      this.name = name;
      this.value = value;
   }

    void write() {
      C14nXmlOutput.access$001(this.this$0, this.name, this.value);
   }

    DynamicAttribute toDynamicAttribute() {
    int nsUriIndex = this.name.nsUriIndex;
    int prefix;
      if (nsUriIndex == -1) {
         prefix = -1;
      } else {
         prefix = this.this$0.nsUriIndex2prefixIndex[nsUriIndex];
      }

      return std::make_shared<DynamicAttribute>(this.this$0, prefix, this.name.localName, this.value);
   }

    int compareTo(C14nXmlOutput$StaticAttribute that) {
      return this.name.compareTo(that.name);
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
