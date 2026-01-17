// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package fmod.fmod;

public final class FMOD_STUDIO_PARAMETER_ID {
    private final long nativePtr;

    public FMOD_STUDIO_PARAMETER_ID(long arg0) {
        this.nativePtr = arg0;
    }

    public long address() {
        return this.nativePtr;
    }
}
