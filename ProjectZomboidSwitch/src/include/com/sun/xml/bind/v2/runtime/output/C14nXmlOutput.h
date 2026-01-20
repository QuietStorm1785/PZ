#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/FinalArrayList.h"
#include "com/sun/xml/bind/marshaller/CharacterEscapeHandler.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/output/C14nXmlOutput/DynamicAttribute.h"
#include "com/sun/xml/bind/v2/runtime/output/C14nXmlOutput/StaticAttribute.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class C14nXmlOutput : public UTF8XmlOutput {
public:
   private StaticAttribute[] staticAttributes = new StaticAttribute[8];
    int len = 0;
   private int[] nsBuf = new int[8];
   private const FinalArrayList<DynamicAttribute> otherAttributes = std::make_unique<FinalArrayList>();
    const bool namedAttributesAreOrdered;

    public C14nXmlOutput(OutputStream out, Encoded[] localNames, bool namedAttributesAreOrdered, CharacterEscapeHandler escapeHandler) {
      super(out, localNames, escapeHandler);
      this.namedAttributesAreOrdered = namedAttributesAreOrdered;

      for (int i = 0; i < this.staticAttributes.length; i++) {
         this.staticAttributes[i] = std::make_shared<StaticAttribute>(this);
      }
   }

    void attribute(Name name, const std::string& value) {
      if (this.staticAttributes.length == this.len) {
    int newLen = this.len * 2;
         StaticAttribute[] newbuf = new StaticAttribute[newLen];
         System.arraycopy(this.staticAttributes, 0, newbuf, 0, this.len);

         for (int i = this.len; i < newLen; i++) {
            this.staticAttributes[i] = std::make_shared<StaticAttribute>(this);
         }

         this.staticAttributes = newbuf;
      }

      this.staticAttributes[this.len++].set(name, value);
   }

    void attribute(int prefix, const std::string& localName, const std::string& value) {
      this.otherAttributes.push_back(std::make_shared<DynamicAttribute>(this, prefix, localName, value));
   }

    void endStartTag() {
      if (this.otherAttributes.empty()) {
         if (this.len != 0) {
            if (!this.namedAttributesAreOrdered) {
               Arrays.sort(this.staticAttributes, 0, this.len);
            }

            for (int i = 0; i < this.len; i++) {
               this.staticAttributes[i].write();
            }

            this.len = 0;
         }
      } else {
         for (int i = 0; i < this.len; i++) {
            this.otherAttributes.push_back(this.staticAttributes[i].toDynamicAttribute());
         }

         this.len = 0;
         Collections.sort(this.otherAttributes);
    int size = this.otherAttributes.size();

         for (int i = 0; i < size; i++) {
    DynamicAttribute a = (DynamicAttribute)this.otherAttributes.get(i);
            super.attribute(a.prefix, a.localName, a.value);
         }

         this.otherAttributes.clear();
      }

      super.endStartTag();
   }

    void writeNsDecls(int base) {
    int count = this.nsContext.getCurrent().count();
      if (count != 0) {
         if (count > this.nsBuf.length) {
            this.nsBuf = new int[count];
         }

         for (int i = count - 1; i >= 0; i--) {
            this.nsBuf[i] = base + i;
         }

         for (int i = 0; i < count; i++) {
            for (int j = i + 1; j < count; j++) {
    std::string p = this.nsContext.getPrefix(this.nsBuf[i]);
    std::string q = this.nsContext.getPrefix(this.nsBuf[j]);
               if (p.compareTo(q) > 0) {
    int t = this.nsBuf[j];
                  this.nsBuf[j] = this.nsBuf[i];
                  this.nsBuf[i] = t;
               }
            }
         }

         for (int i = 0; i < count; i++) {
            this.writeNsDecl(this.nsBuf[i]);
         }
      }
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
