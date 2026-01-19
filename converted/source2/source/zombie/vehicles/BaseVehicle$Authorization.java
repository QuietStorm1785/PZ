package zombie.vehicles;

import java.util.Arrays;
import java.util.HashMap;

public enum BaseVehicle$Authorization {
   Server,
   LocalCollide,
   RemoteCollide,
   Local,
   Remote;

   private static final HashMap<Byte, BaseVehicle$Authorization> authorizations = new HashMap<>();

   public static BaseVehicle$Authorization valueOf(byte var0) {
      return authorizations.getOrDefault(var0, Server);
   }

   public byte index() {
      return (byte)this.ordinal();
   }

   static {
      Arrays.stream(values()).forEach(var0 -> authorizations.put(var0.index(), var0));
   }
}
