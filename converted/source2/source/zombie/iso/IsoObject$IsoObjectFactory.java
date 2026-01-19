package zombie.iso;

public class IsoObject$IsoObjectFactory {
   private final byte classID;
   private final String objectName;
   private final int hashCode;

   public IsoObject$IsoObjectFactory(byte var1, String var2) {
      this.classID = var1;
      this.objectName = var2;
      this.hashCode = var2.hashCode();
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoObject(var1);
   }

   public byte getClassID() {
      return this.classID;
   }

   public String getObjectName() {
      return this.objectName;
   }
}
