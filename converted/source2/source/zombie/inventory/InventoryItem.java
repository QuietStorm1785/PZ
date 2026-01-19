package zombie.inventory;

import java.io.DataInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashMap;
import se.krka.kahlua.vm.KahluaTable;
import se.krka.kahlua.vm.KahluaTableIterator;
import zombie.GameTime;
import zombie.GameWindow;
import zombie.SandboxOptions;
import zombie.Lua.LuaEventManager;
import zombie.Lua.LuaManager;
import zombie.audio.BaseSoundEmitter;
import zombie.characterTextures.BloodBodyPartType;
import zombie.characterTextures.BloodClothingType;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.characters.SurvivorDesc;
import zombie.core.Color;
import zombie.core.Colors;
import zombie.core.Core;
import zombie.core.Translator;
import zombie.core.logger.ExceptionLogger;
import zombie.core.math.PZMath;
import zombie.core.skinnedmodel.model.WorldItemAtlas.ItemTexture;
import zombie.core.skinnedmodel.population.ClothingItem;
import zombie.core.skinnedmodel.visual.ItemVisual;
import zombie.core.stash.StashSystem;
import zombie.core.textures.ColorInfo;
import zombie.core.textures.Texture;
import zombie.core.utils.Bits;
import zombie.debug.DebugLog;
import zombie.debug.DebugOptions;
import zombie.inventory.types.Clothing;
import zombie.inventory.types.Drainable;
import zombie.inventory.types.DrainableComboItem;
import zombie.inventory.types.Food;
import zombie.inventory.types.HandWeapon;
import zombie.inventory.types.InventoryContainer;
import zombie.inventory.types.Key;
import zombie.iso.IsoDirections;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;
import zombie.iso.IsoWorld;
import zombie.iso.objects.IsoWorldInventoryObject;
import zombie.iso.objects.RainManager;
import zombie.network.GameClient;
import zombie.radio.ZomboidRadio;
import zombie.radio.media.MediaData;
import zombie.scripting.ScriptManager;
import zombie.scripting.objects.Item;
import zombie.scripting.objects.ItemReplacement;
import zombie.ui.ObjectTooltip;
import zombie.ui.TextManager;
import zombie.ui.UIFont;
import zombie.ui.ObjectTooltip.Layout;
import zombie.ui.ObjectTooltip.LayoutItem;
import zombie.util.StringUtils;
import zombie.util.Type;
import zombie.util.io.BitHeader;
import zombie.util.io.BitHeaderRead;
import zombie.util.io.BitHeaderWrite;
import zombie.util.io.BitHeader.HeaderSize;
import zombie.vehicles.VehiclePart;
import zombie.world.ItemInfo;
import zombie.world.WorldDictionary;

public class InventoryItem {
   protected IsoGameCharacter previousOwner = null;
   protected Item ScriptItem = null;
   protected ItemType cat = ItemType.None;
   protected ItemContainer container;
   protected int containerX = 0;
   protected int containerY = 0;
   protected String name;
   protected String replaceOnUse = null;
   protected String replaceOnUseFullType = null;
   protected int ConditionMax = 10;
   protected ItemContainer rightClickContainer = null;
   protected Texture texture;
   protected Texture texturerotten;
   protected Texture textureCooked;
   protected Texture textureBurnt;
   protected String type;
   protected String fullType;
   protected int uses = 1;
   protected float Age = 0.0F;
   protected float LastAged = -1.0F;
   protected boolean IsCookable = false;
   protected float CookingTime = 0.0F;
   protected float MinutesToCook = 60.0F;
   protected float MinutesToBurn = 120.0F;
   public boolean Cooked = false;
   protected boolean Burnt = false;
   protected int OffAge = 1000000000;
   protected int OffAgeMax = 1000000000;
   protected float Weight = 1.0F;
   protected float ActualWeight = 1.0F;
   protected String WorldTexture;
   protected String Description;
   protected int Condition = 10;
   protected String OffString = Translator.getText("Tooltip_food_Rotten");
   protected String FreshString = Translator.getText("Tooltip_food_Fresh");
   protected String StaleString = Translator.getText("Tooltip_food_Stale");
   protected String CookedString = Translator.getText("Tooltip_food_Cooked");
   protected String UnCookedString = Translator.getText("Tooltip_food_Uncooked");
   protected String FrozenString = Translator.getText("Tooltip_food_Frozen");
   protected String BurntString = Translator.getText("Tooltip_food_Burnt");
   private String brokenString = Translator.getText("Tooltip_broken");
   protected String module = "Base";
   protected float boredomChange = 0.0F;
   protected float unhappyChange = 0.0F;
   protected float stressChange = 0.0F;
   protected ArrayList<IsoObject> Taken = new ArrayList<>();
   protected IsoDirections placeDir = IsoDirections.Max;
   protected IsoDirections newPlaceDir = IsoDirections.Max;
   private KahluaTable table = null;
   public String ReplaceOnUseOn = null;
   public Color col = Color.white;
   public boolean IsWaterSource = false;
   public boolean CanStoreWater = false;
   public boolean CanStack = false;
   private boolean activated = false;
   private boolean isTorchCone = false;
   private int lightDistance = 0;
   private int Count = 1;
   public float fatigueChange = 0.0F;
   public IsoWorldInventoryObject worldItem = null;
   private String customMenuOption = null;
   private String tooltip = null;
   private String displayCategory = null;
   private int haveBeenRepaired = 1;
   private boolean broken = false;
   private String originalName = null;
   public int id = 0;
   public boolean RequiresEquippedBothHands;
   public ByteBuffer byteData;
   public ArrayList<String> extraItems = null;
   private boolean customName = false;
   private String breakSound = null;
   protected boolean alcoholic = false;
   private float alcoholPower = 0.0F;
   private float bandagePower = 0.0F;
   private float ReduceInfectionPower = 0.0F;
   private boolean customWeight = false;
   private boolean customColor = false;
   private int keyId = -1;
   private boolean taintedWater = false;
   private boolean remoteController = false;
   private boolean canBeRemote = false;
   private int remoteControlID = -1;
   private int remoteRange = 0;
   private float colorRed = 1.0F;
   private float colorGreen = 1.0F;
   private float colorBlue = 1.0F;
   private String countDownSound = null;
   private String explosionSound = null;
   private IsoGameCharacter equipParent = null;
   private String evolvedRecipeName = null;
   private float metalValue = 0.0F;
   private float itemHeat = 1.0F;
   private float meltingTime = 0.0F;
   private String worker;
   private boolean isWet = false;
   private float wetCooldown = -1.0F;
   private String itemWhenDry = null;
   private boolean favorite = false;
   protected ArrayList<String> requireInHandOrInventory = null;
   private String map = null;
   private String stashMap = null;
   public boolean keepOnDeplete = false;
   private boolean zombieInfected = false;
   private boolean rainFactorZero = false;
   private float itemCapacity = -1.0F;
   private int maxCapacity = -1;
   private float brakeForce = 0.0F;
   private int chanceToSpawnDamaged = 0;
   private float conditionLowerNormal = 0.0F;
   private float conditionLowerOffroad = 0.0F;
   private float wheelFriction = 0.0F;
   private float suspensionDamping = 0.0F;
   private float suspensionCompression = 0.0F;
   private float engineLoudness = 0.0F;
   protected ItemVisual visual = null;
   protected String staticModel = null;
   private ArrayList<String> iconsForTexture = null;
   private ArrayList<BloodClothingType> bloodClothingType = new ArrayList<>();
   private int stashChance = 80;
   private String ammoType = null;
   private int maxAmmo = 0;
   private int currentAmmoCount = 0;
   private String gunType = null;
   private String attachmentType = null;
   private ArrayList<String> attachmentsProvided = null;
   private int attachedSlot = -1;
   private String attachedSlotType = null;
   private String attachmentReplacement = null;
   private String attachedToModel = null;
   private String m_alternateModelName = null;
   private short registry_id = -1;
   public int worldZRotation = -1;
   public float worldScale = 1.0F;
   private short recordedMediaIndex = -1;
   private byte mediaType = -1;
   private boolean isInitialised = false;
   public ItemTexture atlasTexture = null;
   private final int maxTextLength = 256;
   public float jobDelta = 0.0F;
   public String jobType = null;
   static ByteBuffer tempBuffer = ByteBuffer.allocate(20000);
   public String mainCategory = null;
   private boolean canBeActivated;
   private float lightStrength;
   public String CloseKillMove = null;
   private boolean beingFilled = false;

   public int getSaveType() {
      throw new RuntimeException("InventoryItem.getSaveType() not implemented for " + this.getClass().getName());
   }

   public IsoWorldInventoryObject getWorldItem() {
      return this.worldItem;
   }

   public void setEquipParent(IsoGameCharacter var1) {
      this.equipParent = var1;
   }

   public IsoGameCharacter getEquipParent() {
      return this.equipParent == null || this.equipParent.getPrimaryHandItem() != this && this.equipParent.getSecondaryHandItem() != this
         ? null
         : this.equipParent;
   }

   public String getBringToBearSound() {
      return this.getScriptItem().getBringToBearSound();
   }

   public String getEquipSound() {
      return this.getScriptItem().getEquipSound();
   }

   public String getUnequipSound() {
      return this.getScriptItem().getUnequipSound();
   }

   public void setWorldItem(IsoWorldInventoryObject var1) {
      this.worldItem = var1;
   }

   public void setJobDelta(float var1) {
      this.jobDelta = var1;
   }

   public float getJobDelta() {
      return this.jobDelta;
   }

   public void setJobType(String var1) {
      this.jobType = var1;
   }

   public String getJobType() {
      return this.jobType;
   }

   public boolean hasModData() {
      return this.table != null && !this.table.isEmpty();
   }

   public KahluaTable getModData() {
      if (this.table == null) {
         this.table = LuaManager.platform.newTable();
      }

      return this.table;
   }

   public void storeInByteData(IsoObject var1) {
      tempBuffer.clear();

      try {
         var1.save(tempBuffer, false);
      } catch (IOException var3) {
         var3.printStackTrace();
      }

      tempBuffer.flip();
      if (this.byteData == null || this.byteData.capacity() < tempBuffer.limit() - 2 + 8) {
         this.byteData = ByteBuffer.allocate(tempBuffer.limit() - 2 + 8);
      }

      tempBuffer.get();
      tempBuffer.get();
      this.byteData.clear();
      this.byteData.put((byte)87);
      this.byteData.put((byte)86);
      this.byteData.put((byte)69);
      this.byteData.put((byte)82);
      this.byteData.putInt(195);
      this.byteData.put(tempBuffer);
      this.byteData.flip();
   }

   public ByteBuffer getByteData() {
      return this.byteData;
   }

