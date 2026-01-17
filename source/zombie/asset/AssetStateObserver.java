// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.asset;

public interface AssetStateObserver {
    void onStateChanged(Asset.State oldState, Asset.State newState, Asset asset);
}
