// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.core.Styles;

/**
 * Really basic geometry data which is used by
 */
public class GeometryData {
    private final FloatList vertexData;
    private final ShortList indexData;

    /**
     * C'tor
     */
    public GeometryData(FloatList _vertexData, ShortList _indexData) {
        this.vertexData = _vertexData;
        this.indexData = _indexData;
    }

    public void clear() {
        this.vertexData.clear();
        this.indexData.clear();
    }

    public FloatList getVertexData() {
        return this.vertexData;
    }

    public ShortList getIndexData() {
        return this.indexData;
    }
}
