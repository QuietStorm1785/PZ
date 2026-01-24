#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include "zombie/util/PZXmlUtil.h"

namespace zombie {
namespace asset {


class FileTask_ParseXML : public FileTask {
public:
      // Use type_info to represent the class type at runtime (C++ alternative to Java's Class<?>)
      const std::type_info& m_type;
      std::string m_filename;

      FileTask_ParseXML(const std::type_info& type, const std::string& filename, std::shared_ptr<IFileTaskCallback> callback, std::shared_ptr<FileSystem> fs)
            : FileTask(fs, callback), m_type(type), m_filename(filename) {}

   std::string getErrorMessage() const {
      return m_filename;
   }

   void done() override {
      m_filename.clear();
   }

    void* call() {
      return PZXmlUtil.parse(this.m_class, this.m_filename);
   }
}
} // namespace asset
} // namespace zombie
