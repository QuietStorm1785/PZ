package zombie.radio.devices;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Map;
import java.util.Map.Entry;
import zombie.GameTime;
import zombie.GameWindow;
import zombie.WorldSoundManager;
import zombie.audio.BaseSoundEmitter;
import zombie.characters.IsoPlayer;
import zombie.core.Color;
import zombie.core.Rand;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.core.raknet.VoiceManager;
import zombie.inventory.InventoryItem;
import zombie.inventory.InventoryItemFactory;
import zombie.inventory.ItemContainer;
import zombie.inventory.ItemUser;
import zombie.inventory.types.DrainableComboItem;
import zombie.inventory.types.Radio;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;
import zombie.iso.IsoWorld;
import zombie.iso.objects.IsoGenerator;
import zombie.iso.objects.IsoWaveSignal;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.network.PacketTypes.PacketType;
import zombie.radio.ZomboidRadio;
import zombie.radio.media.MediaData;
import zombie.radio.media.MediaData.MediaLineData;
import zombie.vehicles.VehiclePart;

public final class DeviceData implements Cloneable {
   private static final float deviceSpeakerSoundMod = 0.4F;
   private static final float deviceButtonSoundVol = 0.05F;
   protected String deviceName = "WaveSignalDevice";
   protected boolean twoWay = false;
   protected int transmitRange = 1000;
   protected int micRange = 5;
   protected boolean micIsMuted = false;
   protected float baseVolumeRange = 15.0F;
   protected float deviceVolume = 1.0F;
   protected boolean isPortable = false;
   protected boolean isTelevision = false;
   protected boolean isHighTier = false;
   protected boolean isTurnedOn = false;
   protected int channel = 88000;
   protected int minChannelRange = 200;
   protected int maxChannelRange = 1000000;
   protected DevicePresets presets = null;
   protected boolean isBatteryPowered = true;
   protected boolean hasBattery = true;
   protected float powerDelta = 1.0F;
   protected float useDelta = 0.001F;
   protected int lastRecordedDistance = -1;
   protected int headphoneType = -1;
   protected WaveSignalDevice parent = null;
   protected GameTime gameTime = null;
   protected boolean channelChangedRecently = false;
   protected BaseSoundEmitter emitter = null;
   protected ArrayList<Long> soundIDs = new ArrayList<>();
   protected short mediaIndex = -1;
   protected byte mediaType = -1;
   protected String mediaItem = null;
   protected MediaData playingMedia = null;
   protected boolean isPlayingMedia = false;
   protected int mediaLineIndex = 0;
   protected float lineCounter = 0.0F;
   protected String currentMediaLine = null;
   protected Color currentMediaColor = null;
   protected boolean isStoppingMedia = false;
   protected float stopMediaCounter = 0.0F;
   protected boolean noTransmit = false;
   private float soundCounterStatic = 0.0F;
   protected long radioLoopSound = 0L;
   protected boolean doTriggerWorldSound = false;
   protected long lastMinuteStamp = -1L;
   protected int listenCnt = 0;
   float nextStaticSound = 0.0F;
   protected float voipCounter = 0.0F;
   protected float signalCounter = 0.0F;
   protected float soundCounter = 0.0F;
   float minmod = 1.5F;
   float maxmod = 5.0F;

   public DeviceData() {
      this(null);
   }

   public DeviceData(WaveSignalDevice var1) {
      this.parent = var1;
      this.presets = new DevicePresets();
      this.gameTime = GameTime.getInstance();
   }

   public void generatePresets() {
      if (this.presets == null) {
         this.presets = new DevicePresets();
      }

      this.presets.clearPresets();
      if (this.isTelevision) {
         Map var1 = ZomboidRadio.getInstance().GetChannelList("Television");
         if (var1 != null) {
            for (Entry var3 : var1.entrySet()) {
               if ((Integer)var3.getKey() >= this.minChannelRange && (Integer)var3.getKey() <= this.maxChannelRange) {
                  this.presets.addPreset((String)var3.getValue(), (Integer)var3.getKey());
               }
            }
         }
      } else {
         int var9 = this.twoWay ? 100 : 300;
         if (this.isHighTier) {
            var9 = 800;
         }

         Map var5 = ZomboidRadio.getInstance().GetChannelList("Emergency");
         if (var5 != null) {
            for (Entry var4 : var5.entrySet()) {
               if ((Integer)var4.getKey() >= this.minChannelRange && (Integer)var4.getKey() <= this.maxChannelRange && Rand.Next(1000) < var9) {
                  this.presets.addPreset((String)var4.getValue(), (Integer)var4.getKey());
               }
            }
         }

         var9 = this.twoWay ? 100 : 800;
         var5 = ZomboidRadio.getInstance().GetChannelList("Radio");
         if (var5 != null) {
            for (Entry var15 : var5.entrySet()) {
               if ((Integer)var15.getKey() >= this.minChannelRange && (Integer)var15.getKey() <= this.maxChannelRange && Rand.Next(1000) < var9) {
                  this.presets.addPreset((String)var15.getValue(), (Integer)var15.getKey());
               }
            }
         }

         if (this.twoWay) {
            var5 = ZomboidRadio.getInstance().GetChannelList("Amateur");
            if (var5 != null) {
               for (Entry var16 : var5.entrySet()) {
                  if ((Integer)var16.getKey() >= this.minChannelRange && (Integer)var16.getKey() <= this.maxChannelRange && Rand.Next(1000) < var9) {
                     this.presets.addPreset((String)var16.getValue(), (Integer)var16.getKey());
                  }
               }
            }
         }

         if (this.isHighTier) {
            var5 = ZomboidRadio.getInstance().GetChannelList("Military");
            if (var5 != null) {
               for (Entry var17 : var5.entrySet()) {
                  if ((Integer)var17.getKey() >= this.minChannelRange && (Integer)var17.getKey() <= this.maxChannelRange && Rand.Next(1000) < 10) {
                     this.presets.addPreset((String)var17.getValue(), (Integer)var17.getKey());
                  }
               }
            }
         }
      }
   }

