#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class ZNetStatistics {
public:
 long lastUserMessageBytesPushed;
 long lastUserMessageBytesSent;
 long lastUserMessageBytesResent;
 long lastUserMessageBytesReceivedProcessed;
 long lastUserMessageBytesReceivedIgnored;
 long lastActualBytesSent;
 long lastActualBytesReceived;
 long totalUserMessageBytesPushed;
 long totalUserMessageBytesSent;
 long totalUserMessageBytesResent;
 long totalUserMessageBytesReceivedProcessed;
 long totalUserMessageBytesReceivedIgnored;
 long totalActualBytesSent;
 long totalActualBytesReceived;
 long connectionStartTime;
 bool isLimitedByCongestionControl;
 long BPSLimitByCongestionControl;
 bool isLimitedByOutgoingBandwidthLimit;
 long BPSLimitByOutgoingBandwidthLimit;
 long messageInSendBufferImmediate;
 long messageInSendBufferHigh;
 long messageInSendBufferMedium;
 long messageInSendBufferLow;
 double bytesInSendBufferImmediate;
 double bytesInSendBufferHigh;
 double bytesInSendBufferMedium;
 double bytesInSendBufferLow;
 long messagesInResendBuffer;
 long bytesInResendBuffer;
 double packetlossLastSecond;
 double packetlossTotal;
}
} // namespace znet
} // namespace core
} // namespace zombie
