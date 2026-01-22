#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {


class DeviceList {
public:
   private const IFileDevice[] m_devices = new IFileDevice[8];

    void add(IFileDevice var1) {
      for (int var2 = 0; var2 < this.m_devices.length; var2++) {
         if (this.m_devices[var2] == nullptr) {
            this.m_devices[var2] = var1;
            break;
         }
      }
   }

    IFile createFile() {
    IFile var1 = nullptr;

      for (int var2 = 0; var2 < this.m_devices.length && this.m_devices[var2] != nullptr; var2++) {
         var1 = this.m_devices[var2].createFile(var1);
      }

    return var1;
   }

    InputStream createStream(const std::string& var1) {
    InputStream var2 = nullptr;

      for (int var3 = 0; var3 < this.m_devices.length && this.m_devices[var3] != nullptr; var3++) {
         var2 = this.m_devices[var3].createStream(var1, var2);
      }

    return var2;
   }
}
} // namespace fileSystem
} // namespace zombie
