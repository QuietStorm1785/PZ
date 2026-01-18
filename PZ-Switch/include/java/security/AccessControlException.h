#pragma once
#include <stdexcept>
#include <string>

namespace java {
namespace security {

/**
 * Exception thrown when access control is violated
 * C++ stub for java.security.AccessControlException
 */
class AccessControlException : public std::runtime_error {
public:
 explicit AccessControlException(const std::string& message)
 : std::runtime_error(message)
 , permission("") {}
 
 AccessControlException(const std::string& message, const std::string& perm)
 : std::runtime_error(message)
 , permission(perm) {}
 
 std::string getPermission() const { return permission; }
 
private:
 std::string permission;
};

} // namespace security
} // namespace java
