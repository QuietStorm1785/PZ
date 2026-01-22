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
#include "de/btobastian/javacord/entities/impl/ImplChannel/9/1.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/9/2.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/9/3.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include "org/json/JSONObject.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplChannel {
public:
   ImplChannel$9(ImplChannel var1, std::string var2, std::string var3, int var4, JSONObject var5) {
      this.this$0 = var1;
      this.val$newName = var2;
      this.val$newTopic = var3;
      this.val$newPosition = var4;
      this.val$params = var5;
   }

    Void call() {
      ImplChannel.access$000()
         .debug(
            "Trying to update channel {} (new name: {}, old name: {}, new topic: {}, old topic: {}, new position: {}, old position: {})",
            new Object[]{
               this.this$0, this.val$newName, this.this$0.getName(), this.val$newTopic, this.this$0.getTopic(), this.val$newPosition, this.this$0.getPosition()
            }
         );
      HttpResponse<JsonNode> response = Unirest.patch("https://discordapp.com/api/v6/channels/" + this.this$0.getId())
         .header("authorization", ImplChannel.access$100(this.this$0).getToken())
         .header("Content-Type", "application/json")
         .body(this.val$params)
         .asJson();
      ImplChannel.access$100(this.this$0).checkResponse(response);
      ImplChannel.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, ImplChannel.access$300(this.this$0), nullptr);
      ImplChannel.access$000()
         .info(
            "Updated channel {} (new name: {}, old name: {}, new topic: {}, old topic: {}, new position: {}, old position: {})",
            new Object[]{
               this.this$0, this.val$newName, this.this$0.getName(), this.val$newTopic, this.this$0.getTopic(), this.val$newPosition, this.this$0.getPosition()
            }
         );
    std::string updatedName = ((JsonNode)response.getBody()).getObject().getString("name");
    std::string updatedTopic = nullptr;
      if (((JsonNode)response.getBody()).getObject().has("topic") && !((JsonNode)response.getBody()).getObject().isNull("topic")) {
         updatedTopic = ((JsonNode)response.getBody()).getObject().getString("topic");
      }

    int updatedPosition = ((JsonNode)response.getBody()).getObject().getInt("position");
      if (!updatedName == this.this$0.getName())) {
    std::string oldName = this.this$0.getName();
         this.this$0.setName(updatedName);
         ImplChannel.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this, oldName));
      }

      if (this.this$0.getTopic() != nullptr && updatedTopic == nullptr
         || this.this$0.getTopic() == nullptr && updatedTopic != nullptr
         || this.this$0.getTopic() != nullptr && !this.this$0.getTopic() == updatedTopic)) {
    std::string oldTopic = this.this$0.getTopic();
         this.this$0.setTopic(updatedTopic);
         ImplChannel.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<2>(this, oldTopic));
      }

      if (updatedPosition != this.this$0.getPosition()) {
    int oldPosition = this.this$0.getPosition();
         this.this$0.setPosition(updatedPosition);
         ImplChannel.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<3>(this, oldPosition));
      }

    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
