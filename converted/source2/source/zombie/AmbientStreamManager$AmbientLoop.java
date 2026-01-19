package zombie;

import fmod.fmod.FMODSoundEmitter;

public final class AmbientStreamManager$AmbientLoop {
   public static float volChangeAmount = 0.01F;
   public float targVol;
   public float currVol;
   public String name;
   public float volumedelta = 1.0F;
   public long channel = -1L;
   public final FMODSoundEmitter emitter = new FMODSoundEmitter();

   public AmbientStreamManager$AmbientLoop(float var1, String var2, float var3) {
      this.volumedelta = var3;
      this.channel = this.emitter.playAmbientLoopedImpl(var2);
      this.targVol = var1;
      this.currVol = 0.0F;
      this.update();
   }

   public void update() {
      if (this.targVol > this.currVol) {
         this.currVol = this.currVol + volChangeAmount;
         if (this.currVol > this.targVol) {
            this.currVol = this.targVol;
         }
      }

      if (this.targVol < this.currVol) {
         this.currVol = this.currVol - volChangeAmount;
         if (this.currVol < this.targVol) {
            this.currVol = this.targVol;
         }
      }

      this.emitter.setVolumeAll(this.currVol * this.volumedelta);
      this.emitter.tick();
   }

   public void stop() {
      this.emitter.stopAll();
   }
}
