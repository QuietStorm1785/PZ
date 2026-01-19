package zombie.inventory;

import gnu.trove.map.hash.THashMap;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map.Entry;
import se.krka.kahlua.j2se.KahluaTableImpl;
import se.krka.kahlua.vm.KahluaTableIterator;
import se.krka.kahlua.vm.KahluaUtil;
import zombie.SandboxOptions;
import zombie.Lua.LuaEventManager;
import zombie.Lua.LuaManager;
import zombie.Lua.LuaManager.GlobalObject;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.core.Core;
import zombie.core.Rand;
import zombie.core.stash.StashSystem;
import zombie.debug.DebugLog;
import zombie.inventory.ItemPickerJava.ItemPickerContainer;
import zombie.inventory.ItemPickerJava.ItemPickerItem;
import zombie.inventory.ItemPickerJava.ItemPickerRoom;
import zombie.inventory.ItemPickerJava.ItemPickerUpgradeWeapons;
import zombie.inventory.ItemPickerJava.ProceduralItem;
import zombie.inventory.ItemPickerJava.VehicleDistribution;
import zombie.inventory.types.DrainableComboItem;
import zombie.inventory.types.Food;
import zombie.inventory.types.HandWeapon;
import zombie.inventory.types.InventoryContainer;
import zombie.inventory.types.Key;
import zombie.inventory.types.MapItem;
import zombie.inventory.types.WeaponPart;
import zombie.iso.ContainerOverlays;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoMetaChunk;
import zombie.iso.IsoObject;
import zombie.iso.IsoWorld;
import zombie.iso.IsoMetaGrid.Zone;
import zombie.iso.areas.IsoRoom;
import zombie.iso.objects.IsoDeadBody;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.radio.ZomboidRadio;
import zombie.radio.media.MediaData;
import zombie.radio.media.RecordedMedia;
import zombie.scripting.ScriptManager;
import zombie.scripting.objects.Item;
import zombie.util.StringUtils;
import zombie.util.Type;
import zombie.util.list.PZArrayList;
import zombie.util.list.PZArrayUtil;

public final class ItemPickerJava {
   private static IsoPlayer player;
   private static float OtherLootModifier;
   private static float FoodLootModifier;
   private static float CannedFoodLootModifier;
   private static float WeaponLootModifier;
   private static float RangedWeaponLootModifier;
   private static float AmmoLootModifier;
   private static float LiteratureLootModifier;
   private static float SurvivalGearsLootModifier;
   private static float MedicalLootModifier;
   private static float BagLootModifier;
   private static float MechanicsLootModifier;
   public static float zombieDensityCap = 8.0F;
   public static final ArrayList<String> NoContainerFillRooms = new ArrayList<>();
   public static final ArrayList<ItemPickerUpgradeWeapons> WeaponUpgrades = new ArrayList<>();
   public static final HashMap<String, ItemPickerUpgradeWeapons> WeaponUpgradeMap = new HashMap<>();
   public static final THashMap<String, ItemPickerRoom> rooms = new THashMap();
   public static final THashMap<String, ItemPickerContainer> containers = new THashMap();
   public static final THashMap<String, ItemPickerContainer> ProceduralDistributions = new THashMap();
   public static final THashMap<String, VehicleDistribution> VehicleDistributions = new THashMap();

   public static void Parse() {
      rooms.clear();
      NoContainerFillRooms.clear();
      WeaponUpgradeMap.clear();
      WeaponUpgrades.clear();
      containers.clear();
      KahluaTableImpl var0 = (KahluaTableImpl)LuaManager.env.rawget("NoContainerFillRooms");

      for (Entry var2 : var0.delegate.entrySet()) {
         String var3 = var2.getKey().toString();
         NoContainerFillRooms.add(var3);
      }

      KahluaTableImpl var10 = (KahluaTableImpl)LuaManager.env.rawget("WeaponUpgrades");

      for (Entry var12 : var10.delegate.entrySet()) {
         String var4 = var12.getKey().toString();
         ItemPickerUpgradeWeapons var5 = new ItemPickerUpgradeWeapons();
         var5.name = var4;
         WeaponUpgrades.add(var5);
         WeaponUpgradeMap.put(var4, var5);
         KahluaTableImpl var6 = (KahluaTableImpl)var12.getValue();

         for (Entry var8 : var6.delegate.entrySet()) {
            String var9 = var8.getValue().toString();
            var5.Upgrades.add(var9);
         }
      }

      ParseSuburbsDistributions();
      ParseVehicleDistributions();
      ParseProceduralDistributions();
   }

