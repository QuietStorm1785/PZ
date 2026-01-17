// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package com.jcraft.jorbis;

public class JOrbisException extends Exception {
    private static final long serialVersionUID = 1L;

    public JOrbisException() {
    }

    public JOrbisException(String string) {
        super("JOrbis: " + string);
    }
}
