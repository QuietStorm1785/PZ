#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "javax/xml/namespace/QName.h"
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


class Transducer {
public:
    virtual ~Transducer() = default;
    bool useNamespace();

    void declareNamespace(ValueT var1, XMLSerializer var2);

    CharSequence print(@NotNull ValueT);

    ValueT parse(CharSequence var1);

    void writeText(XMLSerializer var1, ValueT var2, const std::string& var3);

    void writeLeafElement(XMLSerializer var1, Name var2, @NotNull ValueT, const std::string& var4);

    QName getTypeName(@NotNull ValueT);
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