   private static void ParseSuburbsDistributions() {
      KahluaTableImpl var0 = (KahluaTableImpl)LuaManager.env.rawget("SuburbsDistributions");

      for (Entry var2 : var0.delegate.entrySet()) {
         String var3 = var2.getKey().toString();
         KahluaTableImpl var4 = (KahluaTableImpl)var2.getValue();
         if (var4.delegate.containsKey("rolls")) {
            ItemPickerContainer var12 = ExtractContainersFromLua(var4);
            containers.put(var3, var12);
         } else {
            ItemPickerRoom var5 = new ItemPickerRoom();
            rooms.put(var3, var5);

            for (Entry var7 : var4.delegate.entrySet()) {
               String var8 = var7.getKey().toString();
               if (var7.getValue() instanceof Double) {
                  var5.fillRand = ((Double)var7.getValue()).intValue();
               } else if ("isShop".equals(var8)) {
                  var5.isShop = (Boolean)var7.getValue();
               } else {
                  KahluaTableImpl var9 = null;

                  try {
                     var9 = (KahluaTableImpl)var7.getValue();
                  } catch (Exception var11) {
                     var11.printStackTrace();
                  }

                  if (var9.delegate.containsKey("procedural") || !var8.isEmpty() && var9.delegate.containsKey("rolls") && var9.delegate.containsKey("items")) {
                     ItemPickerContainer var10 = ExtractContainersFromLua(var9);
                     var5.Containers.put(var8, var10);
                  } else {
                     DebugLog.log("ERROR: SuburbsDistributions[\"" + var3 + "\"] is broken");
                  }
               }
            }
         }
      }
   }

   private static void ParseVehicleDistributions() {
      VehicleDistributions.clear();
      KahluaTableImpl var0 = (KahluaTableImpl)LuaManager.env.rawget("VehicleDistributions");
      if (var0 != null && var0.rawget(1) instanceof KahluaTableImpl) {
         var0 = (KahluaTableImpl)var0.rawget(1);

         for (Entry var2 : var0.delegate.entrySet()) {
            if (var2.getKey() instanceof String && var2.getValue() instanceof KahluaTableImpl) {
               KahluaTableImpl var3 = (KahluaTableImpl)var2.getValue();
               VehicleDistribution var4 = new VehicleDistribution();
               if (var3.rawget("Normal") instanceof KahluaTableImpl) {
                  KahluaTableImpl var5 = (KahluaTableImpl)var3.rawget("Normal");
                  ItemPickerRoom var6 = new ItemPickerRoom();

                  for (Entry var8 : var5.delegate.entrySet()) {
                     String var9 = var8.getKey().toString();
                     var6.Containers.put(var9, ExtractContainersFromLua((KahluaTableImpl)var8.getValue()));
                  }

                  var4.Normal = var6;
               }

               if (var3.rawget("Specific") instanceof KahluaTableImpl) {
                  KahluaTableImpl var13 = (KahluaTableImpl)var3.rawget("Specific");

                  for (int var14 = 1; var14 <= var13.len(); var14++) {
                     KahluaTableImpl var15 = (KahluaTableImpl)var13.rawget(var14);
                     ItemPickerRoom var16 = new ItemPickerRoom();

                     for (Entry var10 : var15.delegate.entrySet()) {
                        String var11 = var10.getKey().toString();
                        if (var11.equals("specificId")) {
                           var16.specificId = (String)var10.getValue();
                        } else {
                           var16.Containers.put(var11, ExtractContainersFromLua((KahluaTableImpl)var10.getValue()));
                        }
                     }

                     var4.Specific.add(var16);
                  }
               }

               if (var4.Normal != null) {
                  VehicleDistributions.put((String)var2.getKey(), var4);
               }
            }
         }
      }
   }

   private static void ParseProceduralDistributions() {
      ProceduralDistributions.clear();
      KahluaTableImpl var0 = (KahluaTableImpl)Type.tryCastTo(LuaManager.env.rawget("ProceduralDistributions"), KahluaTableImpl.class);
      if (var0 != null) {
         KahluaTableImpl var1 = (KahluaTableImpl)Type.tryCastTo(var0.rawget("list"), KahluaTableImpl.class);
         if (var1 != null) {
            for (Entry var3 : var1.delegate.entrySet()) {
               String var4 = var3.getKey().toString();
               KahluaTableImpl var5 = (KahluaTableImpl)var3.getValue();
               ItemPickerContainer var6 = ExtractContainersFromLua(var5);
               ProceduralDistributions.put(var4, var6);
            }
         }
      }
   }

