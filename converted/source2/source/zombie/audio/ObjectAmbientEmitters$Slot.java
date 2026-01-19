package zombie.audio;

import fmod.fmod.FMODSoundEmitter;
import zombie.audio.ObjectAmbientEmitters.PerObjectLogic;
import zombie.core.Core;
import zombie.iso.IsoObject;
import zombie.util.Type;

final class ObjectAmbientEmitters$Slot {
   IsoObject object = null;
   PerObjectLogic logic = null;
   BaseSoundEmitter emitter = null;
   long instance = 0L;
   boolean playing = false;

   void playSound(IsoObject var1, PerObjectLogic var2) {
      if (this.emitter == null) {
         this.emitter = (BaseSoundEmitter)(Core.SoundDisabled ? new DummySoundEmitter() : new FMODSoundEmitter());
      }

      var1.getFacingPosition(ObjectAmbientEmitters.tempVector2);
      this.emitter.setPos(ObjectAmbientEmitters.tempVector2.getX(), ObjectAmbientEmitters.tempVector2.getY(), var1.square.z);
      this.object = var1;
      this.logic = var2;
      String var3 = var2.getSoundName();
      if (!this.emitter.isPlaying(var3)) {
         this.emitter.stopAll();
         FMODSoundEmitter var4 = (FMODSoundEmitter)Type.tryCastTo(this.emitter, FMODSoundEmitter.class);
         if (var4 != null) {
            var4.clearParameters();
         }

         this.instance = this.emitter.playSoundImpl(var3, (IsoObject)null);
         var2.startPlaying(this.emitter, this.instance);
      }

      var2.checkParameters(this.emitter, this.instance);
      this.playing = true;
      this.emitter.tick();
   }

   void stopPlaying() {
      if (this.emitter != null && this.instance != 0L) {
         this.logic.stopPlaying(this.emitter, this.instance);
         if (this.emitter.hasSustainPoints(this.instance)) {
            this.emitter.triggerCue(this.instance);
            this.instance = 0L;
         } else {
            this.emitter.stopAll();
            this.instance = 0L;
         }
      }
   }
}