   @Override
   protected Object clone() throws CloneNotSupportedException {
      DeviceData var1 = (DeviceData)super.clone();
      var1.setDevicePresets((DevicePresets)this.presets.clone());
      var1.setParent(null);
      return var1;
   }

   public DeviceData getClone() {
      DeviceData var1;
      try {
         var1 = (DeviceData)this.clone();
      } catch (Exception var3) {
         System.out.println(var3.getMessage());
         var1 = new DeviceData();
      }

      return var1;
   }

   public WaveSignalDevice getParent() {
      return this.parent;
   }

   public void setParent(WaveSignalDevice var1) {
      this.parent = var1;
   }

   public DevicePresets getDevicePresets() {
      return this.presets;
   }

   public void setDevicePresets(DevicePresets var1) {
      if (var1 == null) {
         var1 = new DevicePresets();
      }

      this.presets = var1;
   }

   public void cloneDevicePresets(DevicePresets var1) throws CloneNotSupportedException {
      this.presets.clearPresets();
      if (var1 != null) {
         for (int var2 = 0; var2 < var1.presets.size(); var2++) {
            PresetEntry var3 = (PresetEntry)var1.presets.get(var2);
            this.presets.addPreset(var3.name, var3.frequency);
         }
      }
   }

   public int getMinChannelRange() {
      return this.minChannelRange;
   }

   public void setMinChannelRange(int var1) {
      this.minChannelRange = var1 >= 200 && var1 <= 1000000 ? var1 : 200;
   }

   public int getMaxChannelRange() {
      return this.maxChannelRange;
   }

   public void setMaxChannelRange(int var1) {
      this.maxChannelRange = var1 >= 200 && var1 <= 1000000 ? var1 : 1000000;
   }

   public boolean getIsHighTier() {
      return this.isHighTier;
   }

   public void setIsHighTier(boolean var1) {
      this.isHighTier = var1;
   }

   public boolean getIsBatteryPowered() {
      return this.isBatteryPowered;
   }

   public void setIsBatteryPowered(boolean var1) {
      this.isBatteryPowered = var1;
   }

   public boolean getHasBattery() {
      return this.hasBattery;
   }

   public void setHasBattery(boolean var1) {
      this.hasBattery = var1;
   }

   public void addBattery(DrainableComboItem var1) {
      if (!this.hasBattery && var1 != null && var1.getFullType().equals("Base.Battery")) {
         ItemContainer var2 = var1.getContainer();
         if (var2 != null) {
            if (var2.getType().equals("floor") && var1.getWorldItem() != null && var1.getWorldItem().getSquare() != null) {
               var1.getWorldItem().getSquare().transmitRemoveItemFromSquare(var1.getWorldItem());
               var1.getWorldItem().getSquare().getWorldObjects().remove(var1.getWorldItem());
               var1.getWorldItem().getSquare().chunk.recalcHashCodeObjects();
               var1.getWorldItem().getSquare().getObjects().remove(var1.getWorldItem());
               var1.setWorldItem(null);
            }

            this.powerDelta = var1.getDelta();
            var2.DoRemoveItem(var1);
            this.hasBattery = true;
            this.transmitDeviceDataState((short)2);
         }
      }
   }

   public InventoryItem getBattery(ItemContainer var1) {
      if (this.hasBattery) {
         DrainableComboItem var2 = (DrainableComboItem)InventoryItemFactory.CreateItem("Base.Battery");
         var2.setDelta(this.powerDelta);
         this.powerDelta = 0.0F;
         var1.AddItem(var2);
         this.hasBattery = false;
         this.transmitDeviceDataState((short)2);
         return var2;
      } else {
         return null;
      }
   }

   public void transmitBattryChange() {
      this.transmitDeviceDataState((short)2);
   }

   public void addHeadphones(InventoryItem var1) {
      if (this.headphoneType < 0 && (var1.getFullType().equals("Base.Headphones") || var1.getFullType().equals("Base.Earbuds"))) {
         ItemContainer var2 = var1.getContainer();
         if (var2 != null) {
            if (var2.getType().equals("floor") && var1.getWorldItem() != null && var1.getWorldItem().getSquare() != null) {
               var1.getWorldItem().getSquare().transmitRemoveItemFromSquare(var1.getWorldItem());
               var1.getWorldItem().getSquare().getWorldObjects().remove(var1.getWorldItem());
               var1.getWorldItem().getSquare().chunk.recalcHashCodeObjects();
               var1.getWorldItem().getSquare().getObjects().remove(var1.getWorldItem());
               var1.setWorldItem(null);
            }

            int var3 = var1.getFullType().equals("Base.Headphones") ? 0 : 1;
            var2.DoRemoveItem(var1);
            this.setHeadphoneType(var3);
            this.transmitDeviceDataState((short)6);
         }
      }
   }

   public InventoryItem getHeadphones(ItemContainer var1) {
      if (this.headphoneType >= 0) {
         InventoryItem var2 = null;
         if (this.headphoneType == 0) {
            var2 = InventoryItemFactory.CreateItem("Base.Headphones");
         } else if (this.headphoneType == 1) {
            var2 = InventoryItemFactory.CreateItem("Base.Earbuds");
         }

         if (var2 != null) {
            var1.AddItem(var2);
         }

         this.setHeadphoneType(-1);
         this.transmitDeviceDataState((short)6);
      }

      return null;
   }

   public int getMicRange() {
      return this.micRange;
   }

   public void setMicRange(int var1) {
      this.micRange = var1;
   }

   public boolean getMicIsMuted() {
      return this.micIsMuted;
   }

