#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/THashMap.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/fileSystem/IFile.h"

namespace zombie {
namespace asset {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AssetManager {
public:
 private AssetManager.AssetTable m_assets = new AssetManager.AssetTable();
 AssetManagers m_owner;
 bool m_is_unload_enabled = false;

 void create(AssetType type, AssetManagers owner) {
 owner.add(type, this);
 this->m_owner = owner;
 }

 void destroy() {
 this->m_assets.forEachValue(asset -> {
 if (!asset.empty()) {
 DebugLog.Asset.println("Leaking asset " + asset.getPath());
 }

 this->destroyAsset(asset);
 return true;
 });
 }

 void removeUnreferenced() {
 if (this->m_is_unload_enabled) {
 std::vector arrayList = new ArrayList();
 this->m_assets.forEachValue(assetx -> {
 if (assetx.getRefCount() == 0) {
 arrayList.add(assetx);
 }

 return true;
 });

 for (auto& asset : arrayList) this->m_assets.remove(asset.getPath());
 this->destroyAsset(asset);
 }
 }
 }

 Asset load(AssetPath path) {
 return this->load(path, nullptr);
 }

 Asset load(AssetPath path, AssetManager.AssetParams params) {
 if (!path.isValid()) {
 return nullptr;
 } else {
 Asset asset = this->get(path);
 if (asset == nullptr) {
 asset = this->createAsset(path, params);
 this->m_assets.put(path.getPath(), asset);
 }

 if (asset.empty() && asset.m_priv.m_desired_state == Asset.State.EMPTY) {
 this->doLoad(asset, params);
 }

 asset.addRef();
 return asset;
 }
 }

 void load(Asset asset) {
 if (asset.empty() && asset.m_priv.m_desired_state == Asset.State.EMPTY) {
 this->doLoad(asset, nullptr);
 }

 asset.addRef();
 }

 void unload(AssetPath path) {
 Asset asset = this->get(path);
 if (asset != nullptr) {
 this->unload(asset);
 }
 }

 void unload(Asset asset) {
 int int0 = asset.rmRef();

 assert int0 >= 0;

 if (int0 == 0 && this->m_is_unload_enabled) {
 this->doUnload(asset);
 }
 }

 void reload(AssetPath path) {
 Asset asset = this->get(path);
 if (asset != nullptr) {
 this->reload(asset);
 }
 }

 void reload(Asset asset) {
 this->reload(asset, nullptr);
 }

 void reload(Asset asset, AssetManager.AssetParams params) {
 this->doUnload(asset);
 this->doLoad(asset, params);
 }

 void enableUnload(bool enable) {
 this->m_is_unload_enabled = enable;
 if (enable) {
 this->m_assets.forEachValue(asset -> {
 if (asset.getRefCount() == 0) {
 this->doUnload(asset);
 }

 return true;
 });
 }
 }

 void doLoad(Asset asset, AssetManager.AssetParams assetParams) {
 if (asset.m_priv.m_desired_state != Asset.State.READY) {
 asset.m_priv.m_desired_state = Asset.State.READY;
 asset.setAssetParams(assetParams);
 this->startLoading(asset);
 }
 }

 void doUnload(Asset asset) {
 if (asset.m_priv.m_task != nullptr) {
 asset.m_priv.m_task.cancel();
 asset.m_priv.m_task = nullptr;
 }

 asset.m_priv.m_desired_state = Asset.State.EMPTY;
 this->unloadData(asset);

 assert asset.m_priv.m_empty_dep_count <= 1;

 asset.m_priv.m_empty_dep_count = 1;
 asset.m_priv.m_failed_dep_count = 0;
 asset.m_priv.checkState();
 }

 void onStateChanged(Asset.State old_state, Asset.State new_state, Asset asset) {
 }

 void startLoading(Asset asset) {
 if (asset.m_priv.m_task == nullptr) {
 asset.m_priv.m_task = new AssetTask_LoadFromFileAsync(asset, false);
 asset.m_priv.m_task.execute();
 }
 }

 void onLoadingSucceeded(Asset asset) {
 asset.m_priv.onLoadingSucceeded();
 }

 void onLoadingFailed(Asset asset) {
 asset.m_priv.onLoadingFailed();
 }

 void setTask(Asset asset, AssetTask assetTask) {
 if (asset.m_priv.m_task != nullptr) {
 if (assetTask == nullptr) {
 asset.m_priv.m_task = nullptr;
 }
 } else {
 asset.m_priv.m_task = assetTask;
 }
 }

 bool loadDataFromFile(Asset var1, IFile var2) {
 throw RuntimeException("not implemented");
 }

 void unloadData(Asset var1) {
 }

 public AssetManager.AssetTable getAssetTable() {
 return this->m_assets;
 }

 AssetManagers getOwner() {
 return this->m_owner;
 }

 protected Asset createAsset(AssetPath var1, AssetManager.AssetParams var2);

 protected void destroyAsset(Asset var1);

 Asset get(AssetPath assetPath) {
 return this->m_assets.get(assetPath.getPath());
 }

 public static class AssetParams {
 }

 public static class AssetTable extends THashMap<String, Asset> {
 }
}
} // namespace asset
} // namespace zombie
