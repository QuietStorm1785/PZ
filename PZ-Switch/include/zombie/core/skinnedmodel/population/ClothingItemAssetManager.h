#pragma once
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetTask_RunFileTask.h"
#include "zombie/asset/FileTask_ParseXML.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ClothingItemAssetManager : public AssetManager {
public:
 static const ClothingItemAssetManager instance =
 new ClothingItemAssetManager();

 void startLoading(Asset asset) {
 FileSystem fileSystem = asset.getAssetManager().getOwner().getFileSystem();
 FileTask_ParseXML fileTask_ParseXML = new FileTask_ParseXML(
 ClothingItemXML.class, asset.getPath().getPath(),
 object->this->onFileTaskFinished((ClothingItem)asset, object),
 fileSystem);
 AssetTask_RunFileTask assetTask_RunFileTask =
 new AssetTask_RunFileTask(fileTask_ParseXML, asset);
 this->setTask(asset, assetTask_RunFileTask);
 assetTask_RunFileTask.execute();
 }

 void onFileTaskFinished(ClothingItem clothingItem, void *object) {
 if (object instanceof ClothingItemXML clothingItemXML) {
 clothingItem.m_MaleModel = this->fixPath(clothingItemXML.m_MaleModel);
 clothingItem.m_FemaleModel = this->fixPath(clothingItemXML.m_FemaleModel);
 clothingItem.m_Static = clothingItemXML.m_Static;
 PZArrayUtil.arrayCopy(clothingItem.m_BaseTextures,
 this->fixPaths(clothingItemXML.m_BaseTextures);
 clothingItem.m_AttachBone = clothingItemXML.m_AttachBone;
 PZArrayUtil.arrayCopy(clothingItem.m_Masks, clothingItemXML.m_Masks);
 clothingItem.m_MasksFolder = this->fixPath(clothingItemXML.m_MasksFolder);
 clothingItem.m_UnderlayMasksFolder =
 this->fixPath(clothingItemXML.m_UnderlayMasksFolder);
 PZArrayUtil.arrayCopy(clothingItem.textureChoices,
 this->fixPaths(clothingItemXML.textureChoices);
 clothingItem.m_AllowRandomHue = clothingItemXML.m_AllowRandomHue;
 clothingItem.m_AllowRandomTint = clothingItemXML.m_AllowRandomTint;
 clothingItem.m_DecalGroup = clothingItemXML.m_DecalGroup;
 clothingItem.m_Shader = clothingItemXML.m_Shader;
 clothingItem.m_HatCategory = clothingItemXML.m_HatCategory;
 this->onLoadingSucceeded(clothingItem);
 } else {
 this->onLoadingFailed(clothingItem);
 }
 }

 std::string fixPath(std::string_view string) {
 return string = = nullptr ? nullptr : string.replaceAll("\\\\", "/");
 }

private
 ArrayList<String> fixPaths(ArrayList<String> arrayList) {
 if (arrayList.empty()) {
 return nullptr;
 } else {
 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 arrayList.set(int0, this->fixPath((String)arrayList.get(int0));
 }

 return arrayList;
 }
 }

 void onStateChanged(Asset.State state0, Asset.State state1, Asset asset) {
 super.onStateChanged(state0, state1, asset);
 if (state1 == Asset.State.READY) {
 OutfitManager.instance.onClothingItemStateChanged((ClothingItem)asset);
 }
 }

 Asset createAsset(AssetPath assetPath, AssetManager.AssetParams var2) {
 return new ClothingItem(assetPath, this);
 }

 void destroyAsset(Asset var1) {}
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
