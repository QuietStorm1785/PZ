#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset/State.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/asset/AssetManager/AssetTable.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/fileSystem/IFile.h"

namespace zombie {
namespace asset {


class AssetManager {
public:
    const AssetTable m_assets = new AssetTable();
    AssetManagers m_owner;
    bool m_is_unload_enabled = false;

    void create(AssetType var1, AssetManagers var2) {
      var2.add(var1, this);
      this.m_owner = var2;
   }

    void destroy() {
      this.m_assets.forEachValue(var1 -> {
         if (!var1.isEmpty()) {
            DebugLog.Asset.println("Leaking asset " + var1.getPath());
         }

         this.destroyAsset(var1);
    return true;
      });
   }

    void removeUnreferenced() {
      if (this.m_is_unload_enabled) {
    std::vector var1 = new ArrayList();
         this.m_assets.forEachValue(var1x -> {
            if (var1x.getRefCount() == 0) {
               var1.add(var1x);
            }

    return true;
         });

    for (auto& var3 : var1)            this.m_assets.remove(var3.getPath());
            this.destroyAsset(var3);
         }
      }
   }

    Asset load(AssetPath var1) {
      return this.load(var1, nullptr);
   }

    Asset load(AssetPath var1, AssetParams var2) {
      if (!var1.isValid()) {
    return null;
      } else {
    Asset var3 = this.get(var1);
         if (var3 == nullptr) {
            var3 = this.createAsset(var1, var2);
            this.m_assets.put(var1.getPath(), var3);
         }

         if (var3.isEmpty() && var3.m_priv.m_desired_state == State.EMPTY) {
            this.doLoad(var3, var2);
         }

         var3.addRef();
    return var3;
      }
   }

    void load(Asset var1) {
      if (var1.isEmpty() && var1.m_priv.m_desired_state == State.EMPTY) {
         this.doLoad(var1, nullptr);
      }

      var1.addRef();
   }

    void unload(AssetPath var1) {
    Asset var2 = this.get(var1);
      if (var2 != nullptr) {
         this.unload(var2);
      }
   }

    void unload(Asset var1) {
    int var2 = var1.rmRef();

      assert var2 >= 0;

      if (var2 == 0 && this.m_is_unload_enabled) {
         this.doUnload(var1);
      }
   }

    void reload(AssetPath var1) {
    Asset var2 = this.get(var1);
      if (var2 != nullptr) {
         this.reload(var2);
      }
   }

    void reload(Asset var1) {
      this.reload(var1, nullptr);
   }

    void reload(Asset var1, AssetParams var2) {
      this.doUnload(var1);
      this.doLoad(var1, var2);
   }

    void enableUnload(bool var1) {
      this.m_is_unload_enabled = var1;
      if (var1) {
         this.m_assets.forEachValue(var1x -> {
            if (var1x.getRefCount() == 0) {
               this.doUnload(var1x);
            }

    return true;
         });
      }
   }

    void doLoad(Asset var1, AssetParams var2) {
      if (var1.m_priv.m_desired_state != State.READY) {
         var1.m_priv.m_desired_state = State.READY;
         var1.setAssetParams(var2);
         this.startLoading(var1);
      }
   }

    void doUnload(Asset var1) {
      if (var1.m_priv.m_task != nullptr) {
         var1.m_priv.m_task.cancel();
         var1.m_priv.m_task = nullptr;
      }

      var1.m_priv.m_desired_state = State.EMPTY;
      this.unloadData(var1);

      assert var1.m_priv.m_empty_dep_count <= 1;

      var1.m_priv.m_empty_dep_count = 1;
      var1.m_priv.m_failed_dep_count = 0;
      var1.m_priv.checkState();
   }

    void onStateChanged(State var1, State var2, Asset var3) {
   }

    void startLoading(Asset var1) {
      if (var1.m_priv.m_task == nullptr) {
         var1.m_priv.m_task = new AssetTask_LoadFromFileAsync(var1, false);
         var1.m_priv.m_task.execute();
      }
   }

    void onLoadingSucceeded(Asset var1) {
      var1.m_priv.onLoadingSucceeded();
   }

    void onLoadingFailed(Asset var1) {
      var1.m_priv.onLoadingFailed();
   }

    void setTask(Asset var1, AssetTask var2) {
      if (var1.m_priv.m_task != nullptr) {
         if (var2 == nullptr) {
            var1.m_priv.m_task = nullptr;
         }
      } else {
         var1.m_priv.m_task = var2;
      }
   }

    bool loadDataFromFile(Asset var1, IFile var2) {
      throw new RuntimeException("not implemented");
   }

    void unloadData(Asset var1) {
   }

    AssetTable getAssetTable() {
      return this.m_assets;
   }

    AssetManagers getOwner() {
      return this.m_owner;
   }

   protected abstract Asset createAsset(AssetPath var1, AssetParams var2);

   protected abstract void destroyAsset(Asset var1);

    Asset get(AssetPath var1) {
      return (Asset)this.m_assets.get(var1.getPath());
   }
}
} // namespace asset
} // namespace zombie
