package zombie.radio.media;

import java.util.Comparator;

public class RecordedMedia$MediaNameSorter implements Comparator<MediaData> {
   public int compare(MediaData var1, MediaData var2) {
      return var1.getTranslatedItemDisplayName().compareToIgnoreCase(var2.getTranslatedItemDisplayName());
   }
}
