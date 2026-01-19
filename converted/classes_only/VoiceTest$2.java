package zombie.core.raknet;

import java.nio.ByteBuffer;

class VoiceTest$2 extends Thread {
   @Override
   public void run() {
      while (!VoiceTest.bQuit && !VoiceTest.bQuit) {
         ByteBuffer var1 = VoiceTest.rakNetClientReceive();

         try {
            VoiceTest.rakNetClientDecode(var1);
         } catch (Exception var3) {
            var3.printStackTrace();
         }
      }
   }
}