   public void setMicIsMuted(boolean var1) {
      this.micIsMuted = var1;
      if (this.getParent() != null
         && this.getParent() instanceof Radio
         && ((Radio)this.getParent()).getEquipParent() != null
         && ((Radio)this.getParent()).getEquipParent() instanceof IsoPlayer) {
         IsoPlayer var2 = (IsoPlayer)((Radio)this.getParent()).getEquipParent();
         var2.updateEquippedRadioFreq();
      }
   }

   public int getHeadphoneType() {
      return this.headphoneType;
   }

   public void setHeadphoneType(int var1) {
      this.headphoneType = var1;
   }

   public float getBaseVolumeRange() {
      return this.baseVolumeRange;
   }

   public void setBaseVolumeRange(float var1) {
      this.baseVolumeRange = var1;
   }

   public float getDeviceVolume() {
      return this.deviceVolume;
   }

   public void setDeviceVolume(float var1) {
      this.deviceVolume = var1 < 0.0F ? 0.0F : (var1 > 1.0F ? 1.0F : var1);
      this.transmitDeviceDataState((short)4);
   }

   public void setDeviceVolumeRaw(float var1) {
      this.deviceVolume = var1 < 0.0F ? 0.0F : (var1 > 1.0F ? 1.0F : var1);
   }

   public boolean getIsTelevision() {
      return this.isTelevision;
   }

   public void setIsTelevision(boolean var1) {
      this.isTelevision = var1;
   }

   public String getDeviceName() {
      return this.deviceName;
   }

   public void setDeviceName(String var1) {
      this.deviceName = var1;
   }

   public boolean getIsTwoWay() {
      return this.twoWay;
   }

   public void setIsTwoWay(boolean var1) {
      this.twoWay = var1;
   }

   public int getTransmitRange() {
      return this.transmitRange;
   }

   public void setTransmitRange(int var1) {
      this.transmitRange = var1 > 0 ? var1 : 0;
   }

   public boolean getIsPortable() {
      return this.isPortable;
   }

   public void setIsPortable(boolean var1) {
      this.isPortable = var1;
   }

   public boolean getIsTurnedOn() {
      return this.isTurnedOn;
   }

   public void setIsTurnedOn(boolean var1) {
      if (this.canBePoweredHere()) {
         if (this.isBatteryPowered && !(this.powerDelta > 0.0F)) {
            this.isTurnedOn = false;
         } else {
            this.isTurnedOn = var1;
         }

         this.playSoundSend("RadioButton", false);
         this.transmitDeviceDataState((short)0);
      } else if (this.isTurnedOn) {
         this.isTurnedOn = false;
         this.playSoundSend("RadioButton", false);
         this.transmitDeviceDataState((short)0);
      }

      if (this.getParent() != null
         && this.getParent() instanceof Radio
         && ((Radio)this.getParent()).getEquipParent() != null
         && ((Radio)this.getParent()).getEquipParent() instanceof IsoPlayer) {
         IsoPlayer var2 = (IsoPlayer)((Radio)this.getParent()).getEquipParent();
         var2.updateEquippedRadioFreq();
      }

      IsoGenerator.updateGenerator(this.getParent().getSquare());
   }

   public void setTurnedOnRaw(boolean var1) {
      this.isTurnedOn = var1;
      if (this.getParent() != null
         && this.getParent() instanceof Radio
         && ((Radio)this.getParent()).getEquipParent() != null
         && ((Radio)this.getParent()).getEquipParent() instanceof IsoPlayer) {
         IsoPlayer var2 = (IsoPlayer)((Radio)this.getParent()).getEquipParent();
         var2.updateEquippedRadioFreq();
      }
   }

   public boolean canBePoweredHere() {
      if (this.isBatteryPowered) {
         return true;
      } else if (this.parent instanceof VehiclePart var2) {
         return var2.isInventoryItemUninstalled() ? false : var2.hasDevicePower();
      } else {
         boolean var1 = false;
         if (IsoWorld.instance.isHydroPowerOn()) {
            var1 = true;
         }

         if (this.parent == null || this.parent.getSquare() == null) {
            var1 = false;
         } else if (this.parent.getSquare().haveElectricity()) {
            var1 = true;
         } else if (this.parent.getSquare().getRoom() == null) {
            var1 = false;
         }

         return var1;
      }
   }

   public void setRandomChannel() {
      if (this.presets != null && this.presets.getPresets().size() > 0) {
         int var1 = Rand.Next(0, this.presets.getPresets().size());
         this.channel = ((PresetEntry)this.presets.getPresets().get(var1)).getFrequency();
      } else {
         this.channel = Rand.Next(this.minChannelRange, this.maxChannelRange);
         this.channel = this.channel - this.channel % 200;
      }
   }

   public int getChannel() {
      return this.channel;
   }

   public void setChannel(int var1) {
      this.setChannel(var1, true);
   }

   public void setChannel(int var1, boolean var2) {
      if (var1 >= this.minChannelRange && var1 <= this.maxChannelRange) {
         this.channel = var1;
         this.playSoundSend("RadioButton", false);
         if (this.isTelevision) {
            this.playSoundSend("TelevisionZap", true);
         } else {
            this.playSoundSend("RadioZap", true);
         }

         if (this.radioLoopSound > 0L) {
            this.emitter.stopSound(this.radioLoopSound);
            this.radioLoopSound = 0L;
         }

         this.transmitDeviceDataState((short)1);
         if (var2) {
            this.TriggerPlayerListening(true);
         }
      }
   }

   public void setChannelRaw(int var1) {
      this.channel = var1;
   }

   public float getUseDelta() {
      return this.useDelta;
   }

   public void setUseDelta(float var1) {
      this.useDelta = var1 / 60.0F;
   }

   public float getPower() {
      return this.powerDelta;
   }

