#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iterator>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {


class MessageHistory {
public:
    virtual ~MessageHistory() = default;
    Message getMessageById(const std::string& var1);

   Iterator<Message> iterator();

   Collection<Message> getMessages();

    Message getNewestMessage();

    Message getOldestMessage();

   List<Message> getMessagesSorted();
}
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
