#pragma once
#include <stdexcept>
#include <string>

namespace GraphicsWrapper {

// Base exception for graphics errors
class GraphicsException : public std::runtime_error {
public:
    explicit GraphicsException(const std::string& msg)
        : std::runtime_error(msg) {}
};

// OpenGL-specific exception
class OpenGLException : public GraphicsException {
public:
    explicit OpenGLException(const std::string& msg)
        : GraphicsException("OpenGL Error: " + msg) {}
};

// GLUS-specific exception
class GLUSException : public GraphicsException {
public:
    explicit GLUSException(const std::string& msg)
        : GraphicsException("GLUS Error: " + msg) {}
};

// SDL2-specific exception
class SDL2Exception : public GraphicsException {
public:
    explicit SDL2Exception(const std::string& msg)
        : GraphicsException("SDL2 Error: " + msg) {}
};

} // namespace GraphicsWrapper
