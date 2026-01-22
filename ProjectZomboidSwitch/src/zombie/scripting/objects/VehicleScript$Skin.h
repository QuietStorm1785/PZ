#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace scripting {
namespace objects {


class VehicleScript {
public:
    std::string texture;
    std::string textureRust = nullptr;
    std::string textureMask = nullptr;
    std::string textureLights = nullptr;
    std::string textureDamage1Overlay = nullptr;
    std::string textureDamage1Shell = nullptr;
    std::string textureDamage2Overlay = nullptr;
    std::string textureDamage2Shell = nullptr;
    std::string textureShadow = nullptr;
    Texture textureData;
    Texture textureDataRust;
    Texture textureDataMask;
    Texture textureDataLights;
    Texture textureDataDamage1Overlay;
    Texture textureDataDamage1Shell;
    Texture textureDataDamage2Overlay;
    Texture textureDataDamage2Shell;
    Texture textureDataShadow;

    void copyMissingFrom(VehicleScript$Skin var1) {
      if (this.textureRust == nullptr) {
         this.textureRust = var1.textureRust;
      }

      if (this.textureMask == nullptr) {
         this.textureMask = var1.textureMask;
      }

      if (this.textureLights == nullptr) {
         this.textureLights = var1.textureLights;
      }

      if (this.textureDamage1Overlay == nullptr) {
         this.textureDamage1Overlay = var1.textureDamage1Overlay;
      }

      if (this.textureDamage1Shell == nullptr) {
         this.textureDamage1Shell = var1.textureDamage1Shell;
      }

      if (this.textureDamage2Overlay == nullptr) {
         this.textureDamage2Overlay = var1.textureDamage2Overlay;
      }

      if (this.textureDamage2Shell == nullptr) {
         this.textureDamage2Shell = var1.textureDamage2Shell;
      }

      if (this.textureShadow == nullptr) {
         this.textureShadow = var1.textureShadow;
      }
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
