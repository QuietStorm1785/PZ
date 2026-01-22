#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/FinalizableReferenceQueue/FinalizerLoader.h"
#include "java/net/URL.h"
#include "java/net/URLClassLoader.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class FinalizableReferenceQueue {
public:
   private static const std::string LOADING_ERROR = "Could not load Finalizer in its own class loader. Loading Finalizer in the current class loader instead. As a result, you will not be able to garbage collect this class loader. To support reclaiming this class loader, either resolve the underlying issue, or move Guava to your system class path.";

   public Class<?> loadFinalizer() {
      try {
    ClassLoader finalizerLoader = this.newLoader(this.getBaseUrl());
         return finalizerLoader.loadClass("com.google.common.base.internal.Finalizer");
      } catch (Exception var2) {
         FinalizableReferenceQueue.access$000()
            .log(
               Level.WARNING,
               "Could not load Finalizer in its own class loader. Loading Finalizer in the current class loader instead. As a result, you will not be able to garbage collect this class loader. To support reclaiming this class loader, either resolve the underlying issue, or move Guava to your system class path.",
               (Throwable)var2
            );
    return nullptr;
      }
   }

    URL getBaseUrl() {
    std::string finalizerPath = "com.google.common.base.internal.Finalizer".replace('.', '/') + ".class";
    URL finalizerUrl = this.getClass().getClassLoader().getResource(finalizerPath);
      if (finalizerUrl == nullptr) {
         throw FileNotFoundException(finalizerPath);
      } else {
    std::string urlString = finalizerUrl;
         if (!urlString.endsWith(finalizerPath)) {
            throw IOException("Unsupported path style: " + urlString);
         } else {
            urlString = urlString.substr(0, urlString.length() - finalizerPath.length());
            return std::make_shared<URL>(finalizerUrl, urlString);
         }
      }
   }

    URLClassLoader newLoader(URL base) {
      return std::make_shared<URLClassLoader>(new URL[]{base}, nullptr);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
