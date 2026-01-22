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


class ImplUser {
public:
   ImplUser$1(ImplUser var1) {
      this.this$0 = var1;
   }

   public byte[] call() throws Exception {
      ImplUser.access$000().debug("Trying to get avatar from user {}", this.this$0);
      if (ImplUser.access$100(this.this$0) == nullptr) {
         ImplUser.access$000().debug("User {} seems to have no avatar. Returning empty array!", this.this$0);
         return new byte[0];
      } else {
    URL url = std::make_shared<URL>("https://discordapp.com/api/v6/users/" + ImplUser.access$200(this.this$0) + "/avatars/" + ImplUser.access$100(this.this$0) + ".jpg");
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
         ImplUser.access$000().debug("Got avatar from user {} (size: {})", this.this$0, avatar.length);
    return avatar;
      }
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