   public void setPower(float var1) {
      if (var1 > 1.0F) {
         var1 = 1.0F;
      }

      if (var1 < 0.0F) {
         var1 = 0.0F;
      }

      this.powerDelta = var1;
   }

   public void setInitialPower() {
      this.lastMinuteStamp = this.gameTime.getMinutesStamp();
      this.setPower(this.powerDelta - this.useDelta * (float)this.lastMinuteStamp);
   }

   public void TriggerPlayerListening(boolean var1) {
      if (this.isTurnedOn) {
         ZomboidRadio.getInstance().PlayerListensChannel(this.channel, true, this.isTelevision);
      }
   }

   public void playSoundSend(String var1, boolean var2) {
      this.playSound(var1, var2 ? this.deviceVolume * 0.4F : 0.05F, true);
   }

   public void playSoundLocal(String var1, boolean var2) {
      this.playSound(var1, var2 ? this.deviceVolume * 0.4F : 0.05F, false);
   }

   public void playSound(String var1, float var2, boolean var3) {
      if (!GameServer.bServer) {
         this.setEmitterAndPos();
         if (this.emitter != null) {
            long var4 = var3 ? this.emitter.playSound(var1) : this.emitter.playSoundImpl(var1, (IsoObject)null);
            this.emitter.setVolume(var4, var2);
         }
      }
   }

   public void cleanSoundsAndEmitter() {
      if (this.emitter != null) {
         this.emitter.stopAll();
         IsoWorld.instance.returnOwnershipOfEmitter(this.emitter);
         this.emitter = null;
         this.radioLoopSound = 0L;
      }
   }

   protected void setEmitterAndPos() {
      Object var1 = null;
      if (this.parent != null && this.parent instanceof IsoObject) {
         var1 = (IsoObject)this.parent;
      } else if (this.parent != null && this.parent instanceof Radio) {
         var1 = IsoPlayer.getInstance();
      }

      if (var1 != null) {
         if (this.emitter == null) {
            this.emitter = IsoWorld.instance.getFreeEmitter(var1.getX() + 0.5F, var1.getY() + 0.5F, (int)var1.getZ());
            IsoWorld.instance.takeOwnershipOfEmitter(this.emitter);
         } else {
            this.emitter.setPos(var1.getX() + 0.5F, var1.getY() + 0.5F, (int)var1.getZ());
         }

         if (this.radioLoopSound != 0L) {
            this.emitter.setVolume(this.radioLoopSound, this.deviceVolume * 0.4F);
         }
      }
   }

   protected void updateEmitter() {
      if (!GameServer.bServer) {
         if (!this.isTurnedOn) {
            if (this.emitter != null && this.emitter.isPlaying("RadioButton")) {
               if (this.radioLoopSound > 0L) {
                  this.emitter.stopSound(this.radioLoopSound);
               }

               this.setEmitterAndPos();
               this.emitter.tick();
            } else {
               this.cleanSoundsAndEmitter();
            }
         } else {
            this.setEmitterAndPos();
            if (this.emitter != null) {
               if (this.signalCounter > 0.0F && !this.emitter.isPlaying("RadioTalk")) {
                  if (this.radioLoopSound > 0L) {
                     this.emitter.stopSound(this.radioLoopSound);
                  }

                  this.radioLoopSound = this.emitter.playSoundImpl("RadioTalk", (IsoObject)null);
                  this.emitter.setVolume(this.radioLoopSound, this.deviceVolume * 0.4F);
               }

               String var1 = !this.isTelevision ? "RadioStatic" : "TelevisionTestBeep";
               if (this.radioLoopSound == 0L || this.signalCounter <= 0.0F && !this.emitter.isPlaying(var1)) {
                  if (this.radioLoopSound > 0L) {
                     this.emitter.stopSound(this.radioLoopSound);
                     if (this.isTelevision) {
                        this.playSoundLocal("TelevisionZap", true);
                     } else {
                        this.playSoundLocal("RadioZap", true);
                     }
                  }

                  this.radioLoopSound = this.emitter.playSoundImpl(var1, (IsoObject)null);
                  this.emitter.setVolume(this.radioLoopSound, this.deviceVolume * 0.4F);
               }

               this.emitter.tick();
            }
         }
      }
   }

   public BaseSoundEmitter getEmitter() {
      return this.emitter;
   }

   public void update(boolean var1, boolean var2) {
      if (this.lastMinuteStamp == -1L) {
         this.lastMinuteStamp = this.gameTime.getMinutesStamp();
      }

      if (this.gameTime.getMinutesStamp() > this.lastMinuteStamp) {
         long var3 = this.gameTime.getMinutesStamp() - this.lastMinuteStamp;
         this.lastMinuteStamp = this.gameTime.getMinutesStamp();
         this.listenCnt = (int)(this.listenCnt + var3);
         if (this.listenCnt >= 10) {
            this.listenCnt = 0;
         }

         if (!GameServer.bServer && this.isTurnedOn && var2 && (this.listenCnt == 0 || this.listenCnt == 5)) {
            this.TriggerPlayerListening(true);
         }

         if (this.isTurnedOn && this.isBatteryPowered && this.powerDelta > 0.0F) {
            float var5 = this.powerDelta - this.powerDelta % 0.01F;
            this.setPower(this.powerDelta - this.useDelta * (float)var3);
            if (this.listenCnt == 0 || this.powerDelta == 0.0F || this.powerDelta < var5) {
               if (var1 && GameServer.bServer) {
                  this.transmitDeviceDataStateServer((short)3, null);
               } else if (!var1 && GameClient.bClient) {
                  this.transmitDeviceDataState((short)3);
               }
            }
         }
      }

      if (this.isTurnedOn && (this.isBatteryPowered && this.powerDelta <= 0.0F || !this.canBePoweredHere())) {
         this.isTurnedOn = false;
         if (var1 && GameServer.bServer) {
            this.transmitDeviceDataStateServer((short)0, null);
         } else if (!var1 && GameClient.bClient) {
            this.transmitDeviceDataState((short)0);
         }
      }

      this.updateMediaPlaying();
      this.updateEmitter();
      this.updateSimple();
   }

