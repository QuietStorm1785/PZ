#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {
namespace chat {

enum class ChatType {
   notDefined(-1, ""),
   general(0, "UI_chat_general_chat_title_id"),
   whisper(1, "UI_chat_private_chat_title_id"),
   say(2, "UI_chat_local_chat_title_id"),
   shout(3, "UI_chat_local_chat_title_id"),
   faction(4, "UI_chat_faction_chat_title_id"),
   safehouse(5, "UI_chat_safehouse_chat_title_id"),
   radio(6, "UI_chat_radio_chat_title_id"),
   admin(7, "UI_chat_admin_chat_title_id"),
   server(8, "UI_chat_server_chat_title_id");

    const int value;
    const std::string titleID;

    static ChatType valueOf(int var0) {
      if (general.value == var0) {
    return general;
      } else if (whisper.value == var0) {
    return whisper;
      } else if (say.value == var0) {
    return say;
      } else if (shout.value == var0) {
    return shout;
      } else if (faction.value == var0) {
    return faction;
      } else if (safehouse.value == var0) {
    return safehouse;
      } else if (radio.value == var0) {
    return radio;
      } else if (admin.value == var0) {
    return admin;
      } else {
         return server.value == var0 ? server : notDefined;
      }
   }

    private ChatType(int var3, const std::string& var4) {
      this.value = var3;
      this.titleID = var4;
   }

    int getValue() {
      return this.value;
   }

    std::string getTitleID() {
      return this.titleID;
   }
}
} // namespace chat
} // namespace network
} // namespace zombie
