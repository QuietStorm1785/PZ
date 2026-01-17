// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.audio;

import fmod.fmod.FMODFootstep;
import fmod.fmod.FMODVoice;

public class DummySoundBank extends BaseSoundBank {
    @Override
    public void addVoice(String alias, String sound, float priority) {
    }

    @Override
    public void addFootstep(String alias, String grass, String wood, String concrete, String upstairs) {
    }

    @Override
    public FMODVoice getVoice(String alias) {
        return null;
    }

    @Override
    public FMODFootstep getFootstep(String alias) {
        return null;
    }
}