   public boolean isRequiresEquippedBothHands() {
      return this.RequiresEquippedBothHands;
   }

   public float getA() {
      return this.col.a;
   }

   public float getR() {
      return this.col.r;
   }

   public float getG() {
      return this.col.g;
   }

   public float getB() {
      return this.col.b;
   }

   public InventoryItem(String var1, String var2, String var3, String var4) {
      this.col = Color.white;
      this.texture = Texture.trygetTexture(var4);
      if (this.texture == null) {
         this.texture = Texture.getSharedTexture("media/inventory/Question_On.png");
      }

      this.module = var1;
      this.name = var2;
      this.originalName = var2;
      this.type = var3;
      this.fullType = var1 + "." + var3;
      this.WorldTexture = var4.replace("Item_", "media/inventory/world/WItem_");
      this.WorldTexture = this.WorldTexture + ".png";
   }

   public InventoryItem(String var1, String var2, String var3, Item var4) {
      this.col = Color.white;
      this.texture = var4.NormalTexture;
      this.module = var1;
      this.name = var2;
      this.originalName = var2;
      this.type = var3;
      this.fullType = var1 + "." + var3;
      this.WorldTexture = var4.WorldTextureName;
   }

   public String getType() {
      return this.type;
   }

   public Texture getTex() {
      return this.texture;
   }

   public String getCategory() {
      return this.mainCategory != null ? this.mainCategory : "Item";
   }

   public boolean IsRotten() {
      return this.Age > this.OffAge;
   }

   public float HowRotten() {
      if (this.OffAgeMax - this.OffAge == 0) {
         return this.Age > this.OffAge ? 1.0F : 0.0F;
      } else {
         return (this.Age - this.OffAge) / (this.OffAgeMax - this.OffAge);
      }
   }

   public boolean CanStack(InventoryItem var1) {
      return false;
   }

   public boolean ModDataMatches(InventoryItem var1) {
      KahluaTable var2 = var1.getModData();
      KahluaTable var3 = var1.getModData();
      if (var2 == null && var3 == null) {
         return true;
      } else if (var2 == null) {
         return false;
      } else if (var3 == null) {
         return false;
      } else if (var2.len() != var3.len()) {
         return false;
      } else {
         KahluaTableIterator var4 = var2.iterator();

         while (var4.advance()) {
            Object var5 = var3.rawget(var4.getKey());
            Object var6 = var4.getValue();
            if (!var5.equals(var6)) {
               return false;
            }
         }

         return true;
      }
   }

   public void DoTooltip(ObjectTooltip var1) {
      var1.render();
      UIFont var2 = var1.getFont();
      int var3 = var1.getLineSpacing();
      int var4 = 5;
      String var5 = "";
      if (this.Burnt) {
         var5 = var5 + this.BurntString + " ";
      } else if (this.OffAge < 1000000000 && this.Age < this.OffAge) {
         var5 = var5 + this.FreshString + " ";
      } else if (this.OffAgeMax < 1000000000 && this.Age >= this.OffAgeMax) {
         var5 = var5 + this.OffString + " ";
      } else if (this.OffAgeMax < 1000000000 && this.Age >= this.OffAge) {
         var5 = var5 + this.StaleString + " ";
      }

      if (this.isCooked() && !this.Burnt && !this.hasTag("HideCooked")) {
         var5 = var5 + this.CookedString + " ";
      } else if (this.IsCookable && !this.Burnt && !(this instanceof DrainableComboItem) && !this.hasTag("HideCooked")) {
         var5 = var5 + this.UnCookedString + " ";
      }

      if (this instanceof Food && ((Food)this).isFrozen()) {
         var5 = var5 + this.FrozenString + " ";
      }

      var5 = var5.trim();
      String var6;
      if (var5.isEmpty()) {
         var1.DrawText(var2, var6 = this.getName(), 5.0, var4, 1.0, 1.0, 0.8F, 1.0);
      } else if (this.OffAgeMax < 1000000000 && this.Age >= this.OffAgeMax) {
         var1.DrawText(var2, var6 = Translator.getText("IGUI_FoodNaming", var5, this.name), 5.0, var4, 1.0, 0.1F, 0.1F, 1.0);
      } else {
         var1.DrawText(var2, var6 = Translator.getText("IGUI_FoodNaming", var5, this.name), 5.0, var4, 1.0, 1.0, 0.8F, 1.0);
      }

      var1.adjustWidth(5, var6);
      var4 += var3 + 5;
      if (this.extraItems != null) {
         var1.DrawText(var2, Translator.getText("Tooltip_item_Contains"), 5.0, var4, 1.0, 1.0, 0.8F, 1.0);
         int var7 = 5 + TextManager.instance.MeasureStringX(var2, Translator.getText("Tooltip_item_Contains")) + 4;
         int var8 = (var3 - 10) / 2;

         for (int var9 = 0; var9 < this.extraItems.size(); var9++) {
            InventoryItem var10 = InventoryItemFactory.CreateItem(this.extraItems.get(var9));
            if (!this.IsCookable && var10.IsCookable) {
               var10.setCooked(true);
            }

            if (this.isCooked() && var10.IsCookable) {
               var10.setCooked(true);
            }

            var1.DrawTextureScaled(var10.getTex(), var7, var4 + var8, 10.0, 10.0, 1.0);
            var7 += 11;
         }

         var4 = var4 + var3 + 5;
      }

      if (this instanceof Food && ((Food)this).spices != null) {
         var1.DrawText(var2, Translator.getText("Tooltip_item_Spices"), 5.0, var4, 1.0, 1.0, 0.8F, 1.0);
         int var18 = 5 + TextManager.instance.MeasureStringX(var2, Translator.getText("Tooltip_item_Spices")) + 4;
         int var20 = (var3 - 10) / 2;

         for (int var51 = 0; var51 < ((Food)this).spices.size(); var51++) {
            InventoryItem var53 = InventoryItemFactory.CreateItem((String)((Food)this).spices.get(var51));
            var1.DrawTextureScaled(var53.getTex(), var18, var4 + var20, 10.0, 10.0, 1.0);
            var18 += 11;
         }

         var4 = var4 + var3 + 5;
      }

      Layout var19 = var1.beginLayout();
      var19.setMinLabelWidth(80);
      LayoutItem var21 = var19.addItem();
      var21.setLabel(Translator.getText("Tooltip_item_Weight") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
      boolean var52 = this.isEquipped();
      if (!(this instanceof HandWeapon) && !(this instanceof Clothing) && !(this instanceof DrainableComboItem) && !this.getFullType().contains("Walkie")) {
         float var54 = this.getUnequippedWeight();
         if (var54 > 0.0F && var54 < 0.01F) {
            var54 = 0.01F;
         }

         var21.setValueRightNoPlus(var54);
      } else if (var52) {
         var21.setValue(
            this.getCleanString(this.getEquippedWeight())
               + "    ("
               + this.getCleanString(this.getUnequippedWeight())
               + " "
               + Translator.getText("Tooltip_item_Unequipped")
               + ")",
            1.0F,
            1.0F,
            1.0F,
            1.0F
         );
      } else if (this.getAttachedSlot() > -1) {
         var21.setValue(
            this.getCleanString(this.getHotbarEquippedWeight())
               + "    ("
               + this.getCleanString(this.getUnequippedWeight())
               + " "
               + Translator.getText("Tooltip_item_Unequipped")
               + ")",
            1.0F,
            1.0F,
            1.0F,
            1.0F
         );
      } else {
         var21.setValue(
            this.getCleanString(this.getUnequippedWeight())
               + "    ("
               + this.getCleanString(this.getEquippedWeight())
               + " "
               + Translator.getText("Tooltip_item_Equipped")
               + ")",
            1.0F,
            1.0F,
            1.0F,
            1.0F
         );
      }

      if (var1.getWeightOfStack() > 0.0F) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_item_StackWeight") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         float var55 = var1.getWeightOfStack();
         if (var55 > 0.0F && var55 < 0.01F) {
            var55 = 0.01F;
         }

         var21.setValueRightNoPlus(var55);
      }

      if (this.getMaxAmmo() > 0 && !(this instanceof HandWeapon)) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_weapon_AmmoCount") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValue(this.getCurrentAmmoCount() + " / " + this.getMaxAmmo(), 1.0F, 1.0F, 1.0F, 1.0F);
      }

