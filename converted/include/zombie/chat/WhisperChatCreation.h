#pragma once
#include "zombie/chat/defaultChats/WhisperChat.h"
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

class WhisperChatCreation {
public:
  std::string destPlayerName = null;
  WhisperChat.ChatStatus status = WhisperChat.ChatStatus.None;
  long createTime = 0L;
  final ArrayList<String> messages = std::make_unique<ArrayList<>>();
}
} // namespace chat
} // namespace zombie
