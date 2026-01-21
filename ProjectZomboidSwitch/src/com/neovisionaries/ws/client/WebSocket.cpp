#include <queue>
#include <string>
#include "com/neovisionaries/ws/client/WebSocket.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

WebSocket WebSocket::recreate() {
    // TODO: Implement recreate
    return nullptr;
}

WebSocket WebSocket::recreate(int timeout) {
    // TODO: Implement recreate
    return nullptr;
}

void WebSocket::finalize() {
    // TODO: Implement finalize
}

WebSocketState WebSocket::getState() {
    // TODO: Implement getState
    return nullptr;
}

bool WebSocket::isOpen() {
    // TODO: Implement isOpen
    return false;
}

bool WebSocket::isInState(WebSocketState state) {
    // TODO: Implement isInState
    return false;
}

WebSocket WebSocket::addProtocol(const std::string& protocol) {
    // TODO: Implement addProtocol
    return nullptr;
}

WebSocket WebSocket::removeProtocol(const std::string& protocol) {
    // TODO: Implement removeProtocol
    return nullptr;
}

WebSocket WebSocket::clearProtocols() {
    // TODO: Implement clearProtocols
    return nullptr;
}

WebSocket WebSocket::addExtension(WebSocketExtension extension) {
    // TODO: Implement addExtension
    return nullptr;
}

WebSocket WebSocket::addExtension(const std::string& extension) {
    // TODO: Implement addExtension
    return nullptr;
}

WebSocket WebSocket::removeExtension(WebSocketExtension extension) {
    // TODO: Implement removeExtension
    return nullptr;
}

WebSocket WebSocket::removeExtensions(const std::string& name) {
    // TODO: Implement removeExtensions
    return nullptr;
}

WebSocket WebSocket::clearExtensions() {
    // TODO: Implement clearExtensions
    return nullptr;
}

WebSocket WebSocket::addHeader(const std::string& name, const std::string& value) {
    // TODO: Implement addHeader
    return nullptr;
}

WebSocket WebSocket::removeHeaders(const std::string& name) {
    // TODO: Implement removeHeaders
    return nullptr;
}

WebSocket WebSocket::clearHeaders() {
    // TODO: Implement clearHeaders
    return nullptr;
}

WebSocket WebSocket::setUserInfo(const std::string& userInfo) {
    // TODO: Implement setUserInfo
    return nullptr;
}

WebSocket WebSocket::setUserInfo(const std::string& id, const std::string& password) {
    // TODO: Implement setUserInfo
    return nullptr;
}

WebSocket WebSocket::clearUserInfo() {
    // TODO: Implement clearUserInfo
    return nullptr;
}

bool WebSocket::isExtended() {
    // TODO: Implement isExtended
    return false;
}

WebSocket WebSocket::setExtended(bool extended) {
    // TODO: Implement setExtended
    return nullptr;
}

bool WebSocket::isAutoFlush() {
    // TODO: Implement isAutoFlush
    return false;
}

WebSocket WebSocket::setAutoFlush(bool auto) {
    // TODO: Implement setAutoFlush
    return nullptr;
}

bool WebSocket::isMissingCloseFrameAllowed() {
    // TODO: Implement isMissingCloseFrameAllowed
    return false;
}

WebSocket WebSocket::setMissingCloseFrameAllowed(bool allowed) {
    // TODO: Implement setMissingCloseFrameAllowed
    return nullptr;
}

WebSocket WebSocket::flush() {
    // TODO: Implement flush
    return nullptr;
}

int WebSocket::getFrameQueueSize() {
    // TODO: Implement getFrameQueueSize
    return 0;
}

WebSocket WebSocket::setFrameQueueSize(int size) {
    // TODO: Implement setFrameQueueSize
    return nullptr;
}

int WebSocket::getMaxPayloadSize() {
    // TODO: Implement getMaxPayloadSize
    return 0;
}

WebSocket WebSocket::setMaxPayloadSize(int size) {
    // TODO: Implement setMaxPayloadSize
    return nullptr;
}

long WebSocket::getPingInterval() {
    // TODO: Implement getPingInterval
    return 0;
}

WebSocket WebSocket::setPingInterval(long interval) {
    // TODO: Implement setPingInterval
    return nullptr;
}

