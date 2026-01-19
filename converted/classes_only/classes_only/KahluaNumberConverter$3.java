package zombie.Lua;

import se.krka.kahlua.converter.LuaToJavaConverter;

class KahluaNumberConverter$3 implements LuaToJavaConverter<Double, Float> {
   public Float fromLuaToJava(Double var1, Class<Float> var2) {
      return new Float(var1.floatValue());
   }

   public Class<Float> getJavaType() {
      return Float.class;
   }

   public Class<Double> getLuaType() {
      return Double.class;
   }
}
