#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace sixlegs {
namespace png {


class PngException : public IOException {
public:
    static const Method initCause = getInitCause();
    const bool fatal;

    static Method getInitCause() {
      try {
         return PngException.class.getMethod("initCause", Throwable.class);
      } catch (const jni::JavaException& var1) {
    return null;
      }
   }

   PngException(String var1, boolean var2) {
      this(var1, nullptr, var2);
   }

   PngException(String var1, Throwable var2, boolean var3) {
      super(var1);
      this.fatal = var3;
      if (var2 != nullptr && initCause != nullptr) {
         try {
            initCause.invoke(this, var2);
         } catch (RuntimeException var5) {
    throw var5;
         } catch (const jni::JavaException& var6) {
            throw new IllegalStateException("Error invoking initCause: " + var6.getMessage());
         }
      }
   }

    bool isFatal() {
      return this.fatal;
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
