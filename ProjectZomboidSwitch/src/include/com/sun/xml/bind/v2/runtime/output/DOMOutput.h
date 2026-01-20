#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/marshaller/SAX2DOMEx.h"
#include "com/sun/xml/bind/v2/runtime/AssociationMap.h"
#include "org/w3c/dom/Node.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class DOMOutput : public SAXOutput {
public:
    const AssociationMap assoc;

    public DOMOutput(Node node, AssociationMap assoc) {
      super(std::make_shared<SAX2DOMEx>(node));
      this.assoc = assoc;

      assert assoc != nullptr;
   }

    SAX2DOMEx getBuilder() {
      return (SAX2DOMEx)this.out;
   }

    void endStartTag() {
      super.endStartTag();
    void* op = this.nsContext.getCurrent().getOuterPeer();
      if (op != nullptr) {
         this.assoc.addOuter(this.getBuilder().getCurrentElement(), op);
      }

    void* ip = this.nsContext.getCurrent().getInnerPeer();
      if (ip != nullptr) {
         this.assoc.addInner(this.getBuilder().getCurrentElement(), ip);
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
