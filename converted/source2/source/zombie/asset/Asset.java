package zombie.asset;

import zombie.asset.Asset.ObserverCallback;
import zombie.asset.Asset.PRIVATE;
import zombie.asset.Asset.State;
import zombie.asset.AssetManager.AssetParams;

public abstract class Asset {
   protected final AssetManager m_asset_manager;
   private AssetPath m_path;
   private int m_ref_count;
   final PRIVATE m_priv = new PRIVATE(this);

   protected Asset(AssetPath var1, AssetManager var2) {
      this.m_ref_count = 0;
      this.m_path = var1;
      this.m_asset_manager = var2;
   }

   public abstract AssetType getType();

   public State getState() {
      return this.m_priv.m_current_state;
   }

   public boolean isEmpty() {
      return this.m_priv.m_current_state == State.EMPTY;
   }

   public boolean isReady() {
      return this.m_priv.m_current_state == State.READY;
   }

   public boolean isFailure() {
      return this.m_priv.m_current_state == State.FAILURE;
   }

   public void onCreated(State var1) {
      this.m_priv.onCreated(var1);
   }

   public int getRefCount() {
      return this.m_ref_count;
   }

   public ObserverCallback getObserverCb() {
      if (this.m_priv.m_cb == null) {
         this.m_priv.m_cb = new ObserverCallback();
      }

      return this.m_priv.m_cb;
   }

   public AssetPath getPath() {
      return this.m_path;
   }

   public AssetManager getAssetManager() {
      return this.m_asset_manager;
   }

   protected void onBeforeReady() {
   }

   protected void onBeforeEmpty() {
   }

   public void addDependency(Asset var1) {
      this.m_priv.addDependency(var1);
   }

   public void removeDependency(Asset var1) {
      this.m_priv.removeDependency(var1);
   }

   int addRef() {
      return ++this.m_ref_count;
   }

   int rmRef() {
      return --this.m_ref_count;
   }

   public void setAssetParams(AssetParams var1) {
   }
}
