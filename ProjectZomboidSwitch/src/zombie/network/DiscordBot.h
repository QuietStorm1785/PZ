
#pragma once

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: DiscordBot and inner classes Connector, Listener

class DiscordBot {
public:
    DiscordBot();
    ~DiscordBot();
    // TODO: Port fields and methods from Java DiscordBot

    class Connector {
    public:
        Connector();
        ~Connector();
        // TODO: Port fields and methods from Java DiscordBot.Connector
    };
    class Listener {
    public:
        Listener();
        ~Listener();
        // TODO: Port fields and methods from Java DiscordBot.Listener
    };
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
