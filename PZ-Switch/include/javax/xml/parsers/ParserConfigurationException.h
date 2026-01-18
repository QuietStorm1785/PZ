#ifndef JAVAX_XML_PARSERS_PARSERCONFIGURATIONEXCEPTION_H
#define JAVAX_XML_PARSERS_PARSERCONFIGURATIONEXCEPTION_H

#include <exception>
#include <string>

namespace javax { namespace xml { namespace parsers {

class ParserConfigurationException : public std::exception {
public:
 explicit ParserConfigurationException(const std::string& msg = "Parser configuration error") : message(msg) {}
 const char* what() const noexcept override { return message.c_str(); }
private:
 std::string message;
};

}}} // namespace javax::xml::parsers

#endif // JAVAX_XML_PARSERS_PARSERCONFIGURATIONEXCEPTION_H