   public void updateSimple() {
      if (this.voipCounter >= 0.0F) {
         this.voipCounter = this.voipCounter - 1.25F * GameTime.getInstance().getMultiplier();
      }

      if (this.signalCounter >= 0.0F) {
         this.signalCounter = this.signalCounter - 1.25F * GameTime.getInstance().getMultiplier();
      }

      if (this.soundCounter >= 0.0F) {
         this.soundCounter = (float)(this.soundCounter - 1.25 * GameTime.getInstance().getMultiplier());
      }

      if (this.signalCounter <= 0.0F && this.voipCounter <= 0.0F && this.lastRecordedDistance >= 0) {
         this.lastRecordedDistance = -1;
      }

      this.updateStaticSounds();
      if (GameClient.bClient) {
         this.updateEmitter();
      }

      if (this.doTriggerWorldSound && this.soundCounter <= 0.0F) {
         if (this.isTurnedOn
            && this.deviceVolume > 0.0F
            && (!this.isInventoryDevice() || this.headphoneType < 0)
            && (!GameClient.bClient && !GameServer.bServer || GameClient.bClient && this.isInventoryDevice() || GameServer.bServer && !this.isInventoryDevice())
            )
          {
            Object var1 = null;
            if (this.parent != null && this.parent instanceof IsoObject) {
               var1 = (IsoObject)this.parent;
            } else if (this.parent != null && this.parent instanceof Radio) {
               var1 = IsoPlayer.getInstance();
            } else if (this.parent instanceof VehiclePart) {
               var1 = ((VehiclePart)this.parent).getVehicle();
            }

            if (var1 != null) {
               int var2 = (int)(100.0F * this.deviceVolume);
               int var3 = this.getDeviceSoundVolumeRange();
               WorldSoundManager.instance.addSoundRepeating(var1, (int)var1.getX(), (int)var1.getY(), (int)var1.getZ(), var3, var2, var2 > 50);
            }
         }

         this.doTriggerWorldSound = false;
         this.soundCounter = 300 + Rand.Next(0, 300);
      }
   }

   private void updateStaticSounds() {
      if (this.isTurnedOn) {
         float var1 = GameTime.getInstance().getMultiplier();
         this.nextStaticSound -= var1;
         if (this.nextStaticSound <= 0.0F) {
            if (this.parent != null && this.signalCounter <= 0.0F && !this.isNoTransmit() && !this.isPlayingMedia()) {
               this.parent.AddDeviceText(ZomboidRadio.getInstance().getRandomBzztFzzt(), 1.0F, 1.0F, 1.0F, null, null, -1);
               this.doTriggerWorldSound = true;
            }

            this.setNextStaticSound();
         }
      }
   }

   private void setNextStaticSound() {
      this.nextStaticSound = Rand.Next(250.0F, 1500.0F);
   }

   public int getDeviceVolumeRange() {
      return 5 + (int)(this.baseVolumeRange * this.deviceVolume);
   }

   public int getDeviceSoundVolumeRange() {
      if (this.isInventoryDevice()) {
         Radio var2 = (Radio)this.getParent();
         return var2.getPlayer() != null && var2.getPlayer().getSquare() != null && var2.getPlayer().getSquare().getRoom() != null
            ? 3 + (int)(this.baseVolumeRange * 0.4F * this.deviceVolume)
            : 5 + (int)(this.baseVolumeRange * this.deviceVolume);
      } else if (this.isIsoDevice()) {
         IsoWaveSignal var1 = (IsoWaveSignal)this.getParent();
         return var1.getSquare() != null && var1.getSquare().getRoom() != null
            ? 3 + (int)(this.baseVolumeRange * 0.5F * this.deviceVolume)
            : 5 + (int)(this.baseVolumeRange * 0.75F * this.deviceVolume);
      } else {
         return 5 + (int)(this.baseVolumeRange / 2.0F * this.deviceVolume);
      }
   }

   public void doReceiveSignal(int var1) {
      if (this.isTurnedOn) {
         this.lastRecordedDistance = var1;
         if (this.deviceVolume > 0.0F && (this.isIsoDevice() || this.headphoneType < 0)) {
            Object var2 = null;
            if (this.parent != null && this.parent instanceof IsoObject) {
               var2 = (IsoObject)this.parent;
            } else if (this.parent != null && this.parent instanceof Radio) {
               var2 = IsoPlayer.getInstance();
            } else if (this.parent instanceof VehiclePart) {
               var2 = ((VehiclePart)this.parent).getVehicle();
            }

            if (var2 != null && this.soundCounter <= 0.0F) {
               int var3 = (int)(100.0F * this.deviceVolume);
               int var4 = this.getDeviceSoundVolumeRange();
               WorldSoundManager.instance.addSound(var2, (int)var2.getX(), (int)var2.getY(), (int)var2.getZ(), var4, var3, var3 > 50);
               this.soundCounter = 120.0F;
            }
         }

         this.signalCounter = 300.0F;
         this.doTriggerWorldSound = true;
         this.setNextStaticSound();
      }
   }

   public void doReceiveMPSignal(float var1) {
      this.lastRecordedDistance = (int)var1;
      this.voipCounter = 10.0F;
   }

   public boolean isReceivingSignal() {
      return this.signalCounter > 0.0F || this.voipCounter > 0.0F;
   }

   public int getLastRecordedDistance() {
      return this.lastRecordedDistance;
   }

   public boolean isIsoDevice() {
      return this.getParent() != null && this.getParent() instanceof IsoWaveSignal;
   }

