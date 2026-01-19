package zombie.Lua;

import se.krka.kahlua.converter.LuaToJavaConverter;

class KahluaNumberConverter$6 implements LuaToJavaConverter<Double, Short> {
   public Short fromLuaToJava(Double var1, Class<Short> var2) {
      return var1.shortValue();
   }

   public Class<Short> getJavaType() {
      return Short.class;
   }

   public Class<Double> getLuaType() {
      return Double.class;
   }
}
