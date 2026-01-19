package zombie;

import java.util.ArrayList;
import java.util.Map;
import java.util.TreeMap;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

@XmlRootElement
public final class FileGuidTable {
   public final ArrayList<FileGuidPair> files = new ArrayList<>();
   @XmlTransient
   private final Map<String, String> guidToPath = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
   @XmlTransient
   private final Map<String, String> pathToGuid = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);

   public void setModID(String var1) {
      for (FileGuidPair var3 : this.files) {
         var3.guid = var1 + "-" + var3.guid;
      }
   }

   public void mergeFrom(FileGuidTable var1) {
      this.files.addAll(var1.files);
   }

   public void loaded() {
      for (FileGuidPair var2 : this.files) {
         this.guidToPath.put(var2.guid, var2.path);
         this.pathToGuid.put(var2.path, var2.guid);
      }
   }

   public void clear() {
      this.files.clear();
      this.guidToPath.clear();
      this.pathToGuid.clear();
   }

   public String getFilePathFromGuid(String var1) {
      return this.guidToPath.get(var1);
   }

   public String getGuidFromFilePath(String var1) {
      return this.pathToGuid.get(var1);
   }
}
