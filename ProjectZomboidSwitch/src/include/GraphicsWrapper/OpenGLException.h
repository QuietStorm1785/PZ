#pragma once
// Stub for org/lwjglx/opengl/OpenGLException.h
#include "GraphicsExceptions.h"

namespace GraphicsWrapper {
    class OpenGLException : public GraphicsException {
    public:
        explicit OpenGLException(const std::string& msg) : GraphicsException(msg) {}
    };
}
