package zombie.iso;

import se.krka.kahlua.vm.KahluaTable;
import zombie.Lua.LuaManager;

public final class IsoMetaGrid$Trigger {
   public BuildingDef def;
   public int triggerRange;
   public int zombieExclusionRange;
   public String type;
   public boolean triggered = false;
   public KahluaTable data;

   public IsoMetaGrid$Trigger(BuildingDef var1, int var2, int var3, String var4) {
      this.def = var1;
      this.triggerRange = var2;
      this.zombieExclusionRange = var3;
      this.type = var4;
      this.data = LuaManager.platform.newTable();
   }

   public KahluaTable getModData() {
      return this.data;
   }
}
