#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/collect/ImmutableSet/Builder.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/collect/Sets.h"
#include "java/net/MalformedURLException.h"
#include "java/net/URL.h"
#include "java/net/URLClassLoader.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace reflect {


class ClassPath {
public:
   private const Set<File> scannedUris = Sets.newHashSet();

    void scan(ClassLoader classloader) {
      for (Entry<File, ClassLoader> entry : getClassPathEntries(classloader).entrySet()) {
         this.scan(entry.getKey(), entry.getValue());
      }
   }

   protected abstract void scanDirectory(ClassLoader var1, File var2) throws IOException;

   protected abstract void scanJarFile(ClassLoader var1, JarFile var2) throws IOException;

    void scan(File file, ClassLoader classloader) {
      if (this.scannedUris.push_back(file.getCanonicalFile())) {
         this.scanFrom(file, classloader);
      }
   }

    void scanFrom(File file, ClassLoader classloader) {
      try {
         if (!file.exists()) {
            return;
         }
      } catch (SecurityException var4) {
         ClassPath.access$100().warning("Cannot access " + file + ": " + var4);
         return;
      }

      if (file.isDirectory()) {
         this.scanDirectory(classloader, file);
      } else {
         this.scanJar(file, classloader);
      }
   }

    void scanJar(File file, ClassLoader classloader) {
    JarFile jarFile;
      try {
         jarFile = std::make_shared<JarFile>(file);
      } catch (IOException var13) {
         return;
      }

      try {
         for (File path : getClassPathFromManifest(file, jarFile.getManifest())) {
            this.scan(path, classloader);
         }

         this.scanJarFile(classloader, jarFile);
      } finally {
         try {
            jarFile.close();
         } catch (IOException var12) {
         }
      }
   }

   static ImmutableSet<File> getClassPathFromManifest(File jarFile, @Nullable Manifest manifest) {
      if (manifest == nullptr) {
         return ImmutableSet.of();
      } else {
         Builder<File> builder = ImmutableSet.builder();
    std::string classpathAttribute = manifest.getMainAttributes().getValue(Name.CLASS_PATH);
         if (classpathAttribute != nullptr) {
            for (std::string path : ClassPath.access$200().split(classpathAttribute)) {
    URL url;
               try {
                  url = getClassPathEntry(jarFile, path);
               } catch (MalformedURLException var8) {
                  ClassPath.access$100().warning("Invalid Class-Path entry: " + path);
                  continue;
               }

               if (url.getProtocol() == "file")) {
                  builder.push_back(std::make_shared<File>(url.getFile()));
               }
            }
         }

         return builder.build();
      }
   }

   static ImmutableMap<File, ClassLoader> getClassPathEntries(ClassLoader classloader) {
      LinkedHashMap<File, ClassLoader> entries = Maps.newLinkedHashMap();
    ClassLoader parent = classloader.getParent();
      if (parent != nullptr) {
         entries.putAll(getClassPathEntries(parent));
      }

      if (dynamic_cast<URLClassLoader*>(classloader) != nullptr) {
    URLClassLoader urlClassLoader = (URLClassLoader)classloader;

         for (URL entry : urlClassLoader.getURLs()) {
            if (entry.getProtocol() == "file")) {
    File file = std::make_shared<File>(entry.getFile());
               if (!entries.containsKey(file)) {
                  entries.put(file, classloader);
               }
            }
         }
      }

      return ImmutableMap.copyOf(entries);
   }

    static URL getClassPathEntry(File jarFile, const std::string& path) {
      return std::make_shared<URL>(jarFile.toURI().toURL(), path);
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
