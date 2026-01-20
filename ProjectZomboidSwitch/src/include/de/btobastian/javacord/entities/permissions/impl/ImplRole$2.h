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
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/2/1.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {


class ImplRole {
public:
   ImplRole$2(ImplRole var1) {
      this.this$0 = var1;
   }

    Void call() {
      ImplRole.access$100().debug("Trying to delete role {}", this.this$0);
      HttpResponse<JsonNode> response = Unirest.delete(
            "https://discordapp.com/api/v6/guilds/" + this.this$0.getServer().getId() + "/roles/" + this.this$0.getId()
         )
         .header("authorization", ImplRole.access$200(this.this$0).getToken())
         .asJson();
      ImplRole.access$200(this.this$0).checkResponse(response);
      ImplRole.access$300(this.this$0).removeRole(this.this$0);
      ImplRole.access$100().info("Deleted role {}", this.this$0);
      ImplRole.access$200(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this));
    return nullptr;
   }
}
} // namespace impl
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
