
#pragma once
#include <string>
#include <memory>
#include "zombie/asset/Asset/ObserverCallback.h"
#include "zombie/asset/Asset/PRIVATE.h"
#include "zombie/asset/Asset/State.h"
#include "zombie/asset/AssetManager/AssetParams.h"

namespace zombie::asset {

class AssetType; // Forward declaration if needed

class Asset {
public:
    using ObserverCallbackPtr = std::shared_ptr<ObserverCallback>;
    using PrivatePtr = std::shared_ptr<PRIVATE>;

    Asset(AssetPath path, AssetManager asset_manager);
    virtual ~Asset() = default;

    virtual AssetType getType() const = 0;

    State getState() const;
    bool isEmpty() const;
    bool isReady() const;
    bool isFailure() const;
    void onCreated(State state);
    int getRefCount() const;
    ObserverCallbackPtr getObserverCb();
    AssetPath getPath() const;
    AssetManager getAssetManager() const;
    virtual void onBeforeReady();
    virtual void onBeforeEmpty();
    void addDependency(Asset& asset);
    void removeDependency(Asset& asset);
    int addRef();
    int rmRef();
    virtual void setAssetParams(const AssetParams& params);

protected:
    AssetManager m_asset_manager;
    AssetPath m_path;
    int m_ref_count;
    PrivatePtr m_priv;
};

} // namespace zombie::asset
