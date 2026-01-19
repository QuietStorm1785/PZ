package fmod.fmod;

import zombie.audio.GameSoundClip;
import zombie.iso.IsoObject;

abstract class FMODSoundEmitter$Sound {
   FMODSoundEmitter emitter;
   public GameSoundClip clip;
   public String name;
   public float volume = 1.0F;
   public float pitch = 1.0F;
   public IsoObject parent;
   public float setVolume = 1.0F;
   float setX = 0.0F;
   float setY = 0.0F;
   float setZ = 0.0F;

   FMODSoundEmitter$Sound(FMODSoundEmitter var1) {
      this.emitter = var1;
   }

   abstract long getRef();

   abstract void stop();

   abstract void set3D(boolean var1);

   abstract void release();

   abstract boolean tick(boolean var1);

   float getVolume() {
      this.clip = this.clip.checkReloaded();
      return this.volume * this.clip.getEffectiveVolume();
   }

   abstract void setParameterValue(FMOD_STUDIO_PARAMETER_DESCRIPTION var1, float var2);

   abstract void setTimelinePosition(String var1);

   abstract void triggerCue();

   abstract boolean isTriggeredCue();

   abstract boolean restart();
}
