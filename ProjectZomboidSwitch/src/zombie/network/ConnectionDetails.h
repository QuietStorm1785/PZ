#pragma once

// Ported from Java: ConnectionDetails

namespace zombie {
namespace network {

class UdpConnection;
class LogonResult;
class ByteBuffer;

class ConnectionDetails {
public:
    ConnectionDetails();
    ~ConnectionDetails();

    // Static methods ported from Java
    static void write(UdpConnection* conn, LogonResult* logon, ByteBuffer* buffer);
    static void parse(ByteBuffer* buffer);
    static void writeServerDetails(ByteBuffer* buffer, UdpConnection* conn, LogonResult* logon);
    static void writeGameMap(ByteBuffer* buffer);
    static void writeWorkshopItems(ByteBuffer* buffer);
    static void writeMods(ByteBuffer* buffer);
    static void writeStartLocation(ByteBuffer* buffer);
    static void writeServerOptions(ByteBuffer* buffer);
    static void writeSandboxOptions(ByteBuffer* buffer);
    static void writeGameTime(ByteBuffer* buffer);
    static void writeErosionMain(ByteBuffer* buffer);
    static void writeGlobalObjects(ByteBuffer* buffer);
    static void writeResetID(ByteBuffer* buffer);
    static void writeBerries(ByteBuffer* buffer);
    static void writeWorldDictionary(ByteBuffer* buffer);
};

} // namespace network
} // namespace zombie
