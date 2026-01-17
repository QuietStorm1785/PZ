// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package org.lwjglx.util.vector;

import java.nio.FloatBuffer;

public interface ReadableVector {
    float length();

    float lengthSquared();

    Vector store(FloatBuffer var1);
}
