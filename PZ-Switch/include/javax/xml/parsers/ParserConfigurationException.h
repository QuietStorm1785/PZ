#ifndef JAVAX_XML_PARSERS_PARSERCONFIGURATIONEXCEPTION_H
#define JAVAX_XML_PARSERS_PARSERCONFIGURATIONEXCEPTION_H

#include <exception>
#include <string>
#include <string_view>

namespace javax { namespace xml { namespace parsers {

class ParserConfigurationException : public std::exception {
public:
 explicit ParserConfigurationException(std::string_view msg = "Parser configuration error") : message(msg) {}
 const char* what() const noexcept override { return message.c_str(); }
private:
 std::string message;
};

}}} // namespace javax::xml::parsers

#endif // JAVAX_XML_PARSERS_PARSERCONFIGURATIONEXCEPTION_H
