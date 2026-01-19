#ifndef JAVA_NET_MALFORMEDURL_EXCEPTION_H
#define JAVA_NET_MALFORMEDURL_EXCEPTION_H

#include <exception>
#include <string>
#include <string_view>

namespace java { namespace net {

class MalformedURLException : public std::exception {
public:
 explicit MalformedURLException(std::string_view msg = "Malformed URL") : message(msg) {}
 const char* what() const noexcept override { return message.c_str(); }
private:
 std::string message;
};

}} // namespace java::net

#endif // JAVA_NET_MALFORMEDURL_EXCEPTION_H
