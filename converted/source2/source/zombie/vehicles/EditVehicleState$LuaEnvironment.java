package zombie.vehicles;

import se.krka.kahlua.converter.KahluaConverterManager;
import se.krka.kahlua.integration.LuaCaller;
import se.krka.kahlua.j2se.J2SEPlatform;
import se.krka.kahlua.vm.KahluaTable;
import se.krka.kahlua.vm.KahluaThread;
import zombie.Lua.LuaManager;

public final class EditVehicleState$LuaEnvironment {
   public J2SEPlatform platform;
   public KahluaTable env;
   public KahluaThread thread;
   public LuaCaller caller;

   public EditVehicleState$LuaEnvironment(J2SEPlatform var1, KahluaConverterManager var2, KahluaTable var3) {
      this.platform = var1;
      this.env = var3;
      this.thread = LuaManager.thread;
      this.caller = LuaManager.caller;
   }
}
