package zombie;

import fmod.javafmod;
import fmod.fmod.FMOD_STUDIO_PLAYBACK_STATE;
import zombie.GameSounds.IPreviewSound;
import zombie.audio.GameSoundClip;
import zombie.audio.GameSound.MasterVolume;
import zombie.debug.DebugLog;

final class GameSounds$BankPreviewSound implements IPreviewSound {
   long instance;
   GameSoundClip clip;
   float effectiveGain;

   private GameSounds$BankPreviewSound() {
   }

   public boolean play(GameSoundClip var1) {
      if (var1.eventDescription == null) {
         DebugLog.log("failed to get event " + var1.getEvent());
         return false;
      } else {
         this.instance = javafmod.FMOD_Studio_System_CreateEventInstance(var1.eventDescription.address);
         if (this.instance < 0L) {
            DebugLog.log("failed to create EventInstance: error=" + this.instance);
            this.instance = 0L;
            return false;
         } else {
            this.clip = var1;
            this.effectiveGain = var1.getEffectiveVolumeInMenu();
            javafmod.FMOD_Studio_EventInstance_SetVolume(this.instance, this.effectiveGain);
            javafmod.FMOD_Studio_EventInstance_SetParameterByName(this.instance, "Occlusion", 0.0F);
            javafmod.FMOD_Studio_StartEvent(this.instance);
            if (var1.gameSound.master == MasterVolume.Music) {
               javafmod.FMOD_Studio_EventInstance_SetParameterByName(this.instance, "Volume", 10.0F);
            }

            return true;
         }
      }
   }

   public boolean isPlaying() {
      if (this.instance == 0L) {
         return false;
      } else {
         int var1 = javafmod.FMOD_Studio_GetPlaybackState(this.instance);
         return var1 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPING.index
            ? true
            : var1 != FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPED.index;
      }
   }

   public boolean update() {
      if (this.instance == 0L) {
         return false;
      } else {
         int var1 = javafmod.FMOD_Studio_GetPlaybackState(this.instance);
         if (var1 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPING.index) {
            return false;
         } else if (var1 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPED.index) {
            javafmod.FMOD_Studio_ReleaseEventInstance(this.instance);
            this.instance = 0L;
            this.clip = null;
            return true;
         } else {
            float var2 = this.clip.getEffectiveVolumeInMenu();
            if (this.effectiveGain != var2) {
               this.effectiveGain = var2;
               javafmod.FMOD_Studio_EventInstance_SetVolume(this.instance, this.effectiveGain);
            }

            return false;
         }
      }
   }

   public void stop() {
      if (this.instance != 0L) {
         javafmod.FMOD_Studio_EventInstance_Stop(this.instance, false);
         javafmod.FMOD_Studio_ReleaseEventInstance(this.instance);
         this.instance = 0L;
         this.clip = null;
      }
   }
}
