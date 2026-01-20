#include <sstream>
#include <string>
#include "zombie/GameProfileRecording.h"

namespace zombie {

public GameProfileRecording::GameProfileRecording(const std::string& var1) {
    // TODO: Implement GameProfileRecording
    return nullptr;
}

void GameProfileRecording::setNumFramesPerSegment(int var1) {
    // TODO: Implement setNumFramesPerSegment
}

void GameProfileRecording::setStartTime(long var1) {
    // TODO: Implement setStartTime
}

void GameProfileRecording::logTimeSpan(ProfileArea var1) {
    // TODO: Implement logTimeSpan
}

Span GameProfileRecording::allocSpan(ProfileArea var1) {
    // TODO: Implement allocSpan
    return nullptr;
}

int GameProfileRecording::getOrCreateKey(const std::string& var1) {
    // TODO: Implement getOrCreateKey
    return 0;
}

std::string GameProfileRecording::getValueAt(int var1) {
    // TODO: Implement getValueAt
    return "";
}

void GameProfileRecording::onColumnAdded() {
    // TODO: Implement onColumnAdded
}

void GameProfileRecording::reset() {
    // TODO: Implement reset
}

void GameProfileRecording::openSegmentFile(bool var1) {
    // TODO: Implement openSegmentFile
}

void GameProfileRecording::close() {
    // TODO: Implement close
}

void GameProfileRecording::closeAndDiscard() {
    // TODO: Implement closeAndDiscard
}

void GameProfileRecording::writeData() {
    // TODO: Implement writeData
}

void GameProfileRecording::writeDataRow(std::stringstream var1, Row var2) {
    // TODO: Implement writeDataRow
}

void GameProfileRecording::writeFrameTimeRow(std::stringstream var1, Row var2, int var3) {
    // TODO: Implement writeFrameTimeRow
}

void GameProfileRecording::writeSpan(std::stringstream var1, Row var2, Span var3) {
    // TODO: Implement writeSpan
}

void GameProfileRecording::writeHeader() {
    // TODO: Implement writeHeader
}

} // namespace zombie
