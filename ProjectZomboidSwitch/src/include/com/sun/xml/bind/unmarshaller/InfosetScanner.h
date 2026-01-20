#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/LocatorEx.h"
#include "org/xml/sax/ContentHandler.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace unmarshaller {


class InfosetScanner {
public:
    virtual ~InfosetScanner() = default;
    void scan(XmlNode var1);

    void setContentHandler(ContentHandler var1);

    ContentHandler getContentHandler();

    XmlNode getCurrentElement();

    LocatorEx getLocator();
}
} // namespace unmarshaller
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
