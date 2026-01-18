#pragma once
#include <stdexcept>
#include <string>

namespace java {
namespace net {

/**
 * Exception thrown when URI syntax is invalid
 * C++ stub for java.net.URISyntaxException
 */
class URISyntaxException : public std::runtime_error {
public:
 URISyntaxException(const std::string& message)
 : std::runtime_error(message)
 , input("")
 , reason(message)
 , index(-1) {}
 
 URISyntaxException(const std::string& input, const std::string& reason)
 : std::runtime_error(reason + " in: " + input)
 , input(input)
 , reason(reason)
 , index(-1) {}
 
 URISyntaxException(const std::string& input, const std::string& reason, int index)
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
