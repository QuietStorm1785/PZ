#include <string>
#include "zombie/fileSystem/DeviceList.h"

namespace zombie {
namespace fileSystem {

void DeviceList::add(IFileDevice var1) {
    // Add device to the internal list
    m_devices.push_back(var1);
}

IFile DeviceList::createFile() {
    // Create a file using the first device in the list
    if (!m_devices.empty()) {
        return m_devices.front()->createFile(nullptr);
    }
    return nullptr;
}

InputStream DeviceList::createStream(const std::string& var1) {
    // Create a stream using the first device in the list
    if (!m_devices.empty()) {
        return m_devices.front()->createStream(var1, nullptr);
    }
    return nullptr;
}

} // namespace fileSystem
} // namespace zombie
