// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.debug.options;

public interface IDebugOptionGroup extends IDebugOption {
    Iterable<IDebugOption> getChildren();

    void addChild(IDebugOption childOption);

    void onChildAdded(IDebugOption newChild);

    void onDescendantAdded(IDebugOption newDescendant);
}
