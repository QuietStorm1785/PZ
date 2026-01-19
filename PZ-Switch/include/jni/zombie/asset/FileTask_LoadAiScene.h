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


class FileTask_LoadAiScene :  FileTask {
:
    std::string m_filename;
   EnumSet<AiPostProcessSteps> m_post_process_step_set;

     FileTask_LoadAiScene(const std::string& var1, EnumSet<AiPostProcessSteps> var2, IFileTaskCallback var3, FileSystem var4) {
      super(var4, var3);
      this.m_filename = var1;
      this.m_post_process_step_set = var2;
   }

    std::string getErrorMessage() const {
      return this.m_filename;
   }

    void done() {
      this.m_filename = nullptr;
      this.m_post_process_step_set = nullptr;
   }

    void* call() {
      return Jassimp.importFile(this.m_filename, this.m_post_process_step_set);
   }
}
} // namespace asset
} // namespace zombie
