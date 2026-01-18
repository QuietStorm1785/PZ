#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LWJGLException : public Exception {
public:
  static const long serialVersionUID = 1L;

public
  LWJGLException() {}

public
  LWJGLException(const std::string &string) { super(string); }

public
  LWJGLException(const std::string &string, std::exception throwable) {
    super(string, throwable);
  }

public
  LWJGLException(std::exception throwable) { super(throwable); }
}
} // namespace lwjglx
} // namespace org
