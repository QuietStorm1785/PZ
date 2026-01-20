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
#include "com/mashape/unirest/request/body/MultipartBody.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/entities/message/MessageReceiver.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
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
   ImplUser$4(ImplUser var1, File var2, std::string var3, MessageReceiver var4) {
      this.this$0 = var1;
      this.val$file = var2;
      this.val$comment = var3;
      this.val$receiver = var4;
   }

    Message call() {
      ImplUser.access$000()
         .debug("Trying to send a file to user {} (name: {}, comment: {})", new Object[]{this.this$0, this.val$file.getName(), this.val$comment});
      ImplUser.access$300(this.this$0).checkRateLimit(nullptr, RateLimitType.PRIVATE_MESSAGE, nullptr, nullptr);
      MultipartBody body = Unirest.post("https://discordapp.com/api/v6/channels/" + this.this$0.getUserChannelIdBlocking() + "/messages")
         .header("authorization", ImplUser.access$300(this.this$0).getToken())
         .field("file", this.val$file);
      if (this.val$comment != nullptr) {
         body.field("content", this.val$comment);
      }

      HttpResponse<JsonNode> response = body.asJson();
      ImplUser.access$300(this.this$0).checkResponse(response);
      ImplUser.access$300(this.this$0).checkRateLimit(response, RateLimitType.PRIVATE_MESSAGE, nullptr, nullptr);
      ImplUser.access$000().debug("Sent a file to user {} (name: {}, comment: {})", new Object[]{this.this$0, this.val$file.getName(), this.val$comment});
      return std::make_shared<ImplMessage>(((JsonNode)response.getBody()).getObject(), ImplUser.access$300(this.this$0), this.val$receiver);
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
