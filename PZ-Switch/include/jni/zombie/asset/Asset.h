#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset/ObserverCallback.h"
#include "zombie/asset/Asset/PRIVATE.h"
#include "zombie/asset/Asset/State.h"
#include "zombie/asset/AssetManager/AssetParams.h"

namespace zombie {
namespace asset {


class Asset {
:
    const AssetManager m_asset_manager;
    AssetPath m_path;
    int m_ref_count;
    const PRIVATE m_priv = new PRIVATE(this);

    protected Asset(AssetPath var1, AssetManager var2) {
      this.m_ref_count = 0;
      this.m_path = var1;
      this.m_asset_manager = var2;
   }

    abstract AssetType getType();

    State getState() const {
      return this.m_priv.m_current_state;
   }

    bool isEmpty() {
      return this.m_priv.m_current_state == State.EMPTY;
   }

    bool isReady() {
      return this.m_priv.m_current_state == State.READY;
   }

    bool isFailure() {
      return this.m_priv.m_current_state == State.FAILURE;
   }

    void onCreated(State var1) {
      this.m_priv.onCreated(var1);
   }

    int getRefCount() const {
      return this.m_ref_count;
   }

    ObserverCallback getObserverCb() const {
      if (this.m_priv.m_cb == nullptr) {
         this.m_priv.m_cb = std::make_unique<ObserverCallback>();
      }

      return this.m_priv.m_cb;
   }

    AssetPath getPath() const {
      return this.m_path;
   }

    AssetManager getAssetManager() const {
      return this.m_asset_manager;
   }

    void onBeforeReady() {
   }

    void onBeforeEmpty() {
   }

    void addDependency(Asset var1) {
      this.m_priv.addDependency(var1);
   }

    void removeDependency(Asset var1) {
      this.m_priv.removeDependency(var1);
   }

    int addRef() {
      return ++this.m_ref_count;
   }

    int rmRef() {
      return --this.m_ref_count;
   }

    void setAssetParams(AssetParams var1) {
   }
}
} // namespace asset
} // namespace zombie
