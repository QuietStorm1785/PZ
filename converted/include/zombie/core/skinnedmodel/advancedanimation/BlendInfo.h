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
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BlendInfo {
public:
  std::string name;
  BlendType Type;
  std::string mulDec;
  std::string mulInc;
  float dec;
  float inc;

public
  static class BlendInstance {
    float current = -1.0F;
    float target;
    BlendInfo info;

    std::string GetDebug() {
      std::string string = "Blend: " + this.info.name;
      switch (this.info.Type) {
      case Linear:
        string = string + ", Linear ";
        break;
      case InverseExponential:
        string = string + ", InverseExponential ";
      }

      return string + ", Current " + this.current;
    }

  public
    BlendInstance(BlendInfo blendInfo) { this.info = blendInfo; }

    void set(float float0) {
      this.target = float0;
      if (this.current == -1.0F) {
        this.current = this.target;
      }
    }

    void update() {
      float float0 = 0.0F;
      if (this.current < this.target) {
        float float1 = 1.0F;
        switch (this.info.Type) {
        case InverseExponential:
          float1 = this.current / 1.0F;
          float1 = 1.0F - float1;
          if (float1 < 0.1F) {
            float1 = 0.1F;
          }
        case Linear:
        default:
          float0 = this.info.inc * float1;
          this.current += float0;
          if (this.current > this.target) {
            this.current = this.target;
          }
        }
      } else if (this.current > this.target) {
        float float2 = 1.0F;
        switch (this.info.Type) {
        case InverseExponential:
          float2 = this.current / 1.0F;
          float2 = 1.0F - float2;
          if (float2 < 0.1F) {
            float2 = 0.1F;
          }
        case Linear:
        default:
          float0 = -this.info.dec * float2;
          this.current += float0;
          if (this.current < this.target) {
            this.current = this.target;
          }
        }
      }
    }
  }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
