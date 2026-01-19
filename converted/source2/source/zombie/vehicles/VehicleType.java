package zombie.vehicles;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map.Entry;
import se.krka.kahlua.j2se.KahluaTableImpl;
import zombie.Lua.LuaManager;
import zombie.core.Rand;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.scripting.ScriptManager;
import zombie.scripting.objects.VehicleScript;
import zombie.util.list.PZArrayUtil;
import zombie.vehicles.VehicleType.VehicleTypeDefinition;

public final class VehicleType {
   public final ArrayList<VehicleTypeDefinition> vehiclesDefinition = new ArrayList<>();
   public int chanceToSpawnNormal = 80;
   public int chanceToSpawnBurnt = 0;
   public int spawnRate = 16;
   public int chanceOfOverCar = 0;
   public boolean randomAngle = false;
   public float baseVehicleQuality = 1.0F;
   public String name = "";
   private int chanceToSpawnKey = 70;
   public int chanceToPartDamage = 0;
   public boolean isSpecialCar = false;
   public boolean isBurntCar = false;
   public int chanceToSpawnSpecial = 5;
   public static final HashMap<String, VehicleType> vehicles = new HashMap<>();
   public static final ArrayList<VehicleType> specialVehicles = new ArrayList<>();

   public VehicleType(String var1) {
      this.name = var1;
   }

   public static void init() {
      initNormal();
      validate(vehicles.values());
      validate(specialVehicles);
   }

   private static void validate(Collection<VehicleType> var0) {
   }

   private static void initNormal() {
      boolean var0 = DebugLog.isEnabled(DebugType.Lua);
      KahluaTableImpl var1 = (KahluaTableImpl)LuaManager.env.rawget("VehicleZoneDistribution");

      for (Entry var3 : var1.delegate.entrySet()) {
         String var4 = var3.getKey().toString();
         VehicleType var5 = new VehicleType(var4);
         ArrayList var6 = var5.vehiclesDefinition;
         KahluaTableImpl var7 = (KahluaTableImpl)var3.getValue();
         KahluaTableImpl var8 = (KahluaTableImpl)var7.rawget("vehicles");

         for (Entry var10 : var8.delegate.entrySet()) {
            String var11 = var10.getKey().toString();
            VehicleScript var12 = ScriptManager.instance.getVehicle(var11);
            if (var12 == null) {
               DebugLog.General.warn("vehicle type \"" + var11 + "\" doesn't exist");
            }

            KahluaTableImpl var13 = (KahluaTableImpl)var10.getValue();
            var6.add(new VehicleTypeDefinition(var11, var13.rawgetInt("index"), var13.rawgetFloat("spawnChance")));
         }

         float var21 = 0.0F;

         for (int var23 = 0; var23 < var6.size(); var23++) {
            var21 += ((VehicleTypeDefinition)var6.get(var23)).spawnChance;
         }

         var21 = 100.0F / var21;
         if (var0) {
            DebugLog.Lua.println("Vehicle spawn rate:");
         }

         for (int var24 = 0; var24 < var6.size(); var24++) {
            ((VehicleTypeDefinition)var6.get(var24)).spawnChance *= var21;
            if (var0) {
               DebugLog.Lua
                  .println(
                     var4 + ": " + ((VehicleTypeDefinition)var6.get(var24)).vehicleType + " " + ((VehicleTypeDefinition)var6.get(var24)).spawnChance + "%"
                  );
            }
         }

         if (var7.delegate.containsKey("chanceToPartDamage")) {
            var5.chanceToPartDamage = var7.rawgetInt("chanceToPartDamage");
         }

         if (var7.delegate.containsKey("chanceToSpawnNormal")) {
            var5.chanceToSpawnNormal = var7.rawgetInt("chanceToSpawnNormal");
         }

         if (var7.delegate.containsKey("chanceToSpawnSpecial")) {
            var5.chanceToSpawnSpecial = var7.rawgetInt("chanceToSpawnSpecial");
         }

         if (var7.delegate.containsKey("specialCar")) {
            var5.isSpecialCar = var7.rawgetBool("specialCar");
         }

         if (var7.delegate.containsKey("burntCar")) {
            var5.isBurntCar = var7.rawgetBool("burntCar");
         }

         if (var7.delegate.containsKey("baseVehicleQuality")) {
            var5.baseVehicleQuality = var7.rawgetFloat("baseVehicleQuality");
         }

         if (var7.delegate.containsKey("chanceOfOverCar")) {
            var5.chanceOfOverCar = var7.rawgetInt("chanceOfOverCar");
         }

         if (var7.delegate.containsKey("randomAngle")) {
            var5.randomAngle = var7.rawgetBool("randomAngle");
         }

         if (var7.delegate.containsKey("spawnRate")) {
            var5.spawnRate = var7.rawgetInt("spawnRate");
         }

         if (var7.delegate.containsKey("chanceToSpawnKey")) {
            var5.chanceToSpawnKey = var7.rawgetInt("chanceToSpawnKey");
         }

         if (var7.delegate.containsKey("chanceToSpawnBurnt")) {
            var5.chanceToSpawnBurnt = var7.rawgetInt("chanceToSpawnBurnt");
         }

         vehicles.put(var4, var5);
         if (var5.isSpecialCar) {
            specialVehicles.add(var5);
         }
      }

      HashSet var14 = new HashSet();

      for (VehicleType var17 : vehicles.values()) {
         for (VehicleTypeDefinition var20 : var17.vehiclesDefinition) {
            var14.add(var20.vehicleType);
         }
      }

      for (VehicleScript var18 : ScriptManager.instance.getAllVehicleScripts()) {
         if (!var14.contains(var18.getFullName())) {
            DebugLog.General.warn("vehicle type \"" + var18.getFullName() + "\" isn't in VehicleZoneDistribution");
         }
      }
   }

