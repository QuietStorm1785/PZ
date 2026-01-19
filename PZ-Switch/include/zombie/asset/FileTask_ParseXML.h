#pragma once
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include "zombie/util/PZXmlUtil.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace asset {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FileTask_ParseXML : public FileTask {
public:
 Class < ? extends Object > m_class;
 std::string m_filename;

public FileTask_ParseXML(Class<? extends, std::string_view string, IFileTaskCallback iFileTaskCallback, FileSystem fileSystem) {
 super(fileSystem, iFileTaskCallback);
 this->m_class = clazz;
 this->m_filename = string;
 }

 std::string getErrorMessage() { return this->m_filename; }

 void done() {
 this->m_class = nullptr;
 this->m_filename = nullptr;
 }

 void *call() { return PZXmlUtil.parse(this->m_class, this->m_filename); }
}
} // namespace asset
} // namespace zombie
