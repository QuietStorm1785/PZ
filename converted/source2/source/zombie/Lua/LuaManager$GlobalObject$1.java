package zombie.Lua;

import java.io.File;
import java.util.Comparator;

class LuaManager$GlobalObject$1 implements Comparator<File> {
   public int compare(File var1, File var2) {
      return Long.valueOf(var2.lastModified()).compareTo(var1.lastModified());
   }
}
