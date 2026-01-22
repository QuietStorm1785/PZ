#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/SAXException.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class NamespaceContextImpl {
public:
    const NamespaceContextImpl context;
   private const NamespaceContextImpl$Element prev;
   private NamespaceContextImpl$Element next;
    int oldDefaultNamespaceUriIndex;
    int defaultPrefixIndex;
    int baseIndex;
    const int depth;
    int elementNamePrefix;
    std::string elementLocalName;
    Name elementName;
    void* outerPeer;
    void* innerPeer;

   private NamespaceContextImpl$Element(NamespaceContextImpl this$0, NamespaceContextImpl context, NamespaceContextImpl$Element prev) {
      this.this$0 = this$0;
      this.context = context;
      this.prev = prev;
      this.depth = prev == nullptr ? 0 : prev.depth + 1;
   }

    bool isRootElement() {
      return this.depth == 1;
   }

   public NamespaceContextImpl$Element push() {
      if (this.next == nullptr) {
         this.next = new NamespaceContextImpl$Element(this.this$0, this.context, this);
      }

      this.next.onPushed();
      return this.next;
   }

   public NamespaceContextImpl$Element pop() {
      if (this.oldDefaultNamespaceUriIndex >= 0) {
         NamespaceContextImpl.access$500(this.context).knownUri2prefixIndexMap[this.oldDefaultNamespaceUriIndex] = this.defaultPrefixIndex;
      }

      NamespaceContextImpl.access$602(this.context, this.baseIndex);
      NamespaceContextImpl.access$702(this.context, this.prev);
      this.outerPeer = this.innerPeer = nullptr;
      return this.prev;
   }

    void onPushed() {
      this.oldDefaultNamespaceUriIndex = this.defaultPrefixIndex = -1;
      this.baseIndex = NamespaceContextImpl.access$600(this.context);
      NamespaceContextImpl.access$702(this.context, this);
   }

    void setTagName(int prefix, const std::string& localName, void* outerPeer) {
      if (!$assertionsDisabled && localName == nullptr) {
         throw std::make_unique<AssertionError>();
      } else {
         this.elementNamePrefix = prefix;
         this.elementLocalName = localName;
         this.elementName = nullptr;
         this.outerPeer = outerPeer;
      }
   }

    void setTagName(Name tagName, void* outerPeer) {
      if (!$assertionsDisabled && tagName == nullptr) {
         throw std::make_unique<AssertionError>();
      } else {
         this.elementName = tagName;
         this.outerPeer = outerPeer;
      }
   }

    void startElement(XmlOutput out, void* innerPeer) {
      this.innerPeer = innerPeer;
      if (this.elementName != nullptr) {
         out.beginStartTag(this.elementName);
      } else {
         out.beginStartTag(this.elementNamePrefix, this.elementLocalName);
      }
   }

    void endElement(XmlOutput out) {
      if (this.elementName != nullptr) {
         out.endTag(this.elementName);
         this.elementName = nullptr;
      } else {
         out.endTag(this.elementNamePrefix, this.elementLocalName);
      }
   }

    int count() {
      return NamespaceContextImpl.access$600(this.context) - this.baseIndex;
   }

    std::string getPrefix(int idx) {
      return NamespaceContextImpl.access$800(this.context)[this.baseIndex + idx];
   }

    std::string getNsUri(int idx) {
      return NamespaceContextImpl.access$900(this.context)[this.baseIndex + idx];
   }

    int getBase() {
      return this.baseIndex;
   }

    void* getOuterPeer() {
      return this.outerPeer;
   }

    void* getInnerPeer() {
      return this.innerPeer;
   }

   public NamespaceContextImpl$Element getParent() {
      return this.prev;
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
