#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/AtlasEntry.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureFBO.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class DeadBodyAtlas {
public:
    const int ENTRY_WID;
    const int ENTRY_HGT;
    Texture tex;
   public const std::vector<AtlasEntry> EntryList;
    bool clear;

   public DeadBodyAtlas$Atlas(DeadBodyAtlas var1, int var2, int var3, int var4, int var5) {
      this.this$0 = var1;
      this.EntryList = std::make_unique<std::vector<>>();
      this.clear = true;
      this.ENTRY_WID = var4;
      this.ENTRY_HGT = var5;
      this.tex = std::make_shared<Texture>(var2, var3, 16);
      if (var1.fbo == nullptr) {
         var1.fbo = std::make_shared<TextureFBO>(this.tex, false);
      }
   }

    bool isFull() {
    int var1 = this.tex.getWidth() / this.ENTRY_WID;
    int var2 = this.tex.getHeight() / this.ENTRY_HGT;
      return this.EntryList.size() >= var1 * var2;
   }

    AtlasEntry addBody(const std::string& var1) {
    int var2 = this.tex.getWidth() / this.ENTRY_WID;
    int var3 = this.EntryList.size();
    int var4 = var3 % var2;
    int var5 = var3 / var2;
    AtlasEntry var6 = std::make_shared<AtlasEntry>();
      var6.atlas = this;
      var6.key = var1;
      var6.x = var4 * this.ENTRY_WID;
      var6.y = var5 * this.ENTRY_HGT;
      var6.w = this.ENTRY_WID;
      var6.h = this.ENTRY_HGT;
      var6.tex = this.tex.split(var1, var6.x, this.tex.getHeight() - (var6.y + this.ENTRY_HGT), var6.w, var6.h);
      var6.tex.setName(var1);
      this.EntryList.push_back(var6);
    return var6;
   }

    void addEntry(AtlasEntry var1) {
    int var2 = this.tex.getWidth() / this.ENTRY_WID;
    int var3 = this.EntryList.size();
    int var4 = var3 % var2;
    int var5 = var3 / var2;
      var1.atlas = this;
      var1.x = var4 * this.ENTRY_WID;
      var1.y = var5 * this.ENTRY_HGT;
      var1.w = this.ENTRY_WID;
      var1.h = this.ENTRY_HGT;
      var1.tex = this.tex.split(var1.key, var1.x, this.tex.getHeight() - (var1.y + this.ENTRY_HGT), var1.w, var1.h);
      var1.tex.setName(var1.key);
      this.EntryList.push_back(var1);
   }

    void Reset() {
      this.EntryList.forEach(AtlasEntry::Reset);
      this.EntryList.clear();
      if (!this.tex.isDestroyed()) {
         RenderThread.invokeOnRenderContext(() -> GL11.glDeleteTextures(this.tex.getID()));
      }

      this.tex = nullptr;
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
