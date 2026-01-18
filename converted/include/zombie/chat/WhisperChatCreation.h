#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/chat/defaultChats/WhisperChat.h"

namespace zombie {
namespace chat {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WhisperChatCreation {
public:
 std::string destPlayerName = nullptr;
 WhisperChat.ChatStatus status = WhisperChat.ChatStatus.None;
 long createTime = 0L;
 ArrayList<String> messages = std::make_unique<ArrayList<>>();
}
} // namespace chat
} // namespace zombie
