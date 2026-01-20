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
#include "de/btobastian/javacord/entities/impl/ImplChannel/1/1.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplChannel {
public:
   ImplChannel$1(ImplChannel var1) {
      this.this$0 = var1;
   }

    Void call() {
      ImplChannel.access$000().debug("Trying to delete channel {}", this.this$0);
      HttpResponse<JsonNode> response = Unirest.delete("https://discordapp.com/api/v6/channels/" + ImplChannel.access$200(this.this$0))
         .header("authorization", ImplChannel.access$100(this.this$0).getToken())
         .asJson();
      ImplChannel.access$100(this.this$0).checkResponse(response);
      ImplChannel.access$300(this.this$0).removeChannel(this.this$0);
      ImplChannel.access$000().info("Deleted channel {}", this.this$0);
      ImplChannel.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this));
    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
