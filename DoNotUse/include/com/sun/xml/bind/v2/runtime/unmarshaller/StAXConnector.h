#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/StAXConnector/1.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/StAXConnector/TagNameImpl.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XmlVisitor/TextPredictor.h"
#include "javax/xml/namespace/NamespaceContext.h"
#include "javax/xml/stream/Location.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class StAXConnector {
public:
    const XmlVisitor visitor;
    const UnmarshallingContext context;
    const TextPredictor predictor;
    const TagName tagName = std::make_shared<TagNameImpl>(this, nullptr);

   public abstract void bridge() throws XMLStreamException;

    protected StAXConnector(XmlVisitor visitor) {
      this.visitor = visitor;
      this.context = visitor.getContext();
      this.predictor = visitor.getPredictor();
   }

   protected abstract Location getCurrentLocation();

   protected abstract std::string getCurrentQName();

    void handleStartDocument(NamespaceContext nsc) {
      this.visitor.startDocument(std::make_shared<1>(this), nsc);
   }

    void handleEndDocument() {
      this.visitor.endDocument();
   }

    static std::string fixNull(const std::string& s) {
    return s = = nullptr ? "" : s;
   }

    std::string getQName(const std::string& prefix, const std::string& localName) {
      return prefix != nullptr && prefix.length() != 0 ? prefix + ':' + localName : localName;
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
