package zombie.radio.scripting;

import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.radio.ZomboidRadio;

public final class RadioScriptManager {
   private final Map<Integer, RadioChannel> channels = new LinkedHashMap<>();
   private static RadioScriptManager instance;
   private int currentTimeStamp = 0;
   private ArrayList<RadioChannel> channelsList = new ArrayList<>();

   public static boolean hasInstance() {
      return instance != null;
   }

   public static RadioScriptManager getInstance() {
      if (instance == null) {
         instance = new RadioScriptManager();
      }

      return instance;
   }

   private RadioScriptManager() {
   }

   public void init(int var1) {
   }

   public Map<Integer, RadioChannel> getChannels() {
      return this.channels;
   }

   public ArrayList getChannelsList() {
      this.channelsList.clear();

      for (Entry var2 : this.channels.entrySet()) {
         this.channelsList.add((RadioChannel)var2.getValue());
      }

      return this.channelsList;
   }

   public RadioChannel getRadioChannel(String var1) {
      for (Entry var3 : this.channels.entrySet()) {
         if (((RadioChannel)var3.getValue()).getGUID().equals(var1)) {
            return (RadioChannel)var3.getValue();
         }
      }

      return null;
   }

   public void simulateScriptsUntil(int var1, boolean var2) {
      for (Entry var4 : this.channels.entrySet()) {
         this.simulateChannelUntil(((RadioChannel)var4.getValue()).GetFrequency(), var1, var2);
      }
   }

   public void simulateChannelUntil(int var1, int var2, boolean var3) {
      if (this.channels.containsKey(var1)) {
         RadioChannel var4 = this.channels.get(var1);
         if (var4.isTimeSynced() && !var3) {
            return;
         }

         for (int var5 = 0; var5 < var2; var5++) {
            int var6 = var5 * 24 * 60;
            var4.UpdateScripts(this.currentTimeStamp, var6);
         }

         var4.setTimeSynced(true);
      }
   }

   public int getCurrentTimeStamp() {
      return this.currentTimeStamp;
   }

   public void PlayerListensChannel(int var1, boolean var2, boolean var3) {
      if (this.channels.containsKey(var1) && this.channels.get(var1).IsTv() == var3) {
         this.channels.get(var1).SetPlayerIsListening(var2);
      }
   }

   public void AddChannel(RadioChannel var1, boolean var2) {
      if (var1 == null || !var2 && this.channels.containsKey(var1.GetFrequency())) {
         String var4 = var1 != null ? var1.GetName() : "null";
         DebugLog.log(DebugType.Radio, "Error adding radiochannel (" + var4 + "), channel is null or frequency key already exists");
      } else {
         this.channels.put(var1.GetFrequency(), var1);
         String var3 = var1.GetCategory().name();
         ZomboidRadio.getInstance().addChannelName(var1.GetName(), var1.GetFrequency(), var3, var2);
      }
   }

   public void RemoveChannel(int var1) {
      if (this.channels.containsKey(var1)) {
         this.channels.remove(var1);
         ZomboidRadio.getInstance().removeChannelName(var1);
      }
   }

   public void UpdateScripts(int var1, int var2, int var3) {
      this.currentTimeStamp = var1 * 24 * 60 + var2 * 60 + var3;

      for (Entry var5 : this.channels.entrySet()) {
         ((RadioChannel)var5.getValue()).UpdateScripts(this.currentTimeStamp, var1);
      }
   }

   public void update() {
      for (Entry var2 : this.channels.entrySet()) {
         ((RadioChannel)var2.getValue()).update();
      }
   }

   public void reset() {
      instance = null;
   }

   public void Save(Writer var1) throws IOException {
      for (Entry var3 : this.channels.entrySet()) {
         var1.write(
            var3.getKey() + "," + ((RadioChannel)var3.getValue()).getCurrentScriptLoop() + "," + ((RadioChannel)var3.getValue()).getCurrentScriptMaxLoops()
         );
         RadioScript var4 = ((RadioChannel)var3.getValue()).getCurrentScript();
         if (var4 != null) {
            var1.write("," + var4.GetName() + "," + var4.getStartDay());
         }

         RadioBroadCast var5 = ((RadioChannel)var3.getValue()).getAiringBroadcast();
         if (var5 != null) {
            var1.write("," + var5.getID());
         } else if (((RadioChannel)var3.getValue()).getLastBroadcastID() != null) {
            var1.write("," + ((RadioChannel)var3.getValue()).getLastBroadcastID());
         } else {
            var1.write(",none");
         }

         var1.write("," + (var5 != null ? var5.getCurrentLineNumber() + "" : "-1"));
         var1.write(System.lineSeparator());
      }
   }

   public void Load(List<String> var1) throws IOException, NumberFormatException {
      int var3 = 1;
      int var4 = 1;

      for (String var10 : var1) {
         RadioChannel var11 = null;
         if (var10 != null) {
            var10 = var10.trim();
            String[] var12 = var10.split(",");
            if (var12.length >= 3) {
               int var2 = Integer.parseInt(var12[0]);
               var3 = Integer.parseInt(var12[1]);
               var4 = Integer.parseInt(var12[2]);
               if (this.channels.containsKey(var2)) {
                  var11 = this.channels.get(var2);
                  var11.setTimeSynced(true);
               }
            }

            if (var11 != null && var12.length >= 5) {
               String var7 = var12[3];
               int var5 = Integer.parseInt(var12[4]);
               if (var11 != null) {
                  var11.setActiveScript(var7, var5, var3, var4);
               }
            }

            if (var11 != null && var12.length >= 7) {
               String var8 = var12[5];
               if (!var8.equals("none")) {
                  int var6 = Integer.parseInt(var12[6]);
                  var11.LoadAiringBroadcast(var8, var6);
               }
            }
         }
      }
   }
}
