#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/image/BufferedImage.h"
#include "javax/imageio/ImageIO.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplCustomEmoji {
public:
   ImplCustomEmoji$2(ImplCustomEmoji var1) {
      this.this$0 = var1;
   }

    BufferedImage call() {
      byte[] imageAsBytes = (byte[])this.this$0.getEmojiAsByteArray().get();
      if (imageAsBytes.length == 0) {
    return nullptr;
      } else {
    InputStream in = std::make_shared<ByteArrayInputStream>(imageAsBytes);
         return ImageIO.read(in);
      }
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
