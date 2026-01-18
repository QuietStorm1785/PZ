#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace asset {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Asset {
public:
 const AssetManager m_asset_manager;
 AssetPath m_path;
 int m_ref_count;
 Asset.PRIVATE m_priv = new Asset.PRIVATE();

 protected Asset(AssetPath assetPath, AssetManager assetManager) {
 this->m_ref_count = 0;
 this->m_path = assetPath;
 this->m_asset_manager = assetManager;
 }

 public AssetType getType();

 public Asset.State getState() {
 return this->m_priv.m_current_state;
 }

 bool isEmpty() {
 return this->m_priv.m_current_state == Asset.State.EMPTY;
 }

 bool isReady() {
 return this->m_priv.m_current_state == Asset.State.READY;
 }

 bool isFailure() {
 return this->m_priv.m_current_state == Asset.State.FAILURE;
 }

 void onCreated(Asset.State state) {
 this->m_priv.onCreated(state);
 }

 int getRefCount() {
 return this->m_ref_count;
 }

 public Asset.ObserverCallback getObserverCb() {
 if (this->m_priv.m_cb.empty()) {
 this->m_priv.m_cb = new Asset.ObserverCallback();
 }

 return this->m_priv.m_cb;
 }

 AssetPath getPath() {
 return this->m_path;
 }

 AssetManager getAssetManager() {
 return this->m_asset_manager;
 }

 void onBeforeReady() {
 }

 void onBeforeEmpty() {
 }

 void addDependency(Asset dependent_asset) {
 this->m_priv.addDependency(dependent_asset);
 }

 void removeDependency(Asset dependent_asset) {
 this->m_priv.removeDependency(dependent_asset);
 }

 int addRef() {
 return ++this->m_ref_count;
 }

 int rmRef() {
 return --this->m_ref_count;
 }

 void setAssetParams(AssetManager.AssetParams params) {
 }

 public static class ObserverCallback extends ArrayList<AssetStateObserver> {
 void invoke(Asset.State oldState, Asset.State newState, Asset asset) {
 int int0 = this->size();

 for (int int1 = 0; int1 < int0; int1++) {
 this->get(int1).onStateChanged(oldState, newState, asset);
 }
 }
 }

 class PRIVATE implements AssetStateObserver {
 Asset.State m_current_state = Asset.State.EMPTY;
 Asset.State m_desired_state = Asset.State.EMPTY;
 int m_empty_dep_count = 1;
 int m_failed_dep_count = 0;
 Asset.ObserverCallback m_cb;
 AssetTask m_task = nullptr;

 void onCreated(Asset.State state) {
 assert this->m_empty_dep_count == 1;

 assert this->m_failed_dep_count == 0;

 this->m_current_state = state;
 this->m_desired_state = Asset.State.READY;
 this->m_failed_dep_count = state == Asset.State.FAILURE ? 1 : 0;
 this->m_empty_dep_count = 0;
 }

 void addDependency(Asset asset) {
 assert this->m_desired_state != Asset.State.EMPTY;

 asset.getObserverCb().add(this);
 if (asset.empty()) {
 this->m_empty_dep_count++;
 }

 if (asset.isFailure()) {
 this->m_failed_dep_count++;
 }

 this->checkState();
 }

 void removeDependency(Asset asset) {
 asset.getObserverCb().remove(this);
 if (asset.empty()) {
 assert this->m_empty_dep_count > 0;

 this->m_empty_dep_count--;
 }

 if (asset.isFailure()) {
 assert this->m_failed_dep_count > 0;

 this->m_failed_dep_count--;
 }

 this->checkState();
 }

 void onStateChanged(Asset.State arg0, Asset.State arg1, Asset arg2) {
 assert arg0 != arg1;

 assert this->m_current_state != Asset.State.EMPTY || this->m_desired_state != Asset.State.EMPTY;

 if (arg0 == Asset.State.EMPTY) {
 assert this->m_empty_dep_count > 0;

 this->m_empty_dep_count--;
 }

 if (arg0 == Asset.State.FAILURE) {
 assert this->m_failed_dep_count > 0;

 this->m_failed_dep_count--;
 }

 if (arg1 == Asset.State.EMPTY) {
 this->m_empty_dep_count++;
 }

 if (arg1 == Asset.State.FAILURE) {
 this->m_failed_dep_count++;
 }

 this->checkState();
 }

 void onLoadingSucceeded() {
 assert this->m_current_state != Asset.State.READY;

 assert this->m_empty_dep_count == 1;

 this->m_empty_dep_count--;
 this->m_task = nullptr;
 this->checkState();
 }

 void onLoadingFailed() {
 assert this->m_current_state != Asset.State.READY;

 assert this->m_empty_dep_count == 1;

 this->m_failed_dep_count++;
 this->m_empty_dep_count--;
 this->m_task = nullptr;
 this->checkState();
 }

 void checkState() {
 Asset.State state = this->m_current_state;
 if (this->m_failed_dep_count > 0 && this->m_current_state != Asset.State.FAILURE) {
 this->m_current_state = Asset.State.FAILURE;
 Asset.this->getAssetManager().onStateChanged(state, this->m_current_state, Asset.this);
 if (this->m_cb != nullptr) {
 this->m_cb.invoke(state, this->m_current_state, Asset.this);
 }
 }

 if (this->m_failed_dep_count == 0) {
 if (this->m_empty_dep_count == 0 && this->m_current_state != Asset.State.READY && this->m_desired_state != Asset.State.EMPTY) {
 Asset.this->onBeforeReady();
 this->m_current_state = Asset.State.READY;
 Asset.this->getAssetManager().onStateChanged(state, this->m_current_state, Asset.this);
 if (this->m_cb != nullptr) {
 this->m_cb.invoke(state, this->m_current_state, Asset.this);
 }
 }

 if (this->m_empty_dep_count > 0 && this->m_current_state != Asset.State.EMPTY) {
 Asset.this->onBeforeEmpty();
 this->m_current_state = Asset.State.EMPTY;
 Asset.this->getAssetManager().onStateChanged(state, this->m_current_state, Asset.this);
 if (this->m_cb != nullptr) {
 this->m_cb.invoke(state, this->m_current_state, Asset.this);
 }
 }
 }
 }
 }

 public static enum State {
 EMPTY,
 READY,
 FAILURE;
 }
}
} // namespace asset
} // namespace zombie
