package zombie.radio.StorySounds;

import java.util.ArrayList;

public final class StorySoundEvent {
   protected String name;
   protected ArrayList<EventSound> eventSounds = new ArrayList<>();

   public StorySoundEvent() {
      this("Unnamed");
   }

   public StorySoundEvent(String var1) {
      this.name = var1;
   }

   public String getName() {
      return this.name;
   }

   public void setName(String var1) {
      this.name = var1;
   }

   public ArrayList<EventSound> getEventSounds() {
      return this.eventSounds;
   }

   public void setEventSounds(ArrayList<EventSound> var1) {
      this.eventSounds = var1;
   }
}
