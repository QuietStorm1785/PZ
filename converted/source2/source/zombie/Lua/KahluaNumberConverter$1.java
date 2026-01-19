package zombie.Lua;

import se.krka.kahlua.converter.LuaToJavaConverter;

class KahluaNumberConverter$1 implements LuaToJavaConverter<Double, Long> {
   public Long fromLuaToJava(Double var1, Class<Long> var2) {
      return var1.longValue();
   }

   public Class<Long> getJavaType() {
      return Long.class;
   }

   public Class<Double> getLuaType() {
      return Double.class;
   }
}
