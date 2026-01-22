#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/HttpResponse.h"
#include "com/mashape/unirest/http/JsonNode.h"
#include "com/mashape/unirest/http/Unirest.h"
#include "de/btobastian/javacord/entities/permissions/Ban.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplBan.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include "org/json/JSONArray.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$9(ImplServer var1) {
      this.this$0 = var1;
   }

   public Ban[] call() throws Exception {
      ImplServer.access$000().debug("Trying to get bans for server {}", this.this$0);
      HttpResponse<JsonNode> response = Unirest.get("https://discordapp.com/api/v6/guilds/" + this.this$0.getId() + "/bans")
         .header("authorization", ImplServer.access$100(this.this$0).getToken())
         .asJson();
      ImplServer.access$100(this.this$0).checkResponse(response);
      ImplServer.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, this.this$0, nullptr);
    JSONArray bansJson = ((JsonNode)response.getBody()).getArray();
      Ban[] bans = new Ban[bansJson.length()];

      for (int i = 0; i < bansJson.length(); i++) {
         bans[i] = std::make_shared<ImplBan>(ImplServer.access$100(this.this$0), this.this$0, bansJson.getJSONObject(i));
      }

      ImplServer.access$000().debug("Got bans for server {} (amount: {})", this.this$0, bans.length);
    return bans;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
