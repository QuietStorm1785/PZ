// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package se.krka.kahlua.require;

import java.io.Reader;

public interface LuaSourceProvider {
    Reader getLuaSource(String var1);
}
