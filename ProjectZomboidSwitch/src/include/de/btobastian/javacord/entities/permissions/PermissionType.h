#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {

enum class PermissionType {
   CREATE_INSTANT_INVITE(0),
   KICK_MEMBERS(1),
   BAN_MEMBERS(2),
   ADMINISTRATOR(3),
   MANAGE_CHANNELS(4),
   MANAGE_SERVER(5),
   ADD_REACTIONS(6),
   READ_MESSAGES(10),
   SEND_MESSAGES(11),
   SEND_TTS_MESSAGES(12),
   MANAGE_MESSAGES(13),
   EMBED_LINKS(14),
   ATTACH_FILE(15),
   READ_MESSAGE_HISTORY(16),
   MENTION_EVERYONE(17),
   USE_EXTERNAL_EMOJIS(18),
   VOICE_CONNECT(20),
   VOICE_SPEAK(21),
   VOICE_MUTE_MEMBERS(22),
   VOICE_DEAFEN_MEMBERS(23),
   VOICE_MOVE_MEMBERS(24),
   VOICE_USE_VAD(25),
   CHANGE_NICKNAME(26),
   MANAGE_NICKNAMES(27),
   MANAGE_ROLES(28),
   MANAGE_WEBHOOKS(29),
   MANAGE_EMOJIS(30);

    const int offset;

    private PermissionType(int offset) {
      this.offset = offset;
   }

    int getOffset() {
      return this.offset;
   }

    bool isSet(int i) {
      return (i & 1 << this.offset) != 0;
   }

    int set(int i, bool set) {
      if (!set && this.isSet(i)) {
         i = (int)(i - Math.pow(2.0, this.getOffset()));
      } else if (set && !this.isSet(i)) {
         i = (int)(i + Math.pow(2.0, this.getOffset()));
      }

    return i;
   }
}
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
