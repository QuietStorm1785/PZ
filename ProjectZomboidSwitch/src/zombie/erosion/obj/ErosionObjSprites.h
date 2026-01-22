#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/obj/ErosionObjSprites/Section.h"
#include "zombie/erosion/obj/ErosionObjSprites/Sprites.h"
#include "zombie/erosion/obj/ErosionObjSprites/Stage.h"

namespace zombie {
namespace erosion {
namespace obj {


class ErosionObjSprites {
public:
    static const int SECTION_BASE = 0;
    static const int SECTION_SNOW = 1;
    static const int SECTION_FLOWER = 2;
    static const int SECTION_CHILD = 3;
    static const int NUM_SECTIONS = 4;
    std::string name;
    int stages;
    bool hasSnow;
    bool hasFlower;
    bool hasChildSprite;
    bool noSeasonBase;
    int cycleTime = 1;
   private Stage[] sprites;

    public ErosionObjSprites(int var1, const std::string& var2, bool var3, bool var4, bool var5) {
      this.name = var2;
      this.stages = var1;
      this.hasSnow = var3;
      this.hasFlower = var4;
      this.hasChildSprite = var5;
      this.sprites = new Stage[var1];

      for (int var6 = 0; var6 < var1; var6++) {
         this.sprites[var6] = std::make_unique<Stage>();
         this.sprites[var6].sections[0] = std::make_unique<Section>();
         if (this.hasSnow) {
            this.sprites[var6].sections[1] = std::make_unique<Section>();
         }

         if (this.hasFlower) {
            this.sprites[var6].sections[2] = std::make_unique<Section>();
         }

         if (this.hasChildSprite) {
            this.sprites[var6].sections[3] = std::make_unique<Section>();
         }
      }
   }

    std::string getSprite(int var1, int var2, int var3) {
      return this.sprites[var1] != nullptr && this.sprites[var1].sections[var2] != nullptr && this.sprites[var1].sections[var2].seasons[var3] != nullptr
         ? this.sprites[var1].sections[var2].seasons[var3].getNext()
         : nullptr;
   }

    std::string getBase(int var1, int var2) {
      return this.getSprite(var1, 0, var2);
   }

    std::string getFlower(int var1) {
      return this.hasFlower ? this.getSprite(var1, 2, 0) : nullptr;
   }

    std::string getChildSprite(int var1, int var2) {
      return this.hasChildSprite ? this.getSprite(var1, 3, var2) : nullptr;
   }

    void setSprite(int var1, int var2, const std::string& var3, int var4) {
      if (this.sprites[var1] != nullptr && this.sprites[var1].sections[var2] != nullptr) {
         this.sprites[var1].sections[var2].seasons[var4] = std::make_shared<Sprites>(var3);
      }
   }

    void setSprite(int var1, int var2, std::vector<std::string> var3, int var4) {
      assert !var3.empty();

      if (this.sprites[var1] != nullptr && this.sprites[var1].sections[var2] != nullptr) {
         this.sprites[var1].sections[var2].seasons[var4] = std::make_shared<Sprites>(var3);
      }
   }

    void setBase(int var1, const std::string& var2, int var3) {
      this.setSprite(var1, 0, var2, var3);
   }

    void setBase(int var1, std::vector<std::string> var2, int var3) {
      this.setSprite(var1, 0, var2, var3);
   }

    void setFlower(int var1, const std::string& var2) {
      this.setSprite(var1, 2, var2, 0);
   }

    void setFlower(int var1, std::vector<std::string> var2) {
      this.setSprite(var1, 2, var2, 0);
   }

    void setChildSprite(int var1, const std::string& var2, int var3) {
      this.setSprite(var1, 3, var2, var3);
   }

    void setChildSprite(int var1, std::vector<std::string> var2, int var3) {
      this.setSprite(var1, 3, var2, var3);
   }
}
} // namespace obj
} // namespace erosion
} // namespace zombie
