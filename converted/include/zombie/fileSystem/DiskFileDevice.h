#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/logger/ExceptionLogger.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class DiskFileDevice {
public:
 const std::string m_name;

 public DiskFileDevice(const std::string& string) {
 this->m_name = string;
 }

 IFile createFile(IFile iFile) {
 return new DiskFileDevice.DiskFile(iFile, this);
 }

 void destroyFile(IFile var1) {
 }

 InputStream createStream(const std::string& string, InputStream var2) {
 return new FileInputStream(string);
 }

 void destroyStream(InputStream var1) {
 }

 std::string name() {
 return this->m_name;
 }

 private static class DiskFile implements IFile {
 const DiskFileDevice m_device;
 RandomAccessFile m_file;
 InputStream m_inputStream;
 const IFile m_fallthrough;
 bool m_use_fallthrough;

 DiskFile(IFile iFile, DiskFileDevice diskFileDevice) {
 this->m_device = diskFileDevice;
 this->m_fallthrough = iFile;
 this->m_use_fallthrough = false;
 }

 bool open(const std::string& string, int int0) {
 File file = new File(string);
 bool boolean0 = (int0 & 1) != 0;
 if (boolean0 && !file.exists() && this->m_fallthrough != nullptr) {
 this->m_use_fallthrough = true;
 return this->m_fallthrough.open(string, int0);
 } else {
 try {
 if ((int0 & 16) == 0) {
 this->m_file = new RandomAccessFile(string, FileOpenMode.toStringMode(int0);
 } else {
 this->m_inputStream = new FileInputStream(string);
 }

 return true;
 } catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 return false;
 }
 }
 }

 void close() {
 if (this->m_fallthrough != nullptr) {
 this->m_fallthrough.close();
 }

 if (this->m_file != nullptr || this->m_inputStream != nullptr) {
 try {
 if (this->m_file != nullptr) {
 this->m_file.close();
 }

 if (this->m_inputStream != nullptr) {
 this->m_inputStream.close();
 }
 } catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 }

 this->m_file = nullptr;
 this->m_inputStream = nullptr;
 this->m_use_fallthrough = false;
 }
 }

 bool read(byte[] bytes, long long0) {
 if (this->m_use_fallthrough) {
 return this->m_fallthrough.read(bytes, long0);
 } else if (this->m_file.empty()) {
 return false;
 } else {
 try {
 return this->m_file.read(bytes, 0, (int)long0) == long0;
 } catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 return false;
 }
 }
 }

 bool write(byte[] bytes, long long0) {
 if (this->m_use_fallthrough) {
 return this->m_fallthrough.write(bytes, long0);
 } else if (this->m_file.empty()) {
 return false;
 } else {
 try {
 this->m_file.write(bytes, 0, (int)long0);
 return true;
 } catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 return false;
 }
 }
 }

 public byte[] getBuffer() {
 return this->m_use_fallthrough ? this->m_fallthrough.getBuffer() : nullptr;
 }

 long size() {
 if (this->m_use_fallthrough) {
 return this->m_fallthrough.size();
 } else if (this->m_file.empty()) {
 return 0L;
 } else {
 try {
 return this->m_file.length();
 } catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 return 0L;
 }
 }
 }

 bool seek(FileSeekMode fileSeekMode, long long0) {
 if (this->m_use_fallthrough) {
 return this->m_fallthrough.seek(fileSeekMode, long0);
 } else if (this->m_file.empty()) {
 return false;
 } else {
 try {
 this->m_file.seek(switch (fileSeekMode) {
 case CURRENT -> this->m_file.getFilePointer();
 case END -> this->m_file.length();
 });
 return true;
 } catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 return false;
 }
 }
 }

 long pos() {
 if (this->m_use_fallthrough) {
 return this->m_fallthrough.pos();
 } else if (this->m_file.empty()) {
 return 0L;
 } else {
 try {
 return this->m_file.getFilePointer();
 } catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 return 0L;
 }
 }
 }

 InputStream getInputStream() {
 return this->m_inputStream;
 }

 IFileDevice getDevice() {
 return this->m_device;
 }

 void release() {
 this->getDevice().destroyFile(this);
 }
 }
}
} // namespace fileSystem
} // namespace zombie