   public boolean isInventoryDevice() {
      return this.getParent() != null && this.getParent() instanceof Radio;
   }

   public boolean isVehicleDevice() {
      return this.getParent() instanceof VehiclePart;
   }

   public void transmitPresets() {
      this.transmitDeviceDataState((short)5);
   }

   private void transmitDeviceDataState(short var1) {
      if (GameClient.bClient) {
         try {
            VoiceManager.getInstance().UpdateChannelsRoaming(GameClient.connection);
            this.sendDeviceDataStatePacket(GameClient.connection, var1);
         } catch (Exception var3) {
            System.out.print(var3.getMessage());
         }
      }
   }

   private void transmitDeviceDataStateServer(short var1, UdpConnection var2) {
      if (GameServer.bServer) {
         try {
            for (int var3 = 0; var3 < GameServer.udpEngine.connections.size(); var3++) {
               UdpConnection var4 = (UdpConnection)GameServer.udpEngine.connections.get(var3);
               if (var2 == null || var2 != var4) {
                  this.sendDeviceDataStatePacket(var4, var1);
               }
            }
         } catch (Exception var5) {
            System.out.print(var5.getMessage());
         }
      }
   }

   private void sendDeviceDataStatePacket(UdpConnection var1, short var2) {
      ByteBufferWriter var3 = var1.startPacket();
      PacketType.RadioDeviceDataState.doPacket(var3);
      boolean var4 = false;
      if (this.isIsoDevice()) {
         IsoWaveSignal var5 = (IsoWaveSignal)this.getParent();
         IsoGridSquare var6 = var5.getSquare();
         if (var6 != null) {
            var3.putByte((byte)1);
            var3.putInt(var6.getX());
            var3.putInt(var6.getY());
            var3.putInt(var6.getZ());
            var3.putInt(var6.getObjects().indexOf(var5));
            var4 = true;
         }
      } else if (this.isInventoryDevice()) {
         Radio var7 = (Radio)this.getParent();
         IsoPlayer var10 = null;
         if (var7.getEquipParent() != null && var7.getEquipParent() instanceof IsoPlayer) {
            var10 = (IsoPlayer)var7.getEquipParent();
         }

         if (var10 != null) {
            var3.putByte((byte)0);
            if (GameServer.bServer) {
               var3.putShort(var10 != null ? var10.OnlineID : -1);
            } else {
               var3.putByte((byte)var10.PlayerIndex);
            }

            if (var10.getPrimaryHandItem() == var7) {
               var3.putByte((byte)1);
            } else if (var10.getSecondaryHandItem() == var7) {
               var3.putByte((byte)2);
            } else {
               var3.putByte((byte)0);
            }

            var4 = true;
         }
      } else if (this.isVehicleDevice()) {
         VehiclePart var8 = (VehiclePart)this.getParent();
         var3.putByte((byte)2);
         var3.putShort(var8.getVehicle().VehicleID);
         var3.putShort((short)var8.getIndex());
         var4 = true;
      }

      if (var4) {
         var3.putShort(var2);
         switch (var2) {
            case 0:
               var3.putByte((byte)(this.isTurnedOn ? 1 : 0));
               break;
            case 1:
               var3.putInt(this.channel);
               break;
            case 2:
               var3.putByte((byte)(this.hasBattery ? 1 : 0));
               var3.putFloat(this.powerDelta);
               break;
            case 3:
               var3.putFloat(this.powerDelta);
               break;
            case 4:
               var3.putFloat(this.deviceVolume);
               break;
            case 5:
               var3.putInt(this.presets.getPresets().size());

               for (PresetEntry var11 : this.presets.getPresets()) {
                  GameWindow.WriteString(var3.bb, var11.getName());
                  var3.putInt(var11.getFrequency());
               }
               break;
            case 6:
               var3.putInt(this.headphoneType);
               break;
            case 7:
               var3.putShort(this.mediaIndex);
               var3.putByte((byte)(this.mediaItem != null ? 1 : 0));
               if (this.mediaItem != null) {
                  GameWindow.WriteString(var3.bb, this.mediaItem);
               }
               break;
            case 8:
               if (GameServer.bServer) {
                  var3.putShort(this.mediaIndex);
                  var3.putByte((byte)(this.mediaItem != null ? 1 : 0));
                  if (this.mediaItem != null) {
                     GameWindow.WriteString(var3.bb, this.mediaItem);
                  }
               }
            case 9:
            default:
               break;
            case 10:
               if (GameServer.bServer) {
                  var3.putShort(this.mediaIndex);
                  var3.putInt(this.mediaLineIndex);
               }
         }

         PacketType.RadioDeviceDataState.send(var1);
      } else {
         var1.cancelPacket();
      }
   }

