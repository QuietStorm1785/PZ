package zombie.inventory.types;

import java.util.List;
import zombie.GameTime;
import zombie.Lua.LuaManager;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.core.math.PZMath;
import zombie.interfaces.IUpdater;
import zombie.inventory.InventoryItem;
import zombie.inventory.InventoryItemFactory;
import zombie.inventory.ItemContainer;
import zombie.inventory.ItemUser;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoWorld;
import zombie.iso.objects.RainManager;
import zombie.network.GameServer;
import zombie.scripting.ScriptManager;
import zombie.scripting.objects.Item;
import zombie.scripting.objects.Item.Type;
import zombie.util.StringUtils;

public final class DrainableComboItem extends InventoryItem implements Drainable, IUpdater {
   protected boolean bUseWhileEquiped = true;
   protected boolean bUseWhileUnequiped = false;
   protected int ticksPerEquipUse = 30;
   protected float useDelta = 0.03125F;
   protected float delta = 1.0F;
   protected float ticks = 0.0F;
   protected String ReplaceOnDeplete = null;
   protected String ReplaceOnDepleteFullType = null;
   public List<String> ReplaceOnCooked = null;
   private String OnCooked = null;
   private float rainFactor = 0.0F;
   private boolean canConsolidate = true;
   private float WeightEmpty = 0.0F;
   private static final float MIN_HEAT = 0.2F;
   private static final float MAX_HEAT = 3.0F;
   protected float Heat = 1.0F;
   protected int LastCookMinute = 0;

   public DrainableComboItem(String var1, String var2, String var3, String var4) {
      super(var1, var2, var3, var4);
   }

   public DrainableComboItem(String var1, String var2, String var3, Item var4) {
      super(var1, var2, var3, var4);
   }

   public boolean IsDrainable() {
      return true;
   }

   public int getSaveType() {
      return Type.Drainable.ordinal();
   }

   public boolean CanStack(InventoryItem var1) {
      return false;
   }

   public float getUsedDelta() {
      return this.delta;
   }

   public int getDrainableUsesInt() {
      return (int)Math.floor((this.getUsedDelta() + 1.0E-4) / this.getUseDelta());
   }

   public float getDrainableUsesFloat() {
      return this.getUsedDelta() / this.getUseDelta();
   }

   public void render() {
   }

   public void renderlast() {
   }

   public void setUsedDelta(float var1) {
      this.delta = PZMath.clamp(var1, 0.0F, 1.0F);
      this.updateWeight();
   }

   public boolean shouldUpdateInWorld() {
      if (!GameServer.bServer && this.Heat != 1.0F) {
         return true;
      } else if (this.canStoreWater() && this.isWaterSource() && this.getUsedDelta() < 1.0F) {
         IsoGridSquare var1 = this.getWorldItem().getSquare();
         return var1 != null && var1.isOutside();
      } else {
         return false;
      }
   }

