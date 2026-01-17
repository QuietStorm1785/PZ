#pragma once
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/animation/AnimTrackSampler.h"
#include "zombie/debug/DebugOptions.h"
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
namespace sharedskele {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SharedSkeleAnimationTrack {
public:
  int m_numFrames;
  float m_totalTime;
  bool m_isLooped;
private
  SharedSkeleAnimationTrack.BoneTrack[] m_boneTracks;
  float m_currentTime = 0.0F;

  void set(AnimTrackSampler sampler, float fps) {
    float float0 = sampler.getTotalTime();
    bool boolean0 = sampler.isLooped();
    int int0 = sampler.getNumBones();
    this.m_totalTime = float0;
    this.m_numFrames = PZMath.max((int)(float0 * fps + 0.99F), 1);
    this.m_isLooped = boolean0;
    this.m_boneTracks = new SharedSkeleAnimationTrack.BoneTrack[int0];

    for (int int1 = 0; int1 < int0; int1++) {
      this.m_boneTracks[int1] = new SharedSkeleAnimationTrack.BoneTrack();
      this.m_boneTracks[int1].m_animationData =
          new float[this.m_numFrames * 16];
    }

    Matrix4f matrix4f = new Matrix4f();
    float float1 = float0 / (this.m_numFrames - 1);

    for (int int2 = 0; int2 < this.m_numFrames; int2++) {
      float float2 = float1 * int2;
      sampler.moveToTime(float2);

      for (int int3 = 0; int3 < int0; int3++) {
        sampler.getBoneMatrix(int3, matrix4f);
        int int4 = int2 * 16;
        SharedSkeleAnimationTrack.BoneTrack boneTrack = this.m_boneTracks[int3];
        float[] floats = boneTrack.m_animationData;
        floats[int4] = matrix4f.m00;
        floats[int4 + 1] = matrix4f.m01;
        floats[int4 + 2] = matrix4f.m02;
        floats[int4 + 3] = matrix4f.m03;
        floats[int4 + 4] = matrix4f.m10;
        floats[int4 + 5] = matrix4f.m11;
        floats[int4 + 6] = matrix4f.m12;
        floats[int4 + 7] = matrix4f.m13;
        floats[int4 + 8] = matrix4f.m20;
        floats[int4 + 9] = matrix4f.m21;
        floats[int4 + 10] = matrix4f.m22;
        floats[int4 + 11] = matrix4f.m23;
        floats[int4 + 12] = matrix4f.m30;
        floats[int4 + 13] = matrix4f.m31;
        floats[int4 + 14] = matrix4f.m32;
        floats[int4 + 15] = matrix4f.m33;
      }
    }
  }

  float getTotalTime() { return this.m_totalTime; }

  bool isLooped() { return this.m_isLooped; }

  void moveToTime(float time) { this.m_currentTime = time; }

  float getCurrentTime() { return this.m_currentTime; }

  void getBoneMatrix(int boneIdx, Matrix4f out_matrix) {
    float float0 = this.m_totalTime;
    int int0 = this.m_numFrames;
    float float1 = this.getCurrentTime();
    float float2 = float1 / float0;
    float float3 = float2 * (int0 - 1);
    if (this.isLooped()) {
      this.sampleAtTime_Looped(out_matrix, boneIdx, float3);
    } else {
      this.sampleAtTime_NonLooped(out_matrix, boneIdx, float3);
    }
  }

  int getNumBones() {
    return this.m_boneTracks != nullptr ? this.m_boneTracks.length : 0;
  }

  void sampleAtTime_NonLooped(Matrix4f matrix4f, int int3, float float0) {
    int int0 = (int)float0;
    float float1 = float0 - int0;
    int int1 = PZMath.clamp(int0, 0, this.m_numFrames - 1);
    int int2 = PZMath.clamp(int1 + 1, 0, this.m_numFrames - 1);
    bool boolean0 =
        DebugOptions.instance.Animation.SharedSkeles.AllowLerping.getValue();
    this.sampleBoneData(int3, int1, int2, float1, boolean0, matrix4f);
  }

  void sampleAtTime_Looped(Matrix4f matrix4f, int int3, float float0) {
    int int0 = (int)float0;
    float float1 = float0 - int0;
    int int1 = int0 % this.m_numFrames;
    int int2 = (int1 + 1) % this.m_numFrames;
    bool boolean0 =
        DebugOptions.instance.Animation.SharedSkeles.AllowLerping.getValue();
    this.sampleBoneData(int3, int1, int2, float1, boolean0, matrix4f);
  }

  void sampleBoneData(int int2, int int1, int int3, float float0, bool boolean0,
                      Matrix4f matrix4f) {
    int int0 = int1 * 16;
    SharedSkeleAnimationTrack.BoneTrack boneTrack = this.m_boneTracks[int2];
    float[] floats = boneTrack.m_animationData;
    if (int1 != int3 && boolean0) {
      int int4 = int3 * 16;
      matrix4f.m00 = PZMath.lerp(floats[int0], floats[int4], float0);
      matrix4f.m01 = PZMath.lerp(floats[int0 + 1], floats[int4 + 1], float0);
      matrix4f.m02 = PZMath.lerp(floats[int0 + 2], floats[int4 + 2], float0);
      matrix4f.m03 = PZMath.lerp(floats[int0 + 3], floats[int4 + 3], float0);
      matrix4f.m10 = PZMath.lerp(floats[int0 + 4], floats[int4 + 4], float0);
      matrix4f.m11 = PZMath.lerp(floats[int0 + 5], floats[int4 + 5], float0);
      matrix4f.m12 = PZMath.lerp(floats[int0 + 6], floats[int4 + 6], float0);
      matrix4f.m13 = PZMath.lerp(floats[int0 + 7], floats[int4 + 7], float0);
      matrix4f.m20 = PZMath.lerp(floats[int0 + 8], floats[int4 + 8], float0);
      matrix4f.m21 = PZMath.lerp(floats[int0 + 9], floats[int4 + 9], float0);
      matrix4f.m22 = PZMath.lerp(floats[int0 + 10], floats[int4 + 10], float0);
      matrix4f.m23 = PZMath.lerp(floats[int0 + 11], floats[int4 + 11], float0);
      matrix4f.m30 = PZMath.lerp(floats[int0 + 12], floats[int4 + 12], float0);
      matrix4f.m31 = PZMath.lerp(floats[int0 + 13], floats[int4 + 13], float0);
      matrix4f.m32 = PZMath.lerp(floats[int0 + 14], floats[int4 + 14], float0);
      matrix4f.m33 = PZMath.lerp(floats[int0 + 15], floats[int4 + 15], float0);
    } else {
      matrix4f.m00 = floats[int0];
      matrix4f.m01 = floats[int0 + 1];
      matrix4f.m02 = floats[int0 + 2];
      matrix4f.m03 = floats[int0 + 3];
      matrix4f.m10 = floats[int0 + 4];
      matrix4f.m11 = floats[int0 + 5];
      matrix4f.m12 = floats[int0 + 6];
      matrix4f.m13 = floats[int0 + 7];
      matrix4f.m20 = floats[int0 + 8];
      matrix4f.m21 = floats[int0 + 9];
      matrix4f.m22 = floats[int0 + 10];
      matrix4f.m23 = floats[int0 + 11];
      matrix4f.m30 = floats[int0 + 12];
      matrix4f.m31 = floats[int0 + 13];
      matrix4f.m32 = floats[int0 + 14];
      matrix4f.m33 = floats[int0 + 15];
    }
  }

private
  static class BoneTrack {
  private
    float[] m_animationData;
  }
}
} // namespace sharedskele
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