   public void receiveDeviceDataStatePacket(ByteBuffer var1, UdpConnection var2) throws IOException {
      if (GameClient.bClient || GameServer.bServer) {
         boolean var3 = GameServer.bServer;
         boolean var4 = this.isIsoDevice() || this.isVehicleDevice();
         short var5 = var1.getShort();
         switch (var5) {
            case 0:
               if (var3 && var4) {
                  this.setIsTurnedOn(var1.get() == 1);
               } else {
                  this.isTurnedOn = var1.get() == 1;
               }

               if (var3) {
                  this.transmitDeviceDataStateServer(var5, !var4 ? var2 : null);
               }
               break;
            case 1:
               int var6 = var1.getInt();
               if (var3 && var4) {
                  this.setChannel(var6);
               } else {
                  this.channel = var6;
               }

               if (var3) {
                  this.transmitDeviceDataStateServer(var5, !var4 ? var2 : null);
               }
               break;
            case 2:
               boolean var7 = var1.get() == 1;
               float var8 = var1.getFloat();
               if (var3 && var4) {
                  this.hasBattery = var7;
                  this.setPower(var8);
               } else {
                  this.hasBattery = var7;
                  this.powerDelta = var8;
               }

               if (var3) {
                  this.transmitDeviceDataStateServer(var5, !var4 ? var2 : null);
               }
               break;
            case 3:
               float var9 = var1.getFloat();
               if (var3 && var4) {
                  this.setPower(var9);
               } else {
                  this.powerDelta = var9;
               }

               if (var3) {
                  this.transmitDeviceDataStateServer(var5, !var4 ? var2 : null);
               }
               break;
            case 4:
               float var10 = var1.getFloat();
               if (var3 && var4) {
                  this.setDeviceVolume(var10);
               } else {
                  this.deviceVolume = var10;
               }

               if (var3) {
                  this.transmitDeviceDataStateServer(var5, !var4 ? var2 : null);
               }
               break;
            case 5:
               int var11 = var1.getInt();

               for (int var19 = 0; var19 < var11; var19++) {
                  String var20 = GameWindow.ReadString(var1);
                  int var21 = var1.getInt();
                  if (var19 < this.presets.getPresets().size()) {
                     PresetEntry var22 = (PresetEntry)this.presets.getPresets().get(var19);
                     if (!var22.getName().equals(var20) || var22.getFrequency() != var21) {
                        var22.setName(var20);
                        var22.setFrequency(var21);
                     }
                  } else {
                     this.presets.addPreset(var20, var21);
                  }
               }

               if (var3) {
                  this.transmitDeviceDataStateServer((short)5, !var4 ? var2 : null);
               }
               break;
            case 6:
               this.headphoneType = var1.getInt();
               if (var3) {
                  this.transmitDeviceDataStateServer(var5, !var4 ? var2 : null);
               }
               break;
            case 7:
               this.mediaIndex = var1.getShort();
               if (var1.get() == 1) {
                  this.mediaItem = GameWindow.ReadString(var1);
               }

               if (var3) {
                  this.transmitDeviceDataStateServer(var5, !var4 ? var2 : null);
               }
               break;
            case 8:
               if (GameServer.bServer) {
                  this.StartPlayMedia();
               } else {
                  this.mediaIndex = var1.getShort();
                  if (var1.get() == 1) {
                     this.mediaItem = GameWindow.ReadString(var1);
                  }

                  this.isPlayingMedia = true;
                  this.televisionMediaSwitch();
               }
               break;
            case 9:
               if (GameServer.bServer) {
                  this.StopPlayMedia();
               } else {
                  this.isPlayingMedia = false;
                  this.televisionMediaSwitch();
               }
               break;
            case 10:
               if (GameClient.bClient) {
                  this.mediaIndex = var1.getShort();
                  int var12 = var1.getInt();
                  MediaData var13 = this.getMediaData();
                  if (var13 != null && var12 >= 0 && var12 < var13.getLineCount()) {
                     MediaLineData var14 = var13.getLine(var12);
                     String var15 = var14.getTranslatedText();
                     Color var16 = var14.getColor();
                     String var17 = var14.getTextGuid();
                     String var18 = var14.getCodes();
                     this.parent.AddDeviceText(var15, var16.r, var16.g, var16.b, var17, var18, 0);
                  }
               }
         }
      }
   }

   public void save(ByteBuffer var1, boolean var2) throws IOException {
      GameWindow.WriteString(var1, this.deviceName);
      var1.put((byte)(this.twoWay ? 1 : 0));
      var1.putInt(this.transmitRange);
      var1.putInt(this.micRange);
      var1.put((byte)(this.micIsMuted ? 1 : 0));
      var1.putFloat(this.baseVolumeRange);
      var1.putFloat(this.deviceVolume);
      var1.put((byte)(this.isPortable ? 1 : 0));
      var1.put((byte)(this.isTelevision ? 1 : 0));
      var1.put((byte)(this.isHighTier ? 1 : 0));
      var1.put((byte)(this.isTurnedOn ? 1 : 0));
      var1.putInt(this.channel);
      var1.putInt(this.minChannelRange);
      var1.putInt(this.maxChannelRange);
      var1.put((byte)(this.isBatteryPowered ? 1 : 0));
      var1.put((byte)(this.hasBattery ? 1 : 0));
      var1.putFloat(this.powerDelta);
      var1.putFloat(this.useDelta);
      var1.putInt(this.headphoneType);
      if (this.presets != null) {
         var1.put((byte)1);
         this.presets.save(var1, var2);
      } else {
         var1.put((byte)0);
      }

      var1.putShort(this.mediaIndex);
      var1.put(this.mediaType);
      var1.put((byte)(this.mediaItem != null ? 1 : 0));
      if (this.mediaItem != null) {
         GameWindow.WriteString(var1, this.mediaItem);
      }

      var1.put((byte)(this.noTransmit ? 1 : 0));
   }

   public void load(ByteBuffer var1, int var2, boolean var3) throws IOException {
      if (this.presets == null) {
         this.presets = new DevicePresets();
      }

      if (var2 >= 69) {
         this.deviceName = GameWindow.ReadString(var1);
         this.twoWay = var1.get() == 1;
         this.transmitRange = var1.getInt();
         this.micRange = var1.getInt();
         this.micIsMuted = var1.get() == 1;
         this.baseVolumeRange = var1.getFloat();
         this.deviceVolume = var1.getFloat();
         this.isPortable = var1.get() == 1;
         this.isTelevision = var1.get() == 1;
         this.isHighTier = var1.get() == 1;
         this.isTurnedOn = var1.get() == 1;
         this.channel = var1.getInt();
         this.minChannelRange = var1.getInt();
         this.maxChannelRange = var1.getInt();
         this.isBatteryPowered = var1.get() == 1;
         this.hasBattery = var1.get() == 1;
         this.powerDelta = var1.getFloat();
         this.useDelta = var1.getFloat();
         this.headphoneType = var1.getInt();
         if (var1.get() == 1) {
            this.presets.load(var1, var2, var3);
         }
      }

      if (var2 >= 181) {
         this.mediaIndex = var1.getShort();
         this.mediaType = var1.get();
         if (var1.get() == 1) {
            this.mediaItem = GameWindow.ReadString(var1);
         }

         this.noTransmit = var1.get() == 1;
      }
   }

