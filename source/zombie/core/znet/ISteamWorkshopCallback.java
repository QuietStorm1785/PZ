// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.core.znet;

public interface ISteamWorkshopCallback {
    void onItemCreated(long var1, boolean var3);

    void onItemNotCreated(int var1);

    void onItemUpdated(boolean var1);

    void onItemNotUpdated(int var1);

    void onItemSubscribed(long var1);

    void onItemNotSubscribed(long var1, int var3);

    void onItemDownloaded(long var1);

    void onItemNotDownloaded(long var1, int var3);

    void onItemQueryCompleted(long var1, int var3);

    void onItemQueryNotCompleted(long var1, int var3);
}
