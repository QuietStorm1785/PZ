// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.worldMap.styles;

import java.util.ArrayList;

public final class WorldMapStyle {
    public final ArrayList<WorldMapStyleLayer> m_layers = new ArrayList<>();

    public void copyFrom(WorldMapStyle other) {
        this.m_layers.clear();
        this.m_layers.addAll(other.m_layers);
    }
}
