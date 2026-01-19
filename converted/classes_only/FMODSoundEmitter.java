package fmod.fmod;

import fmod.FMOD_STUDIO_EVENT_PROPERTY;
import fmod.javafmod;
import fmod.javafmodJNI;
import fmod.fmod.FMODSoundEmitter.EventSound;
import fmod.fmod.FMODSoundEmitter.FileSound;
import fmod.fmod.FMODSoundEmitter.ParameterValue;
import fmod.fmod.FMODSoundEmitter.Sound;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.BitSet;
import zombie.GameSounds;
import zombie.SoundManager;
import zombie.audio.BaseSoundEmitter;
import zombie.audio.FMODParameter;
import zombie.audio.GameSound;
import zombie.audio.GameSoundClip;
import zombie.audio.parameters.ParameterOcclusion;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.debug.DebugLog;
import zombie.debug.DebugOptions;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoMovingObject;
import zombie.iso.IsoObject;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.popman.ObjectPool;

public final class FMODSoundEmitter extends BaseSoundEmitter {
   private final ArrayList<Sound> ToStart = new ArrayList<>();
   private final ArrayList<Sound> Instances = new ArrayList<>();
   public float x;
   public float y;
   public float z;
   public EmitterType emitterType;
   public IsoObject parent;
   private final ParameterOcclusion occlusion = new ParameterOcclusion(this);
   private final ArrayList<FMODParameter> parameters = new ArrayList<>();
   public IFMODParameterUpdater parameterUpdater;
   private final ArrayList<ParameterValue> parameterValues = new ArrayList<>();
   private static final ObjectPool<ParameterValue> parameterValuePool = new ObjectPool(ParameterValue::new);
   private static BitSet parameterSet;
   private final ArrayDeque<EventSound> eventSoundPool = new ArrayDeque<>();
   private final ArrayDeque<FileSound> fileSoundPool = new ArrayDeque<>();
   private static long CurrentTimeMS = 0L;

   public FMODSoundEmitter() {
      SoundManager.instance.registerEmitter(this);
      if (parameterSet == null) {
         parameterSet = new BitSet(FMODManager.instance.getParameterCount());
      }
   }

   public void randomStart() {
   }

   public void setPos(float var1, float var2, float var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
   }

   public int stopSound(long var1) {
      for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
         Sound var4 = this.ToStart.get(var3);
         if (var4.getRef() == var1) {
            this.sendStopSound(var4.name, false);
            var4.release();
            this.ToStart.remove(var3--);
         }
      }

      for (int var5 = 0; var5 < this.Instances.size(); var5++) {
         Sound var6 = this.Instances.get(var5);
         if (var6.getRef() == var1) {
            var6.stop();
            this.sendStopSound(var6.name, false);
            var6.release();
            this.Instances.remove(var5--);
         }
      }

