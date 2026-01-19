package zombie.core.raknet;

import java.util.ArrayList;
import zombie.core.raknet.VoiceManagerData.RadioData;

public class VoiceManagerData {
   public static ArrayList<VoiceManagerData> data = new ArrayList<>();
   public long userplaychannel;
   public long userplaysound;
   public boolean userplaymute;
   public long voicetimeout;
   public final ArrayList<RadioData> radioData = new ArrayList<>();
   public boolean isCanHearAll;
   short index;

   public VoiceManagerData(short var1) {
      this.userplaymute = false;
      this.userplaychannel = 0L;
      this.userplaysound = 0L;
      this.voicetimeout = 0L;
      this.index = var1;
   }

   public static VoiceManagerData get(short var0) {
      if (data.size() <= var0) {
         for (short var1 = (short)data.size(); var1 <= var0; var1++) {
            VoiceManagerData var2 = new VoiceManagerData(var1);
            data.add(var2);
         }
      }

      VoiceManagerData var3 = data.get(var0);
      if (var3 == null) {
         var3 = new VoiceManagerData(var0);
         data.set(var0, var3);
      }

      return var3;
   }
}