   public void update() {
      ItemContainer var1 = this.getOutermostContainer();
      if (var1 != null) {
         float var2 = var1.getTemprature();
         if (this.Heat > var2) {
            this.Heat = this.Heat - 0.001F * GameTime.instance.getMultiplier();
            if (this.Heat < Math.max(0.2F, var2)) {
               this.Heat = Math.max(0.2F, var2);
            }
         }

         if (this.Heat < var2) {
            this.Heat = this.Heat + var2 / 1000.0F * GameTime.instance.getMultiplier();
            if (this.Heat > Math.min(3.0F, var2)) {
               this.Heat = Math.min(3.0F, var2);
            }
         }

         if (this.IsCookable) {
            if (this.Heat > 1.6F) {
               int var3 = GameTime.getInstance().getMinutes();
               if (var3 != this.LastCookMinute) {
                  this.LastCookMinute = var3;
                  float var4 = this.Heat / 1.5F;
                  if (var1.getTemprature() <= 1.6F) {
                     var4 *= 0.05F;
                  }

                  float var5 = this.CookingTime;
                  if (var5 < 1.0F) {
                     var5 = 10.0F;
                  }

                  var5 += var4;
                  if (this.isTaintedWater() && var5 > Math.min(this.MinutesToCook, 10.0F)) {
                     this.setTaintedWater(false);
                  }

                  if (!this.isCooked() && var5 > this.MinutesToCook) {
                     this.setCooked(true);
                     if (this.getReplaceOnCooked() != null) {
                        for (int var6 = 0; var6 < this.getReplaceOnCooked().size(); var6++) {
                           InventoryItem var7 = this.container.AddItem(this.getReplaceOnCooked().get(var6));
                           if (var7 != null) {
                              if (var7 instanceof DrainableComboItem) {
                                 ((DrainableComboItem)var7).setUsedDelta(this.getUsedDelta());
                              }

                              var7.copyConditionModData(this);
                           }
                        }

                        this.container.Remove(this);
                        IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
                        return;
                     }

                     if (this.getOnCooked() != null) {
                        LuaManager.caller.protectedCall(LuaManager.thread, LuaManager.env.rawget(this.getOnCooked()), new Object[]{this});
                        return;
                     }
                  }

                  if (this.CookingTime > this.MinutesToBurn) {
                     this.Burnt = true;
                     this.setCooked(false);
                  }
               }
            }
         } else if (var1 != null && var1.isMicrowave() && this.isTaintedWater() && this.Heat > 1.6F) {
            int var11 = GameTime.getInstance().getMinutes();
            if (var11 != this.LastCookMinute) {
               this.LastCookMinute = var11;
               float var13 = 1.0F;
               if (var1.getTemprature() <= 1.6F) {
                  var13 = (float)(var13 * 0.2);
               }

               this.CookingTime += var13;
               if (this.CookingTime > 10.0F) {
                  this.setTaintedWater(false);
               }
            }
         }
      }

      if (this.container == null && this.Heat != 1.0F) {
         float var8 = 1.0F;
         if (this.Heat > var8) {
            this.Heat = this.Heat - 0.001F * GameTime.instance.getMultiplier();
            if (this.Heat < var8) {
               this.Heat = var8;
            }
         }

         if (this.Heat < var8) {
            this.Heat = this.Heat + var8 / 1000.0F * GameTime.instance.getMultiplier();
            if (this.Heat > var8) {
               this.Heat = var8;
            }
         }
      }

      if (this.bUseWhileEquiped && this.delta > 0.0F) {
         IsoPlayer var9 = null;
         if (this.container != null && this.container.parent instanceof IsoPlayer) {
            for (int var12 = 0; var12 < IsoPlayer.numPlayers; var12++) {
               if (this.container.parent == IsoPlayer.players[var12]) {
                  var9 = IsoPlayer.players[var12];
               }
            }
         }

         if (var9 != null && (this.canBeActivated() && this.isActivated() || !this.canBeActivated()) && (var9.isHandItem(this) || var9.isAttachedItem(this))) {
            this.ticks = this.ticks + GameTime.instance.getMultiplier();

            while (this.ticks >= this.ticksPerEquipUse) {
               this.ticks = this.ticks - this.ticksPerEquipUse;
               if (this.delta > 0.0F) {
                  this.Use();
               }
            }
         }
      }

      if (this.bUseWhileUnequiped && this.delta > 0.0F && (this.canBeActivated() && this.isActivated() || !this.canBeActivated())) {
         this.ticks = this.ticks + GameTime.instance.getMultiplier();

         while (this.ticks >= this.ticksPerEquipUse) {
            this.ticks = this.ticks - this.ticksPerEquipUse;
            if (this.delta > 0.0F) {
               this.Use();
            }
         }
      }

      if (this.getWorldItem() != null && this.canStoreWater() && this.isWaterSource() && RainManager.isRaining() && this.getRainFactor() > 0.0F) {
         IsoGridSquare var10 = this.getWorldItem().getSquare();
         if (var10 != null && var10.isOutside()) {
            this.setUsedDelta(this.getUsedDelta() + 0.001F * RainManager.getRainIntensity() * GameTime.instance.getMultiplier() * this.getRainFactor());
            if (this.getUsedDelta() > 1.0F) {
               this.setUsedDelta(1.0F);
            }

            this.setTaintedWater(true);
            this.updateWeight();
         }
      }
   }

   public void Use() {
      if (this.getWorldItem() != null) {
         ItemUser.UseItem(this);
      } else {
         this.delta = this.delta - this.useDelta;
         if (this.uses > 1) {
            int var1 = this.uses - 1;
            this.uses = 1;
            InventoryItem var2 = InventoryItemFactory.CreateItem(this.getFullType());
            var2.setUses(var1);
            this.container.AddItem(var2);
         }

         if (this.delta <= 1.0E-4F) {
            this.delta = 0.0F;
            if (this.getReplaceOnDeplete() != null) {
               String var4 = this.getReplaceOnDepleteFullType();
               if (this.container != null) {
                  InventoryItem var5 = this.container.AddItem(var4);
                  if (this.container.parent instanceof IsoGameCharacter var3) {
                     if (var3.getPrimaryHandItem() == this) {
                        var3.setPrimaryHandItem(var5);
                     }

                     if (var3.getSecondaryHandItem() == this) {
                        var3.setSecondaryHandItem(var5);
                     }
                  }

                  var5.setCondition(this.getCondition());
                  var5.setFavorite(this.isFavorite());
                  this.container.Remove(this);
               }
            } else {
               super.Use();
            }
         }

         this.updateWeight();
      }
   }

