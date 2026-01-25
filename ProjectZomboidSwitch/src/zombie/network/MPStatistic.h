
#pragma once

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: MPStatistic and all inner classes

class MPStatistic {
public:
    MPStatistic();
    ~MPStatistic();
    // TODO: Port fields and methods from Java MPStatistic

    // Inner classes from Java (MainThreadStatistic, ProbeStatistic, SaveTasksStatistic, ServerCellStatistic, TasksStatistic, ThreadStatistic)
    class MainThreadStatistic {
    public:
        MainThreadStatistic();
        ~MainThreadStatistic();
        // TODO: Port fields and methods from Java MPStatistic.MainThreadStatistic
    };
    class ProbeStatistic {
    public:
        ProbeStatistic();
        ~ProbeStatistic();
        // TODO: Port fields and methods from Java MPStatistic.ProbeStatistic
    };
    class SaveTasksStatistic {
    public:
        SaveTasksStatistic();
        ~SaveTasksStatistic();
        // TODO: Port fields and methods from Java MPStatistic.SaveTasksStatistic
    };
    class ServerCellStatistic {
    public:
        ServerCellStatistic();
        ~ServerCellStatistic();
        // TODO: Port fields and methods from Java MPStatistic.ServerCellStatistic
    };
    class TasksStatistic {
    public:
        TasksStatistic();
        ~TasksStatistic();
        // TODO: Port fields and methods from Java MPStatistic.TasksStatistic
    };
    class ThreadStatistic {
    public:
        ThreadStatistic();
        ~ThreadStatistic();
        // TODO: Port fields and methods from Java MPStatistic.ThreadStatistic
    };
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
