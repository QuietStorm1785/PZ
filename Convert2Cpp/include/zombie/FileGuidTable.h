#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/bind/annotation/XmlTransient.h"

namespace zombie {


class FileGuidTable {
public:
   public final ArrayList<FileGuidPair> files = std::make_unique<ArrayList<>>();
   private final Map<String, String> guidToPath = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
   private final Map<String, String> pathToGuid = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);

    void setModID(const std::string& var1) {
      for (FileGuidPair var3 : this.files) {
         var3.guid = var1 + "-" + var3.guid;
      }
   }

    void mergeFrom(FileGuidTable var1) {
      this.files.addAll(var1.files);
   }

    void loaded() {
      for (FileGuidPair var2 : this.files) {
         this.guidToPath.put(var2.guid, var2.path);
         this.pathToGuid.put(var2.path, var2.guid);
      }
   }

    void clear() {
      this.files.clear();
      this.guidToPath.clear();
      this.pathToGuid.clear();
   }

    std::string getFilePathFromGuid(const std::string& var1) {
      return this.guidToPath.get(var1);
   }

    std::string getGuidFromFilePath(const std::string& var1) {
      return this.pathToGuid.get(var1);
   }
}
} // namespace zombie
