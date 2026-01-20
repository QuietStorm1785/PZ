#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/SettableFuture.h"
#include <nlohmann/json.hpp>
#include <mutex>
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/listener/server/ServerJoinListener.h"

namespace de {
namespace btobastian {
namespace javacord {


class ImplDiscordAPI {
public:
   ImplDiscordAPI$1(ImplDiscordAPI& parent) : parent_(parent) {}

   void onServerJoin(DiscordAPI& api, Server& server) {
      std::lock_guard<std::mutex> lock(parent_.listenerLock);
      auto it = parent_.waitingForListener.find(server.getId());
      if (it != parent_.waitingForListener.end()) {
         // Debug log: "Joined or created server. We were waiting for this server!"
         parent_.waitingForListener.erase(it);
         it->second.set_value(server);
      }
   }
private:
   ImplDiscordAPI& parent_;
}
} // namespace javacord
} // namespace btobastian
} // namespace de
