#include "com\neovisionaries\ws\client/WritingThread.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

public WritingThread::WritingThread(WebSocket websocket) {
    // TODO: Implement WritingThread
    return nullptr;
}

void WritingThread::run() {
    // TODO: Implement run
}

void WritingThread::main() {
    // TODO: Implement main
}

void WritingThread::requestStop() {
    // TODO: Implement requestStop
}

bool WritingThread::queueFrame(WebSocketFrame frame) {
    // TODO: Implement queueFrame
    return false;
}

bool WritingThread::isHighPriorityFrame(WebSocketFrame frame) {
    // TODO: Implement isHighPriorityFrame
    return false;
}

void WritingThread::addHighPriorityFrame(WebSocketFrame frame) {
    // TODO: Implement addHighPriorityFrame
}

void WritingThread::queueFlush() {
    // TODO: Implement queueFlush
}

void WritingThread::flushIgnoreError() {
    // TODO: Implement flushIgnoreError
}

void WritingThread::flush() {
    // TODO: Implement flush
}

int WritingThread::waitForFrames() {
    // TODO: Implement waitForFrames
    return 0;
}

void WritingThread::sendFrames(bool last) {
    // TODO: Implement sendFrames
}

bool WritingThread::isFlushNeeded(bool last) {
    // TODO: Implement isFlushNeeded
    return false;
}

long WritingThread::flushIfLongInterval(long lastFlushAt) {
    // TODO: Implement flushIfLongInterval
    return 0;
}

void WritingThread::doFlush() {
    // TODO: Implement doFlush
}

void WritingThread::sendFrame(WebSocketFrame frame) {
    // TODO: Implement sendFrame
}

void WritingThread::changeToClosing() {
    // TODO: Implement changeToClosing
}

void WritingThread::notifyFinished() {
    // TODO: Implement notifyFinished
}

} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