   public static boolean hasTypeForZone(String var0) {
      if (vehicles.isEmpty()) {
         init();
      }

      var0 = var0.toLowerCase();
      return vehicles.containsKey(var0);
   }

   public static VehicleType getRandomVehicleType(String var0) {
      return getRandomVehicleType(var0, true);
   }

   public static VehicleType getRandomVehicleType(String var0, Boolean var1) {
      if (vehicles.isEmpty()) {
         init();
      }

      var0 = var0.toLowerCase();
      VehicleType var2 = vehicles.get(var0);
      if (var2 == null) {
         DebugLog.log(var0 + " Don't exist in VehicleZoneDistribution");
         return null;
      } else if (Rand.Next(100) < var2.chanceToSpawnBurnt) {
         if (Rand.Next(100) < 80) {
            var2 = vehicles.get("normalburnt");
         } else {
            var2 = vehicles.get("specialburnt");
         }

         return var2;
      } else {
         if (var1 && var2.isSpecialCar && Rand.Next(100) < var2.chanceToSpawnNormal) {
            var2 = vehicles.get("parkingstall");
         }

         if (!var2.isBurntCar && !var2.isSpecialCar && Rand.Next(100) < var2.chanceToSpawnSpecial) {
            var2 = (VehicleType)PZArrayUtil.pickRandom(specialVehicles);
         }

         if (var2.isBurntCar) {
            if (Rand.Next(100) < 80) {
               var2 = vehicles.get("normalburnt");
            } else {
               var2 = vehicles.get("specialburnt");
            }
         }

         return var2;
      }
   }

   public static VehicleType getTypeFromName(String var0) {
      if (vehicles.isEmpty()) {
         init();
      }

      return vehicles.get(var0);
   }

   public float getBaseVehicleQuality() {
      return this.baseVehicleQuality;
   }

   public float getRandomBaseVehicleQuality() {
      return Rand.Next(this.baseVehicleQuality - 0.1F, this.baseVehicleQuality + 0.1F);
   }

   public int getChanceToSpawnKey() {
      return this.chanceToSpawnKey;
   }

   public void setChanceToSpawnKey(int var1) {
      this.chanceToSpawnKey = var1;
   }

   public static void Reset() {
      vehicles.clear();
      specialVehicles.clear();
   }
}