   private static ItemPickerContainer ExtractContainersFromLua(KahluaTableImpl var0) {
      ItemPickerContainer var1 = new ItemPickerContainer();
      if (var0.delegate.containsKey("procedural")) {
         var1.procedural = var0.rawgetBool("procedural");
         var1.proceduralItems = ExtractProcList(var0);
         return var1;
      } else {
         if (var0.delegate.containsKey("noAutoAge")) {
            var1.noAutoAge = var0.rawgetBool("noAutoAge");
         }

         if (var0.delegate.containsKey("fillRand")) {
            var1.fillRand = var0.rawgetInt("fillRand");
         }

         if (var0.delegate.containsKey("maxMap")) {
            var1.maxMap = var0.rawgetInt("maxMap");
         }

         if (var0.delegate.containsKey("stashChance")) {
            var1.stashChance = var0.rawgetInt("stashChance");
         }

         if (var0.delegate.containsKey("dontSpawnAmmo")) {
            var1.dontSpawnAmmo = var0.rawgetBool("dontSpawnAmmo");
         }

         if (var0.delegate.containsKey("ignoreZombieDensity")) {
            var1.ignoreZombieDensity = var0.rawgetBool("ignoreZombieDensity");
         }

         double var2 = (Double)var0.delegate.get("rolls");
         if (var0.delegate.containsKey("junk")) {
            var1.junk = ExtractContainersFromLua((KahluaTableImpl)var0.rawget("junk"));
         }

         var1.rolls = (int)var2;
         KahluaTableImpl var4 = (KahluaTableImpl)var0.delegate.get("items");
         ArrayList var5 = new ArrayList();
         int var6 = var4.len();

         for (byte var7 = 0; var7 < var6; var7 += 2) {
            String var8 = (String)Type.tryCastTo(var4.delegate.get(KahluaUtil.toDouble(var7 + 1)), String.class);
            Double var9 = (Double)Type.tryCastTo(var4.delegate.get(KahluaUtil.toDouble(var7 + 2)), Double.class);
            if (var8 != null && var9 != null) {
               Item var10 = ScriptManager.instance.FindItem(var8);
               if (var10 != null && !var10.OBSOLETE) {
                  ItemPickerItem var11 = new ItemPickerItem();
                  var11.itemName = var8;
                  var11.chance = var9.floatValue();
                  var5.add(var11);
               } else if (Core.bDebug) {
                  DebugLog.General.warn("ignoring invalid ItemPicker item type \"%s\"", new Object[]{var8});
               }
            }
         }

         var1.Items = var5.toArray(var1.Items);
         return var1;
      }
   }

   private static ArrayList<ProceduralItem> ExtractProcList(KahluaTableImpl var0) {
      ArrayList var1 = new ArrayList();
      KahluaTableImpl var2 = (KahluaTableImpl)var0.rawget("procList");
      KahluaTableIterator var3 = var2.iterator();

      while (var3.advance()) {
         KahluaTableImpl var4 = (KahluaTableImpl)var3.getValue();
         ProceduralItem var5 = new ProceduralItem();
         var5.name = var4.rawgetStr("name");
         var5.min = var4.rawgetInt("min");
         var5.max = var4.rawgetInt("max");
         var5.weightChance = var4.rawgetInt("weightChance");
         String var6 = var4.rawgetStr("forceForItems");
         String var7 = var4.rawgetStr("forceForZones");
         String var8 = var4.rawgetStr("forceForTiles");
         String var9 = var4.rawgetStr("forceForRooms");
         if (!StringUtils.isNullOrWhitespace(var6)) {
            var5.forceForItems = Arrays.asList(var6.split(";"));
         }

         if (!StringUtils.isNullOrWhitespace(var7)) {
            var5.forceForZones = Arrays.asList(var7.split(";"));
         }

         if (!StringUtils.isNullOrWhitespace(var8)) {
            var5.forceForTiles = Arrays.asList(var8.split(";"));
         }

         if (!StringUtils.isNullOrWhitespace(var9)) {
            var5.forceForRooms = Arrays.asList(var9.split(";"));
         }

         var1.add(var5);
      }

      return var1;
   }

   public static void InitSandboxLootSettings() {
      OtherLootModifier = doSandboxSettings(SandboxOptions.getInstance().OtherLoot.getValue());
      FoodLootModifier = doSandboxSettings(SandboxOptions.getInstance().FoodLoot.getValue());
      WeaponLootModifier = doSandboxSettings(SandboxOptions.getInstance().WeaponLoot.getValue());
      RangedWeaponLootModifier = doSandboxSettings(SandboxOptions.getInstance().RangedWeaponLoot.getValue());
      AmmoLootModifier = doSandboxSettings(SandboxOptions.getInstance().AmmoLoot.getValue());
      CannedFoodLootModifier = doSandboxSettings(SandboxOptions.getInstance().CannedFoodLoot.getValue());
      LiteratureLootModifier = doSandboxSettings(SandboxOptions.getInstance().LiteratureLoot.getValue());
      SurvivalGearsLootModifier = doSandboxSettings(SandboxOptions.getInstance().SurvivalGearsLoot.getValue());
      MedicalLootModifier = doSandboxSettings(SandboxOptions.getInstance().MedicalLoot.getValue());
      MechanicsLootModifier = doSandboxSettings(SandboxOptions.getInstance().MechanicsLoot.getValue());
   }

   private static float doSandboxSettings(int var0) {
      switch (var0) {
         case 1:
            return 0.0F;
         case 2:
            return 0.05F;
         case 3:
            return 0.2F;
         case 4:
            return 0.6F;
         case 5:
            return 1.0F;
         case 6:
            return 2.0F;
         case 7:
            return 3.0F;
         default:
            return 0.6F;
      }
   }

