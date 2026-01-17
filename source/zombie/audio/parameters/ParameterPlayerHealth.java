// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.audio.parameters;

import zombie.audio.FMODLocalParameter;
import zombie.characters.IsoPlayer;
import zombie.core.math.PZMath;

public final class ParameterPlayerHealth extends FMODLocalParameter {
    private final IsoPlayer player;

    public ParameterPlayerHealth(IsoPlayer _player) {
        super("PlayerHealth");
        this.player = _player;
    }

    @Override
    public float calculateCurrentValue() {
        return PZMath.clamp(this.player.getHealth() / 100.0F, 0.0F, 1.0F);
    }
}
