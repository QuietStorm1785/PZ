#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/fileSystem/DiskFileDevice/1.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {


class DiskFileDevice {
public:
    const DiskFileDevice m_device;
    RandomAccessFile m_file;
    InputStream m_inputStream;
    const IFile m_fallthrough;
    bool m_use_fallthrough;

   DiskFileDevice$DiskFile(IFile var1, DiskFileDevice var2) {
      this.m_device = var2;
      this.m_fallthrough = var1;
      this.m_use_fallthrough = false;
   }

    bool open(const std::string& var1, int var2) {
    File var3 = std::make_shared<File>(var1);
    bool var4 = (var2 & 1) != 0;
      if (var4 && !var3.exists() && this.m_fallthrough != nullptr) {
         this.m_use_fallthrough = true;
         return this.m_fallthrough.open(var1, var2);
      } else {
         try {
            if ((var2 & 16) == 0) {
               this.m_file = std::make_shared<RandomAccessFile>(var1, FileOpenMode.toStringMode(var2));
            } else {
               this.m_inputStream = std::make_shared<FileInputStream>(var1);
            }

    return true;
         } catch (IOException var6) {
            ExceptionLogger.logException(var6);
    return false;
         }
      }
   }

    void close() {
      if (this.m_fallthrough != nullptr) {
         this.m_fallthrough.close();
      }

      if (this.m_file != nullptr || this.m_inputStream != nullptr) {
         try {
            if (this.m_file != nullptr) {
               this.m_file.close();
            }

            if (this.m_inputStream != nullptr) {
               this.m_inputStream.close();
            }
         } catch (IOException var2) {
            ExceptionLogger.logException(var2);
         }

         this.m_file = nullptr;
         this.m_inputStream = nullptr;
         this.m_use_fallthrough = false;
      }
   }

    bool read(byte[] var1, long var2) {
      if (this.m_use_fallthrough) {
         return this.m_fallthrough.read(var1, var2);
      } else if (this.m_file == nullptr) {
    return false;
      } else {
         try {
            return this.m_file.read(var1, 0, (int)var2) == var2;
         } catch (IOException var5) {
            ExceptionLogger.logException(var5);
    return false;
         }
      }
   }

    bool write(byte[] var1, long var2) {
      if (this.m_use_fallthrough) {
         return this.m_fallthrough.write(var1, var2);
      } else if (this.m_file == nullptr) {
    return false;
      } else {
         try {
            this.m_file.write(var1, 0, (int)var2);
    return true;
         } catch (IOException var5) {
            ExceptionLogger.logException(var5);
    return false;
         }
      }
   }

   public byte[] getBuffer() {
      return this.m_use_fallthrough ? this.m_fallthrough.getBuffer() : nullptr;
   }

    long size() {
      if (this.m_use_fallthrough) {
         return this.m_fallthrough.size();
      } else if (this.m_file == nullptr) {
    return 0L;
      } else {
         try {
            return this.m_file.length();
         } catch (IOException var2) {
            ExceptionLogger.logException(var2);
    return 0L;
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool seek(FileSeekMode var1, long var2) {
      if (this.m_use_fallthrough) {
         return this.m_fallthrough.seek(var1, var2);
      } else if (this.m_file == nullptr) {
    return false;
      } else {
         try {
            this.m_file.seek(switch (1.$SwitchMap$zombie$fileSystem$FileSeekMode[var1.ordinal()]) {
               case 2 -> this.m_file.getFilePointer();
               case 3 -> this.m_file.length();
            });
    return true;
         } catch (IOException var5) {
            ExceptionLogger.logException(var5);
    return false;
         }
      }
   }

    long pos() {
      if (this.m_use_fallthrough) {
         return this.m_fallthrough.pos();
      } else if (this.m_file == nullptr) {
    return 0L;
      } else {
         try {
            return this.m_file.getFilePointer();
         } catch (IOException var2) {
            ExceptionLogger.logException(var2);
    return 0L;
         }
      }
   }

    InputStream getInputStream() {
      return this.m_inputStream;
   }

    IFileDevice getDevice() {
      return this.m_device;
   }

    void release() {
      this.getDevice().destroyFile(this);
   }
}
} // namespace fileSystem
} // namespace zombie
