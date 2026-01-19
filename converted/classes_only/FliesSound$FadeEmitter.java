package zombie;

import zombie.audio.BaseSoundEmitter;
import zombie.iso.IsoGridSquare;

class FliesSound$FadeEmitter {
   private static final float FADE_IN_RATE = 0.01F;
   private static final float FADE_OUT_RATE = -0.01F;
   BaseSoundEmitter emitter;
   float volume;
   float targetVolume;
   IsoGridSquare sq;

   private FliesSound$FadeEmitter(FliesSound var1) {
      this.this$0 = var1;
      this.emitter = null;
      this.volume = 1.0F;
      this.targetVolume = 1.0F;
      this.sq = null;
   }

   boolean update() {
      if (this.emitter == null) {
         return true;
      } else {
         if (this.volume < this.targetVolume) {
            this.volume = this.volume + 0.01F * (GameTime.getInstance().getMultiplier() / 1.6F);
            if (this.volume >= this.targetVolume) {
               this.volume = this.targetVolume;
               return true;
            }
         } else {
            this.volume = this.volume + -0.01F * (GameTime.getInstance().getMultiplier() / 1.6F);
            if (this.volume <= 0.0F) {
               this.volume = 0.0F;
               this.emitter.stopAll();
               this.emitter = null;
               return true;
            }
         }

         this.emitter.setVolumeAll(this.volume);
         return false;
      }
   }

   void Reset() {
      this.emitter = null;
      this.volume = 1.0F;
      this.targetVolume = 1.0F;
      this.sq = null;
   }
}