   public void updateWeight() {
      if (this.getReplaceOnDeplete() != null) {
         if (this.getUsedDelta() >= 1.0F) {
            this.setCustomWeight(true);
            this.setActualWeight(this.getScriptItem().getActualWeight());
            this.setWeight(this.getActualWeight());
            return;
         }

         Item var1 = ScriptManager.instance.getItem(this.ReplaceOnDepleteFullType);
         if (var1 != null) {
            this.setCustomWeight(true);
            this.setActualWeight((this.getScriptItem().getActualWeight() - var1.getActualWeight()) * this.getUsedDelta() + var1.getActualWeight());
            this.setWeight(this.getActualWeight());
         }
      }

      if (this.getWeightEmpty() != 0.0F) {
         this.setCustomWeight(true);
         this.setActualWeight((this.getScriptItem().getActualWeight() - this.WeightEmpty) * this.getUsedDelta() + this.WeightEmpty);
      }
   }

   public float getWeightEmpty() {
      return this.WeightEmpty;
   }

   public void setWeightEmpty(float var1) {
      this.WeightEmpty = var1;
   }

   public boolean isUseWhileEquiped() {
      return this.bUseWhileEquiped;
   }

   public void setUseWhileEquiped(boolean var1) {
      this.bUseWhileEquiped = var1;
   }

   public boolean isUseWhileUnequiped() {
      return this.bUseWhileUnequiped;
   }

   public void setUseWhileUnequiped(boolean var1) {
      this.bUseWhileUnequiped = var1;
   }

   public int getTicksPerEquipUse() {
      return this.ticksPerEquipUse;
   }

   public void setTicksPerEquipUse(int var1) {
      this.ticksPerEquipUse = var1;
   }

   public float getUseDelta() {
      return this.useDelta;
   }

   public void setUseDelta(float var1) {
      this.useDelta = var1;
   }

   public float getDelta() {
      return this.delta;
   }

   public void setDelta(float var1) {
      this.delta = var1;
   }

   public float getTicks() {
      return this.ticks;
   }

   public void setTicks(float var1) {
      this.ticks = var1;
   }

   public void setReplaceOnDeplete(String var1) {
      this.ReplaceOnDeplete = var1;
      this.ReplaceOnDepleteFullType = this.getReplaceOnDepleteFullType();
   }

   public String getReplaceOnDeplete() {
      return this.ReplaceOnDeplete;
   }

   public String getReplaceOnDepleteFullType() {
      return StringUtils.moduleDotType(this.getModule(), this.ReplaceOnDeplete);
   }

   public void setHeat(float var1) {
      this.Heat = PZMath.clamp(var1, 0.0F, 3.0F);
   }

   public float getHeat() {
      return this.Heat;
   }

   public float getInvHeat() {
      return (1.0F - this.Heat) / 3.0F;
   }

   public boolean finishupdate() {
      if (this.canStoreWater() && this.isWaterSource() && this.getWorldItem() != null && this.getWorldItem().getSquare() != null) {
         return this.getUsedDelta() >= 1.0F;
      } else if (this.isTaintedWater()) {
         return false;
      } else {
         if (this.container != null) {
            if (this.Heat != this.container.getTemprature() || this.container.isTemperatureChanging()) {
               return false;
            }

            if (this.container.type.equals("campfire") || this.container.type.equals("barbecue")) {
               return false;
            }
         }

         return true;
      }
   }

   public int getRemainingUses() {
      return Math.round(this.getUsedDelta() / this.getUseDelta());
   }

   public float getRainFactor() {
      return this.rainFactor;
   }

   public void setRainFactor(float var1) {
      this.rainFactor = var1;
   }

   public boolean canConsolidate() {
      return this.canConsolidate;
   }

   public void setCanConsolidate(boolean var1) {
      this.canConsolidate = var1;
   }

   public List<String> getReplaceOnCooked() {
      return this.ReplaceOnCooked;
   }

   public void setReplaceOnCooked(List<String> var1) {
      this.ReplaceOnCooked = var1;
   }

   public String getOnCooked() {
      return this.OnCooked;
   }

   public void setOnCooked(String var1) {
      this.OnCooked = var1;
   }
}
