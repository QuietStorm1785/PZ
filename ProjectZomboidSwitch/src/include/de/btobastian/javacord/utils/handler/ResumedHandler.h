#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "org/json/JSONObject.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {


class ResumedHandler : public PacketHandler {
public:
    public ResumedHandler(ImplDiscordAPI api) {
      super(api, false, "RESUMED");
   }

    void handle(JSONObject packet) {
   }
}
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
