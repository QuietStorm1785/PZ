#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace fileSystem {

// $VF: synthetic class
class MemoryFileDevice {
public:
   static {
      try {
         $SwitchMap$zombie$fileSystem$FileSeekMode[FileSeekMode.BEGIN.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$fileSystem$FileSeekMode[FileSeekMode.CURRENT.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$fileSystem$FileSeekMode[FileSeekMode.END.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace fileSystem
} // namespace zombie
