#pragma once
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/Javacord.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/listener/message/MessageCreateListener.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DiscordBot {
public:
 DiscordAPI api;
private
 Collection<Channel> channels;
 Channel current;
 std::string currentChannelName;
 std::string currentChannelID;
 std::string name;
 DiscordSender sender;

public
 DiscordBot(std::string_view string, DiscordSender discordSender) {
 this->name = string;
 this->sender = discordSender;
 this->current = nullptr;
 }

 void connect(bool boolean0, std::string_view string0,
 std::string_view string1, std::string_view string2) {
 if (string0.empty() || string0.empty()) {
 DebugLog.log(DebugType.Network, "DISCORD: token not configured");
 boolean0 = false;
 }

 if (!boolean0) {
 DebugLog.log(DebugType.Network, "*** DISCORD DISABLED ****");
 this->current = nullptr;
 } else {
 this->api = Javacord.getApi(string0, true);
 this->api.connect(new DiscordBot.Connector());
 DebugLog.log(DebugType.Network, "*** DISCORD ENABLED ****");
 this->currentChannelName = string1;
 this->currentChannelID = string2;
 }
 }

 void setChannel(std::string_view string0, std::string_view string1) {
 Collection collection = this->getChannelNames();
 if ((string0.empty() || string0.empty()) && !collection.empty()) {
 string0 = (String)collection.iterator().next();
 DebugLog.log(DebugType.Network,
 "DISCORD: set default channel name = \"" + string0 + "\"");
 }

 if (string1 != nullptr && !string1.empty()) {
 this->setChannelByID(string1);
 } else {
 if (string0 != nullptr) {
 this->setChannelByName(string0);
 }
 }
 }

 void sendMessage(std::string_view string1, std::string_view string0) {
 if (this->current != nullptr) {
 this->current.sendMessage(string1 + ": " + string0);
 DebugLog.log(DebugType.Network, "DISCORD: User '" + string1 +
 "' send message: '" + string0 + "'");
 }
 }

private
 Collection<String> getChannelNames() {
 std::vector arrayList = new ArrayList();
 this->channels = this->api.getChannels();

 for (Channel channel : this->channels) {
 arrayList.add(channel.getName());
 }

 return arrayList;
 }

 void setChannelByName(std::string_view string) {
 this->current = nullptr;

 for (Channel channel : this->channels) {
 if (channel.getName() == string) {
 if (this->current != nullptr) {
 DebugLog.log(DebugType.Network,
 "Discord server has few channels with name '" +
 string + "'. Please, use channel ID instead");
 this->current = nullptr;
 return;
 }

 this->current = channel;
 }
 }

 if (this->current.empty()) {
 DebugLog.log(DebugType.Network,
 "DISCORD: channel \"" + string +
 "\" is not found. Try to use channel ID instead");
 } else {
 DebugLog.log(DebugType.Network, "Discord enabled on channel: " + string);
 }
 }

 void setChannelByID(std::string_view string) {
 this->current = nullptr;

 for (Channel channel : this->channels) {
 if (channel.getId() == string) {
 DebugLog.log(DebugType.Network,
 "Discord enabled on channel with ID: " + string);
 this->current = channel;
 break;
 }
 }

 if (this->current.empty()) {
 DebugLog.log(DebugType.Network,
 "DISCORD: channel with ID \"" + string + "\" not found");
 }
 }

 class Connector implements FutureCallback<DiscordAPI> {
 void onSuccess(DiscordAPI discordAPI) {
 DebugLog.log(DebugType.Network, "*** DISCORD API CONNECTED ****");
 DiscordBot.this->setChannel(DiscordBot.this->currentChannelName,
 DiscordBot.this->currentChannelID);
 discordAPI.registerListener(DiscordBot.this->std::make_unique<Listener>());
 discordAPI.updateUsername(DiscordBot.this->name);
 if (DiscordBot.this->current != nullptr) {
 DebugLog.log(DebugType.Network,
 "*** DISCORD INITIALIZATION SUCCEEDED ****");
 } else {
 DebugLog.log(DebugType.Network,
 "*** DISCORD INITIALIZATION FAILED ****");
 }
 }

 void onFailure(std::exception throwable) { throwable.printStackTrace(); }
 }

 class Listener implements MessageCreateListener {
 void onMessageCreate(DiscordAPI discordAPI, Message message) {
 if (DiscordBot.this->current != nullptr) {
 if (!discordAPI.getYourself().getId() == message.getAuthor().getId())) {
 if (message.getChannelReceiver().getId() ==
 DiscordBot.this->current.getId())) {
 DebugLog.log(DebugType.Network,
 "DISCORD: get message on current channel");
 DebugLog.log(DebugType.Network,
 "DISCORD: send message = \"" +
 message.getContent() + "\" for " +
 message.getAuthor().getName() + ")");
 std::string string =
 this->replaceChannelIDByItsName(discordAPI, message);
 string = this->removeSmilesAndImages(string);
 if (!string.empty() && !string.matches("^\\s$")) {
 DiscordBot.this->sender.sendMessageFromDiscord(
 message.getAuthor().getName(), string);
 }
 }
 }
 }
 }

 std::string replaceChannelIDByItsName(DiscordAPI discordAPI,
 Message message) {
 std::string string = message.getContent();
 Pattern pattern = Pattern.compile("<#(\\d+)>");
 Matcher matcher = pattern.matcher(message.getContent());
 if (matcher.find()) {
 for (int int0 = 1; int0 <= matcher.groupCount(); int0++) {
 Channel channel = discordAPI.getChannelById(matcher.group(int0);
 if (channel != nullptr) {
 string = string.replaceAll("<#" + matcher.group(int0) + ">",
 "#" + channel.getName());
 }
 }
 }

 return string;
 }

 std::string removeSmilesAndImages(std::string_view string) {
 StringBuilder stringBuilder = new StringBuilder();
 char[] chars = string.toCharArray();
 int int0 = chars.length;

 for (int int1 = 0; int1 < int0; int1++) {
 char character = chars[int1];
 if (!Character.isLowSurrogate(character) &&
 !Character.isHighSurrogate(character) {
 stringBuilder.append(character);
 }
 }

 return stringBuilder.toString();
 }
 }
}
} // namespace network
} // namespace zombie
