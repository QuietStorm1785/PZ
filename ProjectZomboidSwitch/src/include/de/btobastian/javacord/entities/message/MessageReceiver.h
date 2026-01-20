#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "de/btobastian/javacord/entities/message/embed/EmbedBuilder.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {


class MessageReceiver {
public:
    virtual ~MessageReceiver() = default;
    std::string getId();

   Future<Message> sendMessage(std::string var1);

   Future<Message> sendMessage(std::string var1, std::string var2);

   Future<Message> sendMessage(std::string var1, boolean var2);

   Future<Message> sendMessage(std::string var1, boolean var2, std::string var3);

   Future<Message> sendMessage(std::string var1, EmbedBuilder var2);

   Future<Message> sendMessage(std::string var1, EmbedBuilder var2, std::string var3);

   Future<Message> sendMessage(std::string var1, EmbedBuilder var2, boolean var3);

   Future<Message> sendMessage(std::string var1, EmbedBuilder var2, boolean var3, std::string var4);

   Future<Message> sendMessage(std::string var1, FutureCallback<Message> var2);

   Future<Message> sendMessage(std::string var1, std::string var2, FutureCallback<Message> var3);

   Future<Message> sendMessage(std::string var1, boolean var2, FutureCallback<Message> var3);

   Future<Message> sendMessage(std::string var1, boolean var2, std::string var3, FutureCallback<Message> var4);

   Future<Message> sendMessage(std::string var1, EmbedBuilder var2, FutureCallback<Message> var3);

   Future<Message> sendMessage(std::string var1, EmbedBuilder var2, std::string var3, FutureCallback<Message> var4);

   Future<Message> sendMessage(std::string var1, EmbedBuilder var2, boolean var3, FutureCallback<Message> var4);

   Future<Message> sendMessage(std::string var1, EmbedBuilder var2, boolean var3, std::string var4, FutureCallback<Message> var5);

   Future<Message> sendFile(File var1);

   Future<Message> sendFile(File var1, FutureCallback<Message> var2);

   Future<Message> sendFile(InputStream var1, std::string var2);

   Future<Message> sendFile(InputStream var1, std::string var2, FutureCallback<Message> var3);

   Future<Message> sendFile(File var1, std::string var2);

   Future<Message> sendFile(File var1, std::string var2, FutureCallback<Message> var3);

   Future<Message> sendFile(InputStream var1, std::string var2, std::string var3);

   Future<Message> sendFile(InputStream var1, std::string var2, std::string var3, FutureCallback<Message> var4);

   Future<MessageHistory> getMessageHistory(int var1);

   Future<MessageHistory> getMessageHistory(int var1, FutureCallback<MessageHistory> var2);

   Future<MessageHistory> getMessageHistoryBefore(Message var1, int var2);

   Future<MessageHistory> getMessageHistoryBefore(Message var1, int var2, FutureCallback<MessageHistory> var3);

   Future<MessageHistory> getMessageHistoryBefore(std::string var1, int var2);

   Future<MessageHistory> getMessageHistoryBefore(std::string var1, int var2, FutureCallback<MessageHistory> var3);

   Future<MessageHistory> getMessageHistoryAfter(Message var1, int var2);

   Future<MessageHistory> getMessageHistoryAfter(Message var1, int var2, FutureCallback<MessageHistory> var3);

   Future<MessageHistory> getMessageHistoryAfter(std::string var1, int var2);

   Future<MessageHistory> getMessageHistoryAfter(std::string var1, int var2, FutureCallback<MessageHistory> var3);

    void type();
}
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
