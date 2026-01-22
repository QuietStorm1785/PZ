#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/io/Resources/1.h"
#include "com/google/common/io/Resources/UrlByteSource.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "java/net/URL.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class Resources {
public:
    private Resources() {
   }

    static ByteSource asByteSource(URL url) {
      return std::make_shared<UrlByteSource>(url, nullptr);
   }

    static CharSource asCharSource(URL url, Charset charset) {
    return asByteSource();
   }

   public static byte[] toByteArray(URL url) throws IOException {
    return asByteSource();
   }

    static std::string toString(URL url, Charset charset) {
    return asCharSource();
   }

   public static <T> T readLines(URL url, Charset charset, LineProcessor<T> callback) throws IOException {
      return (T)asCharSource(url, charset).readLines(callback);
   }

   public static List<std::string> readLines(URL url, Charset charset) throws IOException {
    return readLines(std::make_shared<1>();
   }

    static void copy(URL from, OutputStream to) {
      asByteSource(from).copyTo(to);
   }

    static URL getResource(const std::string& resourceName) {
    ClassLoader loader = (ClassLoader)MoreObjects.firstNonNull(Thread.currentThread().getContextClassLoader(), Resources.class.getClassLoader());
    URL url = loader.getResource(resourceName);
      Preconditions.checkArgument(url != nullptr, "resource %s not found.", resourceName);
    return url;
   }

    static URL getResource(Class<?> contextClass, const std::string& resourceName) {
    URL url = contextClass.getResource(resourceName);
      Preconditions.checkArgument(url != nullptr, "resource %s relative to %s not found.", resourceName, contextClass.getName());
    return url;
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
