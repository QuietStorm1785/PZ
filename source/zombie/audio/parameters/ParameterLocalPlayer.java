// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.audio.parameters;

import zombie.audio.FMODLocalParameter;
import zombie.characters.IsoPlayer;

public final class ParameterLocalPlayer extends FMODLocalParameter {
    private final IsoPlayer player;

    public ParameterLocalPlayer(IsoPlayer _player) {
        super("LocalPlayer");
        this.player = _player;
    }

    @Override
    public float calculateCurrentValue() {
        return this.player.isLocalPlayer() ? 1.0F : 0.0F;
    }
}
