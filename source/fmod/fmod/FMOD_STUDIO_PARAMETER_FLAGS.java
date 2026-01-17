// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package fmod.fmod;

public enum FMOD_STUDIO_PARAMETER_FLAGS {
    FMOD_STUDIO_PARAMETER_READONLY(1),
    FMOD_STUDIO_PARAMETER_AUTOMATIC(2),
    FMOD_STUDIO_PARAMETER_GLOBAL(4),
    FMOD_STUDIO_PARAMETER_DISCRETE(8);

    public final int bit;

    private FMOD_STUDIO_PARAMETER_FLAGS(int int1) {
        this.bit = int1;
    }
}
