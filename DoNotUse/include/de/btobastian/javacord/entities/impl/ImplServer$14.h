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


class ImplServer {
public:
   ImplServer$14(ImplServer var1) {
      this.this$0 = var1;
   }

   public byte[] call() throws Exception {
      ImplServer.access$000().debug("Trying to get icon from server {}", this.this$0);
      if (ImplServer.access$400(this.this$0) == nullptr) {
         ImplServer.access$000().debug("Server {} has default icon. Returning empty array!", this.this$0);
         return new byte[0];
      } else {
    URL url = this.this$0.getIconUrl();
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
         byte[] avatar = out.toByteArray();
         ImplServer.access$000().debug("Got icon from server {} (size: {})", this.this$0, avatar.length);
    return avatar;
      }
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
