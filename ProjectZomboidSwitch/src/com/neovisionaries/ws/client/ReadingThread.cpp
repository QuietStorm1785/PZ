#include <string>
#include "com\neovisionaries\ws\client/ReadingThread.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

public ReadingThread::ReadingThread(WebSocket websocket) {
    // TODO: Implement ReadingThread
    return nullptr;
}

void ReadingThread::run() {
    // TODO: Implement run
}

void ReadingThread::main() {
    // TODO: Implement main
}

void ReadingThread::requestStop(long closeDelay) {
    // TODO: Implement requestStop
}

void ReadingThread::callOnFrame(WebSocketFrame frame) {
    // TODO: Implement callOnFrame
}

void ReadingThread::callOnContinuationFrame(WebSocketFrame frame) {
    // TODO: Implement callOnContinuationFrame
}

void ReadingThread::callOnTextFrame(WebSocketFrame frame) {
    // TODO: Implement callOnTextFrame
}

void ReadingThread::callOnBinaryFrame(WebSocketFrame frame) {
    // TODO: Implement callOnBinaryFrame
}

void ReadingThread::callOnCloseFrame(WebSocketFrame frame) {
    // TODO: Implement callOnCloseFrame
}

void ReadingThread::callOnPingFrame(WebSocketFrame frame) {
    // TODO: Implement callOnPingFrame
}

void ReadingThread::callOnPongFrame(WebSocketFrame frame) {
    // TODO: Implement callOnPongFrame
}

void ReadingThread::callOnTextMessage(byte[] data) {
    // TODO: Implement callOnTextMessage
}

void ReadingThread::callOnTextMessage(const std::string& message) {
    // TODO: Implement callOnTextMessage
}

void ReadingThread::callOnBinaryMessage(byte[] message) {
    // TODO: Implement callOnBinaryMessage
}

void ReadingThread::callOnError(WebSocketException cause) {
    // TODO: Implement callOnError
}

void ReadingThread::callOnFrameError(WebSocketException cause, WebSocketFrame frame) {
    // TODO: Implement callOnFrameError
}

void ReadingThread::callOnMessageError(WebSocketException cause, List<WebSocketFrame> frames) {
    // TODO: Implement callOnMessageError
}

void ReadingThread::callOnMessageDecompressionError(WebSocketException cause, byte[] compressed) {
    // TODO: Implement callOnMessageDecompressionError
}

void ReadingThread::callOnTextMessageError(WebSocketException cause, byte[] data) {
    // TODO: Implement callOnTextMessageError
}

WebSocketFrame ReadingThread::readFrame() {
    // TODO: Implement readFrame
    return nullptr;
}

void ReadingThread::verifyFrame(WebSocketFrame frame) {
    // TODO: Implement verifyFrame
}

void ReadingThread::verifyReservedBits(WebSocketFrame frame) {
    // TODO: Implement verifyReservedBits
}

void ReadingThread::verifyReservedBit1(WebSocketFrame frame) {
    // TODO: Implement verifyReservedBit1
}

bool ReadingThread::verifyReservedBit1ForPMCE(WebSocketFrame frame) {
    // TODO: Implement verifyReservedBit1ForPMCE
    return false;
}

void ReadingThread::verifyReservedBit2(WebSocketFrame frame) {
    // TODO: Implement verifyReservedBit2
}

void ReadingThread::verifyReservedBit3(WebSocketFrame frame) {
    // TODO: Implement verifyReservedBit3
}

void ReadingThread::verifyFrameOpcode(WebSocketFrame frame) {
    // TODO: Implement verifyFrameOpcode
}

void ReadingThread::verifyFrameMask(WebSocketFrame frame) {
    // TODO: Implement verifyFrameMask
}

void ReadingThread::verifyFrameFragmentation(WebSocketFrame frame) {
    // TODO: Implement verifyFrameFragmentation
}

void ReadingThread::verifyFrameSize(WebSocketFrame frame) {
    // TODO: Implement verifyFrameSize
}

WebSocketFrame ReadingThread::createCloseFrame(WebSocketException wse) {
    // TODO: Implement createCloseFrame
    return nullptr;
}

bool ReadingThread::handleFrame(WebSocketFrame frame) {
    // TODO: Implement handleFrame
    return false;
}

bool ReadingThread::handleContinuationFrame(WebSocketFrame frame) {
    // TODO: Implement handleContinuationFrame
    return false;
}

bool ReadingThread::handleTextFrame(WebSocketFrame frame) {
    // TODO: Implement handleTextFrame
    return false;
}

bool ReadingThread::handleBinaryFrame(WebSocketFrame frame) {
    // TODO: Implement handleBinaryFrame
    return false;
}

bool ReadingThread::handleCloseFrame(WebSocketFrame frame) {
    // TODO: Implement handleCloseFrame
    return false;
}

bool ReadingThread::handlePingFrame(WebSocketFrame frame) {
    // TODO: Implement handlePingFrame
    return false;
}

bool ReadingThread::handlePongFrame(WebSocketFrame frame) {
    // TODO: Implement handlePongFrame
    return false;
}

void ReadingThread::waitForCloseFrame() {
    // TODO: Implement waitForCloseFrame
}

void ReadingThread::notifyFinished() {
    // TODO: Implement notifyFinished
}

void ReadingThread::scheduleClose() {
    // TODO: Implement scheduleClose
}

void ReadingThread::scheduleCloseTask() {
    // TODO: Implement scheduleCloseTask
}

void ReadingThread::cancelClose() {
    // TODO: Implement cancelClose
}

void ReadingThread::cancelCloseTask() {
    // TODO: Implement cancelCloseTask
}

} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
