#pragma once
#include <stdexcept>
#include <string>
#include <string_view>

namespace javax {
namespace xml {
namespace bind {

/**
 * Exception for JAXB operations
 * C++ stub for javax.xml.bind.JAXBException
 */
class JAXBException : public std::runtime_error {
public:
 explicit JAXBException(std::string_view message)
 : std::runtime_error(message)
 , errorCode("")
 , linkedException(nullptr) {}
 
 JAXBException(std::string_view message, std::string_view code)
 : std::runtime_error(message)
 , errorCode(code)
 , linkedException(nullptr) {}
 
 JAXBException(std::string_view message, std::exception* linked)
 : std::runtime_error(message)
 , errorCode("")
 , linkedException(linked) {}
 
 std::string getErrorCode() const { return errorCode; }
 std::exception* getLinkedException() const { return linkedException; }
 
private:
 std::string errorCode;
 std::exception* linkedException;
};

} // namespace bind
} // namespace xml
} // namespace javax
