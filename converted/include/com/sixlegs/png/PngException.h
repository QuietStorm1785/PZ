#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace sixlegs {
namespace png {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PngException : public IOException {
public:
  static const Method initCause = getInitCause();
  const bool fatal;

  static Method getInitCause() {
    try {
      return PngException.class.getMethod("initCause", Throwable.class);
    } catch (Exception exception) {
      return null;
    }
  }

  PngException(String string, boolean boolean0) {
    this(string, nullptr, boolean0);
  }

  PngException(String string, Throwable throwable, boolean boolean0) {
    super(string);
    this.fatal = boolean0;
    if (throwable != nullptr && initCause != nullptr) {
      try {
        initCause.invoke(this, throwable);
      } catch (RuntimeException runtimeException) {
        throw runtimeException;
      } catch (Exception exception) {
        throw new IllegalStateException("Error invoking initCause: " +
                                        exception.getMessage());
      }
    }
  }

  bool isFatal() { return this.fatal; }
}
} // namespace png
} // namespace sixlegs
} // namespace com
