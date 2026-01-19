package zombie.Lua;

import se.krka.kahlua.converter.JavaToLuaConverter;
import zombie.Lua.KahluaNumberConverter.DoubleCache;

final class KahluaNumberConverter$NumberToLuaConverter<T extends Number> implements JavaToLuaConverter<T> {
   private final Class<T> clazz;

   public KahluaNumberConverter$NumberToLuaConverter(Class<T> var1) {
      this.clazz = var1;
   }

   public Object fromJavaToLua(T var1) {
      return var1 instanceof Double ? var1 : DoubleCache.valueOf(var1.doubleValue());
   }

   public Class<T> getJavaType() {
      return this.clazz;
   }
}
