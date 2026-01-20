#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/ErrorHandler.h"
#include "org/xml/sax/SAXParseException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace api {


class ErrorListener {
public:
    virtual ~ErrorListener() = default;
    void error(SAXParseException var1);

    void fatalError(SAXParseException var1);

    void warning(SAXParseException var1);

    void info(SAXParseException var1);
}
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
