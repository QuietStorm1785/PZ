package zombie.Lua;

import se.krka.kahlua.converter.LuaToJavaConverter;

class KahluaNumberConverter$5 implements LuaToJavaConverter<Double, Character> {
   public Character fromLuaToJava(Double var1, Class<Character> var2) {
      return (char)var1.intValue();
   }

   public Class<Character> getJavaType() {
      return Character.class;
   }

   public Class<Double> getLuaType() {
      return Double.class;
   }
}
