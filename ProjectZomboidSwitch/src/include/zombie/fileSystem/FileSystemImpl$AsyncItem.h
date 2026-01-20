#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace fileSystem {


class FileSystemImpl {
public:
    int m_id;
    FileTask m_task;
   FutureTask<Object> m_future;

   private FileSystemImpl$AsyncItem() {
   }
}
} // namespace fileSystem
} // namespace zombie