   public static void fillContainer(ItemContainer var0, IsoPlayer var1) {
      if (!GameClient.bClient && !"Tutorial".equals(Core.GameMode)) {
         if (var0 != null) {
            IsoGridSquare var2 = var0.getSourceGrid();
            IsoRoom var3 = null;
            if (var2 != null) {
               var3 = var2.getRoom();
               if (!var0.getType().equals("inventorymale") && !var0.getType().equals("inventoryfemale")) {
                  ItemPickerRoom var9 = null;
                  if (rooms.containsKey("all")) {
                     var9 = (ItemPickerRoom)rooms.get("all");
                  }

                  if (var3 != null && rooms.containsKey(var3.getName())) {
                     String var13 = var3.getName();
                     ItemPickerRoom var14 = (ItemPickerRoom)rooms.get(var13);
                     ItemPickerContainer var7 = null;
                     if (var14.Containers.containsKey(var0.getType())) {
                        var7 = (ItemPickerContainer)var14.Containers.get(var0.getType());
                     }

                     if (var7 == null && var14.Containers.containsKey("other")) {
                        var7 = (ItemPickerContainer)var14.Containers.get("other");
                     }

                     if (var7 == null && var14.Containers.containsKey("all")) {
                        var7 = (ItemPickerContainer)var14.Containers.get("all");
                        var13 = "all";
                     }

                     if (var7 == null) {
                        fillContainerType(var9, var0, var13, var1);
                        LuaEventManager.triggerEvent("OnFillContainer", var13, var0.getType(), var0);
                     } else {
                        if (rooms.containsKey(var3.getName())) {
                           var9 = (ItemPickerRoom)rooms.get(var3.getName());
                        }

                        if (var9 != null) {
                           fillContainerType(var9, var0, var3.getName(), var1);
                           LuaEventManager.triggerEvent("OnFillContainer", var3.getName(), var0.getType(), var0);
                        }
                     }
                  } else {
                     Object var11 = null;
                     if (var3 != null) {
                        var11 = var3.getName();
                     } else {
                        var11 = "all";
                     }

                     fillContainerType(var9, var0, (String)var11, var1);
                     LuaEventManager.triggerEvent("OnFillContainer", var11, var0.getType(), var0);
                  }
               } else {
                  String var4 = var0.getType();
                  if (var0.getParent() != null && var0.getParent() instanceof IsoDeadBody) {
                     var4 = ((IsoDeadBody)var0.getParent()).getOutfitName();
                  }

                  for (int var5 = 0; var5 < var0.getItems().size(); var5++) {
                     if (var0.getItems().get(var5) instanceof InventoryContainer) {
                        ItemPickerContainer var6 = (ItemPickerContainer)containers.get(((InventoryItem)var0.getItems().get(var5)).getType());
                        if (var6 != null && Rand.Next(var6.fillRand) == 0) {
                           rollContainerItem(
                              (InventoryContainer)var0.getItems().get(var5),
                              null,
                              (ItemPickerContainer)containers.get(((InventoryItem)var0.getItems().get(var5)).getType())
                           );
                        }
                     }
                  }

                  ItemPickerContainer var10 = (ItemPickerContainer)((ItemPickerRoom)rooms.get("all")).Containers.get("Outfit_" + var4);
                  if (var10 == null) {
                     var10 = (ItemPickerContainer)((ItemPickerRoom)rooms.get("all")).Containers.get(var0.getType());
                  }

                  rollItem(var10, var0, true, var1, null);
               }
            }
         }
      }
   }

   public static void fillContainerType(ItemPickerRoom var0, ItemContainer var1, String var2, IsoGameCharacter var3) {
      boolean var4 = true;
      if (NoContainerFillRooms.contains(var2)) {
         var4 = false;
      }

      Object var5 = null;
      if (var0.Containers.containsKey("all")) {
         var5 = (ItemPickerContainer)var0.Containers.get("all");
         rollItem((ItemPickerContainer)var5, var1, var4, var3, var0);
      }

      var5 = (ItemPickerContainer)var0.Containers.get(var1.getType());
      if (var5 == null) {
         var5 = (ItemPickerContainer)var0.Containers.get("other");
      }

      if (var5 != null) {
         rollItem((ItemPickerContainer)var5, var1, var4, var3, var0);
      }
   }

   public static InventoryItem tryAddItemToContainer(ItemContainer var0, String var1, ItemPickerContainer var2) {
      Item var3 = ScriptManager.instance.FindItem(var1);
      if (var3 == null) {
         return null;
      } else if (var3.OBSOLETE) {
         return null;
      } else {
         float var4 = var3.getActualWeight() * var3.getCount();
         if (!var0.hasRoomFor(null, var4)) {
            return null;
         } else {
            if (var0.getContainingItem() instanceof InventoryContainer) {
               ItemContainer var5 = var0.getContainingItem().getContainer();
               if (var5 != null && !var5.hasRoomFor(null, var4)) {
                  return null;
               }
            }

            return var0.AddItem(var1);
         }
      }
   }

