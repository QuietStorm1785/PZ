package zombie.network.packets;

import zombie.core.Translator;

public enum RequestDataPacket$RequestID {
   ConnectionDetails,
   Descriptors,
   MetaGrid,
   MapZone,
   PlayerZombieDescriptors,
   RadioData;

   public String getDescriptor() {
      return Translator.getText("IGUI_RequestID_" + this.name());
   }
}
