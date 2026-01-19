package zombie.asset;

import java.util.ArrayList;
import zombie.asset.Asset.State;

public final class Asset$ObserverCallback extends ArrayList<AssetStateObserver> {
   public void invoke(State var1, State var2, Asset var3) {
      int var4 = this.size();

      for (int var5 = 0; var5 < var4; var5++) {
         this.get(var5).onStateChanged(var1, var2, var3);
      }
   }
}
