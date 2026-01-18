#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "jassimp/AiPostProcessSteps.h"
#include "jassimp/Jassimp.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include <algorithm>

namespace zombie {
namespace asset {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FileTask_LoadAiScene : public FileTask {
public:
 std::string m_filename;
 EnumSet<AiPostProcessSteps> m_post_process_step_set;

 public FileTask_LoadAiScene(const std::string& string, EnumSet<AiPostProcessSteps> enumSet, IFileTaskCallback iFileTaskCallback, FileSystem fileSystem) {
 super(fileSystem, iFileTaskCallback);
 this->m_filename = string;
 this->m_post_process_step_set = enumSet;
 }

 std::string getErrorMessage() {
 return this->m_filename;
 }

 void done() {
 this->m_filename = nullptr;
 this->m_post_process_step_set = nullptr;
 }

 void* call() {
 return Jassimp.importFile(this->m_filename, this->m_post_process_step_set);
 }
}
} // namespace asset
} // namespace zombie
