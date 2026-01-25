
#pragma once
#include <string>
#include <memory>

namespace zombie::fileSystem {

class IFile;
class IFileDevice;
class FileInputStream;
class DiskFileDevice$DiskFile;

// DiskFileDevice implements IFileDevice
class DiskFileDevice : public IFileDevice {
public:
      std::string m_name;

      explicit DiskFileDevice(const std::string& name)
            : m_name(name) {}

      std::shared_ptr<IFile> createFile(std::shared_ptr<IFile> fallthrough) override;
      void destroyFile(std::shared_ptr<IFile> file) override;
      std::shared_ptr<FileInputStream> createStream(const std::string& name, std::shared_ptr<FileInputStream> stream) override;
      void destroyStream(std::shared_ptr<FileInputStream> stream) override;
      std::string name() const override { return m_name; }
};

} // namespace zombie::fileSystem
