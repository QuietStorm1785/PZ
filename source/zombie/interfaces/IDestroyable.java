// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.interfaces;

public interface IDestroyable {
    /**
     * destory the object
     */
    void destroy();

    /**
     * returns if the object is destryed or not
     */
    boolean isDestroyed();
}
