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
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel/6/1.h"
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel/6/2.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include "org/json/JSONObject.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplVoiceChannel {
public:
   ImplVoiceChannel$6(ImplVoiceChannel var1, std::string var2, int var3, JSONObject var4) {
      this.this$0 = var1;
      this.val$newName = var2;
      this.val$newPosition = var3;
      this.val$params = var4;
   }

    Void call() {
      ImplVoiceChannel.access$000()
         .debug(
            "Trying to update channel {} (new name: {}, old name: {}, new position: {}, old position: {})",
            new Object[]{this.this$0, this.val$newName, this.this$0.getName(), this.val$newPosition, this.this$0.getPosition()}
         );
      HttpResponse<JsonNode> response = Unirest.patch("https://discordapp.com/api/v6/channels/" + this.this$0.getId())
         .header("authorization", ImplVoiceChannel.access$100(this.this$0).getToken())
         .header("Content-Type", "application/json")
         .body(this.val$params)
         .asJson();
      ImplVoiceChannel.access$100(this.this$0).checkResponse(response);
      ImplVoiceChannel.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, ImplVoiceChannel.access$300(this.this$0), nullptr);
      ImplVoiceChannel.access$000()
         .info(
            "Updated channel {} (new name: {}, old name: {}, new position: {}, old position: {})",
            new Object[]{this.this$0, this.val$newName, this.this$0.getName(), this.val$newPosition, this.this$0.getPosition()}
         );
    std::string updatedName = ((JsonNode)response.getBody()).getObject().getString("name");
    int updatedPosition = ((JsonNode)response.getBody()).getObject().getInt("position");
      if (!updatedName == this.this$0.getName())) {
    std::string oldName = this.this$0.getName();
         this.this$0.setName(updatedName);
         ImplVoiceChannel.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this, oldName));
      }

      if (updatedPosition != this.this$0.getPosition()) {
    int oldPosition = this.this$0.getPosition();
         this.this$0.setPosition(updatedPosition);
         ImplVoiceChannel.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<2>(this, oldPosition));
      }

    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