long WebSocket::getPongInterval() {
    // TODO: Implement getPongInterval
    return 0;
}

WebSocket WebSocket::setPongInterval(long interval) {
    // TODO: Implement setPongInterval
    return nullptr;
}

PayloadGenerator WebSocket::getPingPayloadGenerator() {
    // TODO: Implement getPingPayloadGenerator
    return nullptr;
}

WebSocket WebSocket::setPingPayloadGenerator(PayloadGenerator generator) {
    // TODO: Implement setPingPayloadGenerator
    return nullptr;
}

PayloadGenerator WebSocket::getPongPayloadGenerator() {
    // TODO: Implement getPongPayloadGenerator
    return nullptr;
}

WebSocket WebSocket::setPongPayloadGenerator(PayloadGenerator generator) {
    // TODO: Implement setPongPayloadGenerator
    return nullptr;
}

WebSocket WebSocket::addListener(WebSocketListener listener) {
    // TODO: Implement addListener
    return nullptr;
}

WebSocket WebSocket::addListeners(List<WebSocketListener> listeners) {
    // TODO: Implement addListeners
    return nullptr;
}

WebSocket WebSocket::removeListener(WebSocketListener listener) {
    // TODO: Implement removeListener
    return nullptr;
}

WebSocket WebSocket::removeListeners(List<WebSocketListener> listeners) {
    // TODO: Implement removeListeners
    return nullptr;
}

WebSocket WebSocket::clearListeners() {
    // TODO: Implement clearListeners
    return nullptr;
}

Socket WebSocket::getSocket() {
    // TODO: Implement getSocket
    return nullptr;
}

URI WebSocket::getURI() {
    // TODO: Implement getURI
    return nullptr;
}

WebSocket WebSocket::connect() {
    // TODO: Implement connect
    return nullptr;
}

WebSocket WebSocket::connectAsynchronously() {
    // TODO: Implement connectAsynchronously
    return nullptr;
}

new WebSocket::ConnectThread() {
    // TODO: Implement ConnectThread
    return nullptr;
}

WebSocket WebSocket::disconnect() {
    // TODO: Implement disconnect
    return nullptr;
}

WebSocket WebSocket::disconnect(int closeCode) {
    // TODO: Implement disconnect
    return nullptr;
}

WebSocket WebSocket::disconnect(const std::string& reason) {
    // TODO: Implement disconnect
    return nullptr;
}

WebSocket WebSocket::disconnect(int closeCode, const std::string& reason) {
    // TODO: Implement disconnect
    return nullptr;
}

WebSocket WebSocket::disconnect(int closeCode, const std::string& reason, long closeDelay) {
    // TODO: Implement disconnect
    return nullptr;
}

std::string WebSocket::getAgreedProtocol() {
    // TODO: Implement getAgreedProtocol
    return "";
}

WebSocket WebSocket::sendFrame(WebSocketFrame frame) {
    // TODO: Implement sendFrame
    return nullptr;
}

WebSocket WebSocket::sendContinuation() {
    // TODO: Implement sendContinuation
    return nullptr;
}

WebSocket WebSocket::sendContinuation(bool fin) {
    // TODO: Implement sendContinuation
    return nullptr;
}

WebSocket WebSocket::sendContinuation(const std::string& payload) {
    // TODO: Implement sendContinuation
    return nullptr;
}

WebSocket WebSocket::sendContinuation(const std::string& payload, bool fin) {
    // TODO: Implement sendContinuation
    return nullptr;
}

WebSocket WebSocket::sendContinuation(byte[] payload) {
    // TODO: Implement sendContinuation
    return nullptr;
}

WebSocket WebSocket::sendContinuation(byte[] payload, bool fin) {
    // TODO: Implement sendContinuation
    return nullptr;
}

WebSocket WebSocket::sendText(const std::string& message) {
    // TODO: Implement sendText
    return nullptr;
}

WebSocket WebSocket::sendText(const std::string& payload, bool fin) {
    // TODO: Implement sendText
    return nullptr;
}

WebSocket WebSocket::sendBinary(byte[] message) {
    // TODO: Implement sendBinary
    return nullptr;
}

WebSocket WebSocket::sendBinary(byte[] payload, bool fin) {
    // TODO: Implement sendBinary
    return nullptr;
}

