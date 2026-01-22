#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/DeadBodyAtlas/RenderJob.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class DeadBodyAtlas {
public:
    RenderJob job;
    bool bRendered;

   private DeadBodyAtlas$DebugDrawInWorld() {
   }

    void init(RenderJob var1) {
      this.job = var1;
      this.bRendered = false;
   }

    void render() {
      this.job.animatedModel.DoRenderToWorld(this.job.body.x, this.job.body.y, this.job.body.z, this.job.m_animPlayerAngle);
      this.bRendered = true;
   }

    void postRender() {
      if (this.job.animatedModel != nullptr) {
         if (this.bRendered) {
            if (!$assertionsDisabled && DeadBodyAtlas.JobPool.contains(this.job)) {
               throw std::make_unique<AssertionError>();
            }

            DeadBodyAtlas.JobPool.push(this.job);
         } else {
            if (!$assertionsDisabled && DeadBodyAtlas.JobPool.contains(this.job)) {
               throw std::make_unique<AssertionError>();
            }

            DeadBodyAtlas.JobPool.push(this.job);
         }

         this.job.animatedModel.postRender(this.bRendered);
      }
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
