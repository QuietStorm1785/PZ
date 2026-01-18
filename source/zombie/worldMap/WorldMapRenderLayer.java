// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.worldMap;

import java.util.ArrayList;
import zombie.popman.ObjectPool;
import zombie.worldMap.styles.WorldMapStyleLayer;

public final class WorldMapRenderLayer {
    WorldMapStyleLayer m_styleLayer;
    final ArrayList<WorldMapFeature> m_features = new ArrayList<>();
    static ObjectPool<WorldMapRenderLayer> s_pool = new ObjectPool<>(WorldMapRenderLayer::new);
}