WebSocket WebSocket::sendClose() {
    // TODO: Implement sendClose
    return nullptr;
}

WebSocket WebSocket::sendClose(int closeCode) {
    // TODO: Implement sendClose
    return nullptr;
}

WebSocket WebSocket::sendClose(int closeCode, const std::string& reason) {
    // TODO: Implement sendClose
    return nullptr;
}

WebSocket WebSocket::sendPing() {
    // TODO: Implement sendPing
    return nullptr;
}

WebSocket WebSocket::sendPing(byte[] payload) {
    // TODO: Implement sendPing
    return nullptr;
}

WebSocket WebSocket::sendPing(const std::string& payload) {
    // TODO: Implement sendPing
    return nullptr;
}

WebSocket WebSocket::sendPong() {
    // TODO: Implement sendPong
    return nullptr;
}

WebSocket WebSocket::sendPong(byte[] payload) {
    // TODO: Implement sendPong
    return nullptr;
}

WebSocket WebSocket::sendPong(const std::string& payload) {
    // TODO: Implement sendPong
    return nullptr;
}

void WebSocket::changeStateOnConnect() {
    // TODO: Implement changeStateOnConnect
}

WebSocketInputStream WebSocket::openInputStream(Socket socket) {
    // TODO: Implement openInputStream
    return nullptr;
}

WebSocketOutputStream WebSocket::openOutputStream(Socket socket) {
    // TODO: Implement openOutputStream
    return nullptr;
}

std::string WebSocket::generateWebSocketKey() {
    // TODO: Implement generateWebSocketKey
    return "";
}

void WebSocket::writeHandshake(WebSocketOutputStream output, const std::string& key) {
    // TODO: Implement writeHandshake
}

void WebSocket::startThreads() {
    // TODO: Implement startThreads
}

void WebSocket::stopThreads(long closeDelay) {
    // TODO: Implement stopThreads
}

WebSocketInputStream WebSocket::getInput() {
    // TODO: Implement getInput
    return nullptr;
}

WebSocketOutputStream WebSocket::getOutput() {
    // TODO: Implement getOutput
    return nullptr;
}

StateManager WebSocket::getStateManager() {
    // TODO: Implement getStateManager
    return nullptr;
}

ListenerManager WebSocket::getListenerManager() {
    // TODO: Implement getListenerManager
    return nullptr;
}

HandshakeBuilder WebSocket::getHandshakeBuilder() {
    // TODO: Implement getHandshakeBuilder
    return nullptr;
}

void WebSocket::setAgreedExtensions(List<WebSocketExtension> extensions) {
    // TODO: Implement setAgreedExtensions
}

void WebSocket::setAgreedProtocol(const std::string& protocol) {
    // TODO: Implement setAgreedProtocol
}

void WebSocket::onReadingThreadStarted() {
    // TODO: Implement onReadingThreadStarted
}

void WebSocket::onWritingThreadStarted() {
    // TODO: Implement onWritingThreadStarted
}

void WebSocket::callOnConnectedIfNotYet() {
    // TODO: Implement callOnConnectedIfNotYet
}

void WebSocket::onThreadsStarted() {
    // TODO: Implement onThreadsStarted
}

void WebSocket::onReadingThreadFinished(WebSocketFrame closeFrame) {
    // TODO: Implement onReadingThreadFinished
}

void WebSocket::onWritingThreadFinished(WebSocketFrame closeFrame) {
    // TODO: Implement onWritingThreadFinished
}

void WebSocket::onThreadsFinished() {
    // TODO: Implement onThreadsFinished
}

void WebSocket::finish() {
    // TODO: Implement finish
}

void WebSocket::finishAsynchronously() {
    // TODO: Implement finishAsynchronously
}

new WebSocket::1() {
    // TODO: Implement 1
    return nullptr;
}

PerMessageCompressionExtension WebSocket::findAgreedPerMessageCompressionExtension() {
    // TODO: Implement findAgreedPerMessageCompressionExtension
    return nullptr;
}

PerMessageCompressionExtension WebSocket::getPerMessageCompressionExtension() {
    // TODO: Implement getPerMessageCompressionExtension
    return nullptr;
}

} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
