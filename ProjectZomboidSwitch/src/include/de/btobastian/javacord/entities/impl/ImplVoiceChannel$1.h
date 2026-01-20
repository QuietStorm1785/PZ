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
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel/1/1.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplVoiceChannel {
public:
   ImplVoiceChannel$1(ImplVoiceChannel var1) {
      this.this$0 = var1;
   }

    Void call() {
      ImplVoiceChannel.access$000().debug("Trying to delete voice channel {}", this.this$0);
      HttpResponse<JsonNode> response = Unirest.delete("https://discordapp.com/api/v6/channels/" + ImplVoiceChannel.access$200(this.this$0))
         .header("authorization", ImplVoiceChannel.access$100(this.this$0).getToken())
         .asJson();
      ImplVoiceChannel.access$100(this.this$0).checkResponse(response);
      ImplVoiceChannel.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, ImplVoiceChannel.access$300(this.this$0), nullptr);
      ImplVoiceChannel.access$300(this.this$0).removeVoiceChannel(this.this$0);
      ImplVoiceChannel.access$000().info("Deleted voice channel {}", this.this$0);
      ImplVoiceChannel.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this));
    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
