#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class OpenGLException : public RuntimeException {
public:
 static const long serialVersionUID = 1L;

public
 OpenGLException(int int0) { this(createErrorMessage(int0); }

 static std::string createErrorMessage(int int0) {
 std::string string = Util.translateGLErrorString(int0);
 return string + " (" + int0 + ")";
 }

public
 OpenGLException() {}

public
 OpenGLException(std::string_view string) { super(string); }

public
 OpenGLException(std::string_view string, std::exception throwable) {
 super(string, throwable);
 }

public
 OpenGLException(std::exception throwable) { super(throwable); }
}
} // namespace opengl
} // namespace lwjglx
} // namespace org
