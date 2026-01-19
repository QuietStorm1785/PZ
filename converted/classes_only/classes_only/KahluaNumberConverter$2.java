package zombie.Lua;

import se.krka.kahlua.converter.LuaToJavaConverter;

class KahluaNumberConverter$2 implements LuaToJavaConverter<Double, Integer> {
   public Integer fromLuaToJava(Double var1, Class<Integer> var2) {
      return var1.intValue();
   }

   public Class<Integer> getJavaType() {
      return Integer.class;
   }

   public Class<Double> getLuaType() {
      return Double.class;
   }
}
