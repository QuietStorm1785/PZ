// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package se.krka.kahlua.converter;

public interface JavaToLuaConverter<JavaType> {
    Class<JavaType> getJavaType();

    Object fromJavaToLua(JavaType var1);
}
