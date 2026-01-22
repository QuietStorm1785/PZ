#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XmlVisitor/TextPredictor.h"
#include "javax/xml/namespace/NamespaceContext.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class XmlVisitor {
public:
    virtual ~XmlVisitor() = default;
    void startDocument(LocatorEx var1, NamespaceContext var2);

    void endDocument();

    void startElement(TagName var1);

    void endElement(TagName var1);

    void startPrefixMapping(const std::string& var1, const std::string& var2);

    void endPrefixMapping(const std::string& var1);

    void text(CharSequence var1);

    UnmarshallingContext getContext();

    TextPredictor getPredictor();
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
