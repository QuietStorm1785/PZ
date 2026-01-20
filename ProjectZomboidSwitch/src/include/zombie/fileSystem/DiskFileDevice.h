#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/fileSystem/DiskFileDevice/DiskFile.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {


class DiskFileDevice {
public:
    const std::string m_name;

    public DiskFileDevice(const std::string& var1) {
      this.m_name = var1;
   }

    IFile createFile(IFile var1) {
      return std::make_shared<DiskFile>(var1, this);
   }

    void destroyFile(IFile var1) {
   }

    InputStream createStream(const std::string& var1, InputStream var2) {
      return std::make_shared<FileInputStream>(var1);
   }

    void destroyStream(InputStream var1) {
   }

    std::string name() {
      return this.m_name;
   }
}
} // namespace fileSystem
} // namespace zombie