   private static void rollProceduralItem(ArrayList<ProceduralItem> var0, ItemContainer var1, float var2, IsoGameCharacter var3, ItemPickerRoom var4) {
      if (var1.getSourceGrid() != null && var1.getSourceGrid().getRoom() != null) {
         HashMap var5 = var1.getSourceGrid().getRoom().getRoomDef().getProceduralSpawnedContainer();
         HashMap var6 = new HashMap();
         HashMap var7 = new HashMap();

         for (int var8 = 0; var8 < var0.size(); var8++) {
            ProceduralItem var9 = (ProceduralItem)var0.get(var8);
            String var10 = var9.name;
            int var11 = var9.min;
            int var12 = var9.max;
            int var13 = var9.weightChance;
            List var14 = var9.forceForItems;
            List var15 = var9.forceForZones;
            List var16 = var9.forceForTiles;
            List var17 = var9.forceForRooms;
            if (var5.get(var10) == null) {
               var5.put(var10, 0);
            }

            if (var14 != null) {
               for (int var27 = var1.getSourceGrid().getRoom().getRoomDef().x; var27 < var1.getSourceGrid().getRoom().getRoomDef().x2; var27++) {
                  for (int var30 = var1.getSourceGrid().getRoom().getRoomDef().y; var30 < var1.getSourceGrid().getRoom().getRoomDef().y2; var30++) {
                     IsoGridSquare var31 = var1.getSourceGrid().getCell().getGridSquare(var27, var30, var1.getSourceGrid().z);
                     if (var31 != null) {
                        for (int var21 = 0; var21 < var31.getObjects().size(); var21++) {
                           IsoObject var22 = (IsoObject)var31.getObjects().get(var21);
                           if (var14.contains(var22.getSprite().name)) {
                              var6.clear();
                              var6.put(var10, -1);
                              break;
                           }
                        }
                     }
                  }
               }
            } else if (var15 == null) {
               if (var16 != null) {
                  IsoGridSquare var26 = var1.getSourceGrid();
                  if (var26 != null) {
                     for (int var29 = 0; var29 < var26.getObjects().size(); var29++) {
                        IsoObject var20 = (IsoObject)var26.getObjects().get(var29);
                        if (var20.getSprite() != null && var16.contains(var20.getSprite().getName())) {
                           var6.clear();
                           var6.put(var10, -1);
                           break;
                        }
                     }
                  }
               } else if (var17 != null) {
                  IsoGridSquare var25 = var1.getSourceGrid();
                  if (var25 != null) {
                     for (int var28 = 0; var28 < var17.size(); var28++) {
                        if (var25.getBuilding().getRandomRoom((String)var17.get(var28)) != null) {
                           var6.clear();
                           var6.put(var10, -1);
                           break;
                        }
                     }
                  }
               }
            } else {
               ArrayList var18 = IsoWorld.instance.MetaGrid.getZonesAt(var1.getSourceGrid().x, var1.getSourceGrid().y, 0);

               for (int var19 = 0; var19 < var18.size(); var19++) {
                  if ((Integer)var5.get(var10) < var12 && (var15.contains(((Zone)var18.get(var19)).type) || var15.contains(((Zone)var18.get(var19)).name))) {
                     var6.clear();
                     var6.put(var10, -1);
                     break;
                  }
               }
            }

            if (var14 == null && var15 == null && var16 == null && var17 == null) {
               if (var11 == 1 && (Integer)var5.get(var10) == 0) {
                  var6.put(var10, var13);
               } else if ((Integer)var5.get(var10) < var12) {
                  var7.put(var10, var13);
               }
            }
         }

         String var23 = null;
         if (!var6.isEmpty()) {
            var23 = getDistribInHashMap(var6);
         } else if (!var7.isEmpty()) {
            var23 = getDistribInHashMap(var7);
         }

         if (var23 != null) {
            ItemPickerContainer var24 = (ItemPickerContainer)ProceduralDistributions.get(var23);
            if (var24 != null) {
               if (var24.junk != null) {
                  doRollItem(var24.junk, var1, var2, var3, true, true, var4);
               }

               doRollItem(var24, var1, var2, var3, true, false, var4);
               var5.put(var23, (Integer)var5.get(var23) + 1);
            }
         }
      }
   }

   private static String getDistribInHashMap(HashMap<String, Integer> var0) {
      int var1 = 0;
      int var3 = 0;

      for (String var5 : var0.keySet()) {
         var1 += var0.get(var5);
      }

      if (var1 == -1) {
         int var2 = Rand.Next(var0.size());
         Iterator var8 = var0.keySet().iterator();

         for (int var10 = 0; var8.hasNext(); var10++) {
            if (var10 == var2) {
               return (String)var8.next();
            }
         }
      }

      int var7 = Rand.Next(var1);

      for (String var11 : var0.keySet()) {
         int var6 = (Integer)var0.get(var11);
         var3 += var6;
         if (var3 >= var7) {
            return var11;
         }
      }

      return null;
   }

