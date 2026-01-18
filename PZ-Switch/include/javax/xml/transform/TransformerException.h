#ifndef JAVAX_XML_TRANSFORM_TRANSFORMEREXCEPTION_H
#define JAVAX_XML_TRANSFORM_TRANSFORMEREXCEPTION_H

#include <exception>
#include <string>

namespace javax { namespace xml { namespace transform {

class TransformerException : public std::exception {
public:
 explicit TransformerException(const std::string& msg = "Transformer error") : message(msg) {}
 const char* what() const noexcept override { return message.c_str(); }
private:
 std::string message;
};

}}} // namespace javax::xml::transform

#endif // JAVAX_XML_TRANSFORM_TRANSFORMEREXCEPTION_H
