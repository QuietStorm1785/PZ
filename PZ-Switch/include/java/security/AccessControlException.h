#pragma once
#include <stdexcept>
#include <string>
#include <string_view>

namespace java {
namespace security {

/**
 * Exception thrown when access control is violated
 * C++ stub for java.security.AccessControlException
 */
class AccessControlException : public std::runtime_error {
public:
 explicit AccessControlException(std::string_view message)
 : std::runtime_error(message)
 , permission("") {}
 
 AccessControlException(std::string_view message, std::string_view perm)
 : std::runtime_error(message)
 , permission(perm) {}
 
 std::string getPermission() const { return permission; }
 
private:
 std::string permission;
};

} // namespace security
} // namespace java