   public static void rollItem(ItemPickerContainer var0, ItemContainer var1, boolean var2, IsoGameCharacter var3, ItemPickerRoom var4) {
      if (!GameClient.bClient && !GameServer.bServer) {
         player = IsoPlayer.getInstance();
      }

      if (var0 != null && var1 != null) {
         float var5 = 0.0F;
         IsoMetaChunk var6 = null;
         if (player != null && IsoWorld.instance != null) {
            var6 = IsoWorld.instance.getMetaChunk((int)player.getX() / 10, (int)player.getY() / 10);
         } else if (var1.getSourceGrid() != null) {
            var6 = IsoWorld.instance.getMetaChunk(var1.getSourceGrid().getX() / 10, var1.getSourceGrid().getY() / 10);
         }

         if (var6 != null) {
            var5 = var6.getLootZombieIntensity();
         }

         if (var5 > zombieDensityCap) {
            var5 = zombieDensityCap;
         }

         if (var0.ignoreZombieDensity) {
            var5 = 0.0F;
         }

         if (var0.procedural) {
            rollProceduralItem(var0.proceduralItems, var1, var5, var3, var4);
         } else {
            if (var0.junk != null) {
               doRollItem(var0.junk, var1, var5, var3, var2, true, var4);
            }

            doRollItem(var0, var1, var5, var3, var2, false, var4);
         }
      }
   }

   public static void doRollItem(
      ItemPickerContainer var0, ItemContainer var1, float var2, IsoGameCharacter var3, boolean var4, boolean var5, ItemPickerRoom var6
   ) {
      boolean var7 = false;
      boolean var8 = false;
      String var9 = "";
      if (player != null && var3 != null) {
         var7 = var3.Traits.Lucky.isSet();
         var8 = var3.Traits.Unlucky.isSet();
      }

      for (int var10 = 0; var10 < var0.rolls; var10++) {
         ItemPickerItem[] var11 = var0.Items;

         for (int var12 = 0; var12 < var11.length; var12++) {
            ItemPickerItem var13 = var11[var12];
            float var14 = var13.chance;
            var9 = var13.itemName;
            if (var7) {
               var14 *= 1.1F;
            }

            if (var8) {
               var14 *= 0.9F;
            }

            float var15 = getLootModifier(var9);
            if (var15 == 0.0F) {
               return;
            }

            if (var5) {
               var2 = 0.0F;
               var15 = 1.0F;
               var14 = (float)(var14 * 1.4);
            }

            if (Rand.Next(10000) <= var14 * 100.0F * var15 + var2 * 10.0F) {
               InventoryItem var16 = tryAddItemToContainer(var1, var9, var0);
               if (var16 == null) {
                  return;
               }

               checkStashItem(var16, var0);
               if (var1.getType().equals("freezer") && var16 instanceof Food && ((Food)var16).isFreezing()) {
                  ((Food)var16).freeze();
               }

               if (var16 instanceof Key var17) {
                  var17.takeKeyId();
                  if (var1.getSourceGrid() != null && var1.getSourceGrid().getBuilding() != null && var1.getSourceGrid().getBuilding().getDef() != null) {
                     int var18 = var1.getSourceGrid().getBuilding().getDef().getKeySpawned();
                     if (var18 < 2) {
                        var1.getSourceGrid().getBuilding().getDef().setKeySpawned(var18 + 1);
                     } else {
                        var1.Remove(var16);
                     }
                  }
               }

               String var24 = var16.getScriptItem().getRecordedMediaCat();
               if (var24 != null) {
                  RecordedMedia var25 = ZomboidRadio.getInstance().getRecordedMedia();
                  MediaData var19 = var25.getRandomFromCategory(var24);
                  if (var19 == null) {
                     var1.Remove(var16);
                     if ("Home-VHS".equalsIgnoreCase(var24)) {
                        var19 = var25.getRandomFromCategory("Retail-VHS");
                        if (var19 == null) {
                           return;
                        }

                        var16 = var1.AddItem("Base.VHS_Retail");
                        if (var16 == null) {
                           return;
                        }

                        var16.setRecordedMediaData(var19);
                     }

                     return;
                  }

                  var16.setRecordedMediaData(var19);
               }

               if (WeaponUpgradeMap.containsKey(var16.getType())) {
                  DoWeaponUpgrade(var16);
               }

               if (!var0.noAutoAge) {
                  var16.setAutoAge();
               }

               boolean var26 = false;
               if (var6 != null) {
                  var26 = var6.isShop;
               }

               if (!var26 && Rand.Next(100) < 40 && var16 instanceof DrainableComboItem) {
                  float var27 = 1.0F / ((DrainableComboItem)var16).getUseDelta();
                  ((DrainableComboItem)var16).setUsedDelta(Rand.Next(1.0F, var27 - 1.0F) * ((DrainableComboItem)var16).getUseDelta());
               }

               if (!var26 && var16 instanceof HandWeapon && Rand.Next(100) < 40) {
                  var16.setCondition(Rand.Next(1, var16.getConditionMax()));
               }

               if (var16 instanceof HandWeapon && !var0.dontSpawnAmmo && Rand.Next(100) < 90) {
                  int var28 = 30;
                  HandWeapon var20 = (HandWeapon)var16;
                  if (Core.getInstance().getOptionReloadDifficulty() > 1 && !StringUtils.isNullOrEmpty(var20.getMagazineType()) && Rand.Next(100) < 90) {
                     if (Rand.NextBool(3)) {
                        InventoryItem var21 = var1.AddItem(var20.getMagazineType());
                        if (Rand.NextBool(5)) {
                           var21.setCurrentAmmoCount(Rand.Next(1, var21.getMaxAmmo()));
                        }

                        if (!Rand.NextBool(5)) {
                           var21.setCurrentAmmoCount(var21.getMaxAmmo());
                        }
                     } else {
                        if (!StringUtils.isNullOrWhitespace(var20.getMagazineType())) {
                           var20.setContainsClip(true);
                        }

                        if (Rand.NextBool(6)) {
                           var20.setCurrentAmmoCount(Rand.Next(1, var20.getMaxAmmo()));
                        } else {
                           var28 = Rand.Next(60, 100);
                        }
                     }

                     if (var20.haveChamber()) {
                        var20.setRoundChambered(true);
                     }
                  }

                  if (Core.getInstance().getOptionReloadDifficulty() == 1 || StringUtils.isNullOrEmpty(var20.getMagazineType()) && Rand.Next(100) < 30) {
                     var20.setCurrentAmmoCount(Rand.Next(1, var20.getMaxAmmo()));
                     if (var20.haveChamber()) {
                        var20.setRoundChambered(true);
                     }
                  }

                  if (!StringUtils.isNullOrEmpty(var20.getAmmoBox()) && Rand.Next(100) < var28) {
                     var1.AddItem(var20.getAmmoBox());
                  } else if (!StringUtils.isNullOrEmpty(var20.getAmmoType()) && Rand.Next(100) < 50) {
                     var1.AddItems(var20.getAmmoType(), Rand.Next(1, 5));
                  }
               }

               if (var16 instanceof InventoryContainer && containers.containsKey(var16.getType())) {
                  ItemPickerContainer var29 = (ItemPickerContainer)containers.get(var16.getType());
                  if (var4 && Rand.Next(var29.fillRand) == 0) {
                     rollContainerItem((InventoryContainer)var16, var3, (ItemPickerContainer)containers.get(var16.getType()));
                  }
               }
            }
         }
      }
   }

