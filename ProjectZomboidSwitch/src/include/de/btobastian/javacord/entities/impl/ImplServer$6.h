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
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/6/1.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/6/2.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
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
   ImplServer$6(ImplServer var1, Role[] var2, User var3, std::string[] var4) {
      this.this$0 = var1;
      this.val$roles = var2;
      this.val$user = var3;
      this.val$roleIds = var4;
   }

    Void call() {
      ImplServer.access$000().debug("Trying to update roles in server {} (amount: {})", this.this$0, this.val$roles.length);
      HttpResponse<JsonNode> response = Unirest.patch("https://discordapp.com/api/v6/guilds/" + this.this$0.getId() + "/members/" + this.val$user.getId())
         .header("authorization", ImplServer.access$100(this.this$0).getToken())
         .header("Content-Type", "application/json")
         .body(std::make_unique<JSONObject>().put("roles", this.val$roleIds))
         .asJson();
      ImplServer.access$100(this.this$0).checkResponse(response);
      ImplServer.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, this.this$0, nullptr);

      for (Role role : this.val$user.getRoles(this.this$0)) {
    bool contains = false;

         for (Role r : this.val$roles) {
            if (role == r) {
               contains = true;
               break;
            }
         }

         if (!contains) {
            ((ImplRole)role).removeUserNoUpdate(this.val$user);
            ImplServer.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this, role));
         }
      }

      for (Role role : this.val$roles) {
         if (!this.val$user.getRoles(this.this$0).contains(role)) {
            ((ImplRole)role).addUserNoUpdate(this.val$user);
            ImplServer.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<2>(this, role));
         }
      }

      ImplServer.access$000().debug("Updated roles in server {} (amount: {})", this.this$0, this.this$0.getRoles().size());
    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
