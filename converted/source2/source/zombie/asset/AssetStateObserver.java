package zombie.asset;

import zombie.asset.Asset.State;

public interface AssetStateObserver {
   void onStateChanged(State var1, State var2, Asset var3);
}
