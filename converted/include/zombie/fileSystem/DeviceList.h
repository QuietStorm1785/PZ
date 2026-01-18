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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class DeviceList {
public:
 private IFileDevice[] m_devices = new IFileDevice[8];

 void add(IFileDevice device) {
 for (int int0 = 0; int0 < this->m_devices.length; int0++) {
 if (this->m_devices[int0] == nullptr) {
 this->m_devices[int0] = device;
 break;
 }
 }
 }

 IFile createFile() {
 IFile iFile = nullptr;

 for (int int0 = 0; int0 < this->m_devices.length && this->m_devices[int0] != nullptr; int0++) {
 iFile = this->m_devices[int0].createFile(iFile);
 }

 return iFile;
 }

 InputStream createStream(const std::string& path) {
 InputStream inputStream = nullptr;

 for (int int0 = 0; int0 < this->m_devices.length && this->m_devices[int0] != nullptr; int0++) {
 inputStream = this->m_devices[int0].createStream(path, inputStream);
 }

 return inputStream;
 }
}
} // namespace fileSystem
} // namespace zombie
