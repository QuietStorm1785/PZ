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
#include "org/json/JSONObject.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplInviteBuilder {
public:
   ImplInviteBuilder$1(ImplInviteBuilder var1) {
      this.this$0 = var1;
   }

    Invite call() {
      ImplInviteBuilder.access$500()
         .debug(
            "Trying to create invite for channel {} (max uses: {}, temporary: {}, max age: {}",
            new Object[]{
               ImplInviteBuilder.access$000(this.this$0) == nullptr ? ImplInviteBuilder.access$100(this.this$0) : ImplInviteBuilder.access$000(this.this$0),
               ImplInviteBuilder.access$200(this.this$0),
               ImplInviteBuilder.access$300(this.this$0),
               ImplInviteBuilder.access$400(this.this$0)
            }
         );
    JSONObject jsonParam = std::make_shared<JSONObject>();
      if (ImplInviteBuilder.access$200(this.this$0) > 0) {
         jsonParam.put("max_uses", ImplInviteBuilder.access$200(this.this$0));
      }

      if (ImplInviteBuilder.access$300(this.this$0) > -1) {
         jsonParam.put("temporary", ImplInviteBuilder.access$300(this.this$0) == 1);
      }

      if (ImplInviteBuilder.access$400(this.this$0) > 0) {
         jsonParam.put("max_age", ImplInviteBuilder.access$400(this.this$0));
      }

      std::string channelId = ImplInviteBuilder.access$000(this.this$0) == nullptr
         ? ImplInviteBuilder.access$100(this.this$0).getId()
         : ImplInviteBuilder.access$000(this.this$0).getId();
      HttpResponse<JsonNode> response = Unirest.post("https://discordapp.com/api/v6/channels/" + channelId + "/invites")
         .header("authorization", ImplInviteBuilder.access$600(this.this$0).getToken())
         .header("Content-Type", "application/json")
         .body(jsonParam)
         .asJson();
      ImplInviteBuilder.access$600(this.this$0).checkResponse(response);
      ImplInviteBuilder.access$600(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, nullptr, nullptr);
    JSONObject data = ((JsonNode)response.getBody()).getObject();
      ImplInviteBuilder.access$500()
         .debug(
            "Created invite for channel {} (max uses: {}, temporary: {}, max age: {}",
            new Object[]{
               ImplInviteBuilder.access$000(this.this$0) == nullptr ? ImplInviteBuilder.access$100(this.this$0) : ImplInviteBuilder.access$000(this.this$0),
               ImplInviteBuilder.access$200(this.this$0),
               ImplInviteBuilder.access$300(this.this$0),
               data.has("max_age") ? data.getInt("max_age") : -1
            }
         );
      return std::make_shared<ImplInvite>(ImplInviteBuilder.access$600(this.this$0), data);
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
