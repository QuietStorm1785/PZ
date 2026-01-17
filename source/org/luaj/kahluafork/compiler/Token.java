// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package org.luaj.kahluafork.compiler;

public class Token {
    int token;
    double r;
    String ts;

    public void set(Token token0) {
        this.token = token0.token;
        this.r = token0.r;
        this.ts = token0.ts;
    }
}
