
#pragma once

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: PacketTypes and all inner classes

class PacketTypes {
public:
    PacketTypes();
    ~PacketTypes();
    // TODO: Port fields and methods from Java PacketTypes

    // Inner classes from Java (CallbackClientProcess, CallbackServerProcess, PacketAuthorization, PacketAuthorization$Policy, PacketAuthorization$UnauthorizedPacketPolicy, PacketType)
    class CallbackClientProcess {
    public:
        CallbackClientProcess();
        ~CallbackClientProcess();
        // TODO: Port fields and methods from Java PacketTypes.CallbackClientProcess
    };
    class CallbackServerProcess {
    public:
        CallbackServerProcess();
        ~CallbackServerProcess();
        // TODO: Port fields and methods from Java PacketTypes.CallbackServerProcess
    };
    class PacketAuthorization {
    public:
        PacketAuthorization();
        ~PacketAuthorization();
        // TODO: Port fields and methods from Java PacketTypes.PacketAuthorization
        class Policy {
        public:
            Policy();
            ~Policy();
            // TODO: Port fields and methods from Java PacketTypes.PacketAuthorization.Policy
        };
        class UnauthorizedPacketPolicy {
        public:
            UnauthorizedPacketPolicy();
            ~UnauthorizedPacketPolicy();
            // TODO: Port fields and methods from Java PacketTypes.PacketAuthorization.UnauthorizedPacketPolicy
        };
    };
    class PacketType {
    public:
        PacketType();
        ~PacketType();
        // TODO: Port fields and methods from Java PacketTypes.PacketType
    };
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
