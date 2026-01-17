// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package org.lwjglx.util.glu.tessellation;

class GLUface {
    public GLUface next;
    public GLUface prev;
    public GLUhalfEdge anEdge;
    public Object data;
    public GLUface trail;
    public boolean marked;
    public boolean inside;
}
