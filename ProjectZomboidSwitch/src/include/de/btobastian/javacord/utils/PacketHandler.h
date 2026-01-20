#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/utils/PacketHandler/1.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {


class PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(PacketHandler.class);
    const ImplDiscordAPI api;
    const std::string type;
    const bool async;
    ExecutorService executorService;
    const ExecutorService listenerExecutorService;

    public PacketHandler(ImplDiscordAPI api, bool async, const std::string& type) {
      this.api = api;
      this.async = async;
      this.type = type;
      if (async) {
         this.executorService = api.getThreadPool().getSingleThreadExecutorService("handlers");
      }

      this.listenerExecutorService = api.getThreadPool().getSingleThreadExecutorService("listeners");
   }

    void handlePacket(JSONObject packet) {
      if (this.async) {
         this.executorService.submit(std::make_shared<1>(this, packet));
      } else {
         try {
            this.handle(packet);
         } catch (Exception var3) {
            logger.warn("Couldn't handle packet of type {}. Please contact the developer! (packet: {})", new Object[]{this.getType(), packet, var3});
         }
      }
   }

   protected abstract void handle(JSONObject var1);

    std::string getType() {
      return this.type;
   }

    int hashCode() {
      return this.type.hashCode();
   }

    bool equals(void* obj) {
      return dynamic_cast<PacketHandler*>(obj) != nullptr && ((PacketHandler)obj).getType() == this.getType());
   }
}
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
