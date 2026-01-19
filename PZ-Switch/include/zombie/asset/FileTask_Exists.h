#pragma once
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include <cstdint>
#include <fstream>
#include <iostream>
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

class FileTask_Exists : public FileTask {
public:
 std::string fileName;

public
 FileTask_Exists(std::string_view string,
 IFileTaskCallback iFileTaskCallback, FileSystem fileSystem) {
 super(fileSystem, iFileTaskCallback);
 this->fileName = string;
 }

 void done() {}

 void *call() { return new File(this->fileName).exists(); }
}
} // namespace asset
} // namespace zombie
