// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.core.skinnedmodel.model;

public final class SoftwareModelMeshInstance {
    public SoftwareModelMesh softwareMesh;
    public VertexBufferObject vb;
    public String name;

    public SoftwareModelMeshInstance(String _name, SoftwareModelMesh _softwareMesh) {
        this.name = _name;
        this.softwareMesh = _softwareMesh;
        this.vb = new VertexBufferObject();
        this.vb.elements = _softwareMesh.indicesUnskinned;
    }
}
