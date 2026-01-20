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
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/entities/message/MessageReceiver.h"
#include "de/btobastian/javacord/entities/message/embed/EmbedBuilder.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include "org/json/JSONObject.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplUser {
public:
   ImplUser$3(ImplUser var1, std::string var2, boolean var3, EmbedBuilder var4, std::string var5, MessageReceiver var6) {
      this.this$0 = var1;
      this.val$content = var2;
      this.val$tts = var3;
      this.val$embed = var4;
      this.val$nonce = var5;
      this.val$receiver = var6;
   }

    Message call() {
      ImplUser.access$000().debug("Trying to send message to user {} (content: \"{}\", tts: {})", new Object[]{this.this$0, this.val$content, this.val$tts});
      ImplUser.access$300(this.this$0).checkRateLimit(nullptr, RateLimitType.PRIVATE_MESSAGE, nullptr, nullptr);
    JSONObject body = std::make_shared<JSONObject>().put("content", this.val$content).put("tts", this.val$tts).put("mentions", new std::string[0]);
      if (this.val$embed != nullptr) {
         body.put("embed", this.val$embed.toJSONObject());
      }

      if (this.val$nonce != nullptr) {
         body.put("nonce", this.val$nonce);
      }

      HttpResponse<JsonNode> response = Unirest.post("https://discordapp.com/api/v6/channels/" + this.this$0.getUserChannelIdBlocking() + "/messages")
         .header("authorization", ImplUser.access$300(this.this$0).getToken())
         .header("content-type", "application/json")
         .body(body)
         .asJson();
      ImplUser.access$300(this.this$0).checkResponse(response);
      ImplUser.access$300(this.this$0).checkRateLimit(response, RateLimitType.PRIVATE_MESSAGE, nullptr, nullptr);
      ImplUser.access$000().debug("Sent message to user {} (content: \"{}\", tts: {})", new Object[]{this.this$0, this.val$content, this.val$tts});
      return std::make_shared<ImplMessage>(((JsonNode)response.getBody()).getObject(), ImplUser.access$300(this.this$0), this.val$receiver);
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
