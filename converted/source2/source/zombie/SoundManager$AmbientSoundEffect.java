package zombie;

import fmod.javafmod;
import fmod.fmod.Audio;
import fmod.fmod.FMOD_STUDIO_PLAYBACK_STATE;
import zombie.audio.GameSound;
import zombie.audio.GameSoundClip;
import zombie.debug.DebugLog;

public final class SoundManager$AmbientSoundEffect implements Audio {
   public String name;
   public long eventInstance;
   public float gain;
   public GameSoundClip clip;
   public float effectiveVolume;

   public SoundManager$AmbientSoundEffect(String var1) {
      GameSound var2 = GameSounds.getSound(var1);
      if (var2 != null && !var2.clips.isEmpty()) {
         GameSoundClip var3 = var2.getRandomClip();
         if (var3.getEvent() != null) {
            if (var3.eventDescription != null) {
               this.eventInstance = javafmod.FMOD_Studio_System_CreateEventInstance(var3.eventDescription.address);
               if (this.eventInstance >= 0L) {
                  this.clip = var3;
               }
            }
         }
      }
   }

   public void setVolume(float var1) {
      if (this.eventInstance > 0L) {
         this.gain = var1;
         this.effectiveVolume = this.clip.getEffectiveVolume();
         javafmod.FMOD_Studio_EventInstance_SetVolume(this.eventInstance, this.gain * this.effectiveVolume);
      }
   }

   public void start() {
      if (this.eventInstance > 0L) {
         javafmod.FMOD_Studio_StartEvent(this.eventInstance);
      }
   }

   public void pause() {
   }

   public void stop() {
      DebugLog.log("stop ambient " + this.name);
      if (this.eventInstance > 0L) {
         javafmod.FMOD_Studio_EventInstance_Stop(this.eventInstance, false);
      }
   }

   public boolean isPlaying() {
      if (this.eventInstance <= 0L) {
         return false;
      } else {
         int var1 = javafmod.FMOD_Studio_GetPlaybackState(this.eventInstance);
         return var1 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STARTING.index
            || var1 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_PLAYING.index
            || var1 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_SUSTAINING.index;
      }
   }

   public void setName(String var1) {
      this.name = var1;
   }

   public String getName() {
      return this.name;
   }

   public void update() {
      if (this.clip != null) {
         this.clip = this.clip.checkReloaded();
         float var1 = this.clip.getEffectiveVolume();
         if (this.effectiveVolume != var1) {
            this.effectiveVolume = var1;
            javafmod.FMOD_Studio_EventInstance_SetVolume(this.eventInstance, this.gain * this.effectiveVolume);
         }
      }
   }
}
