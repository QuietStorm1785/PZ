package zombie.Lua;

import se.krka.kahlua.converter.LuaToJavaConverter;

class KahluaNumberConverter$4 implements LuaToJavaConverter<Double, Byte> {
   public Byte fromLuaToJava(Double var1, Class<Byte> var2) {
      return var1.byteValue();
   }

   public Class<Byte> getJavaType() {
      return Byte.class;
   }

   public Class<Double> getLuaType() {
      return Double.class;
   }
}
