#pragma once
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace fileSystem {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class MemoryFileDevice {
public:
  IFile createFile(IFile iFile) {
    return new MemoryFileDevice.MemoryFile(iFile, this);
  }

  void destroyFile(IFile var1) {}

  InputStream createStream(const std::string &var1, InputStream var2) {
    return null;
  }

  void destroyStream(InputStream var1) {}

  std::string name() { return "memory"; }

private
  static class MemoryFile implements IFile {
    const MemoryFileDevice m_device;
    byte[] m_buffer;
    long m_size;
    long m_pos;
    IFile m_file;
    bool m_write;

    MemoryFile(IFile iFile, MemoryFileDevice memoryFileDevice) {
      this.m_device = memoryFileDevice;
      this.m_buffer = nullptr;
      this.m_size = 0L;
      this.m_pos = 0L;
      this.m_file = iFile;
      this.m_write = false;
    }

    bool open(const std::string &string, int int0) {
      assert this.m_buffer == nullptr;

      this.m_write = (int0 & 2) != 0;
      if (this.m_file != nullptr) {
        if (this.m_file.open(string, int0)) {
          if ((int0 & 1) != 0) {
            this.m_size = this.m_file.size();
            this.m_buffer = new byte[(int)this.m_size];
            this.m_file.read(this.m_buffer, this.m_size);
            this.m_pos = 0L;
          }

          return true;
        }
      } else if ((int0 & 2) != 0) {
        return true;
      }

      return false;
    }

    void close() {
      if (this.m_file != nullptr) {
        if (this.m_write) {
          this.m_file.seek(FileSeekMode.BEGIN, 0L);
          this.m_file.write(this.m_buffer, this.m_size);
        }

        this.m_file.close();
      }

      this.m_buffer = nullptr;
    }

    bool read(byte[] bytes, long long1) {
      long long0 =
          this.m_pos + long1 < this.m_size ? long1 : this.m_size - this.m_pos;
      System.arraycopy(this.m_buffer, (int)this.m_pos, bytes, 0, (int)long0);
      this.m_pos += long0;
      return false;
    }

    bool write(byte[] bytes, long long3) {
      long long0 = this.m_pos;
      long long1 = this.m_buffer.length;
      long long2 = this.m_size;
      if (long0 + long3 > long1) {
        long long4 = Math.max(long1 * 2L, long0 + long3);
        this.m_buffer = Arrays.copyOf(this.m_buffer, (int)long4);
      }

      System.arraycopy(bytes, 0, this.m_buffer, (int)long0, (int)long3);
      this.m_pos += long3;
      this.m_size = long0 + long3 > long2 ? long0 + long3 : long2;
      return true;
    }

  public
    byte[] getBuffer() { return this.m_buffer; }

    long size() { return this.m_size; }

    bool seek(FileSeekMode fileSeekMode, long long0) {
      switch (fileSeekMode) {
      case BEGIN:
        assert long0 <= this.m_size;

        this.m_pos = long0;
        break;
      case CURRENT:
        assert 0L <= this.m_pos + long0 &&this.m_pos + long0 <= this.m_size;

        this.m_pos += long0;
        break;
      case END:
        assert long0 <= this.m_size;

        this.m_pos = this.m_size - long0;
      }

      bool boolean0 = this.m_pos <= this.m_size;
      this.m_pos = Math.min(this.m_pos, this.m_size);
      return boolean0;
    }

    long pos() { return this.m_pos; }

    InputStream getInputStream() {
      return this.m_file != nullptr ? this.m_file.getInputStream() : nullptr;
    }

    IFileDevice getDevice() { return this.m_device; }

    void release() { this.m_buffer = nullptr; }
  }
}
} // namespace fileSystem
} // namespace zombie
