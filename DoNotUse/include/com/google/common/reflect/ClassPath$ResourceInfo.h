#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/io/ByteSource.h"
#include "com/google/common/io/CharSource.h"
#include "com/google/common/io/Resources.h"
#include "com/google/common/reflect/ClassPath/ClassInfo.h"
#include "java/net/URL.h"
#include <algorithm>
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace reflect {


class ClassPath {
public:
    const std::string resourceName;
    const ClassLoader loader;

   static ClassPath$ResourceInfo of(std::string resourceName, ClassLoader loader) {
      return (ClassPath$ResourceInfo)(resourceName.endsWith(".class") ? std::make_shared<ClassInfo>(resourceName, loader) : new ClassPath$ResourceInfo(resourceName, loader));
   }

   ClassPath$ResourceInfo(std::string resourceName, ClassLoader loader) {
      this.resourceName = (std::string)Preconditions.checkNotNull(resourceName);
      this.loader = (ClassLoader)Preconditions.checkNotNull(loader);
   }

    URL url() {
    URL url = this.loader.getResource(this.resourceName);
      if (url == nullptr) {
         throw NoSuchElementException(this.resourceName);
      } else {
    return url;
      }
   }

    ByteSource asByteSource() {
      return Resources.asByteSource(this.url());
   }

    CharSource asCharSource(Charset charset) {
      return Resources.asCharSource(this.url(), charset);
   }

    std::string getResourceName() {
      return this.resourceName;
   }

    int hashCode() {
      return this.resourceName.hashCode();
   }

    bool equals(void* obj) {
      if (!(dynamic_cast<ClassPath*>(obj) != nullptr$ResourceInfo)) {
    return false;
      } else {
         ClassPath$ResourceInfo that = (ClassPath$ResourceInfo)obj;
         return this.resourceName == that.resourceName) && this.loader == that.loader;
      }
   }

    std::string toString() {
      return this.resourceName;
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
