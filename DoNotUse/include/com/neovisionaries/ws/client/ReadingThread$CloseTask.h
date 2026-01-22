#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/Socket.h"
#include <algorithm>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class ReadingThread {
public:
   private ReadingThread$CloseTask(ReadingThread var1) {
      this.this$0 = var1;
   }

    void run() {
      try {
    Socket socket = ReadingThread.access$100(this.this$0).getSocket();
         socket.close();
      } catch (Throwable var2) {
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
