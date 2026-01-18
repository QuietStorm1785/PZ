#include "zombie/network/DiscordBot.h"

namespace zombie {
namespace network {

public DiscordBot::DiscordBot(const std::string& string, DiscordSender discordSender) {
 // TODO: Implement DiscordBot
 return nullptr;
}

void DiscordBot::connect(bool boolean0, const std::string& string0, const std::string& string1, const std::string& string2) {
 // TODO: Implement connect
}

void DiscordBot::setChannel(const std::string& string0, const std::string& string1) {
 // TODO: Implement setChannel
}

void DiscordBot::sendMessage(const std::string& string1, const std::string& string0) {
 // TODO: Implement sendMessage
}

void DiscordBot::setChannelByName(const std::string& string) {
 // TODO: Implement setChannelByName
}

void DiscordBot::setChannelByID(const std::string& string) {
 // TODO: Implement setChannelByID
}

void DiscordBot::onSuccess(DiscordAPI discordAPI) {
 // TODO: Implement onSuccess
}

void DiscordBot::onFailure(std::exception throwable) {
 // TODO: Implement onFailure
}

void DiscordBot::onMessageCreate(DiscordAPI discordAPI, Message message) {
 // TODO: Implement onMessageCreate
}

std::string DiscordBot::replaceChannelIDByItsName(DiscordAPI discordAPI, Message message) {
 // TODO: Implement replaceChannelIDByItsName
 return "";
}

std::string DiscordBot::removeSmilesAndImages(const std::string& string) {
 // TODO: Implement removeSmilesAndImages
 return "";
}

} // namespace network
} // namespace zombie
