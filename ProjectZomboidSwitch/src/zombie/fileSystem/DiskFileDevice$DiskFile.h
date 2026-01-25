
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include "zombie/fileSystem/DiskFileDevice$1.h"
#include <fstream>
#include <iostream>
#include "zombie/core/logger/ExceptionLogger.h"

namespace zombie::fileSystem {

class RandomAccessFile; // Forward declaration
class FileInputStream;  // Forward declaration
class IFile;
class IFileDevice;
enum class FileSeekMode;

// DiskFileDevice$DiskFile implements IFile
class DiskFileDevice$DiskFile : public IFile {
public:
    std::shared_ptr<IFileDevice> m_device;
    std::shared_ptr<RandomAccessFile> m_file;
    std::shared_ptr<FileInputStream> m_inputStream;
    std::shared_ptr<IFile> m_fallthrough;
    bool m_use_fallthrough;

    DiskFileDevice$DiskFile(std::shared_ptr<IFile> fallthrough, std::shared_ptr<IFileDevice> device)
        : m_device(device), m_fallthrough(fallthrough), m_use_fallthrough(false) {}

    bool open(const std::string& path, int mode) override;
    void close() override;
    bool read(uint8_t* buffer, int64_t length) override;
    bool write(const uint8_t* buffer, int64_t length) override;
    int64_t size() const override;
    bool seek(FileSeekMode mode, int64_t offset) override;
    int64_t pos() const override;
    std::shared_ptr<FileInputStream> getInputStream() override;
    std::shared_ptr<IFileDevice> getDevice() override;
    void release() override;
};

} // namespace zombie::fileSystem
