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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

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

 static ChatType valueOf(int integer) {
 if (general.value == integer) {
 return general;
 } else if (whisper.value == integer) {
 return whisper;
 } else if (say.value == integer) {
 return say;
 } else if (shout.value == integer) {
 return shout;
 } else if (faction.value == integer) {
 return faction;
 } else if (safehouse.value == integer) {
 return safehouse;
 } else if (radio.value == integer) {
 return radio;
 } else if (admin.value == integer) {
 return admin;
 } else {
 return server.value == integer ? server : notDefined;
 }
 }

 private ChatType(int integer, const std::string& string1) {
 this->value = integer;
 this->titleID = string1;
 }

 int getValue() {
 return this->value;
 }

 std::string getTitleID() {
 return this->titleID;
 }
}
} // namespace chat
} // namespace network
} // namespace zombie
