#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace zombie {
namespace core {
namespace raknet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TestServer {
public:
 static RakNetPeerInterface server;
 static ByteBuffer buf = ByteBuffer.allocate(2048);

 static void main(String[] var0) {
 server = std::make_unique<RakNetPeerInterface>();
 server.SetServerPort(12203, 12204);
 server.Init(false);
 int int0 = server.Startup(32);
 System.out.println("Result: " + int0);
 server.SetMaximumIncomingConnections(32);
 server.SetOccasionalPing(true);
 server.SetIncomingPassword("spiffo");
 bool boolean0 = false;

 while (!boolean0) {
 std::string string = "This is a test message";
 ByteBuffer byteBuffer = Receive();
 decode(byteBuffer);
 }
 }

 static void decode(ByteBuffer byteBuffer) {
 int int0 = byteBuffer.get() & 255;
 switch (int0) {
 case 0:
 case 1:
 System.out.println("PING");
 break;
 case 19:
 int int1 = byteBuffer.get() & 255;
 long long0 = server.getGuidFromIndex(int1);
 break;
 case 21:
 System.out.println("ID_DISCONNECTION_NOTIFICATION");
 break;
 case 22:
 System.out.println("ID_CONNECTION_LOST");
 break;
 case 25:
 System.out.println("ID_INCOMPATIBLE_PROTOCOL_VERSION");
 break;
 default:
 System.out.println("Other: " + int0);
 }
 }

 static ByteBuffer Receive() {
 int int0 = buf.position();
 bool boolean0 = false;

 do {
 try {
 Thread.sleep(1L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }

 boolean0 = server.Receive(buf);
 } while (!boolean0);

 return buf;
 }
}
} // namespace raknet
} // namespace core
} // namespace zombie
