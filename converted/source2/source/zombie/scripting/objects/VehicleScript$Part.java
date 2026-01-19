package zombie.scripting.objects;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;
import se.krka.kahlua.vm.KahluaTable;
import zombie.Lua.LuaManager;
import zombie.scripting.objects.VehicleScript.Anim;
import zombie.scripting.objects.VehicleScript.Container;
import zombie.scripting.objects.VehicleScript.Door;
import zombie.scripting.objects.VehicleScript.Model;
import zombie.scripting.objects.VehicleScript.Window;

public final class VehicleScript$Part {
   public String id = "Unknown";
   public String parent;
   public ArrayList<String> itemType;
   public Container container;
   public String area;
   public String wheel;
   public HashMap<String, KahluaTable> tables;
   public HashMap<String, String> luaFunctions;
   public ArrayList<Model> models;
   public boolean bSetAllModelsVisible = true;
   public Door door;
   public Window window;
   public ArrayList<Anim> anims;
   public String category;
   public boolean specificItem = true;
   public boolean mechanicRequireKey = false;
   public boolean repairMechanic = false;
   public boolean hasLightsRear = false;

   public boolean isMechanicRequireKey() {
      return this.mechanicRequireKey;
   }

   public void setMechanicRequireKey(boolean var1) {
      this.mechanicRequireKey = var1;
   }

   public boolean isRepairMechanic() {
      return this.repairMechanic;
   }

   public void setRepairMechanic(boolean var1) {
      this.repairMechanic = var1;
   }

   VehicleScript$Part makeCopy() {
      VehicleScript$Part var1 = new VehicleScript$Part();
      var1.id = this.id;
      var1.parent = this.parent;
      if (this.itemType != null) {
         var1.itemType = new ArrayList<>();
         var1.itemType.addAll(this.itemType);
      }

      if (this.container != null) {
         var1.container = this.container.makeCopy();
      }

      var1.area = this.area;
      var1.wheel = this.wheel;
      if (this.tables != null) {
         var1.tables = new HashMap<>();

         for (Entry var3 : this.tables.entrySet()) {
            KahluaTable var4 = LuaManager.copyTable((KahluaTable)var3.getValue());
            var1.tables.put((String)var3.getKey(), var4);
         }
      }

      if (this.luaFunctions != null) {
         var1.luaFunctions = new HashMap<>();
         var1.luaFunctions.putAll(this.luaFunctions);
      }

      if (this.models != null) {
         var1.models = new ArrayList<>();

         for (int var5 = 0; var5 < this.models.size(); var5++) {
            var1.models.add(this.models.get(var5).makeCopy());
         }
      }

      var1.bSetAllModelsVisible = this.bSetAllModelsVisible;
      if (this.door != null) {
         var1.door = this.door.makeCopy();
      }

      if (this.window != null) {
         var1.window = this.window.makeCopy();
      }

      if (this.anims != null) {
         var1.anims = new ArrayList<>();

         for (int var6 = 0; var6 < this.anims.size(); var6++) {
            var1.anims.add(this.anims.get(var6).makeCopy());
         }
      }

      var1.category = this.category;
      var1.specificItem = this.specificItem;
      var1.mechanicRequireKey = this.mechanicRequireKey;
      var1.repairMechanic = this.repairMechanic;
      var1.hasLightsRear = this.hasLightsRear;
      return var1;
   }
}
