
#pragma once

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: GameServerWorkshopItems and all inner classes

class GameServerWorkshopItems {
public:
    GameServerWorkshopItems();
    ~GameServerWorkshopItems();

    // Static methods
    static void noise(const std::string& msg);
    static bool Install(const std::vector<long>& ids);
    static bool QueryItemDetails(std::vector<class WorkshopItem*>& items);

    // --- Inner classes from Java ---
    class Inner1 {
    public:
        Inner1();
        ~Inner1();
        // (No fields in Java $1 class)
    };

    class ItemQuery {
    public:
        long handle;
        std::vector<zombie::core::znet::SteamUGCDetails> details;
        bool bCompleted;
        bool bNotCompleted;
        ItemQuery();
        ~ItemQuery();
        bool isCompleted() const;
        bool isNotCompleted() const;
        void onItemCreated(long, bool);
        void onItemNotCreated(int);
        void onItemUpdated(bool);
        void onItemNotUpdated(int);
        void onItemSubscribed(long);
        void onItemNotSubscribed(long, int);
        void onItemDownloaded(long);
        void onItemNotDownloaded(long, int);
        void onItemQueryCompleted(long, int);
        void onItemQueryNotCompleted(long, int);
    };

    enum class WorkshopInstallState {
        CheckItemState,
        DownloadPending,
        Ready,
        Fail
    };

    class WorkshopItem {
    public:
        long ID;
        WorkshopInstallState state;
        long downloadStartTime;
        long downloadQueryTime;
        std::string error;
        std::optional<zombie::core::znet::SteamUGCDetails> details;
        WorkshopItem();
        ~WorkshopItem();
        void update();
        void setState(WorkshopInstallState s);
        void CheckItemState();
        void RemoveFolderForReinstall();
        void DownloadPending();
        class Inner1 {
        public:
            WorkshopItem* parent;
            Inner1(WorkshopItem* item) : parent(item) {}
            Inner1();
            ~Inner1();
            // File visitor methods (stubs)
            int visitFile(const std::string& path /*, const BasicFileAttributes& attrs */);
            int postVisitDirectory(const std::string& path /*, std::exception_ptr ex */);
        };
    };
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
