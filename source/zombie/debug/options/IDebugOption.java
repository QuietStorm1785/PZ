// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.debug.options;

public interface IDebugOption {
    String getName();

    IDebugOptionGroup getParent();

    void setParent(IDebugOptionGroup parent);
}
