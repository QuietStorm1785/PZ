
#include "zombie/asset/AssetManager.h"
#include <iostream>

namespace zombie {
namespace asset {

void AssetManager::create(AssetType var1, AssetManagers var2) {
    var2.push_back({var1, *this});
    m_owner = var2;
}


void AssetManager::destroy() {
    for (auto& [key, asset] : m_assets) {
        if (!asset.isEmpty()) {
            std::cerr << "Leaking asset: " << asset.getPath() << std::endl;
        }
        destroyAsset(asset);
    }
}

void AssetManager::removeUnreferenced() {
    if (m_is_unload_enabled) {
        std::vector<Asset> toRemove;
        for (auto& [key, asset] : m_assets) {
            if (asset.getRefCount() == 0) {
                toRemove.push_back(asset);
            }
        }
        for (auto& asset : toRemove) {
            m_assets.erase(asset.getPath().getPath());
            destroyAsset(asset);
        }
    }
}

Asset AssetManager::load(AssetPath var1) {
    return load(var1, nullptr);
}

Asset AssetManager::load(AssetPath var1, AssetParams var2) {
    if (!var1.isValid()) return Asset();
    Asset asset = get(var1);
    if (!asset) {
        asset = createAsset(var1, var2);
        m_assets[var1.getPath()] = asset;
    }
    if (asset.isEmpty() && asset.m_priv->m_desired_state == State::EMPTY) {
        doLoad(asset, var2);
    }
    asset.addRef();
    return asset;
}

void AssetManager::load(Asset var1) {
    if (var1.isEmpty() && var1.m_priv->m_desired_state == State::EMPTY) {
        doLoad(var1, nullptr);
    }
    var1.addRef();
}

void AssetManager::unload(AssetPath var1) {
    Asset asset = get(var1);
    if (asset) {
        unload(asset);
    }
}

void AssetManager::unload(Asset var1) {
    int ref = var1.rmRef();
    // assert(ref >= 0);
    if (ref == 0 && m_is_unload_enabled) {
        doUnload(var1);
    }
}

void AssetManager::reload(AssetPath var1) {
    Asset asset = get(var1);
    if (asset) {
        reload(asset);
    }
}

void AssetManager::reload(Asset var1) {
    reload(var1, nullptr);
}

void AssetManager::reload(Asset var1, AssetParams var2) {
    doUnload(var1);
    doLoad(var1, var2);
}

void AssetManager::enableUnload(bool var1) {
    m_is_unload_enabled = var1;
    if (var1) {
        for (auto& [key, asset] : m_assets) {
            if (asset.getRefCount() == 0) {
                doUnload(asset);
            }
        }
    }
}

void AssetManager::doLoad(Asset var1, AssetParams var2) {
    if (var1.m_priv->m_desired_state != State::READY) {
        var1.m_priv->m_desired_state = State::READY;
        var1.setAssetParams(var2);
        startLoading(var1);
    }
}

void AssetManager::doUnload(Asset var1) {
    if (var1.m_priv->m_task) {
        var1.m_priv->m_task->cancel();
        var1.m_priv->m_task = nullptr;
    }
    var1.m_priv->m_desired_state = State::EMPTY;
    unloadData(var1);
    // assert(var1.m_priv->m_empty_dep_count <= 1);
    var1.m_priv->m_empty_dep_count = 1;
    var1.m_priv->m_failed_dep_count = 0;
    var1.m_priv->checkState();
}

void AssetManager::onStateChanged(State var1, State var2, Asset var3) {
    // No-op by default
}

void AssetManager::startLoading(Asset var1) {
    if (!var1.m_priv->m_task) {
        var1.m_priv->m_task = std::make_shared<AssetTask_LoadFromFileAsync>(var1, false);
        var1.m_priv->m_task->execute();
    }
}

void AssetManager::onLoadingSucceeded(Asset var1) {
    var1.m_priv->onLoadingSucceeded();
}

void AssetManager::onLoadingFailed(Asset var1) {
    var1.m_priv->onLoadingFailed();
}

void AssetManager::setTask(Asset var1, AssetTask var2) {
    if (var1.m_priv->m_task) {
        if (!var2) {
            var1.m_priv->m_task = nullptr;
        }
    } else {
        var1.m_priv->m_task = var2;
    }
}


bool AssetManager::loadDataFromFile(Asset asset, IFile file) {
    if (!file) {
        std::cerr << "loadDataFromFile: file is null for asset " << asset.getPath() << std::endl;
        return false;
    }
    int64_t size = file->size();
    if (size <= 0) {
        std::cerr << "loadDataFromFile: file is empty or error for asset " << asset.getPath() << std::endl;
        return false;
    }
    std::vector<uint8_t> buffer(static_cast<size_t>(size));
    if (!file->read(buffer.data(), size)) {
        std::cerr << "loadDataFromFile: failed to read file for asset " << asset.getPath() << std::endl;
        return false;
    }
    // Optionally, store buffer in asset or process as needed
    std::cout << "Loaded " << size << " bytes for asset: " << asset.getPath() << std::endl;
    return true;
}


void AssetManager::unloadData(Asset asset) {
    // Attempt to close and release any file system resources associated with the asset
    // If the asset has a file or stream, close and release it
    auto file = asset.getInputFile(); // Hypothetical method, implement as needed
    if (file) {
        file->close();
        file->release();
        std::cout << "Closed and released file for asset: " << asset.getPath() << std::endl;
    }
    // If the asset has an input stream, close it (if applicable)
    auto stream = asset.getInputStream();
    if (stream) {
        stream->close();
        std::cout << "Closed input stream for asset: " << asset.getPath() << std::endl;
    }
    // Log the unload operation
    std::cout << "Unloading asset: " << asset.getPath() << std::endl;
}

AssetTable AssetManager::getAssetTable() {
    return m_assets;
}

AssetManagers AssetManager::getOwner() {
    return m_owner;
}

Asset AssetManager::get(AssetPath var1) {
    auto it = m_assets.find(var1.getPath());
    if (it != m_assets.end()) {
        return it->second;
    }
    return Asset();
}

} // namespace asset
} // namespace zombie
