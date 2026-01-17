// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.core.skinnedmodel.advancedanimation;

public final class AnimBoneWeight {
    public String boneName;
    public float weight = 1.0F;
    public boolean includeDescendants = true;

    public AnimBoneWeight() {
    }

    public AnimBoneWeight(String string, float float0) {
        this.boneName = string;
        this.weight = float0;
        this.includeDescendants = true;
    }
}
