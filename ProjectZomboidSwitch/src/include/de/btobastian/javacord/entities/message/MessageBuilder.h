#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {


class MessageBuilder {
public:
    const std::stringstream strBuilder = new std::stringstream();

    MessageBuilder append(const std::string& message) {
      this.strBuilder.append(message);
    return this;
   }

    MessageBuilder appendDecoration(const std::string& message, MessageDecoration... decorations) {
    for (auto& decoration : decorations)         this.strBuilder.append(decoration.getPrefix());
      }

      this.strBuilder.append(message);

    for (auto& decoration : decorations)         this.strBuilder.append(decoration.getSuffix());
      }

    return this;
   }

    MessageBuilder appendCode(const std::string& language, const std::string& message) {
      this.strBuilder
         .append(MessageDecoration.CODE_LONG.getPrefix())
         .append(language)
         .append("\n")
         .append(message)
         .append(MessageDecoration.CODE_LONG.getSuffix());
    return this;
   }

    MessageBuilder appendMention(User user) {
      this.strBuilder.append(user.getMentionTag());
    return this;
   }

    MessageBuilder appendUser(User user) {
      return this.appendMention(user);
   }

    MessageBuilder appendNewLine() {
      this.strBuilder.append("\n");
    return this;
   }

    MessageBuilder appendChannel(Channel channel) {
      this.strBuilder.append(channel.getMentionTag());
    return this;
   }

    MessageBuilder appendRole(Role role) {
      this.strBuilder.append(role.getMentionTag());
    return this;
   }

    std::stringstream getStringBuilder() {
      return this.strBuilder;
   }

    std::string build() {
      return this.strBuilder;
   }

    std::string toString() {
      return this.build();
   }
}
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
