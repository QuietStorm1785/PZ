package zombie;

import fmod.javafmod;
import fmod.fmod.FMODManager;
import zombie.GameSounds.IPreviewSound;
import zombie.audio.GameSound;
import zombie.audio.GameSoundClip;

final class GameSounds$FilePreviewSound implements IPreviewSound {
   long channel;
   GameSoundClip clip;
   float effectiveGain;

   private GameSounds$FilePreviewSound() {
   }

   public boolean play(GameSoundClip var1) {
      GameSound var2 = var1.gameSound;
      long var3 = FMODManager.instance.loadSound(var1.getFile(), var2.isLooped());
      if (var3 == 0L) {
         return false;
      } else {
         this.channel = javafmod.FMOD_System_PlaySound(var3, true);
         this.clip = var1;
         this.effectiveGain = var1.getEffectiveVolumeInMenu();
         javafmod.FMOD_Channel_SetVolume(this.channel, this.effectiveGain);
         javafmod.FMOD_Channel_SetPitch(this.channel, var1.pitch);
         if (var2.isLooped()) {
            javafmod.FMOD_Channel_SetMode(this.channel, FMODManager.FMOD_LOOP_NORMAL);
         }

         javafmod.FMOD_Channel_SetPaused(this.channel, false);
         return true;
      }
   }

   public boolean isPlaying() {
      return this.channel == 0L ? false : javafmod.FMOD_Channel_IsPlaying(this.channel);
   }

   public boolean update() {
      if (this.channel == 0L) {
         return false;
      } else if (!javafmod.FMOD_Channel_IsPlaying(this.channel)) {
         this.channel = 0L;
         this.clip = null;
         return true;
      } else {
         float var1 = this.clip.getEffectiveVolumeInMenu();
         if (this.effectiveGain != var1) {
            this.effectiveGain = var1;
            javafmod.FMOD_Channel_SetVolume(this.channel, this.effectiveGain);
         }

         return false;
      }
   }

   public void stop() {
      if (this.channel != 0L) {
         javafmod.FMOD_Channel_Stop(this.channel);
         this.channel = 0L;
         this.clip = null;
      }
   }
}
