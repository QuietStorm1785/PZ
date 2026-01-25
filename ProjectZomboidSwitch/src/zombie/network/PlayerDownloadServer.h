
#pragma once

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: PlayerDownloadServer and all inner classes

class PlayerDownloadServer {
public:
    PlayerDownloadServer();
    ~PlayerDownloadServer();
    // TODO: Port fields and methods from Java PlayerDownloadServer

    // Inner classes from Java (PlayerDownloadServer$1, EThreadCommand, WorkerThread, WorkerThreadCommand)
    class Inner1 {
    public:
        Inner1();
        ~Inner1();
        // TODO: Port fields and methods from Java PlayerDownloadServer$1
    };
    class EThreadCommand {
    public:
        EThreadCommand();
        ~EThreadCommand();
        // TODO: Port fields and methods from Java PlayerDownloadServer.EThreadCommand
    };
    class WorkerThread {
    public:
        WorkerThread();
        ~WorkerThread();
        // TODO: Port fields and methods from Java PlayerDownloadServer.WorkerThread
    };
    class WorkerThreadCommand {
    public:
        WorkerThreadCommand();
        ~WorkerThreadCommand();
        // TODO: Port fields and methods from Java PlayerDownloadServer.WorkerThreadCommand
    };
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
