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
#include "de/btobastian/javacord/entities/impl/ImplServer/11/1.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$11(ImplServer var1) {
      this.this$0 = var1;
   }

    Role call() {
      ImplServer.access$000().debug("Trying to create a role in server {}", this.this$0);
      HttpResponse<JsonNode> response = Unirest.post("https://discordapp.com/api/v6/guilds/" + this.this$0.getId() + "/roles")
         .header("authorization", ImplServer.access$100(this.this$0).getToken())
         .asJson();
      ImplServer.access$100(this.this$0).checkResponse(response);
      ImplServer.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, this.this$0, nullptr);
    Role role = std::make_shared<ImplRole>(((JsonNode)response.getBody()).getObject(), this.this$0, ImplServer.access$100(this.this$0));
      ImplServer.access$000().info("Created role in server {} (name: {}, id: {})", new Object[]{this.this$0, role.getName(), role.getId()});
      ImplServer.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this, role));
    return role;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
