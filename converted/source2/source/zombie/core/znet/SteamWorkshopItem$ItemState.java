package zombie.core.znet;

public enum SteamWorkshopItem$ItemState {
   None(0),
   Subscribed(1),
   LegacyItem(2),
   Installed(4),
   NeedsUpdate(8),
   Downloading(16),
   DownloadPending(32);

   private final int value;

   private SteamWorkshopItem$ItemState(int var3) {
      this.value = var3;
   }

   public int getValue() {
      return this.value;
   }

   public boolean and(SteamWorkshopItem$ItemState var1) {
      return (this.value & var1.value) != 0;
   }

   public boolean and(long var1) {
      return (this.value & var1) != 0L;
   }

   public boolean not(long var1) {
      return (this.value & var1) == 0L;
   }

   public static String toString(long var0) {
      if (var0 == None.getValue()) {
         return "None";
      } else {
         StringBuilder var2 = new StringBuilder();

         for (SteamWorkshopItem$ItemState var6 : values()) {
            if (var6 != None && var6.and(var0)) {
               if (var2.length() > 0) {
                  var2.append("|");
               }

               var2.append(var6.name());
            }
         }

         return var2.toString();
      }
   }
}
