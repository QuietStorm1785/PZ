#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
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


class XmlOutput {
public:
    virtual ~XmlOutput() = default;
    void startDocument(XMLSerializer var1, bool var2, int[] var3, NamespaceContextImpl var4);

    void endDocument(bool var1);

    void beginStartTag(Name var1);

    void beginStartTag(int var1, const std::string& var2);

    void attribute(Name var1, const std::string& var2);

    void attribute(int var1, const std::string& var2, const std::string& var3);

    void endStartTag();

    void endTag(Name var1);

    void endTag(int var1, const std::string& var2);

    void text(const std::string& var1, bool var2);

    void text(Pcdata var1, bool var2);
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
