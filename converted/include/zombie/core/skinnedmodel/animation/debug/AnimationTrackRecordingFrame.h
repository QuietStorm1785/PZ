#pragma once
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/iso/Vector2.h"
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
namespace debug {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimationTrackRecordingFrame : public GenericNameWeightRecordingFrame {
public:
  Vector2 m_deferredMovement = new Vector2();

public
  AnimationTrackRecordingFrame(const std::string &fileKey) { super(fileKey); }

  void reset() {
    super.reset();
    this.m_deferredMovement.set(0.0F, 0.0F);
  }

  void logAnimWeights(List<AnimationTrack> list, int[] ints, float[] floats,
                      Vector2 vector) {
    for (int int0 = 0; int0 < ints.length; int0++) {
      int int1 = ints[int0];
      if (int1 < 0) {
        break;
      }

      float float0 = floats[int0];
      AnimationTrack animationTrack = (AnimationTrack)list.get(int1);
      std::string string = animationTrack.name;
      int int2 = animationTrack.getLayerIdx();
      this.logWeight(string, int2, float0);
    }

    this.m_deferredMovement.set(vector);
  }

  Vector2 getDeferredMovement() { return this.m_deferredMovement; }

  void writeHeader(StringBuilder logLine) {
    logLine.append(",");
    logLine.append("dm.x").append(",").append("dm.y");
    super.writeHeader(logLine);
  }

  void writeData(StringBuilder stringBuilder) {
    stringBuilder.append(",");
    stringBuilder.append(this.getDeferredMovement().x)
        .append(",")
        .append(this.getDeferredMovement().y);
    super.writeData(stringBuilder);
  }
}
} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
