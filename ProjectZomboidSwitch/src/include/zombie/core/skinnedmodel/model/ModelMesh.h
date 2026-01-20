#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/joml/Vector3f.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"
#include "zombie/core/skinnedmodel/model/ModelMesh/MeshAssetParams.h"
#include "zombie/core/skinnedmodel/model/jassimp/JAssImpImporter/LoadMode.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiScene.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelMesh : public Asset {
public:
    VertexBufferObject vb;
    const Vector3f minXYZ = std::make_shared<Vector3f>(float.MAX_VALUE);
    const Vector3f maxXYZ = std::make_shared<Vector3f>(-float.MAX_VALUE);
    SkinningData skinningData;
    SoftwareModelMesh softwareMesh;
    MeshAssetParams assetParams;
    Matrix4f m_transform;
    bool m_bHasVBO = false;
    bool bStatic;
    ModelMesh m_animationsMesh;
    std::string m_fullPath;
    static const AssetType ASSET_TYPE = std::make_shared<AssetType>("Mesh");

    public ModelMesh(AssetPath var1, AssetManager var2, MeshAssetParams var3) {
      super(var1, var2);
      this.assetParams = var3;
      this.bStatic = this.assetParams != nullptr && this.assetParams.bStatic;
      this.m_animationsMesh = this.assetParams == nullptr ? nullptr : this.assetParams.animationsMesh;
   }

    void onLoadedX(ProcessedAiScene var1) {
    LoadMode var2 = this.assetParams.bStatic ? LoadMode.StaticMesh : LoadMode.Normal;
    SkinningData var3 = this.assetParams.animationsMesh == nullptr ? nullptr : this.assetParams.animationsMesh.skinningData;
      var1.applyToMesh(this, var2, false, var3);
   }

    void onLoadedTxt(ModelTxt var1) {
    SkinningData var2 = this.assetParams.animationsMesh == nullptr ? nullptr : this.assetParams.animationsMesh.skinningData;
      ModelLoader.instance.applyToMesh(var1, this, var2);
   }

    void SetVertexBuffer(VertexBufferObject var1) {
      this.clear();
      this.vb = var1;
      this.bStatic = var1 == nullptr || var1.bStatic;
   }

    void Draw(Shader var1) {
      if (this.vb != nullptr) {
         this.vb.Draw(var1);
      }
   }

    void onBeforeReady() {
      super.onBeforeReady();
      if (this.assetParams != nullptr) {
         this.assetParams.animationsMesh = nullptr;
         this.assetParams = nullptr;
      }
   }

    bool isReady() {
      return super.isReady() && (!this.m_bHasVBO || this.vb != nullptr);
   }

    void setAssetParams(AssetParams var1) {
      this.assetParams = (MeshAssetParams)var1;
   }

    AssetType getType() {
    return ASSET_TYPE;
   }

    void clear() {
      if (this.vb != nullptr) {
         this.vb.clear();
         this.vb = nullptr;
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
