#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/fileSystem/MemoryFileDevice/1.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {



class MemoryFileDevice$MemoryFile {
public:
   std::shared_ptr<MemoryFileDevice> m_device;
   std::vector<uint8_t> m_buffer;
   int64_t m_size;
   int64_t m_pos;
   IFile m_file;
   bool m_write;

   MemoryFileDevice$MemoryFile(IFile file, std::shared_ptr<MemoryFileDevice> device)
      : m_device(device), m_size(0), m_pos(0), m_file(file), m_write(false) {}

   bool open(const std::string& path, int mode) {
      if (!m_buffer.empty()) {
         throw std::runtime_error("Buffer already initialized");
      }
      m_write = (mode & 2) != 0;
      if (m_file) {
         if (m_file->open(path, mode)) {
            if ((mode & 1) != 0) {
               m_size = m_file->size();
               m_buffer.resize(static_cast<size_t>(m_size));
               m_file->read(m_buffer.data(), m_size);
               m_pos = 0;
            }
            return true;
         }
      } else if ((mode & 2) != 0) {
         return true;
      }
      return false;
   }

   void close() {
      if (m_file) {
         if (m_write) {
            m_file->seek(FileSeekMode::BEGIN, 0);
            m_file->write(m_buffer.data(), m_size);
         }
         m_file->close();
      }
      m_buffer.clear();
   }

   bool read(uint8_t* out, int64_t len) {
      int64_t to_read = std::min(len, m_size - m_pos);
      if (to_read > 0) {
         std::copy(m_buffer.begin() + m_pos, m_buffer.begin() + m_pos + to_read, out);
         m_pos += to_read;
         return true;
      }
      return false;
   }

   bool write(const uint8_t* in, int64_t len) {
      int64_t end_pos = m_pos + len;
      if (end_pos > static_cast<int64_t>(m_buffer.size())) {
         m_buffer.resize(static_cast<size_t>(std::max<int64_t>(m_buffer.size() * 2, end_pos)));
      }
      std::copy(in, in + len, m_buffer.begin() + m_pos);
      m_pos += len;
      m_size = std::max(m_size, m_pos);
      return true;
   }

   std::vector<uint8_t>& getBuffer() {
      return m_buffer;
   }

   int64_t size() const {
      return m_size;
   }

   bool seek(FileSeekMode mode, int64_t offset) {
      switch (mode) {
         case FileSeekMode::BEGIN:
            if (offset > m_size) throw std::runtime_error("Seek out of bounds");
            m_pos = offset;
            break;
         case FileSeekMode::CURRENT:
            if (m_pos + offset < 0 || m_pos + offset > m_size) throw std::runtime_error("Seek out of bounds");
            m_pos += offset;
            break;
         case FileSeekMode::END:
            if (offset > m_size) throw std::runtime_error("Seek out of bounds");
            m_pos = m_size - offset;
            break;
         default:
            return false;
      }
      bool ok = m_pos <= m_size;
      m_pos = std::min(m_pos, m_size);
      return ok;
   }

   int64_t pos() const {
      return m_pos;
   }

   InputStream getInputStream() {
      return m_file ? m_file->getInputStream() : nullptr;
   }

   IFileDevice getDevice() {
      return m_device;
   }

   void release() {
      m_buffer.clear();
   }
};
} // namespace fileSystem
} // namespace zombie
