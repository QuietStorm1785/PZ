// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package se.krka.kahlua.converter;

public interface LuaToJavaConverter<LuaType, JavaType> {
    Class<LuaType> getLuaType();

    Class<JavaType> getJavaType();

    JavaType fromLuaToJava(LuaType var1, Class<JavaType> var2);
}
