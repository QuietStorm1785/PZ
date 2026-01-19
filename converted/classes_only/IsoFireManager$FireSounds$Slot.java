package zombie.iso.objects;

import fmod.fmod.FMODSoundEmitter;
import zombie.audio.BaseSoundEmitter;
import zombie.audio.DummySoundEmitter;
import zombie.audio.parameters.ParameterFireSize;
import zombie.core.Core;
import zombie.iso.IsoObject;

final class IsoFireManager$FireSounds$Slot {
   IsoFire fire;
   BaseSoundEmitter emitter;
   final ParameterFireSize parameterFireSize = new ParameterFireSize();
   long instance = 0L;
   boolean playing;

   void playSound(IsoFire var1) {
      if (this.emitter == null) {
         this.emitter = (BaseSoundEmitter)(Core.SoundDisabled ? new DummySoundEmitter() : new FMODSoundEmitter());
         if (!Core.SoundDisabled) {
            ((FMODSoundEmitter)this.emitter).addParameter(this.parameterFireSize);
         }
      }

      this.emitter.setPos(var1.square.x + 0.5F, var1.square.y + 0.5F, var1.square.z);

      byte var2 = switch (var1.LifeStage) {
         case 1, 3 -> 1;
         case 2 -> 2;
         default -> 0;
      };
      this.parameterFireSize.setSize(var2);
      if (var1.isCampfire()) {
         if (!this.emitter.isPlaying("CampfireRunning")) {
            this.instance = this.emitter.playSoundImpl("CampfireRunning", (IsoObject)null);
         }
      } else if (!this.emitter.isPlaying("Fire")) {
         this.instance = this.emitter.playSoundImpl("Fire", (IsoObject)null);
      }

      this.fire = var1;
      this.playing = true;
      this.emitter.tick();
   }

   void stopPlaying() {
      if (this.emitter != null && this.instance != 0L) {
         if (this.emitter.hasSustainPoints(this.instance)) {
            this.emitter.triggerCue(this.instance);
            this.instance = 0L;
         } else {
            this.emitter.stopAll();
            this.instance = 0L;
         }
      } else {
         if (this.emitter != null && !this.emitter.isEmpty()) {
            this.emitter.tick();
         }
      }
   }
}
