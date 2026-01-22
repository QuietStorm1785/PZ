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


class ImplChannel {
public:
   ImplChannel$4(ImplChannel var1, std::string var2, InputStream var3, std::string var4, MessageReceiver var5) {
      this.this$0 = var1;
      this.val$comment = var2;
      this.val$inputStream = var3;
      this.val$filename = var4;
      this.val$receiver = var5;
   }

    Message call() {
      ImplChannel.access$000().debug("Trying to send an input stream in channel {} (comment: {})", this.this$0, this.val$comment);
      ImplChannel.access$100(this.this$0).checkRateLimit(nullptr, RateLimitType.SERVER_MESSAGE, nullptr, this.this$0);
      MultipartBody body = Unirest.post("https://discordapp.com/api/v6/channels/" + ImplChannel.access$200(this.this$0) + "/messages")
         .header("authorization", ImplChannel.access$100(this.this$0).getToken())
         .field("file", this.val$inputStream, this.val$filename);
      if (this.val$comment != nullptr) {
         body.field("content", this.val$comment);
      }

      HttpResponse<JsonNode> response = body.asJson();
      ImplChannel.access$100(this.this$0).checkResponse(response);
      ImplChannel.access$100(this.this$0).checkRateLimit(response, RateLimitType.SERVER_MESSAGE, nullptr, this.this$0);
      ImplChannel.access$000().debug("Sent an input stream in channel {} (comment: {})", this.this$0, this.val$comment);
      return std::make_shared<ImplMessage>(((JsonNode)response.getBody()).getObject(), ImplChannel.access$100(this.this$0), this.val$receiver);
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
