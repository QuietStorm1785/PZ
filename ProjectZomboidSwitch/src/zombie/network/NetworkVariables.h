
#pragma once

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: NetworkVariables and all inner classes

class NetworkVariables {
public:
    NetworkVariables();
    ~NetworkVariables();
    // TODO: Port fields and methods from Java NetworkVariables

    // Inner classes from Java (PredictionTypes, ThumpType, WalkType, ZombieState)
    class PredictionTypes {
    public:
        PredictionTypes();
        ~PredictionTypes();
        // TODO: Port fields and methods from Java NetworkVariables.PredictionTypes
    };
    class ThumpType {
    public:
        ThumpType();
        ~ThumpType();
        // TODO: Port fields and methods from Java NetworkVariables.ThumpType
    };
    class WalkType {
    public:
        WalkType();
        ~WalkType();
        // TODO: Port fields and methods from Java NetworkVariables.WalkType
    };
    class ZombieState {
    public:
        ZombieState();
        ~ZombieState();
        // TODO: Port fields and methods from Java NetworkVariables.ZombieState
    };
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
