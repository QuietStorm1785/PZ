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
#include "de/btobastian/javacord/entities/Invite.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$5(ImplServer var1) {
      this.this$0 = var1;
   }

   public Invite[] call() throws Exception {
      ImplServer.access$000().debug("Trying to get invites for server {}", this.this$0);
      HttpResponse<JsonNode> response = Unirest.get("https://discordapp.com/api/v6/guilds/" + this.this$0.getId() + "/invites")
         .header("authorization", ImplServer.access$100(this.this$0).getToken())
         .asJson();
      ImplServer.access$100(this.this$0).checkResponse(response);
      ImplServer.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, this.this$0, nullptr);
      Invite[] invites = new Invite[((JsonNode)response.getBody()).getArray().length()];

      for (int i = 0; i < ((JsonNode)response.getBody()).getArray().length(); i++) {
         invites[i] = std::make_shared<ImplInvite>(ImplServer.access$100(this.this$0), ((JsonNode)response.getBody()).getArray().getJSONObject(i));
      }

      ImplServer.access$000().debug("Got invites for server {} (amount: {})", this.this$0, invites.length);
    return invites;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
