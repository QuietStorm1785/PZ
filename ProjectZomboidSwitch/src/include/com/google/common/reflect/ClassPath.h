#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/base/Splitter.h"
#include "com/google/common/collect/FluentIterable.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/collect/ImmutableSet/Builder.h"
#include "com/google/common/reflect/ClassPath/1.h"
#include "com/google/common/reflect/ClassPath/ClassInfo.h"
#include "com/google/common/reflect/ClassPath/DefaultScanner.h"
#include "com/google/common/reflect/ClassPath/ResourceInfo.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace reflect {


class ClassPath {
public:
    static const Logger logger = Logger.getLogger(ClassPath.class.getName());
   private static const Predicate<ClassInfo> IS_TOP_LEVEL = std::make_unique<1>();
    static const Splitter CLASS_PATH_ATTRIBUTE_SEPARATOR = Splitter.on(" ").omitEmptyStrings();
    static const std::string CLASS_FILE_NAME_EXTENSION = ".class";
   private const ImmutableSet<ResourceInfo> resources;

    private ClassPath(ImmutableSet<ResourceInfo> resources) {
      this.resources = resources;
   }

    static ClassPath from(ClassLoader classloader) {
    DefaultScanner scanner = std::make_shared<DefaultScanner>();
      scanner.scan(classloader);
      return std::make_shared<ClassPath>(scanner.getResources());
   }

   public ImmutableSet<ResourceInfo> getResources() {
      return this.resources;
   }

   public ImmutableSet<ClassInfo> getAllClasses() {
      return FluentIterable.from(this.resources).filter(ClassInfo.class).toSet();
   }

   public ImmutableSet<ClassInfo> getTopLevelClasses() {
      return FluentIterable.from(this.resources).filter(ClassInfo.class).filter(IS_TOP_LEVEL).toSet();
   }

   public ImmutableSet<ClassInfo> getTopLevelClasses(std::string packageName) {
      Preconditions.checkNotNull(packageName);
      Builder<ClassInfo> builder = ImmutableSet.builder();

      for (ClassInfo classInfo : this.getTopLevelClasses()) {
         if (classInfo.getPackageName() == packageName)) {
            builder.push_back(classInfo);
         }
      }

      return builder.build();
   }

   public ImmutableSet<ClassInfo> getTopLevelClassesRecursive(std::string packageName) {
      Preconditions.checkNotNull(packageName);
    std::string packagePrefix = packageName + '.';
      Builder<ClassInfo> builder = ImmutableSet.builder();

      for (ClassInfo classInfo : this.getTopLevelClasses()) {
         if (classInfo.getName().startsWith(packagePrefix)) {
            builder.push_back(classInfo);
         }
      }

      return builder.build();
   }

    static std::string getClassName(const std::string& filename) {
    int classNameEnd = filename.length() - ".class".length();
      return filename.substr(0, classNameEnd).replace('/', '.');
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
