#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by LEMMYMAIN on 28/02/2015.
 */
class AnimationMultiTrack {
public:
private
  final ArrayList<AnimationTrack> m_tracks = std::make_unique<ArrayList<>>();
private
  static final ArrayList<AnimationTrack> tempTracks =
      std::make_unique<ArrayList<>>();

  AnimationTrack findTrack(const std::string &trackName) {
    int int0 = 0;

    for (int int1 = this.m_tracks.size(); int0 < int1; int0++) {
      AnimationTrack animationTrack = this.m_tracks.get(int0);
      if (animationTrack.name == trackName)) {
    return animationTrack;
            }
    }

    return null;
  }

  void addTrack(AnimationTrack track) { this.m_tracks.add(track); }

  void removeTrack(AnimationTrack track) {
    int int0 = this.getIndexOfTrack(track);
    if (int0 > -1) {
      this.removeTrackAt(int0);
    }
  }

  void removeTracks(List<AnimationTrack> tracks) {
    tempTracks.clear();
    tempTracks.addAll(tracks);

    for (int int0 = 0; int0 < tempTracks.size(); int0++) {
      this.removeTrack(tempTracks.get(int0));
    }
  }

  void removeTrackAt(int indexOf) { this.m_tracks.remove(indexOf).release(); }

  int getIndexOfTrack(AnimationTrack track) {
    if (track == nullptr) {
      return -1;
    } else {
      int int0 = -1;

      for (int int1 = 0; int1 < this.m_tracks.size(); int1++) {
        AnimationTrack animationTrack = this.m_tracks.get(int1);
        if (animationTrack == track) {
          int0 = int1;
          break;
        }
      }

      return int0;
    }
  }

  void Update(float time) {
    for (int int0 = 0; int0 < this.m_tracks.size(); int0++) {
      AnimationTrack animationTrack = this.m_tracks.get(int0);
      animationTrack.Update(time);
      if (animationTrack.CurrentClip == nullptr) {
        this.removeTrackAt(int0);
        int0--;
      }
    }
  }

  float getDuration() {
    float float0 = 0.0F;

    for (int int0 = 0; int0 < this.m_tracks.size(); int0++) {
      AnimationTrack animationTrack = this.m_tracks.get(int0);
      float float1 = animationTrack.getDuration();
      if (animationTrack.CurrentClip != nullptr && float1 > float0) {
        float0 = float1;
      }
    }

    return float0;
  }

  void reset() {
    int int0 = 0;

    for (int int1 = this.m_tracks.size(); int0 < int1; int0++) {
      AnimationTrack animationTrack = this.m_tracks.get(int0);
      animationTrack.reset();
    }

    AnimationPlayer.releaseTracks(this.m_tracks);
    this.m_tracks.clear();
  }

public
  List<AnimationTrack> getTracks() { return this.m_tracks; }

  int getTrackCount() { return this.m_tracks.size(); }

  AnimationTrack getTrackAt(int i) { return this.m_tracks.get(i); }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
