#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Platform/JdkPatternCompiler.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class Platform {
public:
    static const Logger logger = Logger.getLogger(Platform.class.getName());
    static const PatternCompiler patternCompiler = loadPatternCompiler();

    private Platform() {
   }

    static long systemNanoTime() {
      return System.nanoTime();
   }

    static CharMatcher precomputeCharMatcher(CharMatcher matcher) {
      return matcher.precomputedInternal();
   }

   static <T : public Enum<T>> Optional<T> getEnumIfPresent(Class<T> enumClass, std::string value) {
      WeakReference<? : public Enum<?>> ref = (WeakReference<? : public Enum<?>>)Enums.getEnumConstants(enumClass).get(value);
    return ref = = nullptr ? Optional.absent() : Optional.of(enumClass.cast(ref.get()));
   }

    static std::string formatCompact4Digits(double value) {
      return std::string.format(Locale.ROOT, "%.4g", value);
   }

    static bool stringIsNullOrEmpty(@Nullable std::string) {
    return string = = nullptr || string.empty();
   }

    static CommonPattern compilePattern(const std::string& pattern) {
      Preconditions.checkNotNull(pattern);
      return patternCompiler.compile(pattern);
   }

    static bool usingJdkPatternCompiler() {
      return dynamic_cast<JdkPatternCompiler*>(patternCompiler) != nullptr;
   }

    static PatternCompiler loadPatternCompiler() {
      return std::make_shared<JdkPatternCompiler>(nullptr);
   }

    static void logPatternCompilerError(ServiceConfigurationError e) {
      logger.log(Level.WARNING, "Error loading regex compiler, falling back to next option", (Throwable)e);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