      if (!(this instanceof HandWeapon) && this.getAmmoType() != null) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("ContextMenu_AmmoType") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         String var56 = InventoryItemFactory.CreateItem(this.getAmmoType()).getDisplayName();
         var21.setValue(Translator.getText(var56), 1.0F, 1.0F, 1.0F, 1.0F);
      }

      if (this.gunType != null) {
         Item var57 = ScriptManager.instance.FindItem(this.getGunType());
         if (var57 == null) {
            var57 = ScriptManager.instance.FindItem(this.getModule() + "." + this.ammoType);
         }

         if (var57 != null) {
            var21 = var19.addItem();
            var21.setLabel(Translator.getText("ContextMenu_GunType") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
            var21.setValue(var57.getDisplayName(), 1.0F, 1.0F, 1.0F, 1.0F);
         }
      }

      if (Core.bDebug && DebugOptions.instance.TooltipInfo.getValue()) {
         var21 = var19.addItem();
         var21.setLabel("getActualWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.getActualWeight());
         var21 = var19.addItem();
         var21.setLabel("getWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.getWeight());
         var21 = var19.addItem();
         var21.setLabel("getEquippedWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.getEquippedWeight());
         var21 = var19.addItem();
         var21.setLabel("getUnequippedWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.getUnequippedWeight());
         var21 = var19.addItem();
         var21.setLabel("getContentsWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.getContentsWeight());
         if (this instanceof Key || "Doorknob".equals(this.type)) {
            var21 = var19.addItem();
            var21.setLabel("DBG: keyId", 1.0F, 1.0F, 0.8F, 1.0F);
            var21.setValueRightNoPlus(this.getKeyId());
         }

         var21 = var19.addItem();
         var21.setLabel("ID", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.id);
         var21 = var19.addItem();
         var21.setLabel("DictionaryID", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.registry_id);
         ClothingItem var58 = this.getClothingItem();
         if (var58 != null) {
            var21 = var19.addItem();
            var21.setLabel("ClothingItem", 1.0F, 1.0F, 1.0F, 1.0F);
            var21.setValue(this.getClothingItem().m_Name, 1.0F, 1.0F, 1.0F, 1.0F);
         }
      }

      if (this.getFatigueChange() != 0.0F) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_item_Fatigue") + ": ", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRight((int)(this.getFatigueChange() * 100.0F), false);
      }

      if (this instanceof DrainableComboItem) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("IGUI_invpanel_Remaining") + ": ", 1.0F, 1.0F, 0.8F, 1.0F);
         float var59 = ((DrainableComboItem)this).getUsedDelta();
         ColorInfo var11 = new ColorInfo();
         Core.getInstance().getBadHighlitedColor().interp(Core.getInstance().getGoodHighlitedColor(), var59, var11);
         var21.setProgress(var59, var11.getR(), var11.getG(), var11.getB(), 1.0F);
      }

      if (this.isTaintedWater() && SandboxOptions.instance.EnableTaintedWaterText.getValue()) {
         var21 = var19.addItem();
         if (this.isCookable()) {
            var21.setLabel(Translator.getText("Tooltip_item_TaintedWater"), 1.0F, 0.5F, 0.5F, 1.0F);
         } else {
            var21.setLabel(Translator.getText("Tooltip_item_TaintedWater_Plastic"), 1.0F, 0.5F, 0.5F, 1.0F);
         }
      }

      this.DoTooltip(var1, var19);
      if (this.getRemoteControlID() != -1) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_TrapControllerID"), 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValue(Integer.toString(this.getRemoteControlID()), 1.0F, 1.0F, 0.8F, 1.0F);
      }

      if (!FixingManager.getFixes(this).isEmpty()) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_weapon_Repaired") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         if (this.getHaveBeenRepaired() == 1) {
            var21.setValue(Translator.getText("Tooltip_never"), 1.0F, 1.0F, 1.0F, 1.0F);
         } else {
            var21.setValue(this.getHaveBeenRepaired() - 1 + "x", 1.0F, 1.0F, 1.0F, 1.0F);
         }
      }

      if (this.isEquippedNoSprint()) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_CantSprintEquipped"), 1.0F, 0.1F, 0.1F, 1.0F);
      }

      if (this.isWet()) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_Wetness") + ": ", 1.0F, 1.0F, 0.8F, 1.0F);
         float var60 = this.getWetCooldown() / 10000.0F;
         ColorInfo var64 = new ColorInfo();
         Core.getInstance().getGoodHighlitedColor().interp(Core.getInstance().getBadHighlitedColor(), var60, var64);
         var21.setProgress(var60, var64.getR(), var64.getG(), var64.getB(), 1.0F);
      }

      if (this.getMaxCapacity() > 0) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_container_Capacity") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         float var61 = this.getMaxCapacity();
         if (this.isConditionAffectsCapacity()) {
            var61 = VehiclePart.getNumberByCondition(this.getMaxCapacity(), this.getCondition(), 5.0F);
         }

         if (this.getItemCapacity() > -1.0F) {
            var21.setValue(this.getItemCapacity() + " / " + var61, 1.0F, 1.0F, 0.8F, 1.0F);
         } else {
            var21.setValue("0 / " + var61, 1.0F, 1.0F, 0.8F, 1.0F);
         }
      }

      if (this.getConditionMax() > 0 && this.getMechanicType() > 0) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_weapon_Condition") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValue(this.getCondition() + " / " + this.getConditionMax(), 1.0F, 1.0F, 0.8F, 1.0F);
      }

      if (this.isRecordedMedia()) {
         MediaData var62 = this.getMediaData();
         if (var62 != null) {
            if (var62.getTranslatedTitle() != null) {
               var21 = var19.addItem();
               var21.setLabel(Translator.getText("Tooltip_media_title") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
               var21.setValue(var62.getTranslatedTitle(), 1.0F, 1.0F, 1.0F, 1.0F);
               if (var62.getTranslatedSubTitle() != null) {
                  var21 = var19.addItem();
                  var21.setLabel("", 1.0F, 1.0F, 0.8F, 1.0F);
                  var21.setValue(var62.getTranslatedSubTitle(), 1.0F, 1.0F, 1.0F, 1.0F);
               }
            }

            if (var62.getTranslatedAuthor() != null) {
               var21 = var19.addItem();
               var21.setLabel(Translator.getText("Tooltip_media_author") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
               var21.setValue(var62.getTranslatedAuthor(), 1.0F, 1.0F, 1.0F, 1.0F);
            }
         }
      }

      if (Core.getInstance().getOptionShowItemModInfo() && !this.isVanilla()) {
         var21 = var19.addItem();
         Color var63 = Colors.CornFlowerBlue;
         var21.setLabel("Mod: " + this.getModName(), var63.r, var63.g, var63.b, 1.0F);
         ItemInfo var65 = WorldDictionary.getItemInfoFromID(this.registry_id);
         if (var65 != null && var65.getModOverrides() != null) {
            var21 = var19.addItem();
            float var12 = 0.5F;
            if (var65.getModOverrides().size() == 1) {
               var21.setLabel("This item overrides: " + WorldDictionary.getModNameFromID((String)var65.getModOverrides().get(0)), var12, var12, var12, 1.0F);
            } else {
               var21.setLabel("This item overrides:", var12, var12, var12, 1.0F);

               for (int var13 = 0; var13 < var65.getModOverrides().size(); var13++) {
                  var21 = var19.addItem();
                  var21.setLabel(" - " + WorldDictionary.getModNameFromID((String)var65.getModOverrides().get(var13)), var12, var12, var12, 1.0F);
               }
            }
         }
      }

      if (this.getTooltip() != null) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText(this.tooltip), 1.0F, 1.0F, 0.8F, 1.0F);
      }

      var4 = var19.render(5, var4, var1);
      var1.endLayout(var19);
      var4 += var1.padBottom;
      var1.setHeight(var4);
      if (var1.getWidth() < 150.0) {
         var1.setWidth(150.0);
      }
   }

   public String getCleanString(float var1) {
      float var2 = (int)((var1 + 0.005) * 100.0) / 100.0F;
      return Float.toString(var2);
   }

   public void DoTooltip(ObjectTooltip var1, Layout var2) {
   }

   public void SetContainerPosition(int var1, int var2) {
      this.containerX = var1;
      this.containerY = var2;
   }

   public void Use() {
      this.Use(false);
   }

   public void UseItem() {
      this.Use(false);
   }

   public void Use(boolean var1) {
      this.Use(var1, false);
   }

   public void Use(boolean var1, boolean var2) {
      if (this.isDisappearOnUse() || var1) {
         this.uses--;
         if (this.replaceOnUse != null && !var2 && !var1 && this.container != null) {
            String var3 = this.replaceOnUse;
            if (!this.replaceOnUse.contains(".")) {
               var3 = this.module + "." + var3;
            }

            InventoryItem var4 = this.container.AddItem(var3);
            if (var4 != null) {
               var4.setConditionFromModData(this);
            }

            this.container.setDrawDirty(true);
            this.container.setDirty(true);
            var4.setFavorite(this.isFavorite());
         }

         if (this.uses <= 0) {
            if (this.keepOnDeplete) {
               return;
            }

            if (this.container != null) {
               if (this.container.parent instanceof IsoGameCharacter && !(this instanceof HandWeapon)) {
                  IsoGameCharacter var5 = (IsoGameCharacter)this.container.parent;
                  var5.removeFromHands(this);
               }

               this.container.Items.remove(this);
               this.container.setDirty(true);
               this.container.setDrawDirty(true);
               this.container = null;
            }
         }
      }
   }

   public boolean shouldUpdateInWorld() {
      if (!GameClient.bClient && !this.rainFactorZero && this.canStoreWater() && this.hasReplaceType("WaterSource")) {
         IsoGridSquare var1 = this.getWorldItem().getSquare();
         return var1 != null && var1.isOutside();
      } else {
         return false;
      }
   }

   public void update() {
      if (this.isWet()) {
         this.wetCooldown = this.wetCooldown - 1.0F * GameTime.instance.getMultiplier();
         if (this.wetCooldown <= 0.0F) {
            InventoryItem var1 = InventoryItemFactory.CreateItem(this.itemWhenDry);
            if (this.isFavorite()) {
               var1.setFavorite(true);
            }

            IsoWorldInventoryObject var2 = this.getWorldItem();
            if (var2 != null) {
               IsoGridSquare var3 = var2.getSquare();
               var3.AddWorldInventoryItem(var1, var2.getX() % 1.0F, var2.getY() % 1.0F, var2.getZ() % 1.0F);
               var3.transmitRemoveItemFromSquare(var2);
               if (this.getContainer() != null) {
                  this.getContainer().setDirty(true);
                  this.getContainer().setDrawDirty(true);
               }

               var3.chunk.recalcHashCodeObjects();
               this.setWorldItem(null);
            } else if (this.getContainer() != null) {
               this.getContainer().addItem(var1);
               this.getContainer().Remove(this);
            }

            this.setWet(false);
            IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
            LuaEventManager.triggerEvent("OnContainerUpdate");
         }
      }

      if (!GameClient.bClient
         && !this.rainFactorZero
         && this.getWorldItem() != null
         && this.canStoreWater()
         && this.hasReplaceType("WaterSource")
         && RainManager.isRaining()) {
         IsoWorldInventoryObject var4 = this.getWorldItem();
         IsoGridSquare var5 = var4.getSquare();
         if (var5 != null && var5.isOutside()) {
            InventoryItem var6 = InventoryItemFactory.CreateItem(this.getReplaceType("WaterSource"));
            if (var6 == null) {
               this.rainFactorZero = true;
               return;
            }

            var6.setCondition(this.getCondition());
            if (var6 instanceof DrainableComboItem && var6.canStoreWater()) {
               if (((DrainableComboItem)var6).getRainFactor() == 0.0F) {
                  this.rainFactorZero = true;
                  return;
               }

               ((DrainableComboItem)var6).setUsedDelta(0.0F);
               var4.swapItem(var6);
            }
         }
      }
   }

   public boolean finishupdate() {
      return !GameClient.bClient
            && !this.rainFactorZero
            && this.canStoreWater()
            && this.hasReplaceType("WaterSource")
            && this.getWorldItem() != null
            && this.getWorldItem().getObjectIndex() != -1
         ? false
         : !this.isWet();
   }

   public void updateSound(BaseSoundEmitter var1) {
   }

   public String getFullType() {
      assert this.fullType != null && this.fullType.equals(this.module + "." + this.type);

      return this.fullType;
   }

   public void save(ByteBuffer var1, boolean var2) throws IOException {
      var2 = false;
      if (GameWindow.DEBUG_SAVE) {
         DebugLog.log(this.getFullType());
      }

      var1.putShort(this.registry_id);
      var1.put((byte)this.getSaveType());
      var1.putInt(this.id);
      BitHeaderWrite var3 = BitHeader.allocWrite(HeaderSize.Byte, var1);
      if (this.uses != 1) {
         var3.addFlags(1);
         if (this.uses > 32767) {
            var1.putShort((short)32767);
         } else {
            var1.putShort((short)this.uses);
         }
      }

      if (this.IsDrainable() && ((DrainableComboItem)this).getUsedDelta() < 1.0F) {
         var3.addFlags(2);
         float var4 = ((DrainableComboItem)this).getUsedDelta();
         byte var5 = (byte)((byte)(var4 * 255.0F) + -128);
         var1.put(var5);
      }

      if (this.Condition != this.ConditionMax) {
         var3.addFlags(4);
         var1.put((byte)this.getCondition());
      }

      if (this.visual != null) {
         var3.addFlags(8);
         this.visual.save(var1);
      }

      if (this.isCustomColor() && (this.col.r != 1.0F || this.col.g != 1.0F || this.col.b != 1.0F || this.col.a != 1.0F)) {
         var3.addFlags(16);
         var1.put(Bits.packFloatUnitToByte(this.getColor().r));
         var1.put(Bits.packFloatUnitToByte(this.getColor().g));
         var1.put(Bits.packFloatUnitToByte(this.getColor().b));
         var1.put(Bits.packFloatUnitToByte(this.getColor().a));
      }

      if (this.itemCapacity != -1.0F) {
         var3.addFlags(32);
         var1.putFloat(this.itemCapacity);
      }

      BitHeaderWrite var7 = BitHeader.allocWrite(HeaderSize.Integer, var1);
      if (this.table != null && !this.table.isEmpty()) {
         var7.addFlags(1);
         this.table.save(var1);
      }

      if (this.isActivated()) {
         var7.addFlags(2);
      }

      if (this.haveBeenRepaired != 1) {
         var7.addFlags(4);
         var1.putShort((short)this.getHaveBeenRepaired());
      }

      if (this.name != null && !this.name.equals(this.originalName)) {
         var7.addFlags(8);
         GameWindow.WriteString(var1, this.name);
      }

      if (this.byteData != null) {
         var7.addFlags(16);
         this.byteData.rewind();
         var1.putInt(this.byteData.limit());
         var1.put(this.byteData);
         this.byteData.flip();
      }

      if (this.extraItems != null && this.extraItems.size() > 0) {
         var7.addFlags(32);
         var1.putInt(this.extraItems.size());

         for (int var8 = 0; var8 < this.extraItems.size(); var8++) {
            var1.putShort(WorldDictionary.getItemRegistryID(this.extraItems.get(var8)));
         }
      }

      if (this.isCustomName()) {
         var7.addFlags(64);
      }

      if (this.isCustomWeight()) {
         var7.addFlags(128);
         var1.putFloat(this.isCustomWeight() ? this.getActualWeight() : -1.0F);
      }

      if (this.keyId != -1) {
         var7.addFlags(256);
         var1.putInt(this.getKeyId());
      }

      if (this.isTaintedWater()) {
         var7.addFlags(512);
      }

      if (this.remoteControlID != -1 || this.remoteRange != 0) {
         var7.addFlags(1024);
         var1.putInt(this.getRemoteControlID());
         var1.putInt(this.getRemoteRange());
      }

      if (this.colorRed != 1.0F || this.colorGreen != 1.0F || this.colorBlue != 1.0F) {
         var7.addFlags(2048);
         var1.put(Bits.packFloatUnitToByte(this.colorRed));
         var1.put(Bits.packFloatUnitToByte(this.colorGreen));
         var1.put(Bits.packFloatUnitToByte(this.colorBlue));
      }

      if (this.worker != null) {
         var7.addFlags(4096);
         GameWindow.WriteString(var1, this.getWorker());
      }

      if (this.wetCooldown != -1.0F) {
         var7.addFlags(8192);
         var1.putFloat(this.wetCooldown);
      }

      if (this.isFavorite()) {
         var7.addFlags(16384);
      }

      if (this.stashMap != null) {
         var7.addFlags(32768);
         GameWindow.WriteString(var1, this.stashMap);
      }

      if (this.isInfected()) {
         var7.addFlags(65536);
      }

      if (this.currentAmmoCount != 0) {
         var7.addFlags(131072);
         var1.putInt(this.currentAmmoCount);
      }

      if (this.attachedSlot != -1) {
         var7.addFlags(262144);
         var1.putInt(this.attachedSlot);
      }

      if (this.attachedSlotType != null) {
         var7.addFlags(524288);
         GameWindow.WriteString(var1, this.attachedSlotType);
      }

      if (this.attachedToModel != null) {
         var7.addFlags(1048576);
         GameWindow.WriteString(var1, this.attachedToModel);
      }

      if (this.maxCapacity != -1) {
         var7.addFlags(2097152);
         var1.putInt(this.maxCapacity);
      }

      if (this.isRecordedMedia()) {
         var7.addFlags(4194304);
         var1.putShort(this.recordedMediaIndex);
      }

      if (this.worldZRotation > -1) {
         var7.addFlags(8388608);
         var1.putInt(this.worldZRotation);
      }

      if (this.worldScale != 1.0F) {
         var7.addFlags(16777216);
         var1.putFloat(this.worldScale);
      }

      if (this.isInitialised) {
         var7.addFlags(33554432);
      }

      if (!var7.equals(0)) {
         var3.addFlags(64);
         var7.write();
      } else {
         var1.position(var7.getStartPosition());
      }

      var3.write();
      var3.release();
      var7.release();
   }

   public static InventoryItem loadItem(ByteBuffer var0, int var1) throws IOException {
      return loadItem(var0, var1, true);
   }

   public static InventoryItem loadItem(ByteBuffer var0, int var1, boolean var2) throws IOException {
      int var3 = var0.getInt();
      if (var3 <= 0) {
         throw new IOException("InventoryItem.loadItem() invalid item data length: " + var3);
      } else {
         int var4 = var0.position();
         short var5 = var0.getShort();
         byte var6 = -1;
         if (var1 >= 70) {
            var6 = var0.get();
            if (var6 < 0) {
               DebugLog.log("InventoryItem.loadItem() invalid item save-type " + var6 + ", itemtype: " + WorldDictionary.getItemTypeDebugString(var5));
               return null;
            }
         }

         InventoryItem var7 = InventoryItemFactory.CreateItem(var5);
         if (var2 && var6 != -1 && var7 != null && var7.getSaveType() != var6) {
            DebugLog.log("InventoryItem.loadItem() ignoring \"" + var7.getFullType() + "\" because type changed from " + var6 + " to " + var7.getSaveType());
            var7 = null;
         }

         if (var7 != null) {
            try {
               var7.load(var0, var1);
            } catch (Exception var9) {
               ExceptionLogger.logException(var9);
               var7 = null;
            }
         }

         if (var7 != null) {
            if (var3 != -1 && var0.position() != var4 + var3) {
               var0.position(var4 + var3);
               DebugLog.log(
                  "InventoryItem.loadItem() data length not matching, resetting buffer position to '"
                     + (var4 + var3)
                     + "'. itemtype: "
                     + WorldDictionary.getItemTypeDebugString(var5)
               );
               if (Core.bDebug) {
                  throw new IOException("InventoryItem.loadItem() read more data than save() wrote (" + WorldDictionary.getItemTypeDebugString(var5) + ")");
               }
            }

            return var7;
         } else {
            if (var0.position() >= var4 + var3) {
               if (var0.position() >= var4 + var3) {
                  var0.position(var4 + var3);
                  DebugLog.log(
                     "InventoryItem.loadItem() item == null, resetting buffer position to '"
                        + (var4 + var3)
                        + "'. itemtype: "
                        + WorldDictionary.getItemTypeDebugString(var5)
                  );
               }
            } else {
               while (var0.position() < var4 + var3) {
                  var0.get();
               }

               DebugLog.log("InventoryItem.loadItem() item == null, skipped bytes. itemtype: " + WorldDictionary.getItemTypeDebugString(var5));
            }

            return null;
         }
      }
   }

   public void load(ByteBuffer var1, int var2) throws IOException {
      this.id = var1.getInt();
      BitHeaderRead var3 = BitHeader.allocRead(HeaderSize.Byte, var1);
      this.uses = 1;
      if (this.IsDrainable()) {
         ((DrainableComboItem)this).setUsedDelta(1.0F);
      }

      this.Condition = this.ConditionMax;
      this.customColor = false;
      this.col = Color.white;
      this.itemCapacity = -1.0F;
      this.activated = false;
      this.haveBeenRepaired = 1;
      this.customName = false;
      this.customWeight = false;
      this.keyId = -1;
      this.taintedWater = false;
      this.remoteControlID = -1;
      this.remoteRange = 0;
      this.colorRed = this.colorGreen = this.colorBlue = 1.0F;
      this.worker = null;
      this.wetCooldown = -1.0F;
      this.favorite = false;
      this.stashMap = null;
      this.zombieInfected = false;
      this.currentAmmoCount = 0;
      this.attachedSlot = -1;
      this.attachedSlotType = null;
      this.attachedToModel = null;
      this.maxCapacity = -1;
      this.recordedMediaIndex = -1;
      this.worldZRotation = -1;
      this.worldScale = 1.0F;
      this.isInitialised = false;
      if (!var3.equals(0)) {
         if (var3.hasFlags(1)) {
            this.uses = var1.getShort();
         }

         if (var3.hasFlags(2)) {
            byte var4 = var1.get();
            float var5 = PZMath.clamp((var4 - -128) / 255.0F, 0.0F, 1.0F);
            ((DrainableComboItem)this).setUsedDelta(var5);
         }

         if (var3.hasFlags(4)) {
            this.setCondition(var1.get(), false);
         }

         if (var3.hasFlags(8)) {
            this.visual = new ItemVisual();
            this.visual.load(var1, var2);
         }

         if (var3.hasFlags(16)) {
            float var9 = Bits.unpackByteToFloatUnit(var1.get());
            float var11 = Bits.unpackByteToFloatUnit(var1.get());
            float var6 = Bits.unpackByteToFloatUnit(var1.get());
            float var7 = Bits.unpackByteToFloatUnit(var1.get());
            this.setColor(new Color(var9, var11, var6, var7));
         }

         if (var3.hasFlags(32)) {
            this.itemCapacity = var1.getFloat();
         }

         if (var3.hasFlags(64)) {
            BitHeaderRead var10 = BitHeader.allocRead(HeaderSize.Integer, var1);
            if (var10.hasFlags(1)) {
               if (this.table == null) {
                  this.table = LuaManager.platform.newTable();
               }

               this.table.load(var1, var2);
            }

            this.activated = var10.hasFlags(2);
            if (var10.hasFlags(4)) {
               this.setHaveBeenRepaired(var1.getShort());
            }

            if (var10.hasFlags(8)) {
               this.name = GameWindow.ReadString(var1);
            }

            if (var10.hasFlags(16)) {
               int var12 = var1.getInt();
               this.byteData = ByteBuffer.allocate(var12);

               for (int var17 = 0; var17 < var12; var17++) {
                  this.byteData.put(var1.get());
               }

               this.byteData.flip();
            }

            if (var10.hasFlags(32)) {
               int var13 = var1.getInt();
               if (var13 > 0) {
                  this.extraItems = new ArrayList<>();

                  for (int var18 = 0; var18 < var13; var18++) {
                     short var20 = var1.getShort();
                     String var8 = WorldDictionary.getItemTypeFromID(var20);
                     this.extraItems.add(var8);
                  }
               }
            }

            this.setCustomName(var10.hasFlags(64));
            if (var10.hasFlags(128)) {
               float var14 = var1.getFloat();
               if (var14 >= 0.0F) {
                  this.setActualWeight(var14);
                  this.setWeight(var14);
                  this.setCustomWeight(true);
               }
            }

            if (var10.hasFlags(256)) {
               this.setKeyId(var1.getInt());
            }

            this.setTaintedWater(var10.hasFlags(512));
            if (var10.hasFlags(1024)) {
               this.setRemoteControlID(var1.getInt());
               this.setRemoteRange(var1.getInt());
            }

            if (var10.hasFlags(2048)) {
               float var15 = Bits.unpackByteToFloatUnit(var1.get());
               float var19 = Bits.unpackByteToFloatUnit(var1.get());
               float var21 = Bits.unpackByteToFloatUnit(var1.get());
               this.setColorRed(var15);
               this.setColorGreen(var19);
               this.setColorBlue(var21);
               this.setColor(new Color(this.colorRed, this.colorGreen, this.colorBlue));
            }

            if (var10.hasFlags(4096)) {
               this.setWorker(GameWindow.ReadString(var1));
            }

            if (var10.hasFlags(8192)) {
               this.setWetCooldown(var1.getFloat());
            }

            this.setFavorite(var10.hasFlags(16384));
            if (var10.hasFlags(32768)) {
               this.stashMap = GameWindow.ReadString(var1);
            }

            this.setInfected(var10.hasFlags(65536));
            if (var10.hasFlags(131072)) {
               this.setCurrentAmmoCount(var1.getInt());
            }

            if (var10.hasFlags(262144)) {
               this.attachedSlot = var1.getInt();
            }

            if (var10.hasFlags(524288)) {
               if (var2 < 179) {
                  short var16 = var1.getShort();
                  this.attachedSlotType = null;
               } else {
                  this.attachedSlotType = GameWindow.ReadString(var1);
               }
            }

            if (var10.hasFlags(1048576)) {
               this.attachedToModel = GameWindow.ReadString(var1);
            }

            if (var10.hasFlags(2097152)) {
               this.maxCapacity = var1.getInt();
            }

            if (var10.hasFlags(4194304)) {
               this.setRecordedMediaIndex(var1.getShort());
            }

            if (var10.hasFlags(8388608)) {
               this.setWorldZRotation(var1.getInt());
            }

            if (var10.hasFlags(16777216)) {
               this.worldScale = var1.getFloat();
            }

            this.setInitialised(var10.hasFlags(33554432));
            var10.release();
         }
      }

      var3.release();
   }

   public boolean IsFood() {
      return false;
   }

   public boolean IsWeapon() {
      return false;
   }

   public boolean IsDrainable() {
      return false;
   }

   public boolean IsLiterature() {
      return false;
   }

   public boolean IsClothing() {
      return false;
   }

   public boolean IsInventoryContainer() {
      return false;
   }

   public boolean IsMap() {
      return false;
   }

   static InventoryItem LoadFromFile(DataInputStream var0) throws IOException {
      GameWindow.ReadString(var0);
      return null;
   }

   public ItemContainer getOutermostContainer() {
      if (this.container != null && !"floor".equals(this.container.type)) {
         ItemContainer var1 = this.container;

         while (
            var1.getContainingItem() != null
               && var1.getContainingItem().getContainer() != null
               && !"floor".equals(var1.getContainingItem().getContainer().type)
         ) {
            var1 = var1.getContainingItem().getContainer();
         }

         return var1;
      } else {
         return null;
      }
   }

   public boolean isInLocalPlayerInventory() {
      if (!GameClient.bClient) {
         return false;
      } else {
         ItemContainer var1 = this.getOutermostContainer();
         if (var1 == null) {
            return false;
         } else {
            return var1.getParent() instanceof IsoPlayer ? ((IsoPlayer)var1.getParent()).isLocalPlayer() : false;
         }
      }
   }

   public boolean isInPlayerInventory() {
      ItemContainer var1 = this.getOutermostContainer();
      return var1 == null ? false : var1.getParent() instanceof IsoPlayer;
   }

   public ItemReplacement getItemReplacementPrimaryHand() {
      return this.ScriptItem.replacePrimaryHand;
   }

   public ItemReplacement getItemReplacementSecondHand() {
      return this.ScriptItem.replaceSecondHand;
   }

   public ClothingItem getClothingItem() {
      if ("RightHand".equalsIgnoreCase(this.getAlternateModelName())) {
         return this.getItemReplacementPrimaryHand().clothingItem;
      } else {
         return "LeftHand".equalsIgnoreCase(this.getAlternateModelName())
            ? this.getItemReplacementSecondHand().clothingItem
            : this.ScriptItem.getClothingItemAsset();
      }
   }

   public String getAlternateModelName() {
      if (this.getContainer() != null && this.getContainer().getParent() instanceof IsoGameCharacter) {
         IsoGameCharacter var1 = (IsoGameCharacter)this.getContainer().getParent();
         if (var1.getPrimaryHandItem() == this && this.getItemReplacementPrimaryHand() != null) {
            return "RightHand";
         }

         if (var1.getSecondaryHandItem() == this && this.getItemReplacementSecondHand() != null) {
            return "LeftHand";
         }
      }

      return this.m_alternateModelName;
   }

   public ItemVisual getVisual() {
      ClothingItem var1 = this.getClothingItem();
      if (var1 != null && var1.isReady()) {
         if (this.visual == null) {
            this.visual = new ItemVisual();
            this.visual.setItemType(this.getFullType());
            this.visual.pickUninitializedValues(var1);
         }

         this.visual.setClothingItemName(var1.m_Name);
         this.visual.setAlternateModelName(this.getAlternateModelName());
         return this.visual;
      } else {
         this.visual = null;
         return null;
      }
   }

   public boolean allowRandomTint() {
      ClothingItem var1 = this.getClothingItem();
      return var1 != null ? var1.m_AllowRandomTint : false;
   }

   public void synchWithVisual() {
      if (this instanceof Clothing || this instanceof InventoryContainer) {
         ItemVisual var1 = this.getVisual();
         if (var1 != null) {
            if (this instanceof Clothing && this.getBloodClothingType() != null) {
               BloodClothingType.calcTotalBloodLevel((Clothing)this);
            }

            ClothingItem var2 = this.getClothingItem();
            if (var2.m_AllowRandomTint) {
               this.setColor(new Color(var1.m_Tint.r, var1.m_Tint.g, var1.m_Tint.b));
            } else {
               this.setColor(new Color(this.getColorRed(), this.getColorGreen(), this.getColorBlue()));
            }

            if ((var2.m_BaseTextures.size() > 1 || var1.m_TextureChoice > -1) && this.getIconsForTexture() != null) {
               String var3 = null;
               if (var1.m_BaseTexture > -1 && this.getIconsForTexture().size() > var1.m_BaseTexture) {
                  var3 = this.getIconsForTexture().get(var1.m_BaseTexture);
               } else if (var1.m_TextureChoice > -1 && this.getIconsForTexture().size() > var1.m_TextureChoice) {
                  var3 = this.getIconsForTexture().get(var1.m_TextureChoice);
               }

               if (!StringUtils.isNullOrWhitespace(var3)) {
                  this.texture = Texture.trygetTexture("Item_" + var3);
                  if (this.texture == null) {
                     this.texture = Texture.getSharedTexture("media/inventory/Question_On.png");
                  }
               }
            }
         }
      }
   }

   public int getContainerX() {
      return this.containerX;
   }

   public void setContainerX(int var1) {
      this.containerX = var1;
   }

   public int getContainerY() {
      return this.containerY;
   }

   public void setContainerY(int var1) {
      this.containerY = var1;
   }

   public boolean isDisappearOnUse() {
      return this.getScriptItem().isDisappearOnUse();
   }

   public String getName() {
      if (this.isBroken()) {
         return Translator.getText("IGUI_ItemNaming", this.brokenString, this.name);
      } else if (this.isTaintedWater() && SandboxOptions.instance.EnableTaintedWaterText.getValue()) {
         return Translator.getText("IGUI_ItemNameTaintedWater", this.name);
      } else if (this.getRemoteControlID() != -1) {
         return Translator.getText("IGUI_ItemNameControllerLinked", this.name);
      } else {
         return this.getMechanicType() > 0
            ? Translator.getText("IGUI_ItemNameMechanicalType", this.name, Translator.getText("IGUI_VehicleType_" + this.getMechanicType()))
            : this.name;
      }
   }

   public void setName(String var1) {
      if (var1.length() > 256) {
         var1 = var1.substring(0, Math.min(var1.length(), 256));
      }

      this.name = var1;
   }

   public String getReplaceOnUse() {
      return this.replaceOnUse;
   }

   public void setReplaceOnUse(String var1) {
      this.replaceOnUse = var1;
      this.replaceOnUseFullType = StringUtils.moduleDotType(this.getModule(), var1);
   }

   public String getReplaceOnUseFullType() {
      return this.replaceOnUseFullType;
   }

   public int getConditionMax() {
      return this.ConditionMax;
   }

   public void setConditionMax(int var1) {
      this.ConditionMax = var1;
   }

   public ItemContainer getRightClickContainer() {
      return this.rightClickContainer;
   }

   public void setRightClickContainer(ItemContainer var1) {
      this.rightClickContainer = var1;
   }

   public String getSwingAnim() {
      return this.getScriptItem().SwingAnim;
   }

   public Texture getTexture() {
      return this.texture;
   }

   public void setTexture(Texture var1) {
      this.texture = var1;
   }

   public Texture getTexturerotten() {
      return this.texturerotten;
   }

   public void setTexturerotten(Texture var1) {
      this.texturerotten = var1;
   }

   public Texture getTextureCooked() {
      return this.textureCooked;
   }

   public void setTextureCooked(Texture var1) {
      this.textureCooked = var1;
   }

   public Texture getTextureBurnt() {
      return this.textureBurnt;
   }

   public void setTextureBurnt(Texture var1) {
      this.textureBurnt = var1;
   }

   public void setType(String var1) {
      this.type = var1;
      this.fullType = this.module + "." + var1;
   }

   public int getCurrentUses() {
      return this.uses;
   }

   @Deprecated
   public int getUses() {
      return 1;
   }

   @Deprecated
   public void setUses(int var1) {
   }

   public float getAge() {
      return this.Age;
   }

   public void setAge(float var1) {
      this.Age = var1;
   }

   public float getLastAged() {
      return this.LastAged;
   }

   public void setLastAged(float var1) {
      this.LastAged = var1;
   }

   public void updateAge() {
   }

   public void setAutoAge() {
   }

   public boolean isIsCookable() {
      return this.IsCookable;
   }

   public boolean isCookable() {
      return this.IsCookable;
   }

   public void setIsCookable(boolean var1) {
      this.IsCookable = var1;
   }

   public float getCookingTime() {
      return this.CookingTime;
   }

   public void setCookingTime(float var1) {
      this.CookingTime = var1;
   }

   public float getMinutesToCook() {
      return this.MinutesToCook;
   }

   public void setMinutesToCook(float var1) {
      this.MinutesToCook = var1;
   }

   public float getMinutesToBurn() {
      return this.MinutesToBurn;
   }

   public void setMinutesToBurn(float var1) {
      this.MinutesToBurn = var1;
   }

   public boolean isCooked() {
      return this.Cooked;
   }

   public void setCooked(boolean var1) {
      this.Cooked = var1;
   }

   public boolean isBurnt() {
      return this.Burnt;
   }

   public void setBurnt(boolean var1) {
      this.Burnt = var1;
   }

   public int getOffAge() {
      return this.OffAge;
   }

   public void setOffAge(int var1) {
      this.OffAge = var1;
   }

   public int getOffAgeMax() {
      return this.OffAgeMax;
   }

   public void setOffAgeMax(int var1) {
      this.OffAgeMax = var1;
   }

   public float getWeight() {
      return this.Weight;
   }

   public void setWeight(float var1) {
      this.Weight = var1;
   }

   public float getActualWeight() {
      return this.getDisplayName().equals(this.getFullType()) ? 0.0F : this.ActualWeight;
   }

   public void setActualWeight(float var1) {
      this.ActualWeight = var1;
   }

   public String getWorldTexture() {
      return this.WorldTexture;
   }

   public void setWorldTexture(String var1) {
      this.WorldTexture = var1;
   }

   public String getDescription() {
      return this.Description;
   }

   public void setDescription(String var1) {
      this.Description = var1;
   }

   public int getCondition() {
      return this.Condition;
   }

   public void setCondition(int var1, boolean var2) {
      var1 = Math.max(0, var1);
      if (this.Condition > 0 && var1 <= 0 && var2 && this.getBreakSound() != null && !this.getBreakSound().isEmpty() && IsoPlayer.getInstance() != null) {
         IsoPlayer.getInstance().playSound(this.getBreakSound());
      }

      this.Condition = var1;
      this.setBroken(var1 <= 0);
   }

   public void setCondition(int var1) {
      this.setCondition(var1, true);
   }

   public String getOffString() {
      return this.OffString;
   }

   public void setOffString(String var1) {
      this.OffString = var1;
   }

   public String getCookedString() {
      return this.CookedString;
   }

   public void setCookedString(String var1) {
      this.CookedString = var1;
   }

   public String getUnCookedString() {
      return this.UnCookedString;
   }

   public void setUnCookedString(String var1) {
      this.UnCookedString = var1;
   }

   public String getBurntString() {
      return this.BurntString;
   }

   public void setBurntString(String var1) {
      this.BurntString = var1;
   }

   public String getModule() {
      return this.module;
   }

   public void setModule(String var1) {
      this.module = var1;
      this.fullType = var1 + "." + this.type;
   }

   public boolean isAlwaysWelcomeGift() {
      return this.getScriptItem().isAlwaysWelcomeGift();
   }

   public boolean isCanBandage() {
      return this.getScriptItem().isCanBandage();
   }

   public float getBoredomChange() {
      return this.boredomChange;
   }

   public void setBoredomChange(float var1) {
      this.boredomChange = var1;
   }

   public float getUnhappyChange() {
      return this.unhappyChange;
   }

   public void setUnhappyChange(float var1) {
      this.unhappyChange = var1;
   }

   public float getStressChange() {
      return this.stressChange;
   }

   public void setStressChange(float var1) {
      this.stressChange = var1;
   }

   public ArrayList<String> getTags() {
      return this.ScriptItem.getTags();
   }

   public boolean hasTag(String var1) {
      ArrayList var2 = this.getTags();

      for (int var3 = 0; var3 < var2.size(); var3++) {
         if (((String)var2.get(var3)).equalsIgnoreCase(var1)) {
            return true;
         }
      }

      return false;
   }

   public ArrayList<IsoObject> getTaken() {
      return this.Taken;
   }

   public void setTaken(ArrayList<IsoObject> var1) {
      this.Taken = var1;
   }

   public IsoDirections getPlaceDir() {
      return this.placeDir;
   }

   public void setPlaceDir(IsoDirections var1) {
      this.placeDir = var1;
   }

   public IsoDirections getNewPlaceDir() {
      return this.newPlaceDir;
   }

   public void setNewPlaceDir(IsoDirections var1) {
      this.newPlaceDir = var1;
   }

   public void setReplaceOnUseOn(String var1) {
      this.ReplaceOnUseOn = var1;
   }

   public String getReplaceOnUseOn() {
      return this.ReplaceOnUseOn;
   }

   public String getReplaceOnUseOnString() {
      String var1 = this.getReplaceOnUseOn();
      if (var1.split("-")[0].trim().contains("WaterSource")) {
         var1 = var1.split("-")[1];
         if (!var1.contains(".")) {
            var1 = this.getModule() + "." + var1;
         }
      }

      return var1;
   }

   public String getReplaceTypes() {
      return this.getScriptItem().getReplaceTypes();
   }

   public HashMap<String, String> getReplaceTypesMap() {
      return this.getScriptItem().getReplaceTypesMap();
   }

   public String getReplaceType(String var1) {
      return this.getScriptItem().getReplaceType(var1);
   }

   public boolean hasReplaceType(String var1) {
      return this.getScriptItem().hasReplaceType(var1);
   }

   public void setIsWaterSource(boolean var1) {
      this.IsWaterSource = var1;
   }

   public boolean isWaterSource() {
      return this.IsWaterSource;
   }

   boolean CanStackNoTemp(InventoryItem var1) {
      return false;
   }

   public void CopyModData(KahluaTable var1) {
      this.copyModData(var1);
   }

   public void copyModData(KahluaTable var1) {
      if (this.table != null) {
         this.table.wipe();
      }

      if (var1 != null) {
         LuaManager.copyTable(this.getModData(), var1);
      }
   }

   public int getCount() {
      return this.Count;
   }

   public void setCount(int var1) {
      this.Count = var1;
   }

   public boolean isActivated() {
      return this.activated;
   }

   public void setActivated(boolean var1) {
      this.activated = var1;
      if (this.canEmitLight() && GameClient.bClient && this.getEquipParent() != null) {
         if (this.getEquipParent().getPrimaryHandItem() == this) {
            this.getEquipParent().reportEvent("EventSetActivatedPrimary");
         } else if (this.getEquipParent().getSecondaryHandItem() == this) {
            this.getEquipParent().reportEvent("EventSetActivatedSecondary");
         }
      }
   }

   public void setActivatedRemote(boolean var1) {
      this.activated = var1;
   }

   public void setCanBeActivated(boolean var1) {
      this.canBeActivated = var1;
   }

   public boolean canBeActivated() {
      return this.canBeActivated;
   }

   public void setLightStrength(float var1) {
      this.lightStrength = var1;
   }

   public float getLightStrength() {
      return this.lightStrength;
   }

   public boolean isTorchCone() {
      return this.isTorchCone;
   }

   public void setTorchCone(boolean var1) {
      this.isTorchCone = var1;
   }

   public float getTorchDot() {
      return this.getScriptItem().torchDot;
   }

   public int getLightDistance() {
      return this.lightDistance;
   }

   public void setLightDistance(int var1) {
      this.lightDistance = var1;
   }

   public boolean canEmitLight() {
      if (this.getLightStrength() <= 0.0F) {
         return false;
      } else {
         Drainable var1 = (Drainable)Type.tryCastTo(this, Drainable.class);
         return var1 == null || !(var1.getUsedDelta() <= 0.0F);
      }
   }

   public boolean isEmittingLight() {
      return !this.canEmitLight() ? false : !this.canBeActivated() || this.isActivated();
   }

   public boolean canStoreWater() {
      return this.CanStoreWater;
   }

   public float getFatigueChange() {
      return this.fatigueChange;
   }

   public void setFatigueChange(float var1) {
      this.fatigueChange = var1;
   }

   public float getCurrentCondition() {
      Float var1 = (float)this.Condition / this.ConditionMax;
      return Float.valueOf(var1 * 100.0F);
   }

   public void setColor(Color var1) {
      this.col = var1;
   }

   public Color getColor() {
      return this.col;
   }

   public ColorInfo getColorInfo() {
      return new ColorInfo(this.col.getRedFloat(), this.col.getGreenFloat(), this.col.getBlueFloat(), this.col.getAlphaFloat());
   }

   public boolean isTwoHandWeapon() {
      return this.getScriptItem().TwoHandWeapon;
   }

   public String getCustomMenuOption() {
      return this.customMenuOption;
   }

   public void setCustomMenuOption(String var1) {
      this.customMenuOption = var1;
   }

   public void setTooltip(String var1) {
      this.tooltip = var1;
   }

   public String getTooltip() {
      return this.tooltip;
   }

   public String getDisplayCategory() {
      return this.displayCategory;
   }

   public void setDisplayCategory(String var1) {
      this.displayCategory = var1;
   }

   public int getHaveBeenRepaired() {
      return this.haveBeenRepaired;
   }

   public void setHaveBeenRepaired(int var1) {
      this.haveBeenRepaired = var1;
   }

   public boolean isBroken() {
      return this.broken;
   }

   public void setBroken(boolean var1) {
      this.broken = var1;
   }

   public String getDisplayName() {
      return this.name;
   }

   public boolean isTrap() {
      return this.getScriptItem().Trap;
   }

   public void addExtraItem(String var1) {
      if (this.extraItems == null) {
         this.extraItems = new ArrayList<>();
      }

      this.extraItems.add(var1);
   }

   public boolean haveExtraItems() {
      return this.extraItems != null;
   }

   public ArrayList<String> getExtraItems() {
      return this.extraItems;
   }

   public float getExtraItemsWeight() {
      if (!this.haveExtraItems()) {
         return 0.0F;
      } else {
         float var1 = 0.0F;

         for (int var2 = 0; var2 < this.extraItems.size(); var2++) {
            InventoryItem var3 = InventoryItemFactory.CreateItem(this.extraItems.get(var2));
            var1 += var3.getActualWeight();
         }

         return var1 * 0.6F;
      }
   }

   public boolean isCustomName() {
      return this.customName;
   }

   public void setCustomName(boolean var1) {
      this.customName = var1;
   }

   public boolean isFishingLure() {
      return this.getScriptItem().FishingLure;
   }

   public void copyConditionModData(InventoryItem var1) {
      if (var1.hasModData()) {
         KahluaTableIterator var2 = var1.getModData().iterator();

         while (var2.advance()) {
            if (var2.getKey() instanceof String && ((String)var2.getKey()).startsWith("condition:")) {
               this.getModData().rawset(var2.getKey(), var2.getValue());
            }
         }
      }
   }

   public void setConditionFromModData(InventoryItem var1) {
      if (var1.hasModData()) {
         Object var2 = var1.getModData().rawget("condition:" + this.getType());
         if (var2 != null && var2 instanceof Double) {
            this.setCondition((int)Math.round((Double)var2 * this.getConditionMax()));
         }
      }
   }

   public String getBreakSound() {
      return this.breakSound;
   }

   public void setBreakSound(String var1) {
      this.breakSound = var1;
   }

   public String getPlaceOneSound() {
      return this.getScriptItem().getPlaceOneSound();
   }

   public String getPlaceMultipleSound() {
      return this.getScriptItem().getPlaceMultipleSound();
   }

   public String getSoundByID(String var1) {
      return this.getScriptItem().getSoundByID(var1);
   }

   public void setBeingFilled(boolean var1) {
      this.beingFilled = var1;
   }

   public boolean isBeingFilled() {
      return this.beingFilled;
   }

   public String getFillFromDispenserSound() {
      return this.getScriptItem().getFillFromDispenserSound();
   }

   public String getFillFromTapSound() {
      return this.getScriptItem().getFillFromTapSound();
   }

   public boolean isAlcoholic() {
      return this.alcoholic;
   }

   public void setAlcoholic(boolean var1) {
      this.alcoholic = var1;
   }

   public float getAlcoholPower() {
      return this.alcoholPower;
   }

   public void setAlcoholPower(float var1) {
      this.alcoholPower = var1;
   }

   public float getBandagePower() {
      return this.bandagePower;
   }

   public void setBandagePower(float var1) {
      this.bandagePower = var1;
   }

   public float getReduceInfectionPower() {
      return this.ReduceInfectionPower;
   }

   public void setReduceInfectionPower(float var1) {
      this.ReduceInfectionPower = var1;
   }

   public final void saveWithSize(ByteBuffer var1, boolean var2) throws IOException {
      int var3 = var1.position();
      var1.putInt(0);
      int var4 = var1.position();
      this.save(var1, var2);
      int var5 = var1.position();
      var1.position(var3);
      var1.putInt(var5 - var4);
      var1.position(var5);
   }

   public boolean isCustomWeight() {
      return this.customWeight;
   }

   public void setCustomWeight(boolean var1) {
      this.customWeight = var1;
   }

   public float getContentsWeight() {
      if (!StringUtils.isNullOrEmpty(this.getAmmoType())) {
         Item var1 = ScriptManager.instance.FindItem(this.getAmmoType());
         if (var1 != null) {
            return var1.getActualWeight() * this.getCurrentAmmoCount();
         }
      }

      return 0.0F;
   }

   public float getHotbarEquippedWeight() {
      return (this.getActualWeight() + this.getContentsWeight()) * 0.7F;
   }

   public float getEquippedWeight() {
      return (this.getActualWeight() + this.getContentsWeight()) * 0.3F;
   }

   public float getUnequippedWeight() {
      return this.getActualWeight() + this.getContentsWeight();
   }

   public boolean isEquipped() {
      return this.getContainer() != null && this.getContainer().getParent() instanceof IsoGameCharacter
         ? ((IsoGameCharacter)this.getContainer().getParent()).isEquipped(this)
         : false;
   }

   public int getKeyId() {
      return this.keyId;
   }

   public void setKeyId(int var1) {
      this.keyId = var1;
   }

   public boolean isTaintedWater() {
      return this.taintedWater;
   }

   public void setTaintedWater(boolean var1) {
      this.taintedWater = var1;
   }

   public boolean isRemoteController() {
      return this.remoteController;
   }

   public void setRemoteController(boolean var1) {
      this.remoteController = var1;
   }

   public boolean canBeRemote() {
      return this.canBeRemote;
   }

   public void setCanBeRemote(boolean var1) {
      this.canBeRemote = var1;
   }

   public int getRemoteControlID() {
      return this.remoteControlID;
   }

   public void setRemoteControlID(int var1) {
      this.remoteControlID = var1;
   }

   public int getRemoteRange() {
      return this.remoteRange;
   }

   public void setRemoteRange(int var1) {
      this.remoteRange = var1;
   }

   public String getExplosionSound() {
      return this.explosionSound;
   }

   public void setExplosionSound(String var1) {
      this.explosionSound = var1;
   }

   public String getCountDownSound() {
      return this.countDownSound;
   }

   public void setCountDownSound(String var1) {
      this.countDownSound = var1;
   }

   public float getColorRed() {
      return this.colorRed;
   }

   public void setColorRed(float var1) {
      this.colorRed = var1;
   }

   public float getColorGreen() {
      return this.colorGreen;
   }

   public void setColorGreen(float var1) {
      this.colorGreen = var1;
   }

   public float getColorBlue() {
      return this.colorBlue;
   }

   public void setColorBlue(float var1) {
      this.colorBlue = var1;
   }

   public String getEvolvedRecipeName() {
      return this.evolvedRecipeName;
   }

   public void setEvolvedRecipeName(String var1) {
      this.evolvedRecipeName = var1;
   }

   public float getMetalValue() {
      return this.metalValue;
   }

   public void setMetalValue(float var1) {
      this.metalValue = var1;
   }

   public float getItemHeat() {
      return this.itemHeat;
   }

   public void setItemHeat(float var1) {
      if (var1 > 2.0F) {
         var1 = 2.0F;
      }

      if (var1 < 0.0F) {
         var1 = 0.0F;
      }

      this.itemHeat = var1;
   }

   public float getInvHeat() {
      return 1.0F - this.itemHeat;
   }

   public float getMeltingTime() {
      return this.meltingTime;
   }

   public void setMeltingTime(float var1) {
      if (var1 > 100.0F) {
         var1 = 100.0F;
      }

      if (var1 < 0.0F) {
         var1 = 0.0F;
      }

      this.meltingTime = var1;
   }

   public String getWorker() {
      return this.worker;
   }

   public void setWorker(String var1) {
      this.worker = var1;
   }

   public int getID() {
      return this.id;
   }

   public void setID(int var1) {
      this.id = var1;
   }

   public boolean isWet() {
      return this.isWet;
   }

   public void setWet(boolean var1) {
      this.isWet = var1;
   }

   public float getWetCooldown() {
      return this.wetCooldown;
   }

   public void setWetCooldown(float var1) {
      this.wetCooldown = var1;
   }

   public String getItemWhenDry() {
      return this.itemWhenDry;
   }

   public void setItemWhenDry(String var1) {
      this.itemWhenDry = var1;
   }

   public boolean isFavorite() {
      return this.favorite;
   }

   public void setFavorite(boolean var1) {
      this.favorite = var1;
   }

   public ArrayList<String> getRequireInHandOrInventory() {
      return this.requireInHandOrInventory;
   }

   public void setRequireInHandOrInventory(ArrayList<String> var1) {
      this.requireInHandOrInventory = var1;
   }

   public boolean isCustomColor() {
      return this.customColor;
   }

   public void setCustomColor(boolean var1) {
      this.customColor = var1;
   }

   public void doBuildingStash() {
      if (this.stashMap != null) {
         if (GameClient.bClient) {
            GameClient.sendBuildingStashToDo(this.stashMap);
         } else {
            StashSystem.prepareBuildingStash(this.stashMap);
         }
      }
   }

   public void setStashMap(String var1) {
      this.stashMap = var1;
   }

   public int getMechanicType() {
      return this.getScriptItem().vehicleType;
   }

   public float getItemCapacity() {
      return this.itemCapacity;
   }

   public void setItemCapacity(float var1) {
      this.itemCapacity = var1;
   }

   public int getMaxCapacity() {
      return this.maxCapacity;
   }

   public void setMaxCapacity(int var1) {
      this.maxCapacity = var1;
   }

   public boolean isConditionAffectsCapacity() {
      return this.ScriptItem != null && this.ScriptItem.isConditionAffectsCapacity();
   }

   public float getBrakeForce() {
      return this.brakeForce;
   }

   public void setBrakeForce(float var1) {
      this.brakeForce = var1;
   }

   public int getChanceToSpawnDamaged() {
      return this.chanceToSpawnDamaged;
   }

   public void setChanceToSpawnDamaged(int var1) {
      this.chanceToSpawnDamaged = var1;
   }

   public float getConditionLowerNormal() {
      return this.conditionLowerNormal;
   }

   public void setConditionLowerNormal(float var1) {
      this.conditionLowerNormal = var1;
   }

   public float getConditionLowerOffroad() {
      return this.conditionLowerOffroad;
   }

   public void setConditionLowerOffroad(float var1) {
      this.conditionLowerOffroad = var1;
   }

   public float getWheelFriction() {
      return this.wheelFriction;
   }

   public void setWheelFriction(float var1) {
      this.wheelFriction = var1;
   }

   public float getSuspensionDamping() {
      return this.suspensionDamping;
   }

   public void setSuspensionDamping(float var1) {
      this.suspensionDamping = var1;
   }

   public float getSuspensionCompression() {
      return this.suspensionCompression;
   }

   public void setSuspensionCompression(float var1) {
      this.suspensionCompression = var1;
   }

   public void setInfected(boolean var1) {
      this.zombieInfected = var1;
   }

   public boolean isInfected() {
      return this.zombieInfected;
   }

   public float getEngineLoudness() {
      return this.engineLoudness;
   }

   public void setEngineLoudness(float var1) {
      this.engineLoudness = var1;
   }

   public String getStaticModel() {
      return this.getScriptItem().getStaticModel();
   }

   public ArrayList<String> getIconsForTexture() {
      return this.iconsForTexture;
   }

   public void setIconsForTexture(ArrayList<String> var1) {
      this.iconsForTexture = var1;
   }

   public float getScore(SurvivorDesc var1) {
      return 0.0F;
   }

   public IsoGameCharacter getPreviousOwner() {
      return this.previousOwner;
   }

   public void setPreviousOwner(IsoGameCharacter var1) {
      this.previousOwner = var1;
   }

   public Item getScriptItem() {
      return this.ScriptItem;
   }

   public void setScriptItem(Item var1) {
      this.ScriptItem = var1;
   }

   public ItemType getCat() {
      return this.cat;
   }

   public void setCat(ItemType var1) {
      this.cat = var1;
   }

   public ItemContainer getContainer() {
      return this.container;
   }

   public void setContainer(ItemContainer var1) {
      this.container = var1;
   }

   public ArrayList<BloodClothingType> getBloodClothingType() {
      return this.bloodClothingType;
   }

   public void setBloodClothingType(ArrayList<BloodClothingType> var1) {
      this.bloodClothingType = var1;
   }

   public void setBlood(BloodBodyPartType var1, float var2) {
      ItemVisual var3 = this.getVisual();
      if (var3 != null) {
         var3.setBlood(var1, var2);
      }
   }

   public float getBlood(BloodBodyPartType var1) {
      ItemVisual var2 = this.getVisual();
      return var2 != null ? var2.getBlood(var1) : 0.0F;
   }

   public void setDirt(BloodBodyPartType var1, float var2) {
      ItemVisual var3 = this.getVisual();
      if (var3 != null) {
         var3.setDirt(var1, var2);
      }
   }

   public float getDirt(BloodBodyPartType var1) {
      ItemVisual var2 = this.getVisual();
      return var2 != null ? var2.getDirt(var1) : 0.0F;
   }

   public String getClothingItemName() {
      return this.getScriptItem().ClothingItem;
   }

   public int getStashChance() {
      return this.stashChance;
   }

   public void setStashChance(int var1) {
      this.stashChance = var1;
   }

   public String getEatType() {
      return this.getScriptItem().eatType;
   }

   public boolean isUseWorldItem() {
      return this.getScriptItem().UseWorldItem;
   }

   public boolean isHairDye() {
      return this.getScriptItem().hairDye;
   }

   public String getAmmoType() {
      return this.ammoType;
   }

   public void setAmmoType(String var1) {
      this.ammoType = var1;
   }

   public int getMaxAmmo() {
      return this.maxAmmo;
   }

   public void setMaxAmmo(int var1) {
      this.maxAmmo = var1;
   }

   public int getCurrentAmmoCount() {
      return this.currentAmmoCount;
   }

   public void setCurrentAmmoCount(int var1) {
      this.currentAmmoCount = var1;
   }

   public String getGunType() {
      return this.gunType;
   }

   public void setGunType(String var1) {
      this.gunType = var1;
   }

   public boolean hasBlood() {
      if (this instanceof Clothing) {
         if (this.getBloodClothingType() == null || this.getBloodClothingType().isEmpty()) {
            return false;
         }

         ArrayList var1 = BloodClothingType.getCoveredParts(this.getBloodClothingType());
         if (var1 == null) {
            return false;
         }

         for (int var2 = 0; var2 < var1.size(); var2++) {
            if (this.getBlood((BloodBodyPartType)var1.get(var2)) > 0.0F) {
               return true;
            }
         }
      } else {
         if (this instanceof HandWeapon) {
            return ((HandWeapon)this).getBloodLevel() > 0.0F;
         }

         if (this instanceof InventoryContainer) {
            return ((InventoryContainer)this).getBloodLevel() > 0.0F;
         }
      }

      return false;
   }

   public boolean hasDirt() {
      if (this instanceof Clothing) {
         if (this.getBloodClothingType() == null || this.getBloodClothingType().isEmpty()) {
            return false;
         }

         ArrayList var1 = BloodClothingType.getCoveredParts(this.getBloodClothingType());
         if (var1 == null) {
            return false;
         }

         for (int var2 = 0; var2 < var1.size(); var2++) {
            if (this.getDirt((BloodBodyPartType)var1.get(var2)) > 0.0F) {
               return true;
            }
         }
      }

      return false;
   }

   public String getAttachmentType() {
      return this.attachmentType;
   }

   public void setAttachmentType(String var1) {
      this.attachmentType = var1;
   }

   public int getAttachedSlot() {
      return this.attachedSlot;
   }

   public void setAttachedSlot(int var1) {
      this.attachedSlot = var1;
   }

   public ArrayList<String> getAttachmentsProvided() {
      return this.attachmentsProvided;
   }

   public void setAttachmentsProvided(ArrayList<String> var1) {
      this.attachmentsProvided = var1;
   }

   public String getAttachedSlotType() {
      return this.attachedSlotType;
   }

   public void setAttachedSlotType(String var1) {
      this.attachedSlotType = var1;
   }

   public String getAttachmentReplacement() {
      return this.attachmentReplacement;
   }

   public void setAttachmentReplacement(String var1) {
      this.attachmentReplacement = var1;
   }

   public String getAttachedToModel() {
      return this.attachedToModel;
   }

   public void setAttachedToModel(String var1) {
      this.attachedToModel = var1;
   }

   public String getFabricType() {
      return this.getScriptItem().fabricType;
   }

   public String getStringItemType() {
      Item var1 = ScriptManager.instance.FindItem(this.getFullType());
      if (var1 != null && var1.getType() != null) {
         if (var1.getType() == zombie.scripting.objects.Item.Type.Food) {
            return var1.CannedFood ? "CannedFood" : "Food";
         } else if ("Ammo".equals(var1.getDisplayCategory())) {
            return "Ammo";
         } else if (var1.getType() == zombie.scripting.objects.Item.Type.Weapon && !var1.isRanged()) {
            return "MeleeWeapon";
         } else if (var1.getType() != zombie.scripting.objects.Item.Type.WeaponPart
            && (var1.getType() != zombie.scripting.objects.Item.Type.Weapon || !var1.isRanged())
            && (var1.getType() != zombie.scripting.objects.Item.Type.Normal || StringUtils.isNullOrEmpty(var1.getAmmoType()))) {
            if (var1.getType() == zombie.scripting.objects.Item.Type.Literature) {
               return "Literature";
            } else if (var1.Medical) {
               return "Medical";
            } else if (var1.SurvivalGear) {
               return "SurvivalGear";
            } else {
               return var1.MechanicsItem ? "Mechanic" : "Other";
            }
         } else {
            return "RangedWeapon";
         }
      } else {
         return "Other";
      }
   }

   public boolean isProtectFromRainWhileEquipped() {
      return this.getScriptItem().ProtectFromRainWhenEquipped;
   }

   public boolean isEquippedNoSprint() {
      return this.getScriptItem().equippedNoSprint;
   }

   public String getBodyLocation() {
      return this.getScriptItem().BodyLocation;
   }

   public String getMakeUpType() {
      return this.getScriptItem().makeUpType;
   }

   public boolean isHidden() {
      return this.getScriptItem().isHidden();
   }

   public String getConsolidateOption() {
      return this.getScriptItem().consolidateOption;
   }

   public ArrayList<String> getClothingItemExtra() {
      return this.getScriptItem().clothingItemExtra;
   }

   public ArrayList<String> getClothingItemExtraOption() {
      return this.getScriptItem().clothingItemExtraOption;
   }

   public String getWorldStaticItem() {
      return this.getModData().rawget("Flatpack") == "true" ? "Flatpack" : this.getScriptItem().worldStaticModel;
   }

   public void setRegistry_id(Item var1) {
      if (var1.getFullName().equals(this.getFullType())) {
         this.registry_id = var1.getRegistry_id();
      } else if (Core.bDebug) {
         WorldDictionary.DebugPrintItem(var1);
         throw new RuntimeException("These types should always match");
      }
   }

   public short getRegistry_id() {
      return this.registry_id;
   }

   public String getModID() {
      return this.ScriptItem != null && this.ScriptItem.getModID() != null ? this.ScriptItem.getModID() : WorldDictionary.getItemModID(this.registry_id);
   }

   public String getModName() {
      return WorldDictionary.getModNameFromID(this.getModID());
   }

   public boolean isVanilla() {
      if (this.getModID() != null) {
         return this.getModID().equals("pz-vanilla");
      } else if (Core.bDebug) {
         WorldDictionary.DebugPrintItem(this);
         throw new RuntimeException("Item has no modID?");
      } else {
         return true;
      }
   }

   public short getRecordedMediaIndex() {
      return this.recordedMediaIndex;
   }

   public void setRecordedMediaIndex(short var1) {
      this.recordedMediaIndex = var1;
      if (this.recordedMediaIndex >= 0) {
         MediaData var2 = ZomboidRadio.getInstance().getRecordedMedia().getMediaDataFromIndex(this.recordedMediaIndex);
         this.mediaType = -1;
         if (var2 != null) {
            this.name = var2.getTranslatedItemDisplayName();
            this.mediaType = var2.getMediaType();
         } else {
            this.recordedMediaIndex = -1;
         }
      } else {
         this.mediaType = -1;
         this.name = this.getScriptItem().getDisplayName();
      }
   }

   public void setRecordedMediaIndexInteger(int var1) {
      this.setRecordedMediaIndex((short)var1);
   }

   public boolean isRecordedMedia() {
      return this.recordedMediaIndex >= 0;
   }

   public MediaData getMediaData() {
      return this.isRecordedMedia() ? ZomboidRadio.getInstance().getRecordedMedia().getMediaDataFromIndex(this.recordedMediaIndex) : null;
   }

   public byte getMediaType() {
      return this.mediaType;
   }

   public void setMediaType(byte var1) {
      this.mediaType = var1;
   }

   public void setRecordedMediaData(MediaData var1) {
      if (var1 != null && var1.getIndex() >= 0) {
         this.setRecordedMediaIndex(var1.getIndex());
      }
   }

   public void setWorldZRotation(int var1) {
      this.worldZRotation = var1;
   }

   public void setWorldScale(float var1) {
      this.worldScale = var1;
   }

   public String getLuaCreate() {
      return this.getScriptItem().getLuaCreate();
   }

   public boolean isInitialised() {
      return this.isInitialised;
   }

   public void setInitialised(boolean var1) {
      this.isInitialised = var1;
   }

   public void initialiseItem() {
      this.setInitialised(true);
      if (this.getLuaCreate() != null) {
         Object var1 = LuaManager.getFunctionObject(this.getLuaCreate());
         if (var1 != null) {
            LuaManager.caller.protectedCallVoid(LuaManager.thread, var1, this);
         }
      }
   }

   public String getSoundParameter(String var1) {
      return this.getScriptItem().getSoundParameter(var1);
   }
}
