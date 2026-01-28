#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include "org/lwjgl/util/glu/GLU.h"
#include "zombie/characters/AttachedItems/AttachedModelName.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/Atlas.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/AtlasEntry.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/BodyParams.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/BodyTexture.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/BodyTextureDrawer.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/CharacterTextureVisual.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/Checksummer.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/ClearAtlasTexture.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/DebugDrawInWorld.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/RenderJob.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoMannequin.h"
#include "zombie/popman/ObjectPool.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {


class DeadBodyAtlas {
public:
    static const int ATLAS_SIZE = 1024;
    TextureFBO fbo;
    static const DeadBodyAtlas instance = std::make_shared<DeadBodyAtlas>();
    static const Vector2 tempVector2 = std::make_shared<Vector2>();
   private const std::unordered_map<std::string, BodyTexture> EntryMap = std::make_unique<std::unordered_map<>>();
   private const std::vector<Atlas> AtlasList = std::make_unique<std::vector<>>();
    const BodyParams bodyParams = std::make_shared<BodyParams>();
    int updateCounter = -1;
    const Checksummer checksummer = std::make_shared<Checksummer>();
   private static const std::stack<RenderJob> JobPool = std::make_unique<std::stack<>>();
   private const DebugDrawInWorld[] debugDrawInWorld = new DebugDrawInWorld[3];
    long debugDrawTime;
   private const std::vector<RenderJob> RenderJobs = std::make_unique<std::vector<>>();
    const CharacterTextureVisual characterTextureVisualFemale = std::make_shared<CharacterTextureVisual>(true);
    const CharacterTextureVisual characterTextureVisualMale = std::make_shared<CharacterTextureVisual>(false);
    const CharacterTextures characterTexturesFemale = std::make_shared<CharacterTextures>();
    const CharacterTextures characterTexturesMale = std::make_shared<CharacterTextures>();
   private const ObjectPool<BodyTextureDrawer> bodyTextureDrawerPool = std::make_shared<ObjectPool>(BodyTextureDrawer::new);

    void lightingUpdate(int var1, bool var2) {
      if (var1 != this.updateCounter && var2) {
         this.updateCounter = var1;
      }
   }

    BodyTexture getBodyTexture(IsoDeadBody var1) {
      this.bodyParams.init(var1);
      return this.getBodyTexture(this.bodyParams);
   }

    BodyTexture getBodyTexture(IsoZombie var1) {
      this.bodyParams.init(var1);
      return this.getBodyTexture(this.bodyParams);
   }

    BodyTexture getBodyTexture(IsoMannequin var1) {
      this.bodyParams.init(var1);
      return this.getBodyTexture(this.bodyParams);
   }

    BodyTexture getBodyTexture(bool var1, const std::string& var2, const std::string& var3, IsoDirections var4, int var5, float var6) {
    CharacterTextures var7 = var1 ? this.characterTexturesFemale : this.characterTexturesMale;
    BodyTexture var8 = var7.getTexture(var2, var3, var4, var5);
      if (var8 != nullptr) {
    return var8;
      } else {
         this.bodyParams.init(var1 ? this.characterTextureVisualFemale : this.characterTextureVisualMale, var4, var2, var3, var6);
         this.bodyParams.variables.put("zombieWalkType", "1");
    BodyTexture var9 = this.getBodyTexture(this.bodyParams);
         var7.addTexture(var2, var3, var4, var5, var9);
    return var9;
      }
   }

    BodyTexture getBodyTexture(BodyParams var1) {
    std::string var2 = this.getBodyKey(var1);
    BodyTexture var3 = this.EntryMap.get(var2);
      if (var3 != nullptr) {
    return var3;
      } else {
    AtlasEntry var4 = std::make_shared<AtlasEntry>();
         var4.key = var2;
         var4.lightKey = this.getLightKey(var1);
         var4.updateCounter = this.updateCounter;
         var3 = std::make_unique<BodyTexture>();
         var3.entry = var4;
         this.EntryMap.put(var2, var3);
         this.RenderJobs.push_back(RenderJob.getNew().init(var1, var4));
    return var3;
      }
   }

