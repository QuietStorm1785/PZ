package zombie.core.raknet;

class VoiceManager$4 extends Thread {
   VoiceManager$4(VoiceManager var1) {
      this.this$0 = var1;
   }

   @Override
   public void run() {
      while (!this.this$0.bQuit) {
         try {
            this.this$0.UpdateVMClient();
            sleep(VoiceManager.period / 2);
         } catch (Exception var2) {
            var2.printStackTrace();
         }
      }
   }
}
