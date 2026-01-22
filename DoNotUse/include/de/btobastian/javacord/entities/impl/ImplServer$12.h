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
#include "de/btobastian/javacord/entities/Region.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/12/1.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include "org/json/JSONObject.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$12(ImplServer var1, std::string var2, Region var3, JSONObject var4) {
      this.this$0 = var1;
      this.val$newName = var2;
      this.val$newRegion = var3;
      this.val$params = var4;
   }

    Void call() {
      ImplServer.access$000()
         .debug(
            "Trying to update server {} (new name: {}, old name: {}, new region: {}, old region: {}",
            new Object[]{
               this.this$0,
               this.val$newName,
               this.this$0.getName(),
               this.val$newRegion == nullptr ? "nullptr" : this.val$newRegion.getKey(),
               this.this$0.getRegion().getKey()
            }
         );
      HttpResponse<JsonNode> response = Unirest.patch("https://discordapp.com/api/v6/guilds/" + this.this$0.getId())
         .header("authorization", ImplServer.access$100(this.this$0).getToken())
         .header("Content-Type", "application/json")
         .body(this.val$params)
         .asJson();
      ImplServer.access$100(this.this$0).checkResponse(response);
      ImplServer.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, this.this$0, nullptr);
      ImplServer.access$000()
         .debug(
            "Updated server {} (new name: {}, old name: {}, new region: {}, old region: {}",
            new Object[]{
               this.this$0,
               this.val$newName,
               this.this$0.getName(),
               this.val$newRegion == nullptr ? "nullptr" : this.val$newRegion.getKey(),
               this.this$0.getRegion().getKey()
            }
         );
    std::string name = ((JsonNode)response.getBody()).getObject().getString("name");
      if (!this.this$0.getName() == name)) {
    std::string oldName = this.this$0.getName();
         ImplServer.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this, oldName));
      }

    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
