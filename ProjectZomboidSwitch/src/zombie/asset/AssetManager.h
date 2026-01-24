
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cstdint>
#include "zombie/asset/Asset/State.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/asset/AssetManager/AssetTable.h"
#include "zombie/fileSystem/IFile.h"

namespace zombie::asset {

class Asset;
class AssetType;
class AssetManagers;

class AssetManager {
public:
    using AssetTablePtr = std::shared_ptr<AssetTable>;

    AssetManager();
    virtual ~AssetManager() = default;

    void create(const AssetType& type, const std::shared_ptr<AssetManagers>& owner);
    virtual void destroy();
    virtual void removeUnreferenced();
    virtual Asset load(const AssetPath& path);
    virtual Asset load(const AssetPath& path, const std::shared_ptr<AssetParams>& params);
    virtual void load(const Asset& asset);
    virtual void unload(const AssetPath& path);
    virtual void unload(const Asset& asset);
    virtual void reload(const AssetPath& path);
    virtual void reload(const Asset& asset);
    virtual void reload(const Asset& asset, const std::shared_ptr<AssetParams>& params);
    virtual void enableUnload(bool enable);
    virtual void doLoad(const Asset& asset, const std::shared_ptr<AssetParams>& params);
    virtual void doUnload(const Asset& asset);
    virtual void onStateChanged(State oldState, State newState, const Asset& asset);
    virtual void startLoading(const Asset& asset);
    virtual void onLoadingSucceeded(const Asset& asset);
    virtual void onLoadingFailed(const Asset& asset);
    virtual void setTask(const Asset& asset, const std::shared_ptr<class AssetTask>& task);
    virtual bool loadDataFromFile(const Asset& asset, const std::shared_ptr<fileSystem::IFile>& file);
    virtual void unloadData(const Asset& asset);
    AssetTablePtr getAssetTable() const;
    std::shared_ptr<AssetManagers> getOwner() const;
    virtual Asset get(const AssetPath& path) const;

protected:
    virtual Asset createAsset(const AssetPath& path, const std::shared_ptr<AssetParams>& params) = 0;
    virtual void destroyAsset(const Asset& asset) = 0;

    AssetTablePtr m_assets;
    std::shared_ptr<AssetManagers> m_owner;
    bool m_is_unload_enabled = false;
};

} // namespace zombie::asset
