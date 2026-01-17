// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package org.lwjglx;

import org.lwjgl.glfw.GLFW;

public class Sys {
    public static long getTimerResolution() {
        return 1000L;
    }

    public static long getTime() {
        return (long)(GLFW.glfwGetTime() * 1000.0);
    }

    public static long getNanoTime() {
        return (long)(GLFW.glfwGetTime() * 1.0E9);
    }
}