   public boolean hasMedia() {
      return this.mediaIndex >= 0;
   }

   public short getMediaIndex() {
      return this.mediaIndex;
   }

   public void setMediaIndex(short var1) {
      this.mediaIndex = var1;
   }

   public byte getMediaType() {
      return this.mediaType;
   }

   public void setMediaType(byte var1) {
      this.mediaType = var1;
   }

   public void addMediaItem(InventoryItem var1) {
      if (this.mediaIndex < 0 && var1.isRecordedMedia() && var1.getMediaType() == this.mediaType) {
         ItemContainer var2 = var1.getContainer();
         if (var2 != null) {
            this.mediaIndex = var1.getRecordedMediaIndex();
            this.mediaItem = var1.getFullType();
            ItemUser.RemoveItem(var1);
            this.transmitDeviceDataState((short)7);
         }
      }
   }

   public InventoryItem removeMediaItem(ItemContainer var1) {
      if (this.hasMedia()) {
         InventoryItem var2 = InventoryItemFactory.CreateItem(this.mediaItem);
         var2.setRecordedMediaIndex(this.mediaIndex);
         var1.AddItem(var2);
         this.mediaIndex = -1;
         this.mediaItem = null;
         if (this.isPlayingMedia()) {
            this.StopPlayMedia();
         }

         this.transmitDeviceDataState((short)7);
         return var2;
      } else {
         return null;
      }
   }

   public boolean isPlayingMedia() {
      return this.isPlayingMedia;
   }

   public void StartPlayMedia() {
      if (GameClient.bClient) {
         this.transmitDeviceDataState((short)8);
      } else if (!this.isPlayingMedia() && this.getIsTurnedOn() && this.hasMedia()) {
         this.playingMedia = ZomboidRadio.getInstance().getRecordedMedia().getMediaDataFromIndex(this.mediaIndex);
         if (this.playingMedia != null) {
            this.isPlayingMedia = true;
            this.mediaLineIndex = 0;
            this.prePlayingMedia();
            if (GameServer.bServer) {
               this.transmitDeviceDataStateServer((short)8, null);
            }
         }
      }
   }

   private void prePlayingMedia() {
      this.lineCounter = 60.0F * this.maxmod * 0.5F;
      this.televisionMediaSwitch();
   }

   private void postPlayingMedia() {
      this.isStoppingMedia = true;
      this.stopMediaCounter = 60.0F * this.maxmod * 0.5F;
      this.televisionMediaSwitch();
   }

   private void televisionMediaSwitch() {
      if (this.mediaType == 1) {
         ZomboidRadio.getInstance().getRandomBzztFzzt();
         this.parent.AddDeviceText(ZomboidRadio.getInstance().getRandomBzztFzzt(), 0.5F, 0.5F, 0.5F, null, null, 0);
         this.playSoundLocal("TelevisionZap", true);
      }
   }

   public void StopPlayMedia() {
      if (GameClient.bClient) {
         this.transmitDeviceDataState((short)9);
      } else {
         this.playingMedia = null;
         this.postPlayingMedia();
         if (GameServer.bServer) {
            this.transmitDeviceDataStateServer((short)9, null);
         }
      }
   }

   public void updateMediaPlaying() {
      if (!GameClient.bClient) {
         if (this.isStoppingMedia) {
            this.stopMediaCounter = this.stopMediaCounter - 1.25F * GameTime.getInstance().getMultiplier();
            if (this.stopMediaCounter <= 0.0F) {
               this.isPlayingMedia = false;
               this.isStoppingMedia = false;
            }
         } else {
            if (this.hasMedia() && this.isPlayingMedia()) {
               if (!this.getIsTurnedOn()) {
                  this.StopPlayMedia();
                  return;
               }

               if (this.playingMedia != null) {
                  this.lineCounter = this.lineCounter - 1.25F * GameTime.getInstance().getMultiplier();
                  if (this.lineCounter <= 0.0F) {
                     MediaLineData var1 = this.playingMedia.getLine(this.mediaLineIndex);
                     if (var1 != null) {
                        String var2 = var1.getTranslatedText();
                        Color var3 = var1.getColor();
                        this.lineCounter = var2.length() / 10.0F * 60.0F;
                        if (this.lineCounter < 60.0F * this.minmod) {
                           this.lineCounter = 60.0F * this.minmod;
                        } else if (this.lineCounter > 60.0F * this.maxmod) {
                           this.lineCounter = 60.0F * this.maxmod;
                        }

                        if (GameServer.bServer) {
                           this.currentMediaLine = var2;
                           this.currentMediaColor = var3;
                           this.transmitDeviceDataStateServer((short)10, null);
                        } else {
                           String var4 = var1.getTextGuid();
                           String var5 = var1.getCodes();
                           this.parent.AddDeviceText(var2, var3.r, var3.g, var3.b, var4, var5, 0);
                        }

                        this.mediaLineIndex++;
                     } else {
                        this.StopPlayMedia();
                     }
                  }
               }
            }
         }
      }
   }

   public MediaData getMediaData() {
      return this.mediaIndex >= 0 ? ZomboidRadio.getInstance().getRecordedMedia().getMediaDataFromIndex(this.mediaIndex) : null;
   }

   public boolean isNoTransmit() {
      return this.noTransmit;
   }

   public void setNoTransmit(boolean var1) {
      this.noTransmit = var1;
   }
}
