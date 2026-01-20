#include <string>
#include "com\neovisionaries\ws\client/PeriodicalFrameSender.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

public PeriodicalFrameSender::PeriodicalFrameSender(WebSocket webSocket, const std::string& timerName, PayloadGenerator generator) {
    // TODO: Implement PeriodicalFrameSender
    return nullptr;
}

void PeriodicalFrameSender::start() {
    // TODO: Implement start
}

void PeriodicalFrameSender::stop() {
    // TODO: Implement stop
}

long PeriodicalFrameSender::getInterval() {
    // TODO: Implement getInterval
    return 0;
}

void PeriodicalFrameSender::setInterval(long interval) {
    // TODO: Implement setInterval
}

PayloadGenerator PeriodicalFrameSender::getPayloadGenerator() {
    // TODO: Implement getPayloadGenerator
    return nullptr;
}

void PeriodicalFrameSender::setPayloadGenerator(PayloadGenerator generator) {
    // TODO: Implement setPayloadGenerator
}

void PeriodicalFrameSender::doTask() {
    // TODO: Implement doTask
}

WebSocketFrame PeriodicalFrameSender::createFrame() {
    // TODO: Implement createFrame
    return nullptr;
}

bool PeriodicalFrameSender::schedule(Timer timer, Task task, long interval) {
    // TODO: Implement schedule
    return false;
}

} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
