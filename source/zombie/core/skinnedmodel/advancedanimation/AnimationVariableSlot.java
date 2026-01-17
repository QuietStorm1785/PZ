// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.core.skinnedmodel.advancedanimation;

public abstract class AnimationVariableSlot implements IAnimationVariableSlot {
    private final String m_key;

    protected AnimationVariableSlot(String string) {
        this.m_key = string.toLowerCase().trim();
    }

    @Override
    public String getKey() {
        return this.m_key;
    }
}
