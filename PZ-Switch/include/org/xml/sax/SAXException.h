#ifndef ORG_XML_SAX_SAXEXCEPTION_H
#define ORG_XML_SAX_SAXEXCEPTION_H

#include <exception>
#include <string>
#include <string_view>

namespace org { namespace xml { namespace sax {

class SAXException : public std::exception {
public:
 explicit SAXException(std::string_view msg = "SAX error") : message(msg) {}
 const char* what() const noexcept override { return message.c_str(); }
private:
 std::string message;
};

}}} // namespace org::xml::sax

#endif // ORG_XML_SAX_SAXEXCEPTION_H