   private static void checkStashItem(InventoryItem var0, ItemPickerContainer var1) {
      if (var1.stashChance > 0 && var0 instanceof MapItem && !StringUtils.isNullOrEmpty(((MapItem)var0).getMapID())) {
         var0.setStashChance(var1.stashChance);
      }

      StashSystem.checkStashItem(var0);
   }

   public static void rollContainerItem(InventoryContainer var0, IsoGameCharacter var1, ItemPickerContainer var2) {
      if (var2 != null) {
         ItemContainer var3 = var0.getInventory();
         float var4 = 0.0F;
         IsoMetaChunk var5 = null;
         if (player != null && IsoWorld.instance != null) {
            var5 = IsoWorld.instance.getMetaChunk((int)player.getX() / 10, (int)player.getY() / 10);
         }

         if (var5 != null) {
            var4 = var5.getLootZombieIntensity();
         }

         if (var4 > zombieDensityCap) {
            var4 = zombieDensityCap;
         }

         if (var2.ignoreZombieDensity) {
            var4 = 0.0F;
         }

         boolean var6 = false;
         boolean var7 = false;
         String var8 = "";
         if (player != null && var1 != null) {
            var6 = var1.Traits.Lucky.isSet();
            var7 = var1.Traits.Unlucky.isSet();
         }

         for (int var9 = 0; var9 < var2.rolls; var9++) {
            ItemPickerItem[] var10 = var2.Items;

            for (int var11 = 0; var11 < var10.length; var11++) {
               ItemPickerItem var12 = var10[var11];
               float var13 = var12.chance;
               var8 = var12.itemName;
               if (var6) {
                  var13 *= 1.1F;
               }

               if (var7) {
                  var13 *= 0.9F;
               }

               float var14 = getLootModifier(var8);
               if (Rand.Next(10000) <= var13 * 100.0F * var14 + var4 * 10.0F) {
                  InventoryItem var15 = tryAddItemToContainer(var3, var8, var2);
                  if (var15 == null) {
                     return;
                  }

                  MapItem var16 = (MapItem)Type.tryCastTo(var15, MapItem.class);
                  if (var16 != null && !StringUtils.isNullOrEmpty(var16.getMapID()) && var2.maxMap > 0) {
                     int var17 = 0;

                     for (int var18 = 0; var18 < var3.getItems().size(); var18++) {
                        MapItem var19 = (MapItem)Type.tryCastTo((InventoryItem)var3.getItems().get(var18), MapItem.class);
                        if (var19 != null && !StringUtils.isNullOrEmpty(var19.getMapID())) {
                           var17++;
                        }
                     }

                     if (var17 > var2.maxMap) {
                        var3.Remove(var15);
                     }
                  }

                  checkStashItem(var15, var2);
                  if (var3.getType().equals("freezer") && var15 instanceof Food && ((Food)var15).isFreezing()) {
                     ((Food)var15).freeze();
                  }

                  if (var15 instanceof Key var21) {
                     var21.takeKeyId();
                     if (var3.getSourceGrid() != null && var3.getSourceGrid().getBuilding() != null && var3.getSourceGrid().getBuilding().getDef() != null) {
                        int var22 = var3.getSourceGrid().getBuilding().getDef().getKeySpawned();
                        if (var22 < 2) {
                           var3.getSourceGrid().getBuilding().getDef().setKeySpawned(var22 + 1);
                        } else {
                           var3.Remove(var15);
                        }
                     }
                  }

                  if (!var3.getType().equals("freezer")) {
                     var15.setAutoAge();
                  }
               }
            }
         }
      }
   }

