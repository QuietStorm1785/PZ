#pragma once
#include <stdexcept>
#include <string>
#include <string_view>

namespace java {
namespace net {

/**
 * Exception thrown when URI syntax is invalid
 * C++ stub for java.net.URISyntaxException
 */
class URISyntaxException : public std::runtime_error {
public:
 URISyntaxException(std::string_view message)
 : std::runtime_error(message)
 , input("")
 , reason(message)
 , index(-1) {}
 
 URISyntaxException(std::string_view input, std::string_view reason)
 : std::runtime_error(reason + " in: " + input)
 , input(input)
 , reason(reason)
 , index(-1) {}
 
 URISyntaxException(std::string_view input, std::string_view reason, int index)
 : std::runtime_error(reason + " at index " + std::to_string(index) + " in: " + input)
 , input(input)
 , reason(reason)
 , index(index) {}
 
 std::string getInput() const { return input; }
 std::string getReason() const { return reason; }
 int getIndex() const { return index; }
 
private:
 std::string input;
 std::string reason;
 int index;
};

} // namespace net
} // namespace java
