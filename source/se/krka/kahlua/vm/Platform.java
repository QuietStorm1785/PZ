// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package se.krka.kahlua.vm;

public interface Platform {
    double pow(double arg0, double arg1);

    KahluaTable newTable();

    KahluaTable newEnvironment();

    void setupEnvironment(KahluaTable arg0);
}
