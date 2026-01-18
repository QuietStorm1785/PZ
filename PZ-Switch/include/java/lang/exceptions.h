#pragma once
#include <stdexcept>
#include <string>

namespace java {
namespace lang {

/**
 * Exception thrown when a nullptr pointer is accessed
 * C++ stub for java.lang.NullPointerException
 */
class NullPointerException : public std::runtime_error {
public:
 NullPointerException()
 : std::runtime_error("Null pointer") {}
 
 explicit NullPointerException(const std::string& message)
 : std::runtime_error(message) {}
};

/**
 * Exception thrown for illegal arguments
 * C++ stub for java.lang.IllegalArgumentException
 */
class IllegalArgumentException : public std::runtime_error {
public:
 IllegalArgumentException()
 : std::runtime_error("Illegal argument") {}
 
 explicit IllegalArgumentException(const std::string& message)
 : std::runtime_error(message) {}
};

/**
 * Exception thrown for illegal state
 * C++ stub for java.lang.IllegalStateException
 */
class IllegalStateException : public std::runtime_error {
public:
 IllegalStateException()
 : std::runtime_error("Illegal state") {}
 
 explicit IllegalStateException(const std::string& message)
 : std::runtime_error(message) {}
};

/**
 * Exception for unsupported operations
 * C++ stub for java.lang.UnsupportedOperationException
 */
class UnsupportedOperationException : public std::runtime_error {
public:
 UnsupportedOperationException()
 : std::runtime_error("Unsupported operation") {}
 
 explicit UnsupportedOperationException(const std::string& message)
 : std::runtime_error(message) {}
};

/**
 * Base runtime exception
 * C++ stub for java.lang.RuntimeException
 */
class RuntimeException : public std::runtime_error {
public:
 RuntimeException()
 : std::runtime_error("Runtime exception") {}
 
 explicit RuntimeException(const std::string& message)
 : std::runtime_error(message) {}
};

} // namespace lang
} // namespace java

// Global namespace aliases for convenience
using NullPointerException = java::lang::NullPointerException;
using IllegalArgumentException = java::lang::IllegalArgumentException;
using IllegalStateException = java::lang::IllegalStateException;
using UnsupportedOperationException = java::lang::UnsupportedOperationException;
using RuntimeException = java::lang::RuntimeException;
