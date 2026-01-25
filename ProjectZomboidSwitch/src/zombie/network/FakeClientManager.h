
#pragma once

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: FakeClientManager and all inner classes

class FakeClientManager {
public:
    FakeClientManager();
    ~FakeClientManager();
    // TODO: Port fields and methods from Java FakeClientManager

    // Inner classes from Java (FakeClientManager$1, Client, Client$Request, Client$State, HordeCreator, Movement, Movement$Motion, Movement$Type, Network, Player, Player$Clothes, PlayerManager, PlayerManager$RemotePlayer, SoundMaker, StringUTF, Zombie, ZombieSimulator, ZombieSimulator$Behaviour)
    class Inner1 {
    public:
        Inner1();
        ~Inner1();
        // TODO: Port fields and methods from Java FakeClientManager$1
    };
    class Client {
    public:
        Client();
        ~Client();
        // TODO: Port fields and methods from Java FakeClientManager.Client
        class Request {
        public:
            Request();
            ~Request();
            // TODO: Port fields and methods from Java FakeClientManager.Client.Request
        };
        class State {
        public:
            State();
            ~State();
            // TODO: Port fields and methods from Java FakeClientManager.Client.State
        };
    };
    class HordeCreator {
    public:
        HordeCreator();
        ~HordeCreator();
        // TODO: Port fields and methods from Java FakeClientManager.HordeCreator
    };
    class Movement {
    public:
        Movement();
        ~Movement();
        // TODO: Port fields and methods from Java FakeClientManager.Movement
        class Motion {
        public:
            Motion();
            ~Motion();
            // TODO: Port fields and methods from Java FakeClientManager.Movement.Motion
        };
        class Type {
        public:
            Type();
            ~Type();
            // TODO: Port fields and methods from Java FakeClientManager.Movement.Type
        };
    };
    class Network {
    public:
        Network();
        ~Network();
        // TODO: Port fields and methods from Java FakeClientManager.Network
    };
    class Player {
    public:
        Player();
        ~Player();
        // TODO: Port fields and methods from Java FakeClientManager.Player
        class Clothes {
        public:
            Clothes();
            ~Clothes();
            // TODO: Port fields and methods from Java FakeClientManager.Player.Clothes
        };
    };
    class PlayerManager {
    public:
        PlayerManager();
        ~PlayerManager();
        // TODO: Port fields and methods from Java FakeClientManager.PlayerManager
        class RemotePlayer {
        public:
            RemotePlayer();
            ~RemotePlayer();
            // TODO: Port fields and methods from Java FakeClientManager.PlayerManager.RemotePlayer
        };
    };
    class SoundMaker {
    public:
        SoundMaker();
        ~SoundMaker();
        // TODO: Port fields and methods from Java FakeClientManager.SoundMaker
    };
    class StringUTF {
    public:
        StringUTF();
        ~StringUTF();
        // TODO: Port fields and methods from Java FakeClientManager.StringUTF
    };
    class Zombie {
    public:
        Zombie();
        ~Zombie();
        // TODO: Port fields and methods from Java FakeClientManager.Zombie
    };
    class ZombieSimulator {
    public:
        ZombieSimulator();
        ~ZombieSimulator();
        // TODO: Port fields and methods from Java FakeClientManager.ZombieSimulator
        class Behaviour {
        public:
            Behaviour();
            ~Behaviour();
            // TODO: Port fields and methods from Java FakeClientManager.ZombieSimulator.Behaviour
        };
    };
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
