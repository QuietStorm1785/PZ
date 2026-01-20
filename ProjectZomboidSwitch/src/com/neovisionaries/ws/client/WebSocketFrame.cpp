#include <sstream>
#include <string>
#include "com\neovisionaries\ws\client/WebSocketFrame.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

bool WebSocketFrame::getFin() {
    // TODO: Implement getFin
    return false;
}

WebSocketFrame WebSocketFrame::setFin(bool fin) {
    // TODO: Implement setFin
    return nullptr;
}

bool WebSocketFrame::getRsv1() {
    // TODO: Implement getRsv1
    return false;
}

WebSocketFrame WebSocketFrame::setRsv1(bool rsv1) {
    // TODO: Implement setRsv1
    return nullptr;
}

bool WebSocketFrame::getRsv2() {
    // TODO: Implement getRsv2
    return false;
}

WebSocketFrame WebSocketFrame::setRsv2(bool rsv2) {
    // TODO: Implement setRsv2
    return nullptr;
}

bool WebSocketFrame::getRsv3() {
    // TODO: Implement getRsv3
    return false;
}

WebSocketFrame WebSocketFrame::setRsv3(bool rsv3) {
    // TODO: Implement setRsv3
    return nullptr;
}

int WebSocketFrame::getOpcode() {
    // TODO: Implement getOpcode
    return 0;
}

WebSocketFrame WebSocketFrame::setOpcode(int opcode) {
    // TODO: Implement setOpcode
    return nullptr;
}

bool WebSocketFrame::isContinuationFrame() {
    // TODO: Implement isContinuationFrame
    return false;
}

bool WebSocketFrame::isTextFrame() {
    // TODO: Implement isTextFrame
    return false;
}

bool WebSocketFrame::isBinaryFrame() {
    // TODO: Implement isBinaryFrame
    return false;
}

bool WebSocketFrame::isCloseFrame() {
    // TODO: Implement isCloseFrame
    return false;
}

bool WebSocketFrame::isPingFrame() {
    // TODO: Implement isPingFrame
    return false;
}

bool WebSocketFrame::isPongFrame() {
    // TODO: Implement isPongFrame
    return false;
}

bool WebSocketFrame::isDataFrame() {
    // TODO: Implement isDataFrame
    return false;
}

bool WebSocketFrame::isControlFrame() {
    // TODO: Implement isControlFrame
    return false;
}

bool WebSocketFrame::getMask() {
    // TODO: Implement getMask
    return false;
}

WebSocketFrame WebSocketFrame::setMask(bool mask) {
    // TODO: Implement setMask
    return nullptr;
}

bool WebSocketFrame::hasPayload() {
    // TODO: Implement hasPayload
    return false;
}

int WebSocketFrame::getPayloadLength() {
    // TODO: Implement getPayloadLength
    return 0;
}

std::string WebSocketFrame::getPayloadText() {
    // TODO: Implement getPayloadText
    return "";
}

WebSocketFrame WebSocketFrame::setPayload(byte[] payload) {
    // TODO: Implement setPayload
    return nullptr;
}

WebSocketFrame WebSocketFrame::setPayload(const std::string& payload) {
    // TODO: Implement setPayload
    return nullptr;
}

WebSocketFrame WebSocketFrame::setCloseFramePayload(int closeCode, const std::string& reason) {
    // TODO: Implement setCloseFramePayload
    return nullptr;
}

int WebSocketFrame::getCloseCode() {
    // TODO: Implement getCloseCode
    return 0;
}

std::string WebSocketFrame::getCloseReason() {
    // TODO: Implement getCloseReason
    return "";
}

std::string WebSocketFrame::toString() {
    // TODO: Implement toString
    return "";
}

bool WebSocketFrame::appendPayloadCommon(std::stringstream builder) {
    // TODO: Implement appendPayloadCommon
    return false;
}

void WebSocketFrame::appendPayloadText(std::stringstream builder) {
    // TODO: Implement appendPayloadText
}

void WebSocketFrame::appendPayloadClose(std::stringstream builder) {
    // TODO: Implement appendPayloadClose
}

void WebSocketFrame::appendPayloadBinary(std::stringstream builder) {
    // TODO: Implement appendPayloadBinary
}

WebSocketFrame WebSocketFrame::createContinuationFrame() {
    // TODO: Implement createContinuationFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::createContinuationFrame(byte[] payload) {
    // TODO: Implement createContinuationFrame
    return nullptr;
}

return WebSocketFrame::createContinuationFrame() {
    // TODO: Implement createContinuationFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::createContinuationFrame(const std::string& payload) {
    // TODO: Implement createContinuationFrame
    return nullptr;
}

return WebSocketFrame::createContinuationFrame() {
    // TODO: Implement createContinuationFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::createTextFrame(const std::string& payload) {
    // TODO: Implement createTextFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::createBinaryFrame(byte[] payload) {
    // TODO: Implement createBinaryFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::createCloseFrame() {
    // TODO: Implement createCloseFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::createCloseFrame(int closeCode) {
    // TODO: Implement createCloseFrame
    return nullptr;
}

return WebSocketFrame::createCloseFrame() {
    // TODO: Implement createCloseFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::createCloseFrame(int closeCode, const std::string& reason) {
    // TODO: Implement createCloseFrame
    return nullptr;
}

return WebSocketFrame::createCloseFrame() {
    // TODO: Implement createCloseFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::createPingFrame() {
    // TODO: Implement createPingFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::createPingFrame(byte[] payload) {
    // TODO: Implement createPingFrame
    return nullptr;
}

return WebSocketFrame::createPingFrame() {
    // TODO: Implement createPingFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::createPingFrame(const std::string& payload) {
    // TODO: Implement createPingFrame
    return nullptr;
}

return WebSocketFrame::createPingFrame() {
    // TODO: Implement createPingFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::createPongFrame() {
    // TODO: Implement createPongFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::createPongFrame(byte[] payload) {
    // TODO: Implement createPongFrame
    return nullptr;
}

return WebSocketFrame::createPongFrame() {
    // TODO: Implement createPongFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::createPongFrame(const std::string& payload) {
    // TODO: Implement createPongFrame
    return nullptr;
}

return WebSocketFrame::createPongFrame() {
    // TODO: Implement createPongFrame
    return nullptr;
}

WebSocketFrame WebSocketFrame::compressFrame(WebSocketFrame frame, PerMessageCompressionExtension pmce) {
    // TODO: Implement compressFrame
    return nullptr;
}

return WebSocketFrame::split() {
    // TODO: Implement split
    return nullptr;
}

} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
