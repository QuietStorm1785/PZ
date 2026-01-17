#pragma once
#include "org/joml/Matrix4f.h"
#include "org/joml/Vector3f.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"
#include "zombie/core/skinnedmodel/model/jassimp/JAssImpImporter.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiScene.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by LEMMYATI on 03/01/14.
 */
class ModelMesh : public Asset {
public:
  VertexBufferObject vb;
  const Vector3f minXYZ = new Vector3f(Float.MAX_VALUE);
  const Vector3f maxXYZ = new Vector3f(-Float.MAX_VALUE);
  SkinningData skinningData;
  SoftwareModelMesh softwareMesh;
public
  ModelMesh.MeshAssetParams assetParams;
  Matrix4f m_transform;
  bool m_bHasVBO = false;
  bool bStatic;
  ModelMesh m_animationsMesh;
  std::string m_fullPath;
  static const AssetType ASSET_TYPE = new AssetType("Mesh");

public
  ModelMesh(AssetPath path, AssetManager manager,
            ModelMesh.MeshAssetParams params) {
    super(path, manager);
    this.assetParams = params;
    this.bStatic = this.assetParams != nullptr && this.assetParams.bStatic;
    this.m_animationsMesh =
        this.assetParams == nullptr ? nullptr : this.assetParams.animationsMesh;
  }

  void onLoadedX(ProcessedAiScene processedAiScene) {
    JAssImpImporter.LoadMode loadMode =
        this.assetParams.bStatic ? JAssImpImporter.LoadMode.StaticMesh
                                 : JAssImpImporter.LoadMode.Normal;
    SkinningData skinningDatax =
        this.assetParams.animationsMesh == null
            ? null
            : this.assetParams.animationsMesh.skinningData;
    processedAiScene.applyToMesh(this, loadMode, false, skinningDatax);
  }

  void onLoadedTxt(ModelTxt modelTxt) {
    SkinningData skinningDatax =
        this.assetParams.animationsMesh == null
            ? null
            : this.assetParams.animationsMesh.skinningData;
    ModelLoader.instance.applyToMesh(modelTxt, this, skinningDatax);
  }

  void SetVertexBuffer(VertexBufferObject _vb) {
    this.clear();
    this.vb = _vb;
    this.bStatic = _vb == nullptr || _vb.bStatic;
  }

  void Draw(Shader shader) {
    if (this.vb != nullptr) {
      this.vb.Draw(shader);
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

  void setAssetParams(AssetManager.AssetParams params) {
    this.assetParams = (ModelMesh.MeshAssetParams)params;
  }

  AssetType getType() { return ASSET_TYPE; }

  void clear() {
    if (this.vb != nullptr) {
      this.vb.clear();
      this.vb = nullptr;
    }
  }

public
  static final class MeshAssetParams extends AssetManager.AssetParams {
    bool bStatic;
    ModelMesh animationsMesh;
  }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
