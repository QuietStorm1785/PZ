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
   Class<? : public Object> m_class;
    std::string m_filename;

    public FileTask_ParseXML(Class<? extends, const std::string& var2, IFileTaskCallback var3, FileSystem var4) {
      super(var4, var3);
      this.m_class = var1;
      this.m_filename = var2;
   }

    std::string getErrorMessage() {
      return this.m_filename;
   }

    void done() {
      this.m_class = nullptr;
      this.m_filename = nullptr;
   }

    void* call() {
      return PZXmlUtil.parse(this.m_class, this.m_filename);
   }
}
} // namespace asset
} // namespace zombie
