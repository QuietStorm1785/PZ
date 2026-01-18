#ifndef JAVA_SECURITY_INVALIDPARAMETEREXCEPTION_H
#define JAVA_SECURITY_INVALIDPARAMETEREXCEPTION_H

#include <exception>
#include <string>

namespace java { namespace security {

class InvalidParameterException : public std::exception {
public:
 explicit InvalidParameterException(const std::string& msg = "Invalid parameter") : message(msg) {}
 const char* what() const noexcept override { return message.c_str(); }
private:
 std::string message;
};

}} // namespace java::security

#endif // JAVA_SECURITY_INVALIDPARAMETEREXCEPTION_H
