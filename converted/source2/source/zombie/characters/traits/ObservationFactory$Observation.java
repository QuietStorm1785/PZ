package zombie.characters.traits;

import java.util.ArrayList;
import zombie.interfaces.IListBoxItem;

public class ObservationFactory$Observation implements IListBoxItem {
   private String traitID;
   private String name;
   private String description;
   public ArrayList<String> MutuallyExclusive = new ArrayList<>(0);

   public ObservationFactory$Observation(String var1, String var2, String var3) {
      this.setTraitID(var1);
      this.setName(var2);
      this.setDescription(var3);
   }

   public String getLabel() {
      return this.getName();
   }

   public String getLeftLabel() {
      return this.getName();
   }

   public String getRightLabel() {
      return null;
   }

   public String getDescription() {
      return this.description;
   }

   public void setDescription(String var1) {
      this.description = var1;
   }

   public String getTraitID() {
      return this.traitID;
   }

   public void setTraitID(String var1) {
      this.traitID = var1;
   }

   public String getName() {
      return this.name;
   }

   public void setName(String var1) {
      this.name = var1;
   }
}
