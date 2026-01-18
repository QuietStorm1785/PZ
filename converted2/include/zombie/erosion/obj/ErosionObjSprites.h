#pragma once
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace erosion {
namespace obj {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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
private
  ErosionObjSprites.Stage[] sprites;

public
  ErosionObjSprites(int int0, const std::string &string, bool boolean0,
                    bool boolean1, bool boolean2) {
    this.name = string;
    this.stages = int0;
    this.hasSnow = boolean0;
    this.hasFlower = boolean1;
    this.hasChildSprite = boolean2;
    this.sprites = new ErosionObjSprites.Stage[int0];

    for (int int1 = 0; int1 < int0; int1++) {
      this.sprites[int1] = new ErosionObjSprites.Stage();
      this.sprites[int1].sections[0] = new ErosionObjSprites.Section();
      if (this.hasSnow) {
        this.sprites[int1].sections[1] = new ErosionObjSprites.Section();
      }

      if (this.hasFlower) {
        this.sprites[int1].sections[2] = new ErosionObjSprites.Section();
      }

      if (this.hasChildSprite) {
        this.sprites[int1].sections[3] = new ErosionObjSprites.Section();
      }
    }
  }

  std::string getSprite(int int2, int int1, int int0) {
    return this.sprites[int2] != nullptr &&
                   this.sprites[int2].sections[int1] != nullptr &&
                   this.sprites[int2].sections[int1].seasons[int0] != nullptr
               ? this.sprites[int2].sections[int1].seasons[int0].getNext()
               : nullptr;
  }

  std::string getBase(int int0, int int1) {
    return this.getSprite(int0, 0, int1);
  }

  std::string getFlower(int int0) {
    return this.hasFlower ? this.getSprite(int0, 2, 0) : nullptr;
  }

  std::string getChildSprite(int int0, int int1) {
    return this.hasChildSprite ? this.getSprite(int0, 3, int1) : nullptr;
  }

  void setSprite(int int1, int int0, const std::string &string, int int2) {
    if (this.sprites[int1] != nullptr &&
        this.sprites[int1].sections[int0] != nullptr) {
      this.sprites[int1].sections[int0].seasons[int2] =
          new ErosionObjSprites.Sprites(string);
    }
  }

  void setSprite(int int1, int int0, ArrayList<String> arrayList, int int2) {
    assert !arrayList.isEmpty();

    if (this.sprites[int1] != nullptr &&
        this.sprites[int1].sections[int0] != nullptr) {
      this.sprites[int1].sections[int0].seasons[int2] =
          new ErosionObjSprites.Sprites(arrayList);
    }
  }

  void setBase(int int0, const std::string &string, int int1) {
    this.setSprite(int0, 0, string, int1);
  }

  void setBase(int int0, ArrayList<String> arrayList, int int1) {
    this.setSprite(int0, 0, arrayList, int1);
  }

  void setFlower(int int0, const std::string &string) {
    this.setSprite(int0, 2, string, 0);
  }

  void setFlower(int int0, ArrayList<String> arrayList) {
    this.setSprite(int0, 2, arrayList, 0);
  }

  void setChildSprite(int int0, const std::string &string, int int1) {
    this.setSprite(int0, 3, string, int1);
  }

  void setChildSprite(int int0, ArrayList<String> arrayList, int int1) {
    this.setSprite(int0, 3, arrayList, int1);
  }

private
  static class Section {
  public
    ErosionObjSprites.Sprites[] seasons = new ErosionObjSprites.Sprites[6];
  }

  private static final class Sprites {
  public
    final ArrayList<String> sprites = std::make_unique<ArrayList<>>();
    int index = -1;

  public
    Sprites(const std::string &string) {
      if (Core.bDebug || GameServer.bServer && GameServer.bDebug) {
        IsoSprite sprite = IsoSpriteManager.instance.getSprite(string);
        if (sprite.CurrentAnim.Frames.size() == 0 ||
            !GameServer.bServer && sprite.CurrentAnim.Frames.get(0).getTexture(
                                       IsoDirections.N) == nullptr ||
            sprite.ID < 10000) {
          DebugLog.log("EMPTY SPRITE " + string);
        }
      }

      this.sprites.add(string);
    }

  public
    Sprites(ArrayList<String> arrayList) {
      if (Core.bDebug || GameServer.bServer && GameServer.bDebug) {
        for (int int0 = 0; int0 < arrayList.size(); int0++) {
          IsoSprite sprite =
              IsoSpriteManager.instance.getSprite((String)arrayList.get(int0));
          if (sprite.CurrentAnim.Frames.size() == 0 ||
              !GameServer.bServer &&
                  sprite.CurrentAnim.Frames.get(0).getTexture(
                      IsoDirections.N) == nullptr ||
              sprite.ID < 10000) {
            DebugLog.log("EMPTY SPRITE " + (String)arrayList.get(int0));
          }
        }
      }

      this.sprites.addAll(arrayList);
    }

    std::string getNext() {
      if (++this.index >= this.sprites.size()) {
        this.index = 0;
      }

      return this.sprites.get(this.index);
    }
  }

  private static class Stage {
  public
    ErosionObjSprites.Section[] sections = new ErosionObjSprites.Section[4];
  }
}
} // namespace obj
} // namespace erosion
} // namespace zombie