    void checkLights(Texture var1, IsoDeadBody var2) {
      if (var1 != nullptr) {
    BodyTexture var3 = this.EntryMap.get(var1.getName());
         if (var3 != nullptr) {
    AtlasEntry var4 = var3.entry;
            if (var4 != nullptr && var4.tex == var1) {
               if (var4.updateCounter != this.updateCounter) {
                  var4.updateCounter = this.updateCounter;
                  this.bodyParams.init(var2);
    std::string var5 = this.getLightKey(this.bodyParams);
                  if (!var4.lightKey == var5)) {
                     this.EntryMap.remove(var4.key);
                     var4.key = this.getBodyKey(this.bodyParams);
                     var4.lightKey = var5;
                     var1.setNameOnly(var4.key);
                     this.EntryMap.put(var4.key, var3);
    RenderJob var6 = RenderJob.getNew().init(this.bodyParams, var4);
                     var6.bClearThisSlotOnly = true;
                     this.RenderJobs.push_back(var6);
                     this.render();
                  }
               }
            }
         }
      }
   }

    void checkLights(Texture var1, IsoZombie var2) {
      if (var1 != nullptr) {
    BodyTexture var3 = this.EntryMap.get(var1.getName());
         if (var3 != nullptr) {
    AtlasEntry var4 = var3.entry;
            if (var4 != nullptr && var4.tex == var1) {
               if (var4.updateCounter != this.updateCounter) {
                  var4.updateCounter = this.updateCounter;
                  this.bodyParams.init(var2);
    std::string var5 = this.getLightKey(this.bodyParams);
                  if (!var4.lightKey == var5)) {
                     this.EntryMap.remove(var4.key);
                     var4.key = this.getBodyKey(this.bodyParams);
                     var4.lightKey = var5;
                     var1.setNameOnly(var4.key);
                     this.EntryMap.put(var4.key, var3);
    RenderJob var6 = RenderJob.getNew().init(this.bodyParams, var4);
                     var6.bClearThisSlotOnly = true;
                     this.RenderJobs.push_back(var6);
                     this.render();
                  }
               }
            }
         }
      }
   }

    void assignEntryToAtlas(AtlasEntry var1, int var2, int var3) {
      if (var1.atlas == nullptr) {
         for (int var4 = 0; var4 < this.AtlasList.size(); var4++) {
    Atlas var5 = this.AtlasList.get(var4);
            if (!var5.isFull() && var5.ENTRY_WID == var2 && var5.ENTRY_HGT == var3) {
               var5.addEntry(var1);
               return;
            }
         }

    Atlas var6 = std::make_shared<Atlas>(this, 1024, 1024, var2, var3);
         var6.addEntry(var1);
         this.AtlasList.push_back(var6);
      }
   }

    std::string getBodyKey(BodyParams var1) {
      if (var1.humanVisual == this.characterTextureVisualFemale.humanVisual) {
         return "SZF_" + var1.animSetName + "_" + var1.stateName + "_" + var1.dir + "_" + var1.trackTime;
      } else if (var1.humanVisual == this.characterTextureVisualMale.humanVisual) {
         return "SZM_" + var1.animSetName + "_" + var1.stateName + "_" + var1.dir + "_" + var1.trackTime;
      } else {
         try {
            this.checksummer.reset();
    HumanVisual var2 = var1.humanVisual;
            this.checksummer.update((byte)var1.dir.index());
            this.checksummer.update((int)(PZMath.wrap(var1.angle, 0.0F, (float) (Math.PI * 2)) * (180.0F / (float)Math.PI)));
            this.checksummer.update(var2.getHairModel());
            this.checksummer.update(var2.getBeardModel());
            this.checksummer.update(var2.getSkinColor());
            this.checksummer.update(var2.getSkinTexture());
            this.checksummer.update((int)(var2.getTotalBlood() * 100.0F));
            this.checksummer.update(var1.primaryHandItem);
            this.checksummer.update(var1.secondaryHandItem);

            for (int var3 = 0; var3 < var1.attachedModelNames.size(); var3++) {
    AttachedModelName var4 = var1.attachedModelNames.get(var3);
               this.checksummer.update(var4.attachmentNameSelf);
               this.checksummer.update(var4.attachmentNameParent);
               this.checksummer.update(var4.modelName);
               this.checksummer.update((int)(var4.bloodLevel * 100.0F));
            }

            this.checksummer.update(var1.bFemale);
            this.checksummer.update(var1.bZombie);
            this.checksummer.update(var1.bSkeleton);
            this.checksummer.update(var1.animSetName);
            this.checksummer.update(var1.stateName);
    ItemVisuals var9 = var1.itemVisuals;

            for (int var10 = 0; var10 < var9.size(); var10++) {
    ItemVisual var5 = (ItemVisual)var9.get(var10);
    ClothingItem var6 = var5.getClothingItem();
               if (var6 != nullptr) {
                  this.checksummer.update(var5.getBaseTexture(var6));
                  this.checksummer.update(var5.getTextureChoice(var6));
                  this.checksummer.update(var5.getTint(var6));
                  this.checksummer.update(var6.getModel(var2.isFemale()));
                  this.checksummer.update((int)(var5.getTotalBlood() * 100.0F));
               }
            }

            this.checksummer.update(var1.fallOnFront);
            this.checksummer.update(var1.bStanding);
            this.checksummer.update(var1.bOutside);
            this.checksummer.update(var1.bRoom);
    float var11 = (int)(var1.ambient.r * 10.0F) / 10.0F;
            this.checksummer.update((byte)(var11 * 255.0F));
    float var12 = (int)(var1.ambient.g * 10.0F) / 10.0F;
            this.checksummer.update((byte)(var12 * 255.0F));
    float var13 = (int)(var1.ambient.b * 10.0F) / 10.0F;
            this.checksummer.update((byte)(var13 * 255.0F));
            this.checksummer.update((int)var1.trackTime);

            for (int var7 = 0; var7 < var1.lights.length; var7++) {
               this.checksummer.update(var1.lights[var7], var1.x, var1.y, var1.z);
            }

            return this.checksummer.checksumToString();
         } catch (Throwable var8) {
            ExceptionLogger.logException(var8);
            return "bogus";
         }
      }
   }

    std::string getLightKey(BodyParams var1) {
      try {
         this.checksummer.reset();
         this.checksummer.update(var1.bOutside);
         this.checksummer.update(var1.bRoom);
    float var2 = (int)(var1.ambient.r * 10.0F) / 10.0F;
         this.checksummer.update((byte)(var2 * 255.0F));
    float var3 = (int)(var1.ambient.g * 10.0F) / 10.0F;
         this.checksummer.update((byte)(var3 * 255.0F));
    float var4 = (int)(var1.ambient.b * 10.0F) / 10.0F;
         this.checksummer.update((byte)(var4 * 255.0F));

         for (int var5 = 0; var5 < var1.lights.length; var5++) {
            this.checksummer.update(var1.lights[var5], var1.x, var1.y, var1.z);
         }

         return this.checksummer.checksumToString();
      } catch (Throwable var6) {
         ExceptionLogger.logException(var6);
         return "bogus";
      }
   }

    void render() {
      for (int var1 = 0; var1 < this.AtlasList.size(); var1++) {
    Atlas var2 = this.AtlasList.get(var1);
         if (var2.clear) {
            SpriteRenderer.instance.drawGeneric(std::make_shared<ClearAtlasTexture>(var2));
         }
      }

      if (!this.RenderJobs.empty()) {
         for (int var3 = 0; var3 < this.RenderJobs.size(); var3++) {
    RenderJob var4 = this.RenderJobs.get(var3);
            if (var4.done != 1 || var4.renderRefCount <= 0) {
               if (var4.done == 1 && var4.renderRefCount == 0) {
                  this.RenderJobs.remove(var3--);

                  assert !JobPool.contains(var4);

                  JobPool.push(var4);
               } else if (var4.renderMain()) {
                  var4.renderRefCount++;
                  SpriteRenderer.instance.drawGeneric(var4);
               }
            }
         }
      }
   }

    void renderDebug() {
      if (Core.bDebug && DebugOptions.instance.DeadBodyAtlasRender.getValue()) {
         if (JobPool.empty()) {
            return;
         }

         if (JobPool.get(JobPool.size() - 1).entry.atlas == nullptr) {
            return;
         }

         if (this.debugDrawInWorld[0] == nullptr) {
            for (int var1 = 0; var1 < this.debugDrawInWorld.length; var1++) {
               this.debugDrawInWorld[var1] = std::make_unique<DebugDrawInWorld>();
            }
         }

    int var5 = SpriteRenderer.instance.getMainStateIndex();
    long var2 = System.currentTimeMillis();
         if (var2 - this.debugDrawTime < 500L) {
    RenderJob var4 = JobPool.pop();
            var4.done = 0;
            var4.bClearThisSlotOnly = true;
            this.RenderJobs.push_back(var4);
         } else if (var2 - this.debugDrawTime < 1000L) {
    RenderJob var6 = JobPool.pop();
            var6.done = 0;
            var6.renderMain();
            this.debugDrawInWorld[var5].init(var6);
            SpriteRenderer.instance.drawGeneric(this.debugDrawInWorld[var5]);
         } else {
            this.debugDrawTime = var2;
         }
      }
   }

    void renderUI() {
      if (Core.bDebug && DebugOptions.instance.DeadBodyAtlasRender.getValue()) {
    int var1 = 512 / Core.TileScale;
    int var2 = 0;
    int var3 = 0;

         for (int var4 = 0; var4 < this.AtlasList.size(); var4++) {
    Atlas var5 = this.AtlasList.get(var4);
            SpriteRenderer.instance.renderi(nullptr, var2, var3, var1, var1, 1.0F, 1.0F, 1.0F, 0.75F, nullptr);
            SpriteRenderer.instance.renderi(var5.tex, var2, var3, var1, var1, 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
    float var6 = (float)var1 / var5.tex.getWidth();

            for (int var7 = 0; var7 <= var5.tex.getWidth() / var5.ENTRY_WID; var7++) {
               SpriteRenderer.instance
                  .renderline(
                     nullptr, (int)(var2 + var7 * var5.ENTRY_WID * var6), var3, (int)(var2 + var7 * var5.ENTRY_WID * var6), var3 + var1, 0.5F, 0.5F, 0.5F, 1.0F
                  );
            }

            for (int var8 = 0; var8 <= var5.tex.getHeight() / var5.ENTRY_HGT; var8++) {
               SpriteRenderer.instance
                  .renderline(
                     nullptr,
                     var2,
                     (int)(var3 + var1 - var8 * var5.ENTRY_HGT * var6),
                     var2 + var1,
                     (int)(var3 + var1 - var8 * var5.ENTRY_HGT * var6),
                     0.5F,
                     0.5F,
                     0.5F,
                     1.0F
                  );
            }

            var3 += var1;
            if (var3 + var1 > Core.getInstance().getScreenHeight()) {
               var3 = 0;
               var2 += var1;
            }
         }

         SpriteRenderer.instance.renderi(nullptr, var2, var3, var1, var1, 1.0F, 1.0F, 1.0F, 0.5F, nullptr);
         SpriteRenderer.instance.renderi((Texture)ModelManager.instance.bitmap.getTexture(), var2, var3, var1, var1, 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
      }
   }

    void Reset() {
      if (this.fbo != nullptr) {
         this.fbo.destroyLeaveTexture();
         this.fbo = nullptr;
      }

      this.AtlasList.forEach(Atlas::Reset);
      this.AtlasList.clear();
      this.EntryMap.clear();
      this.characterTexturesFemale.clear();
      this.characterTexturesMale.clear();
      JobPool.forEach(RenderJob::Reset);
      JobPool.clear();
      this.RenderJobs.clear();
   }

    void toBodyAtlas(RenderJob var1) {
      GL11.glPushAttrib(2048);
      if (this.fbo.getTexture() != var1.entry.atlas.tex) {
         this.fbo.setTexture(var1.entry.atlas.tex);
      }

      this.fbo.startDrawing();
      GL11.glViewport(0, 0, this.fbo.getWidth(), this.fbo.getHeight());
      GL11.glMatrixMode(5889);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
    int var2 = var1.entry.atlas.tex.getWidth();
    int var3 = var1.entry.atlas.tex.getHeight();
      GLU.gluOrtho2D(0.0F, var2, var3, 0.0F);
      GL11.glMatrixMode(5888);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
      GL11.glEnable(3553);
      GL11.glDisable(3089);
      if (var1.entry.atlas.clear) {
         GL11.glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
         GL11.glClear(16640);
         GL11.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
         var1.entry.atlas.clear = false;
      }

      if (var1.bClearThisSlotOnly) {
         GL11.glEnable(3089);
         GL11.glScissor(var1.entry.x, 1024 - var1.entry.y - var1.entry.h, var1.entry.w, var1.entry.h);
         GL11.glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
         GL11.glClear(16640);
         GL11.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    int var4 = SpriteRenderer.instance.getRenderingPlayerIndex();
    int var5 = var4 != 0 && var4 != 2 ? Core.getInstance().getOffscreenTrueWidth() / 2 : 0;
    int var6 = var4 != 0 && var4 != 1 ? Core.getInstance().getOffscreenTrueHeight() / 2 : 0;
    int var7 = Core.getInstance().getOffscreenTrueWidth();
    int var8 = Core.getInstance().getOffscreenTrueHeight();
         if (IsoPlayer.numPlayers > 1) {
            var7 /= 2;
         }

         if (IsoPlayer.numPlayers > 2) {
            var8 /= 2;
         }

         GL11.glScissor(var5, var6, var7, var8);
         GL11.glDisable(3089);
      }

    int var9 = ModelManager.instance.bitmap.getTexture().getWidth() / 8 * Core.TileScale;
    int var10 = ModelManager.instance.bitmap.getTexture().getHeight() / 8 * Core.TileScale;
    int var11 = var1.entry.x - (var9 - var1.entry.atlas.ENTRY_WID) / 2;
    int var12 = var1.entry.y - (var10 - var1.entry.atlas.ENTRY_HGT) / 2;
      ModelManager.instance.bitmap.getTexture().bind();
      GL11.glBegin(7);
      GL11.glColor3f(1.0F, 1.0F, 1.0F);
      GL11.glTexCoord2f(0.0F, 0.0F);
      GL11.glVertex2i(var11, var12);
      GL11.glTexCoord2f(1.0F, 0.0F);
      GL11.glVertex2i(var11 + var9, var12);
      GL11.glTexCoord2f(1.0F, 1.0F);
      GL11.glVertex2i(var11 + var9, var12 + var10);
      GL11.glTexCoord2f(0.0F, 1.0F);
      GL11.glVertex2i(var11, var12 + var10);
      GL11.glEnd();
      Texture.lastTextureID = 0;
      GL11.glBindTexture(3553, 0);
      this.fbo.endDrawing();
      GL11.glEnable(3089);
      GL11.glMatrixMode(5889);
      GL11.glPopMatrix();
      GL11.glMatrixMode(5888);
      GL11.glPopMatrix();
      GL11.glPopAttrib();
      var1.entry.ready = true;
      var1.done = 1;
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
