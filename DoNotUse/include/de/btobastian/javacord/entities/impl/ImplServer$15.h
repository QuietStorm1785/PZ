#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$15(ImplServer var1) {
      this.this$0 = var1;
   }

   public byte[] call() throws Exception {
      byte[] imageAsBytes = (byte[])this.this$0.getIconAsByteArray().get();
      return imageAsBytes.length == 0 ? nullptr : imageAsBytes;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
