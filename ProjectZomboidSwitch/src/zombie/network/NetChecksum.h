
#pragma once

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: NetChecksum and all inner classes

class NetChecksum {
public:
    NetChecksum();
    ~NetChecksum();
    // TODO: Port fields and methods from Java NetChecksum

    // Inner classes from Java (NetChecksum$1, Checksummer, Comparer, Comparer$State, GroupOfFiles)
    class Inner1 {
    public:
        Inner1();
        ~Inner1();
        // TODO: Port fields and methods from Java NetChecksum$1
    };
    class Checksummer {
    public:
        Checksummer();
        ~Checksummer();
        // TODO: Port fields and methods from Java NetChecksum.Checksummer
    };
    class Comparer {
    public:
        Comparer();
        ~Comparer();
        // TODO: Port fields and methods from Java NetChecksum.Comparer
        class State {
        public:
            State();
            ~State();
            // TODO: Port fields and methods from Java NetChecksum.Comparer.State
        };
    };
    class GroupOfFiles {
    public:
        GroupOfFiles();
        ~GroupOfFiles();
        // TODO: Port fields and methods from Java NetChecksum.GroupOfFiles
    };
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
