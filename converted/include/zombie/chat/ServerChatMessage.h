#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace chat {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Messages which sent by server to any chat stream. This applied stream setting
 * but author always Server
 */
class ServerChatMessage : public ChatMessage {
public:
public
  ServerChatMessage(ChatBase chat, const std::string &text) {
    super(chat, text);
    super.setAuthor("Server");
    this.setServerAuthor(true);
  }

  std::string getAuthor() { return super.getAuthor(); }

  void setAuthor(const std::string &author) {
    throw std::make_unique<UnsupportedOperationException>();
  }
}
} // namespace chat
} // namespace zombie
