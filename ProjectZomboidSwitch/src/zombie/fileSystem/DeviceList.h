
#pragma once
#include <string>
#include <array>
#include <memory>

namespace zombie::fileSystem {

class IFileDevice;
class IFile;
class FileInputStream;

class DeviceList {
public:
   static constexpr size_t MaxDevices = 8;
   std::array<std::shared_ptr<IFileDevice>, MaxDevices> m_devices{};

   void add(const std::shared_ptr<IFileDevice>& device) {
      for (auto& slot : m_devices) {
         if (!slot) {
            slot = device;
            break;
         }
      }
   }

   std::shared_ptr<IFile> createFile() {
      std::shared_ptr<IFile> file = nullptr;
      for (const auto& device : m_devices) {
         if (!device) break;
         file = device->createFile(file);
      }
      return file;
   }

   std::shared_ptr<FileInputStream> createStream(const std::string& name) {
      std::shared_ptr<FileInputStream> stream = nullptr;
      for (const auto& device : m_devices) {
         if (!device) break;
         stream = device->createStream(name, stream);
      }
      return stream;
   }
};

} // namespace zombie::fileSystem
