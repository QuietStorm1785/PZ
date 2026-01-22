#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/network/ServerChunkLoader/SaveTask.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class ServerChunkLoader {
public:
   private byte[] bytes;

   public ServerChunkLoader$SaveGameTimeTask(ServerChunkLoader var1, GameTime var2) {
      this.this$0 = var1;

      try {
         try (
    ByteArrayOutputStream var3 = std::make_shared<ByteArrayOutputStream>(32768);
    DataOutputStream var4 = std::make_shared<DataOutputStream>(var3);
         ) {
            var2.save(var4);
            var4.close();
            this.bytes = var3.toByteArray();
         }
      } catch (Exception var11) {
         var11.printStackTrace();
      }
   }

    void save() {
      if (this.bytes != nullptr) {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_t.bin");

         try (FileOutputStream var2 = std::make_shared<FileOutputStream>(var1)) {
            var2.write(this.bytes);
         } catch (Exception var7) {
            var7.printStackTrace();
            return;
         }
      }
   }

    void release() {
   }

    int wx() {
    return 0;
   }

    int wy() {
    return 0;
   }
}
} // namespace network
} // namespace zombie
