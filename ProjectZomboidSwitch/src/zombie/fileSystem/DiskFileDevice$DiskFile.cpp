#include <string>
#include "zombie/fileSystem/DiskFileDevice$DiskFile.h"

namespace zombie {
namespace fileSystem {

bool DiskFileDevice$DiskFile::open(const std::string& var1, int var2) {
    // Check if READ flag is set and file does not exist, use fallthrough if available
    bool readFlag = (var2 & 1) != 0;
    std::ifstream testFile(var1);
    bool exists = testFile.good();
    testFile.close();
    if (readFlag && !exists && m_fallthrough) {
        m_use_fallthrough = true;
        return m_fallthrough->open(var1, var2);
    } else {
        try {
            if ((var2 & 16) == 0) {
                // Not a stream: open for read/write
                m_file = std::make_shared<RandomAccessFile>(var1, FileOpenMode::toStringMode(var2));
            } else {
                // Stream mode
                m_inputStream = std::make_shared<FileInputStream>(var1);
            }
            return true;
        } catch (const std::exception& ex) {
            ExceptionLogger::logException(ex);
            return false;
        }
    }
}

void DiskFileDevice$DiskFile::close() {
    // Close fallthrough if used
    if (m_fallthrough) {
        m_fallthrough->close();
    }

    // Close file and input stream if they exist
    try {
        if (m_file) {
            m_file->close();
        }
        if (m_inputStream) {
            m_inputStream->close();
        }
    } catch (const std::exception& ex) {
        ExceptionLogger::logException(ex);
    }

    m_file.reset();
    m_inputStream.reset();
    m_use_fallthrough = false;
}

bool DiskFileDevice$DiskFile::read(byte[] var1, long var2) {
    // If using fallthrough, delegate read
    if (m_use_fallthrough && m_fallthrough) {
        return m_fallthrough->read(var1, var2);
    }

    try {
        if (m_file) {
            // RandomAccessFile read
            return m_file->read(var1, var2);
        } else if (m_inputStream) {
            // FileInputStream read
            return m_inputStream->read(var1, var2);
        }
    } catch (const std::exception& ex) {
        ExceptionLogger::logException(ex);
    }
    return false;
}

bool DiskFileDevice$DiskFile::write(byte[] var1, long var2) {
    // If using fallthrough, delegate write
    if (m_use_fallthrough && m_fallthrough) {
        return m_fallthrough->write(var1, var2);
    }

    try {
        if (m_file) {
            // RandomAccessFile write
            return m_file->write(var1, var2);
        }
    } catch (const std::exception& ex) {
        ExceptionLogger::logException(ex);
    }
    return false;
}

long DiskFileDevice$DiskFile::size() {
    // If using fallthrough, delegate size
    if (m_use_fallthrough && m_fallthrough) {
        return m_fallthrough->size();
    }
    try {
        if (m_file) {
            return m_file->size();
        }
    } catch (const std::exception& ex) {
        ExceptionLogger::logException(ex);
    }
    return 0;
}

bool DiskFileDevice$DiskFile::seek(FileSeekMode var1, long var2) {
    // If using fallthrough, delegate seek
    if (m_use_fallthrough && m_fallthrough) {
        return m_fallthrough->seek(var1, var2);
    }
    try {
        if (m_file) {
            return m_file->seek(var1, var2);
        }
    } catch (const std::exception& ex) {
        ExceptionLogger::logException(ex);
    }
    return false;
}

long DiskFileDevice$DiskFile::pos() {
    // If using fallthrough, delegate pos
    if (m_use_fallthrough && m_fallthrough) {
        return m_fallthrough->pos();
    }
    try {
        if (m_file) {
            return m_file->pos();
        }
    } catch (const std::exception& ex) {
        ExceptionLogger::logException(ex);
    }
    return 0;
}

InputStream DiskFileDevice$DiskFile::getInputStream() {
    // If using fallthrough, delegate getInputStream
    if (m_use_fallthrough && m_fallthrough) {
        return m_fallthrough->getInputStream();
    }
    if (m_inputStream) {
        return m_inputStream.get();
    }
    return nullptr;
}

IFileDevice DiskFileDevice$DiskFile::getDevice() {
    // If using fallthrough, delegate getDevice
    if (m_use_fallthrough && m_fallthrough) {
        return m_fallthrough->getDevice();
    }
    return this;
}

void DiskFileDevice$DiskFile::release() {
    // If using fallthrough, delegate release
    if (m_use_fallthrough && m_fallthrough) {
        m_fallthrough->release();
        return;
    }
    // Release file and input stream
    m_file.reset();
    m_inputStream.reset();
    m_use_fallthrough = false;
}

} // namespace fileSystem
} // namespace zombie
