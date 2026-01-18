// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.core.znet;

public interface IServerBrowserCallback {
    void OnServerResponded(int var1);

    void OnServerFailedToRespond(int var1);

    void OnRefreshComplete();

    void OnServerResponded(String var1, int var2);

    void OnServerFailedToRespond(String var1, int var2);

    void OnSteamRulesRefreshComplete(String var1, int var2);
}
