package zombie.Lua;

import se.krka.kahlua.converter.KahluaConverterManager;
import zombie.Lua.KahluaNumberConverter.1;
import zombie.Lua.KahluaNumberConverter.2;
import zombie.Lua.KahluaNumberConverter.3;
import zombie.Lua.KahluaNumberConverter.4;
import zombie.Lua.KahluaNumberConverter.5;
import zombie.Lua.KahluaNumberConverter.6;
import zombie.Lua.KahluaNumberConverter.7;
import zombie.Lua.KahluaNumberConverter.NumberToLuaConverter;

public final class KahluaNumberConverter {
   private KahluaNumberConverter() {
   }

   public static void install(KahluaConverterManager var0) {
      var0.addLuaConverter(new 1());
      var0.addLuaConverter(new 2());
      var0.addLuaConverter(new 3());
      var0.addLuaConverter(new 4());
      var0.addLuaConverter(new 5());
      var0.addLuaConverter(new 6());
      var0.addJavaConverter(new NumberToLuaConverter(Double.class));
      var0.addJavaConverter(new NumberToLuaConverter(Float.class));
      var0.addJavaConverter(new NumberToLuaConverter(Integer.class));
      var0.addJavaConverter(new NumberToLuaConverter(Long.class));
      var0.addJavaConverter(new NumberToLuaConverter(Short.class));
      var0.addJavaConverter(new NumberToLuaConverter(Byte.class));
      var0.addJavaConverter(new NumberToLuaConverter(Character.class));
      var0.addJavaConverter(new NumberToLuaConverter(double.class));
      var0.addJavaConverter(new NumberToLuaConverter(float.class));
      var0.addJavaConverter(new NumberToLuaConverter(int.class));
      var0.addJavaConverter(new NumberToLuaConverter(long.class));
      var0.addJavaConverter(new NumberToLuaConverter(short.class));
      var0.addJavaConverter(new NumberToLuaConverter(byte.class));
      var0.addJavaConverter(new NumberToLuaConverter(char.class));
      var0.addJavaConverter(new 7());
   }
}
