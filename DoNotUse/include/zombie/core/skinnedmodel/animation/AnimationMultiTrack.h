#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationMultiTrack {
public:
   private const std::vector<AnimationTrack> m_tracks = std::make_unique<std::vector<>>();
   private static const std::vector<AnimationTrack> tempTracks = std::make_unique<std::vector<>>();

    AnimationTrack findTrack(const std::string& var1) {
    int var2 = 0;

      for (int var3 = this.m_tracks.size(); var2 < var3; var2++) {
    AnimationTrack var4 = this.m_tracks.get(var2);
         if (var4.name == var1)) {
    return var4;
         }
      }

    return nullptr;
   }

    void addTrack(AnimationTrack var1) {
      this.m_tracks.push_back(var1);
   }

    void removeTrack(AnimationTrack var1) {
    int var2 = this.getIndexOfTrack(var1);
      if (var2 > -1) {
         this.removeTrackAt(var2);
      }
   }

    void removeTracks(List<AnimationTrack> var1) {
      tempTracks.clear();
      tempTracks.addAll(var1);

      for (int var2 = 0; var2 < tempTracks.size(); var2++) {
         this.removeTrack(tempTracks.get(var2));
      }
   }

    void removeTrackAt(int var1) {
      this.m_tracks.remove(var1).release();
   }

    int getIndexOfTrack(AnimationTrack var1) {
      if (var1 == nullptr) {
         return -1;
      } else {
    int var2 = -1;

         for (int var3 = 0; var3 < this.m_tracks.size(); var3++) {
    AnimationTrack var4 = this.m_tracks.get(var3);
            if (var4 == var1) {
               var2 = var3;
               break;
            }
         }

    return var2;
      }
   }

    void Update(float var1) {
      for (int var2 = 0; var2 < this.m_tracks.size(); var2++) {
    AnimationTrack var3 = this.m_tracks.get(var2);
         var3.Update(var1);
         if (var3.CurrentClip == nullptr) {
            this.removeTrackAt(var2);
            var2--;
         }
      }
   }

    float getDuration() {
    float var1 = 0.0F;

      for (int var2 = 0; var2 < this.m_tracks.size(); var2++) {
    AnimationTrack var3 = this.m_tracks.get(var2);
    float var4 = var3.getDuration();
         if (var3.CurrentClip != nullptr && var4 > var1) {
            var1 = var4;
         }
      }

    return var1;
   }

    void reset() {
    int var1 = 0;

      for (int var2 = this.m_tracks.size(); var1 < var2; var1++) {
    AnimationTrack var3 = this.m_tracks.get(var1);
         var3.reset();
      }

      AnimationPlayer.releaseTracks(this.m_tracks);
      this.m_tracks.clear();
   }

   public List<AnimationTrack> getTracks() {
      return this.m_tracks;
   }

    int getTrackCount() {
      return this.m_tracks.size();
   }

    AnimationTrack getTrackAt(int var1) {
      return this.m_tracks.get(var1);
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
