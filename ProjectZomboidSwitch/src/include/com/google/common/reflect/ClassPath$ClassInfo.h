#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/CharMatcher.h"
#include "com/google/common/reflect/ClassPath/ResourceInfo.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class ClassPath {
public:
    const std::string className;

   ClassPath$ClassInfo(std::string resourceName, ClassLoader loader) {
      super(resourceName, loader);
      this.className = ClassPath.getClassName(resourceName);
   }

    std::string getPackageName() {
      return Reflection.getPackageName(this.className);
   }

    std::string getSimpleName() {
    int lastDollarSign = this.className.lastIndexOf(36);
      if (lastDollarSign != -1) {
    std::string innerClassName = this.className.substr(lastDollarSign + 1);
         return CharMatcher.digit().trimLeadingFrom(innerClassName);
      } else {
    std::string packageName = this.getPackageName();
         return packageName.empty() ? this.className : this.className.substr(packageName.length() + 1);
      }
   }

    std::string getName() {
      return this.className;
   }

   public Class<?> load() {
      try {
         return this.loader.loadClass(this.className);
      } catch (ClassNotFoundException var2) {
         throw IllegalStateException(var2);
      }
   }

    std::string toString() {
      return this.className;
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
