package zombie;

import fmod.javafmod;
import fmod.fmod.FMODManager;
import fmod.fmod.FMOD_STUDIO_PLAYBACK_STATE;
import zombie.audio.GameSoundClip;

final class SoundManager$Music {
   public GameSoundClip clip;
   public long instance;
   public long channel;
   public long sound;
   public float effectiveVolume;

   private SoundManager$Music() {
   }

   public boolean isPlaying() {
      if (this.instance != 0L) {
         int var1 = javafmod.FMOD_Studio_GetPlaybackState(this.instance);
         return var1 != FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPED.index && var1 != FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPING.index;
      } else {
         return this.channel != 0L && javafmod.FMOD_Channel_IsPlaying(this.channel);
      }
   }

   public void update() {
      this.clip = this.clip.checkReloaded();
      float var1 = this.clip.getEffectiveVolume();
      if (this.effectiveVolume != var1) {
         this.effectiveVolume = var1;
         if (this.instance != 0L) {
            javafmod.FMOD_Studio_EventInstance_SetVolume(this.instance, this.effectiveVolume);
         }

         if (this.channel != 0L) {
            javafmod.FMOD_Channel_SetVolume(this.channel, this.effectiveVolume);
         }
      }
   }

   public float getPosition() {
      if (this.instance != 0L) {
         long var3 = javafmod.FMOD_Studio_GetTimelinePosition(this.instance);
         return (float)var3;
      } else if (this.channel != 0L) {
         long var1 = javafmod.FMOD_Channel_GetPosition(this.channel, FMODManager.FMOD_TIMEUNIT_MS);
         return (float)var1;
      } else {
         return 0.0F;
      }
   }

   public void stop() {
      if (this.instance != 0L) {
         javafmod.FMOD_Studio_EventInstance_Stop(this.instance, false);
         javafmod.FMOD_Studio_ReleaseEventInstance(this.instance);
         this.instance = 0L;
      }

      if (this.channel != 0L) {
         javafmod.FMOD_Channel_Stop(this.channel);
         this.channel = 0L;
         javafmod.FMOD_Sound_Release(this.sound);
         this.sound = 0L;
      }
   }
}
