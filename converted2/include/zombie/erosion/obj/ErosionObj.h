#pragma once
#include "zombie/erosion/ErosionMain.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/util/list/PZArrayList.h"
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

class ErosionObj {
public:
  const ErosionObjSprites sprites;
  std::string name;
  int stages;
  bool hasSnow;
  bool hasFlower;
  bool hasChildSprite;
  float bloomStart;
  float bloomEnd;
  bool noSeasonBase;
  int cycleTime = 1;

public
  ErosionObj(ErosionObjSprites erosionObjSprites, int int0, float float0,
             float float1, bool boolean0) {
    this.sprites = erosionObjSprites;
    this.name = erosionObjSprites.name;
    this.stages = erosionObjSprites.stages;
    this.hasSnow = erosionObjSprites.hasSnow;
    this.hasFlower = erosionObjSprites.hasFlower;
    this.hasChildSprite = erosionObjSprites.hasChildSprite;
    this.bloomStart = float0;
    this.bloomEnd = float1;
    this.noSeasonBase = boolean0;
    this.cycleTime = int0;
  }

  IsoObject getObject(IsoGridSquare square, bool boolean0) {
    PZArrayList pZArrayList = square.getObjects();

    for (int int0 = pZArrayList.size() - 1; int0 >= 0; int0--) {
      IsoObject object = (IsoObject)pZArrayList.get(int0);
      if (this.name == object.getName())) {
          if (boolean0) {
            pZArrayList.remove(int0);
          }

          object.doNotSync = true;
          return object;
        }
    }

    return null;
  }

  IsoObject createObject(IsoGridSquare square, int int0, bool boolean0,
                         int int1) {
    std::string string =
        this.sprites.getBase(int0, this.noSeasonBase ? 0 : int1);
    if (string == nullptr) {
      string = "";
    }

    void *object;
    if (boolean0) {
      object = IsoTree.getNew();
      ((IsoObject)object).sprite =
          IsoSpriteManager.instance.NamedMap.get(string);
      ((IsoObject)object).square = square;
      ((IsoObject)object).sx = 0.0F;
      ((IsoTree)object).initTree();
    } else {
      object = IsoObject.getNew(square, string, this.name, false);
    }

    ((IsoObject)object).setName(this.name);
    ((IsoObject)object).doNotSync = true;
    return (IsoObject)object;
  }

  bool placeObject(IsoGridSquare square, int int0, bool boolean0, int int1,
                   bool boolean1) {
    IsoObject object = this.createObject(square, int0, boolean0, int1);
    if (object != nullptr &&
        this.setStageObject(int0, object, int1, boolean1)) {
      object.doNotSync = true;
      if (!boolean0) {
        square.getObjects().add(object);
        object.addToWorld();
      } else {
        square.AddTileObject(object);
      }

      return true;
    } else {
      return false;
    }
  }

  bool setStageObject(int int0, IsoObject object, int int1, bool boolean0) {
    object.doNotSync = true;
    if (int0 >= 0 && int0 < this.stages && object != nullptr) {
      std::string string =
          this.sprites.getBase(int0, this.noSeasonBase ? 0 : int1);
      if (string == nullptr) {
        object.setSprite(this.getSprite(""));
        if (object.AttachedAnimSprite != nullptr) {
          object.AttachedAnimSprite.clear();
        }

        return true;
      } else {
        IsoSprite sprite = this.getSprite(string);
        object.setSprite(sprite);
        if (this.hasChildSprite || this.hasFlower) {
          if (object.AttachedAnimSprite == nullptr) {
            object.AttachedAnimSprite = std::make_unique<ArrayList<>>();
          }

          object.AttachedAnimSprite.clear();
          if (this.hasChildSprite && int1 != 0) {
            string = this.sprites.getChildSprite(int0, int1);
            if (string != nullptr) {
              sprite = this.getSprite(string);
              object.AttachedAnimSprite.add(sprite.newInstance());
            }
          }

          if (this.hasFlower && boolean0) {
            string = this.sprites.getFlower(int0);
            if (string != nullptr) {
              sprite = this.getSprite(string);
              object.AttachedAnimSprite.add(sprite.newInstance());
            }
          }
        }

        return true;
      }
    } else {
      return false;
    }
  }

  bool setStage(IsoGridSquare square, int int0, int int1, bool boolean0) {
    IsoObject object = this.getObject(square, false);
    return object != nullptr ? this.setStageObject(int0, object, int1, boolean0)
                             : false;
  }

  IsoObject removeObject(IsoGridSquare square) {
    return this.getObject(square, true);
  }

  IsoSprite getSprite(const std::string &string) {
    return ErosionMain.getInstance().getSpriteManager().getSprite(string);
  }
}
} // namespace obj
} // namespace erosion
} // namespace zombie
