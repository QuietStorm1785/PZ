#ifndef ORG_XML_SAX_SAXEXCEPTION_H
#define ORG_XML_SAX_SAXEXCEPTION_H

#include <exception>
#include <string>

namespace org { namespace xml { namespace sax {

class SAXException : public std::exception {
public:
 explicit SAXException(const std::string& msg = "SAX error") : message(msg) {}
 const char* what() const noexcept override { return message.c_str(); }
private:
 std::string message;
};

}}} // namespace org::xml::sax

#endif // ORG_XML_SAX_SAXEXCEPTION_H