   private static void DoWeaponUpgrade(InventoryItem var0) {
      ItemPickerUpgradeWeapons var1 = WeaponUpgradeMap.get(var0.getType());
      if (var1 != null) {
         if (var1.Upgrades.size() != 0) {
            int var2 = Rand.Next(var1.Upgrades.size());

            for (int var3 = 0; var3 < var2; var3++) {
               String var4 = (String)PZArrayUtil.pickRandom(var1.Upgrades);
               InventoryItem var5 = InventoryItemFactory.CreateItem(var4);
               ((HandWeapon)var0).attachWeaponPart((WeaponPart)var5);
            }
         }
      }
   }

   public static float getLootModifier(String var0) {
      Item var1 = ScriptManager.instance.FindItem(var0);
      if (var1 == null) {
         return 0.6F;
      } else {
         float var2 = OtherLootModifier;
         if (var1.getType() == zombie.scripting.objects.Item.Type.Food) {
            if (var1.CannedFood) {
               var2 = CannedFoodLootModifier;
            } else {
               var2 = FoodLootModifier;
            }
         }

         if ("Ammo".equals(var1.getDisplayCategory())) {
            var2 = AmmoLootModifier;
         }

         if (var1.getType() == zombie.scripting.objects.Item.Type.Weapon && !var1.isRanged()) {
            var2 = WeaponLootModifier;
         }

         if (var1.getType() == zombie.scripting.objects.Item.Type.WeaponPart
            || var1.getType() == zombie.scripting.objects.Item.Type.Weapon && var1.isRanged()
            || var1.getType() == zombie.scripting.objects.Item.Type.Normal && !StringUtils.isNullOrEmpty(var1.getAmmoType())) {
            var2 = RangedWeaponLootModifier;
         }

         if (var1.getType() == zombie.scripting.objects.Item.Type.Literature) {
            var2 = LiteratureLootModifier;
         }

         if (var1.Medical) {
            var2 = MedicalLootModifier;
         }

         if (var1.SurvivalGear) {
            var2 = SurvivalGearsLootModifier;
         }

         if (var1.MechanicsItem) {
            var2 = MechanicsLootModifier;
         }

         return var2;
      }
   }

   public static void updateOverlaySprite(IsoObject var0) {
      ContainerOverlays.instance.updateContainerOverlaySprite(var0);
   }

   public static void doOverlaySprite(IsoGridSquare var0) {
      if (!GameClient.bClient) {
         if (var0 != null && var0.getRoom() != null && !var0.isOverlayDone()) {
            PZArrayList var1 = var0.getObjects();

            for (int var2 = 0; var2 < var1.size(); var2++) {
               IsoObject var3 = (IsoObject)var1.get(var2);
               if (var3 != null && var3.getContainer() != null && !var3.getContainer().isExplored()) {
                  fillContainer(var3.getContainer(), IsoPlayer.getInstance());
                  var3.getContainer().setExplored(true);
                  if (GameServer.bServer) {
                     GlobalObject.sendItemsInContainer(var3, var3.getContainer());
                  }
               }

               updateOverlaySprite(var3);
            }

            var0.setOverlayDone(true);
         }
      }
   }

   public static ItemPickerContainer getItemContainer(String var0, String var1, String var2, boolean var3) {
      ItemPickerRoom var4 = (ItemPickerRoom)rooms.get(var0);
      if (var4 == null) {
         return null;
      } else {
         ItemPickerContainer var5 = (ItemPickerContainer)var4.Containers.get(var1);
         if (var5 != null && var5.procedural) {
            ArrayList var6 = var5.proceduralItems;

            for (int var7 = 0; var7 < var6.size(); var7++) {
               ProceduralItem var8 = (ProceduralItem)var6.get(var7);
               if (var2.equals(var8.name)) {
                  ItemPickerContainer var9 = (ItemPickerContainer)ProceduralDistributions.get(var2);
                  if (var9.junk != null && var3) {
                     return var9.junk;
                  }

                  if (!var3) {
                     return var9;
                  }
               }
            }
         }

         return var3 ? var5.junk : var5;
      }
   }
}
