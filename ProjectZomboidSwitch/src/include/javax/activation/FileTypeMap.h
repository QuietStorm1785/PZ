#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class FileTypeMap {
public:
    static FileTypeMap defaultMap = nullptr;
   private static Map<ClassLoader, FileTypeMap> map = std::make_unique<WeakHashMap<>>();

   public abstract std::string getContentType(File var1);

   public abstract std::string getContentType(std::string var1);

   public static /* synchronized - TODO: add std::mutex */ void setDefaultFileTypeMap(FileTypeMap fileTypeMap) {
    SecurityManager security = System.getSecurityManager();
      if (security != nullptr) {
         try {
            security.checkSetFactory();
         } catch (SecurityException var4) {
    ClassLoader cl = FileTypeMap.class.getClassLoader();
            if (cl == nullptr || cl.getParent() == nullptr || cl != fileTypeMap.getClass().getClassLoader()) {
    throw var4;
            }
         }
      }

      map.remove(SecuritySupport.getContextClassLoader());
      defaultMap = fileTypeMap;
   }

   public static /* synchronized - TODO: add std::mutex */ FileTypeMap getDefaultFileTypeMap() {
      if (defaultMap != nullptr) {
    return defaultMap;
      } else {
    ClassLoader tccl = SecuritySupport.getContextClassLoader();
    FileTypeMap def = map.get(tccl);
         if (def == nullptr) {
            def = std::make_unique<MimetypesFileTypeMap>();
            map.put(tccl, def);
         }

    return def;
      }
   }
}
} // namespace activation
} // namespace javax
