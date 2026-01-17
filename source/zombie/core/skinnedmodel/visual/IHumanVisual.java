// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.core.skinnedmodel.visual;

public interface IHumanVisual {
    HumanVisual getHumanVisual();

    void getItemVisuals(ItemVisuals itemVisuals);

    boolean isFemale();

    boolean isZombie();

    boolean isSkeleton();
}
