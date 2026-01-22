#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/MPStatistic/TasksStatistic.h"

namespace zombie {
namespace network {


class MPStatistic {
public:
    int SaveUnloadedTasksAdded = 0;
    int SaveLoadedTasksAdded = 0;
    int SaveGameTimeTasksAdded = 0;
    int QuitThreadTasksAdded = 0;

    void Clear() {
      super.Clear();
      this.SaveUnloadedTasksAdded = 0;
      this.SaveLoadedTasksAdded = 0;
      this.SaveGameTimeTasksAdded = 0;
      this.QuitThreadTasksAdded = 0;
   }

    std::string PrintTitle(const std::string& var1) {
      return var1 + "SaveUnloadedAdded; " + var1 + "SaveLoadedAdded; " + var1 + "SaveGameTimeAdded; " + var1 + "QuitThreadAdded; " + var1 + "Processed; ";
   }

    std::string Print() {
      return this.SaveUnloadedTasksAdded
         + "; "
         + this.SaveLoadedTasksAdded
         + "; "
         + this.SaveGameTimeTasksAdded
         + "; "
         + this.QuitThreadTasksAdded
         + "; "
         + this.processed
         + "; ";
   }

    void SaveUnloadedTasksAdded() {
      this.SaveUnloadedTasksAdded++;
   }

    void SaveLoadedTasksAdded() {
      this.SaveLoadedTasksAdded++;
   }

    void SaveGameTimeTasksAdded() {
      this.SaveGameTimeTasksAdded++;
   }

    void QuitThreadTasksAdded() {
      this.QuitThreadTasksAdded++;
   }
}
} // namespace network
} // namespace zombie
