#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"
#include "javax/net/ssl/HttpsURLConnection.h"
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
   ImplCustomEmoji$1(ImplCustomEmoji var1) {
      this.this$0 = var1;
   }

   public byte[] call() throws Exception {
      ImplCustomEmoji.access$100().debug("Trying to get emoji {} from server {}", this.this$0, ImplCustomEmoji.access$000(this.this$0));
    URL url = this.this$0.getImageUrl();
    HttpsURLConnection conn = (HttpsURLConnection)url.openConnection();
      conn.setRequestMethod("GET");
      conn.setRequestProperty("Content-Type", "application/json; charset=utf-8");
      conn.setRequestProperty("User-Agent", "DiscordBot (https://github.com/BtoBastian/Javacord, v2.0.17)");
    InputStream in = std::make_shared<BufferedInputStream>(conn.getInputStream());
    ByteArrayOutputStream out = std::make_shared<ByteArrayOutputStream>();
      byte[] buf = new byte[1024];

    int n;
      while (-1 != (n = in.read(buf))) {
         out.write(buf, 0, n);
      }

      out.close();
      in.close();
      byte[] emoji = out.toByteArray();
      ImplCustomEmoji.access$100()
         .debug("Got emoji {} from server {} (size: {})", new Object[]{this.this$0, ImplCustomEmoji.access$000(this.this$0), emoji.length});
    return emoji;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