      return 0;
   }

   public void stopSoundLocal(long var1) {
      for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
         Sound var4 = this.ToStart.get(var3);
         if (var4.getRef() == var1) {
            var4.release();
            this.ToStart.remove(var3--);
         }
      }

      for (int var5 = 0; var5 < this.Instances.size(); var5++) {
         Sound var6 = this.Instances.get(var5);
         if (var6.getRef() == var1) {
            var6.stop();
            var6.release();
            this.Instances.remove(var5--);
         }
      }
   }

   public int stopSoundByName(String var1) {
      GameSound var2 = GameSounds.getSound(var1);
      if (var2 == null) {
         return 0;
      } else {
         for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
            Sound var4 = this.ToStart.get(var3);
            if (var2.clips.contains(var4.clip)) {
               var4.release();
               this.ToStart.remove(var3--);
            }
         }

         for (int var5 = 0; var5 < this.Instances.size(); var5++) {
            Sound var6 = this.Instances.get(var5);
            if (var2.clips.contains(var6.clip)) {
               var6.stop();
               var6.release();
               this.Instances.remove(var5--);
            }
         }

         return 0;
      }
   }

   public void stopOrTriggerSound(long var1) {
      int var3 = this.findToStart(var1);
      if (var3 != -1) {
         Sound var6 = this.ToStart.remove(var3);
         this.sendStopSound(var6.name, true);
         var6.release();
      } else {
         var3 = this.findInstance(var1);
         if (var3 != -1) {
            Sound var4 = this.Instances.get(var3);
            this.sendStopSound(var4.name, true);
            if (var4.clip.hasSustainPoints()) {
               var4.triggerCue();
            } else {
               this.Instances.remove(var3);
               var4.stop();
               var4.release();
            }
         }
      }
   }

   public void stopOrTriggerSoundByName(String var1) {
      GameSound var2 = GameSounds.getSound(var1);
      if (var2 != null) {
         for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
            Sound var4 = this.ToStart.get(var3);
            if (var2.clips.contains(var4.clip)) {
               this.ToStart.remove(var3--);
               var4.release();
            }
         }

         for (int var5 = 0; var5 < this.Instances.size(); var5++) {
            Sound var6 = this.Instances.get(var5);
            if (var2.clips.contains(var6.clip)) {
               if (var6.clip.hasSustainPoints()) {
                  var6.triggerCue();
               } else {
                  var6.stop();
                  var6.release();
                  this.Instances.remove(var5--);
               }
            }
         }
      }
   }

   private void limitSound(GameSound var1, int var2) {
      int var3 = this.countToStart(var1) + this.countInstances(var1);
      if (var3 > var2) {
         for (int var4 = 0; var4 < this.ToStart.size(); var4++) {
            Sound var5 = this.ToStart.get(var4);
            if (var1.clips.contains(var5.clip)) {
               this.ToStart.remove(var4--);
               var5.release();
               if (--var3 <= var2) {
                  return;
               }
            }
         }

         for (int var6 = 0; var6 < this.Instances.size(); var6++) {
            Sound var7 = this.Instances.get(var6);
            if (var1.clips.contains(var7.clip)) {
               if (var7.clip.hasSustainPoints()) {
                  if (!var7.isTriggeredCue()) {
                     var7.triggerCue();
                  }
               } else {
                  var7.stop();
                  var7.release();
                  this.Instances.remove(var6--);
                  if (--var3 <= var2) {
                     return;
                  }
               }
            }
         }
      }
   }

   public void setVolume(long var1, float var3) {
      for (int var4 = 0; var4 < this.ToStart.size(); var4++) {
         Sound var5 = this.ToStart.get(var4);
         if (var5.getRef() == var1) {
            var5.volume = var3;
         }
      }

      for (int var6 = 0; var6 < this.Instances.size(); var6++) {
         Sound var7 = this.Instances.get(var6);
         if (var7.getRef() == var1) {
            var7.volume = var3;
         }
      }
   }

   public void setPitch(long var1, float var3) {
      for (int var4 = 0; var4 < this.ToStart.size(); var4++) {
         Sound var5 = this.ToStart.get(var4);
         if (var5.getRef() == var1) {
            var5.pitch = var3;
         }
      }

      for (int var6 = 0; var6 < this.Instances.size(); var6++) {
         Sound var7 = this.Instances.get(var6);
         if (var7.getRef() == var1) {
            var7.pitch = var3;
         }
      }
   }

   public boolean hasSustainPoints(long var1) {
      for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
         Sound var4 = this.ToStart.get(var3);
         if (var4.getRef() == var1) {
            if (var4.clip.eventDescription == null) {
               return false;
            }

            return var4.clip.eventDescription.bHasSustainPoints;
         }
      }

      for (int var5 = 0; var5 < this.Instances.size(); var5++) {
         Sound var6 = this.Instances.get(var5);
         if (var6.getRef() == var1) {
            if (var6.clip.eventDescription == null) {
               return false;
            }

            return var6.clip.eventDescription.bHasSustainPoints;
         }
      }

      return false;
   }

   public void triggerCue(long var1) {
      for (int var3 = 0; var3 < this.Instances.size(); var3++) {
         Sound var4 = this.Instances.get(var3);
         if (var4.getRef() == var1) {
            var4.triggerCue();
         }
      }
   }

   public void setVolumeAll(float var1) {
      for (int var2 = 0; var2 < this.ToStart.size(); var2++) {
         Sound var3 = this.ToStart.get(var2);
         var3.volume = var1;
      }

      for (int var4 = 0; var4 < this.Instances.size(); var4++) {
         Sound var5 = this.Instances.get(var4);
         var5.volume = var1;
      }
   }

   public void stopAll() {
      for (int var1 = 0; var1 < this.ToStart.size(); var1++) {
         Sound var2 = this.ToStart.get(var1);
         var2.release();
      }

      for (int var3 = 0; var3 < this.Instances.size(); var3++) {
         Sound var4 = this.Instances.get(var3);
         var4.stop();
         var4.release();
      }

      this.ToStart.clear();
      this.Instances.clear();
   }

   public long playSound(String var1) {
      if (GameClient.bClient) {
         if (this.parent instanceof IsoMovingObject) {
            if (!(this.parent instanceof IsoPlayer) || !((IsoPlayer)this.parent).isInvisible()) {
               GameClient.instance.PlaySound(var1, false, (IsoMovingObject)this.parent);
            }
         } else {
            GameClient.instance.PlayWorldSound(var1, (int)this.x, (int)this.y, (byte)this.z);
         }
      }

      return GameServer.bServer ? 0L : this.playSoundImpl(var1, (IsoObject)null);
   }

   public long playSound(String var1, IsoGameCharacter var2) {
      if (GameClient.bClient) {
         if (!var2.isInvisible()) {
            GameClient.instance.PlaySound(var1, false, var2);
         }

         return var2.isInvisible() && !DebugOptions.instance.Character.Debug.PlaySoundWhenInvisible.getValue() ? 0L : this.playSoundImpl(var1, (IsoObject)null);
      } else {
         return GameServer.bServer ? 0L : this.playSoundImpl(var1, (IsoObject)null);
      }
   }

   public long playSound(String var1, int var2, int var3, int var4) {
      this.x = var2;
      this.y = var3;
      this.z = var4;
      return this.playSound(var1);
   }

   public long playSound(String var1, IsoGridSquare var2) {
      this.x = var2.x + 0.5F;
      this.y = var2.y + 0.5F;
      this.z = var2.z;
      return this.playSound(var1);
   }

   public long playSoundImpl(String var1, IsoGridSquare var2) {
      this.x = var2.x + 0.5F;
      this.y = var2.y + 0.5F;
      this.z = var2.z + 0.5F;
      return this.playSoundImpl(var1, (IsoObject)null);
   }

   public long playSound(String var1, boolean var2) {
      return this.playSound(var1);
   }

   public long playSoundImpl(String var1, boolean var2, IsoObject var3) {
      return this.playSoundImpl(var1, var3);
   }

   public long playSoundLooped(String var1) {
      if (GameClient.bClient) {
         if (this.parent instanceof IsoMovingObject) {
            GameClient.instance.PlaySound(var1, true, (IsoMovingObject)this.parent);
         } else {
            GameClient.instance.PlayWorldSound(var1, (int)this.x, (int)this.y, (byte)this.z);
         }
      }

      return this.playSoundLoopedImpl(var1);
   }

   public long playSoundLoopedImpl(String var1) {
      return this.playSoundImpl(var1, false, null);
   }

   public long playSound(String var1, IsoObject var2) {
      if (GameClient.bClient) {
         if (var2 instanceof IsoMovingObject) {
            GameClient.instance.PlaySound(var1, false, (IsoMovingObject)this.parent);
         } else {
            GameClient.instance.PlayWorldSound(var1, (int)this.x, (int)this.y, (byte)this.z);
         }
      }

      return GameServer.bServer ? 0L : this.playSoundImpl(var1, var2);
   }

   public long playSoundImpl(String var1, IsoObject var2) {
      GameSound var3 = GameSounds.getSound(var1);
      if (var3 == null) {
         return 0L;
      } else {
         GameSoundClip var4 = var3.getRandomClip();
         return this.playClip(var4, var2);
      }
   }

   public long playClip(GameSoundClip var1, IsoObject var2) {
      Sound var3 = this.addSound(var1, 1.0F, var2);
      return var3 == null ? 0L : var3.getRef();
   }

   public long playAmbientSound(String var1) {
      if (GameServer.bServer) {
         return 0L;
      } else {
         GameSound var2 = GameSounds.getSound(var1);
         if (var2 == null) {
            return 0L;
         } else {
            GameSoundClip var3 = var2.getRandomClip();
            Sound var4 = this.addSound(var3, 1.0F, null);
            if (var4 instanceof FileSound) {
               ((FileSound)var4).ambient = true;
            }

            return var4 == null ? 0L : var4.getRef();
         }
      }
   }

   public long playAmbientLoopedImpl(String var1) {
      if (GameServer.bServer) {
         return 0L;
      } else {
         GameSound var2 = GameSounds.getSound(var1);
         if (var2 == null) {
            return 0L;
         } else {
            GameSoundClip var3 = var2.getRandomClip();
            Sound var4 = this.addSound(var3, 1.0F, null);
            return var4 == null ? 0L : var4.getRef();
         }
      }
   }

   public void set3D(long var1, boolean var3) {
      for (int var4 = 0; var4 < this.ToStart.size(); var4++) {
         Sound var5 = this.ToStart.get(var4);
         if (var5.getRef() == var1) {
            var5.set3D(var3);
         }
      }

      for (int var6 = 0; var6 < this.Instances.size(); var6++) {
         Sound var7 = this.Instances.get(var6);
         if (var7.getRef() == var1) {
            var7.set3D(var3);
         }
      }
   }

   public void tick() {
      if (!this.isEmpty()) {
         this.occlusion.update();

         for (int var1 = 0; var1 < this.parameters.size(); var1++) {
            FMODParameter var2 = this.parameters.get(var1);
            var2.update();
         }
      }

      for (int var4 = 0; var4 < this.ToStart.size(); var4++) {
         Sound var6 = this.ToStart.get(var4);
         this.Instances.add(var6);
      }

      for (int var5 = 0; var5 < this.Instances.size(); var5++) {
         Sound var7 = this.Instances.get(var5);
         boolean var3 = this.ToStart.contains(var7);
         if (var7.tick(var3)) {
            this.Instances.remove(var5--);
            var7.release();
         }
      }

      this.ToStart.clear();
   }

   public boolean hasSoundsToStart() {
      return !this.ToStart.isEmpty();
   }

   public boolean isEmpty() {
      return this.ToStart.isEmpty() && this.Instances.isEmpty();
   }

   public boolean isPlaying(long var1) {
      for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
         if (this.ToStart.get(var3).getRef() == var1) {
            return true;
         }
      }

      for (int var4 = 0; var4 < this.Instances.size(); var4++) {
         if (this.Instances.get(var4).getRef() == var1) {
            return true;
         }
      }

      return false;
   }

   public boolean isPlaying(String var1) {
      for (int var2 = 0; var2 < this.ToStart.size(); var2++) {
         if (var1.equals(this.ToStart.get(var2).name)) {
            return true;
         }
      }

      for (int var3 = 0; var3 < this.Instances.size(); var3++) {
         if (var1.equals(this.Instances.get(var3).name)) {
            return true;
         }
      }

      return false;
   }

   public boolean restart(long var1) {
      int var3 = this.findToStart(var1);
      if (var3 != -1) {
         return true;
      } else {
         var3 = this.findInstance(var1);
         return var3 != -1 && this.Instances.get(var3).restart();
      }
   }

   private int findInstance(long var1) {
      for (int var3 = 0; var3 < this.Instances.size(); var3++) {
         Sound var4 = this.Instances.get(var3);
         if (var4.getRef() == var1) {
            return var3;
         }
      }

      return -1;
   }

   private int findInstance(String var1) {
      GameSound var2 = GameSounds.getSound(var1);
      if (var2 == null) {
         return -1;
      } else {
         for (int var3 = 0; var3 < this.Instances.size(); var3++) {
            Sound var4 = this.Instances.get(var3);
            if (var2.clips.contains(var4.clip)) {
               return var3;
            }
         }

         return -1;
      }
   }

   private int findToStart(long var1) {
      for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
         Sound var4 = this.ToStart.get(var3);
         if (var4.getRef() == var1) {
            return var3;
         }
      }

      return -1;
   }

   private int findToStart(String var1) {
      GameSound var2 = GameSounds.getSound(var1);
      if (var2 == null) {
         return -1;
      } else {
         for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
            Sound var4 = this.ToStart.get(var3);
            if (var2.clips.contains(var4.clip)) {
               return var3;
            }
         }

         return -1;
      }
   }

   private int countToStart(GameSound var1) {
      int var2 = 0;

      for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
         Sound var4 = this.ToStart.get(var3);
         if (var1.clips.contains(var4.clip)) {
            var2++;
         }
      }

      return var2;
   }

   private int countInstances(GameSound var1) {
      int var2 = 0;

      for (int var3 = 0; var3 < this.Instances.size(); var3++) {
         Sound var4 = this.Instances.get(var3);
         if (var1.clips.contains(var4.clip)) {
            var2++;
         }
      }

      return var2;
   }

   public void addParameter(FMODParameter var1) {
      this.parameters.add(var1);
   }

   public void setParameterValue(long var1, FMOD_STUDIO_PARAMETER_DESCRIPTION var3, float var4) {
      if (var1 != 0L && var3 != null) {
         int var5 = this.findInstance(var1);
         if (var5 != -1) {
            Sound var8 = this.Instances.get(var5);
            var8.setParameterValue(var3, var4);
         } else {
            var5 = this.findParameterValue(var1, var3);
            if (var5 != -1) {
               this.parameterValues.get(var5).value = var4;
            } else {
               ParameterValue var6 = (ParameterValue)parameterValuePool.alloc();
               var6.eventInstance = var1;
               var6.parameterDescription = var3;
               var6.value = var4;
               this.parameterValues.add(var6);
            }
         }
      }
   }

   public void setTimelinePosition(long var1, String var3) {
      if (var1 != 0L) {
         int var4 = this.findToStart(var1);
         if (var4 != -1) {
            Sound var5 = this.ToStart.get(var4);
            var5.setTimelinePosition(var3);
         }
      }
   }

   private int findParameterValue(long var1, FMOD_STUDIO_PARAMETER_DESCRIPTION var3) {
      for (int var4 = 0; var4 < this.parameterValues.size(); var4++) {
         ParameterValue var5 = this.parameterValues.get(var4);
         if (var5.eventInstance == var1 && var5.parameterDescription == var3) {
            return var4;
         }
      }

      return -1;
   }

   public void clearParameters() {
      this.occlusion.resetToDefault();
      this.parameters.clear();
      parameterValuePool.releaseAll(this.parameterValues);
      this.parameterValues.clear();
   }

   private void startEvent(long var1, GameSoundClip var3) {
      parameterSet.clear();
      ArrayList var4 = this.parameters;
      ArrayList var5 = var3.eventDescription.parameters;

      for (int var6 = 0; var6 < var5.size(); var6++) {
         FMOD_STUDIO_PARAMETER_DESCRIPTION var7 = (FMOD_STUDIO_PARAMETER_DESCRIPTION)var5.get(var6);
         int var8 = this.findParameterValue(var1, var7);
         if (var8 != -1) {
            ParameterValue var11 = this.parameterValues.get(var8);
            javafmod.FMOD_Studio_EventInstance_SetParameterByID(var1, var7.id, var11.value, false);
            parameterSet.set(var7.globalIndex, true);
         } else if (var7 == this.occlusion.getParameterDescription()) {
            this.occlusion.startEventInstance(var1);
            parameterSet.set(var7.globalIndex, true);
         } else {
            for (int var9 = 0; var9 < var4.size(); var9++) {
               FMODParameter var10 = (FMODParameter)var4.get(var9);
               if (var10.getParameterDescription() == var7) {
                  var10.startEventInstance(var1);
                  parameterSet.set(var7.globalIndex, true);
                  break;
               }
            }
         }
      }

      if (this.parameterUpdater != null) {
         this.parameterUpdater.startEvent(var1, var3, parameterSet);
      }
   }

   private void updateEvent(long var1, GameSoundClip var3) {
      if (this.parameterUpdater != null) {
         this.parameterUpdater.updateEvent(var1, var3);
      }
   }

   private void stopEvent(long var1, GameSoundClip var3) {
      parameterSet.clear();
      ArrayList var4 = this.parameters;
      ArrayList var5 = var3.eventDescription.parameters;

      for (int var6 = 0; var6 < var5.size(); var6++) {
         FMOD_STUDIO_PARAMETER_DESCRIPTION var7 = (FMOD_STUDIO_PARAMETER_DESCRIPTION)var5.get(var6);
         int var8 = this.findParameterValue(var1, var7);
         if (var8 != -1) {
            ParameterValue var11 = this.parameterValues.remove(var8);
            parameterValuePool.release(var11);
            parameterSet.set(var7.globalIndex, true);
         } else if (var7 == this.occlusion.getParameterDescription()) {
            this.occlusion.stopEventInstance(var1);
            parameterSet.set(var7.globalIndex, true);
         } else {
            for (int var9 = 0; var9 < var4.size(); var9++) {
               FMODParameter var10 = (FMODParameter)var4.get(var9);
               if (var10.getParameterDescription() == var7) {
                  var10.stopEventInstance(var1);
                  parameterSet.set(var7.globalIndex, true);
                  break;
               }
            }
         }
      }

      if (this.parameterUpdater != null) {
         this.parameterUpdater.stopEvent(var1, var3, parameterSet);
      }
   }

   private EventSound allocEventSound() {
      return this.eventSoundPool.isEmpty() ? new EventSound(this) : this.eventSoundPool.pop();
   }

   private void releaseEventSound(EventSound var1) {
      assert !this.eventSoundPool.contains(var1);

      this.eventSoundPool.push(var1);
   }

   private FileSound allocFileSound() {
      return this.fileSoundPool.isEmpty() ? new FileSound(this) : this.fileSoundPool.pop();
   }

   private void releaseFileSound(FileSound var1) {
      assert !this.fileSoundPool.contains(var1);

      this.fileSoundPool.push(var1);
   }

   private Sound addSound(GameSoundClip var1, float var2, IsoObject var3) {
      if (var1 == null) {
         DebugLog.log("null sound passed to SoundEmitter.playSoundImpl");
         return null;
      } else {
         if (var1.gameSound.maxInstancesPerEmitter > 0) {
            this.limitSound(var1.gameSound, var1.gameSound.maxInstancesPerEmitter - 1);
         }

         if (var1.event != null && !var1.event.isEmpty()) {
            if (var1.eventDescription == null) {
               return null;
            } else {
               FMOD_STUDIO_EVENT_DESCRIPTION var9 = var1.eventDescription;
               if (var1.eventDescriptionMP != null && this.parent instanceof IsoPlayer && !((IsoPlayer)this.parent).isLocalPlayer()) {
                  var9 = var1.eventDescriptionMP;
               }

               long var5 = javafmod.FMOD_Studio_System_CreateEventInstance(var9.address);
               if (var5 < 0L) {
                  return null;
               } else {
                  if (var1.hasMinDistance()) {
                     javafmodJNI.FMOD_Studio_EventInstance_SetProperty(
                        var5, FMOD_STUDIO_EVENT_PROPERTY.FMOD_STUDIO_EVENT_PROPERTY_MINIMUM_DISTANCE.ordinal(), var1.getMinDistance()
                     );
                  }

                  if (var1.hasMaxDistance()) {
                     javafmodJNI.FMOD_Studio_EventInstance_SetProperty(
                        var5, FMOD_STUDIO_EVENT_PROPERTY.FMOD_STUDIO_EVENT_PROPERTY_MAXIMUM_DISTANCE.ordinal(), var1.getMaxDistance()
                     );
                  }

                  EventSound var7 = this.allocEventSound();
                  var7.clip = var1;
                  var7.name = var1.gameSound.getName();
                  var7.eventInstance = var5;
                  var7.volume = var2;
                  var7.parent = var3;
                  var7.setVolume = 1.0F;
                  var7.setX = var7.setY = var7.setZ = 0.0F;
                  this.ToStart.add(var7);
                  return var7;
               }
            }
         } else if (var1.file != null && !var1.file.isEmpty()) {
            long var4 = FMODManager.instance.loadSound(var1.file);
            if (var4 == 0L) {
               return null;
            } else {
               long var6 = javafmod.FMOD_System_PlaySound(var4, true);
               javafmod.FMOD_Channel_SetVolume(var6, 0.0F);
               javafmod.FMOD_Channel_SetPriority(var6, 9 - var1.priority);
               javafmod.FMOD_Channel_SetChannelGroup(var6, FMODManager.instance.channelGroupInGameNonBankSounds);
               if (var1.distanceMax == 0.0F || this.x == 0.0F && this.y == 0.0F) {
                  javafmod.FMOD_Channel_SetMode(var6, FMODManager.FMOD_2D);
               }

               FileSound var8 = this.allocFileSound();
               var8.clip = var1;
               var8.name = var1.gameSound.getName();
               var8.sound = var4;
               var8.pitch = var1.pitch;
               var8.channel = var6;
               var8.parent = var3;
               var8.volume = var2;
               var8.setVolume = 1.0F;
               var8.setX = var8.setY = var8.setZ = 0.0F;
               var8.is3D = -1;
               var8.ambient = false;
               this.ToStart.add(var8);
               return var8;
            }
         } else {
            return null;
         }
      }
   }

   private void sendStopSound(String var1, boolean var2) {
      if (GameClient.bClient && this.parent instanceof IsoMovingObject) {
         GameClient.instance.StopSound((IsoMovingObject)this.parent, var1, var2);
      }
   }

   public static void update() {
      CurrentTimeMS = System.currentTimeMillis();
   }
}
