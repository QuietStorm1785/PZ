#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/chat/defaultChats/WhisperChat/ChatStatus.h"

namespace zombie {
namespace chat {


class WhisperChatCreation {
public:
    std::string destPlayerName = nullptr;
    ChatStatus status = ChatStatus.None;
    long createTime = 0L;
   const std::vector<std::string> messages = std::make_unique<std::vector<>>();
}
} // namespace chat
} // namespace zombie
