// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.asset;

public abstract class AssetTask {
    public Asset m_asset;

    public AssetTask(Asset asset) {
        this.m_asset = asset;
    }

    public abstract void execute();

    public abstract void cancel();
}
