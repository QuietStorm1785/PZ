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
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/1/1.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/1/2.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/1/3.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/1/4.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/1/5.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/1/6.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include "java/awt/Color.h"
#include "org/json/JSONObject.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {


class ImplRole {
public:
   ImplRole$1(ImplRole var1, std::string var2, int var3, boolean var4, int var5, boolean var6) {
      this.this$0 = var1;
      this.val$name = var2;
      this.val$color = var3;
      this.val$hoist = var4;
      this.val$allow = var5;
      this.val$mentionable = var6;
   }

    Void call() {
      ImplRole.access$100()
         .debug(
            "Trying to update role {} (new name: {}, old name: {}, new color: {}, old color: {}, new hoist: {}, old hoist: {}, new allow: {}, old allow: {})",
            new Object[]{
               this.this$0,
               this.val$name,
               this.this$0.getName(),
               this.val$color & 16777215,
               this.this$0.getColor().getRGB() & 16777215,
               this.val$hoist,
               this.this$0.getHoist(),
               this.val$allow,
               ImplRole.access$000(this.this$0).getAllowed()
            }
         );
      HttpResponse<JsonNode> response = Unirest.patch(
            "https://discordapp.com/api/v6/guilds/" + ImplRole.access$300(this.this$0).getId() + "/roles/" + ImplRole.access$400(this.this$0)
         )
         .header("authorization", ImplRole.access$200(this.this$0).getToken())
         .header("Content-Type", "application/json")
         .body(
    std::make_shared<JSONObject>();
               .put("name", this.val$name)
               .put("color", this.val$color & 16777215)
               .put("hoist", this.val$hoist)
               .put("permissions", this.val$allow)
               .put("mentionable", this.val$mentionable)
               
         )
         .asJson();
      ImplRole.access$200(this.this$0).checkResponse(response);
      ImplRole.access$200(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, nullptr, nullptr);
      ImplRole.access$100()
         .info(
            "Updated role {} (new name: {}, old name: {}, new color: {}, old color: {}, new hoist: {}, old hoist: {}, new allow: {}, old allow: {})",
            new Object[]{
               this.this$0,
               this.val$name,
               this.this$0.getName(),
               this.val$color & 16777215,
               this.this$0.getColor().getRGB() & 16777215,
               this.val$hoist,
               this.this$0.getHoist(),
               this.val$allow,
               ImplRole.access$000(this.this$0).getAllowed()
            }
         );
      if (ImplRole.access$000(this.this$0).getAllowed() != this.val$allow) {
    ImplPermissions oldPermissions = ImplRole.access$000(this.this$0);
         ImplRole.access$002(this.this$0, std::make_shared<ImplPermissions>(this.val$allow));
         ImplRole.access$200(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this, oldPermissions));
      }

      if (ImplRole.access$500(this.this$0) == this.val$name)) {
    std::string oldName = ImplRole.access$500(this.this$0);
         ImplRole.access$502(this.this$0, this.val$name);
         ImplRole.access$200(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<2>(this, oldName));
      }

      if (ImplRole.access$600(this.this$0).getRGB() != std::make_shared<Color>(this.val$color).getRGB()) {
    Color oldColor = ImplRole.access$600(this.this$0);
         ImplRole.access$602(this.this$0, std::make_shared<Color>(this.val$color));
         ImplRole.access$200(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<3>(this, oldColor));
      }

      if (ImplRole.access$700(this.this$0) != this.val$hoist) {
         ImplRole.access$702(this.this$0, this.val$hoist);
         ImplRole.access$200(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<4>(this));
      }

      if (ImplRole.access$800(this.this$0) != ImplRole.access$800(this.this$0)) {
         ImplRole.access$802(this.this$0, ImplRole.access$800(this.this$0));
         ImplRole.access$200(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<5>(this));
      }

      if (ImplRole.access$900(this.this$0) != this.val$mentionable) {
         ImplRole.access$902(this.this$0, this.val$mentionable);
         ImplRole.access$200(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<6>(this));
      }

    return nullptr;
   }
}
} // namespace impl
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
