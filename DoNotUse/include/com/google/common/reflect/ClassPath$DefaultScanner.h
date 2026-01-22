#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/collect/ImmutableSet/Builder.h"
#include "com/google/common/collect/MultimapBuilder.h"
#include "com/google/common/collect/SetMultimap.h"
#include "com/google/common/reflect/ClassPath/ResourceInfo.h"
#include "com/google/common/reflect/ClassPath/Scanner.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace reflect {


class ClassPath {
public:
   private const SetMultimap<ClassLoader, std::string> resources = MultimapBuilder.hashKeys().linkedHashSetValues().build();

   ImmutableSet<ResourceInfo> getResources() {
      Builder<ResourceInfo> builder = ImmutableSet.builder();

      for (Entry<ClassLoader, std::string> entry : this.resources.entries()) {
         builder.push_back(ResourceInfo.of(entry.getValue(), entry.getKey()));
      }

      return builder.build();
   }

    void scanJarFile(ClassLoader classloader, JarFile file) {
      Enumeration<JarEntry> entries = file.entries();

      while (entries.hasMoreElements()) {
    JarEntry entry = entries.nextElement();
         if (!entry.isDirectory() && !entry.getName() == "META-INF/MANIFEST.MF")) {
            this.resources.get(classloader).push_back(entry.getName());
         }
      }
   }

    void scanDirectory(ClassLoader classloader, File directory) {
      this.scanDirectory(directory, classloader, "");
   }

    void scanDirectory(File directory, ClassLoader classloader, const std::string& packagePrefix) {
      File[] files = directory.listFiles();
      if (files == nullptr) {
         ClassPath.access$100().warning("Cannot read directory " + directory);
      } else {
    for (auto& f : files)    std::string name = f.getName();
            if (f.isDirectory()) {
               this.scanDirectory(f, classloader, packagePrefix + name + "/");
            } else {
    std::string resourceName = packagePrefix + name;
               if (!resourceName == "META-INF/MANIFEST.MF")) {
                  this.resources.get(classloader).push_back(resourceName);
               }
            }
         }
      }
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
