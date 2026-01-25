#include <string>
#include "zombie/fileSystem/MemoryFileDevice$MemoryFile.h"

namespace zombie {
namespace fileSystem {

bool MemoryFileDevice$MemoryFile::open(const std::string& var1, int var2) {
    // Write logic based on Java/header
    if (m_buffer) return false;
    m_write = (var2 & 2) != 0;
    if (m_file) {
        if (m_file->open(var1, var2)) {
            if ((var2 & 1) != 0) {
                m_size = m_file->size();
                m_buffer.resize(static_cast<size_t>(m_size));
                m_file->read(m_buffer.data(), m_size);
                m_pos = 0;
            }
            return true;
        }
    } else if ((var2 & 2) != 0) {
        return true;
    }
    return false;
}
}

void MemoryFileDevice$MemoryFile::close() {
    if (m_file) {
        if (m_write) {
            m_file->seek(FileSeekMode::BEGIN, 0);
            m_file->write(m_buffer.data(), m_size);
        }
        m_file->close();
    }
    m_buffer.clear();
}
}

bool MemoryFileDevice$MemoryFile::read(uint8_t* var1, long var2) {
    long toRead = (m_pos + var2 < m_size) ? var2 : (m_size - m_pos);
    std::copy(m_buffer.begin() + m_pos, m_buffer.begin() + m_pos + toRead, var1);
    m_pos += toRead;
    return toRead > 0;
}
}

bool MemoryFileDevice$MemoryFile::write(const uint8_t* var1, long var2) {
    long cur = m_pos;
    long cap = m_buffer.size();
    long sz = m_size;
    if (cur + var2 > cap) {
        long newCap = std::max(cap * 2, cur + var2);
        m_buffer.resize(static_cast<size_t>(newCap));
    }
    std::copy(var1, var1 + var2, m_buffer.begin() + cur);
    m_pos += var2;
    m_size = std::max(cur + var2, sz);
    return true;
}
}

long MemoryFileDevice$MemoryFile::size() {
    return m_size;
}
}

bool MemoryFileDevice$MemoryFile::seek(FileSeekMode var1, long var2) {
    switch (var1) {
        case FileSeekMode::BEGIN:
            if (var2 > m_size) return false;
            m_pos = var2;
            break;
        case FileSeekMode::CURRENT:
            if (0 > m_pos + var2 || m_pos + var2 > m_size) return false;
            m_pos += var2;
            break;
        case FileSeekMode::END:
            if (var2 > m_size) return false;
            m_pos = m_size - var2;
            break;
    }
    bool ok = m_pos <= m_size;
    m_pos = std::min(m_pos, m_size);
    return ok;
}
}

long MemoryFileDevice$MemoryFile::pos() {
    return m_pos;
}
}

InputStream MemoryFileDevice$MemoryFile::getInputStream() {
    return m_file ? m_file->getInputStream() : nullptr;
}
}

IFileDevice MemoryFileDevice$MemoryFile::getDevice() {
    return m_device;
}
}

void MemoryFileDevice$MemoryFile::release() {
    m_buffer.clear();
}
}

} // namespace fileSystem
} // namespace zombie
