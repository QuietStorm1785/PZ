#include <string>
#include "zombie/chat/ChatElement.h"

namespace zombie {
namespace chat {

public ChatElement::ChatElement(ChatElementOwner var1, int var2, const std::string& var3) {
    // TODO: Implement ChatElement
    return nullptr;
}

void ChatElement::setMaxChatLines(int var1) {
    // TODO: Implement setMaxChatLines
}

int ChatElement::getMaxChatLines() {
    // TODO: Implement getMaxChatLines
    return 0;
}

void ChatElement::setMaxCharsPerLine(int var1) {
    // TODO: Implement setMaxCharsPerLine
}

bool ChatElement::IsSpeaking() {
    // TODO: Implement IsSpeaking
    return false;
}

std::string ChatElement::getTalkerType() {
    // TODO: Implement getTalkerType
    return "";
}

void ChatElement::setTalkerType(const std::string& var1) {
    // TODO: Implement setTalkerType
}

std::string ChatElement::getSayLine() {
    // TODO: Implement getSayLine
    return "";
}

std::string ChatElement::getSayLineTag() {
    // TODO: Implement getSayLineTag
    return "";
}

void ChatElement::setHistoryRange(float var1) {
    // TODO: Implement setHistoryRange
}

void ChatElement::setUseEuclidean(bool var1) {
    // TODO: Implement setUseEuclidean
}

bool ChatElement::getHasChatToDisplay() {
    // TODO: Implement getHasChatToDisplay
    return false;
}

float ChatElement::getDistance(IsoPlayer var1) {
    // TODO: Implement getDistance
    return 0;
}

bool ChatElement::playerWithinBounds(IsoPlayer var1, float var2) {
    // TODO: Implement playerWithinBounds
    return false;
}

void ChatElement::SayDebug(int var1, const std::string& var2) {
    // TODO: Implement SayDebug
}

void ChatElement::Say(const std::string& var1) {
    // TODO: Implement Say
}

void ChatElement::addChatLine(const std::string& var1, float var2, float var3, float var4, float var5) {
    // TODO: Implement addChatLine
}

void ChatElement::addChatLine(const std::string& var1, float var2, float var3, float var4) {
    // TODO: Implement addChatLine
}

float ChatElement::getScrambleValue(IsoPlayer var1, float var2) {
    // TODO: Implement getScrambleValue
    return 0;
}

void ChatElement::updateChatLines() {
    // TODO: Implement updateChatLines
}

void ChatElement::updateHistory() {
    // TODO: Implement updateHistory
}

void ChatElement::update() {
    // TODO: Implement update
}

void ChatElement::renderBatched(int var1, int var2, int var3) {
    // TODO: Implement renderBatched
}

void ChatElement::renderBatched(int var1, int var2, int var3, bool var4) {
    // TODO: Implement renderBatched
}

void ChatElement::clear(int var1) {
    // TODO: Implement clear
}

void ChatElement::RenderBatch(int var0) {
    // TODO: Implement RenderBatch
}

void ChatElement::NoRender(int var0) {
    // TODO: Implement NoRender
}

void ChatElement::addNoLogText(const std::string& var0) {
    // TODO: Implement addNoLogText
}

} // namespace chat
} // namespace zombie
