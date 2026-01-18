#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace asset {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FileTask_Exists : public FileTask {
public:
 std::string fileName;

 public FileTask_Exists(const std::string& string, IFileTaskCallback iFileTaskCallback, FileSystem fileSystem) {
 super(fileSystem, iFileTaskCallback);
 this->fileName = string;
 }

 void done() {
 }

 void* call() {
 return new File(this->fileName).exists();
 }
}
} // namespace asset
} // namespace zombie
