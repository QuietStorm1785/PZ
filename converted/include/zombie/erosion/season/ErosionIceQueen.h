#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"

namespace zombie {
namespace erosion {
namespace season {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ErosionIceQueen {
public:
 static ErosionIceQueen instance;
 private ArrayList<ErosionIceQueen.Sprite> sprites = std::make_unique<ArrayList<>>();
 const IsoSpriteManager SprMngr;
 bool snowState;

 void addSprite(const std::string& _sprite, const std::string& _winterSprite) {
 IsoSprite sprite0 = this->SprMngr.getSprite(_sprite);
 IsoSprite sprite1 = this->SprMngr.getSprite(_winterSprite);
 if (sprite0 != nullptr && sprite1 != nullptr) {
 sprite0.setName(_sprite);
 this->sprites.add(new ErosionIceQueen.Sprite(sprite0, _sprite, _winterSprite);
 }
 }

 void setSnow(bool _isSnow) {
 if (this->snowState != _isSnow) {
 this->snowState = _isSnow;

 for (int int0 = 0; int0 < this->sprites.size(); int0++) {
 ErosionIceQueen.Sprite sprite = this->sprites.get(int0);
 sprite.sprite.ReplaceCurrentAnimFrames(this->snowState ? sprite.winter : sprite.normal);
 }
 }
 }

 public ErosionIceQueen(IsoSpriteManager _sprMngr) {
 instance = this;
 this->SprMngr = _sprMngr;
 this->setRoofSnow();

 for (int int0 = 0; int0 < 10; int0++) {
 this->addSprite("vegetation_ornamental_01_" + int0, "f_bushes_2_" + (int0 + 10);
 this->addSprite("f_bushes_2_" + int0, "f_bushes_2_" + (int0 + 10);
 }
 }

 void setRoofSnowA() {
 for (int int0 = 0; int0 < 128; int0++) {
 std::string string0 = "e_roof_snow_1_" + int0;

 for (int int1 = 1; int1 <= 5; int1++) {
 std::string string1 = "roofs_0" + int1 + "_" + int0;
 this->addSprite(string1, string0);
 }
 }
 }

 void setRoofSnow() {
 for (int int0 = 1; int0 <= 5; int0++) {
 for (int int1 = 0; int1 < 128; int1++) {
 int int2 = int1;
 switch (int0) {
 case 1:
 if (int1 >= 72 && int1 <= 79) {
 int2 = int1 - 8;
 }

 if (int1 == 112 || int1 == 114) {
 int2 = 0;
 }

 if (int1 == 113 || int1 == 115) {
 int2 = 1;
 }

 if (int1 == 116 || int1 == 118) {
 int2 = 4;
 }

 if (int1 == 117 || int1 == 119) {
 int2 = 5;
 }
 break;
 case 2:
 if (int1 == 50) {
 int2 = 106;
 }

 if (int1 == 51) {
 int2 = 107;
 }

 if (int1 >= 72 && int1 <= 79) {
 int2 = int1 - 8;
 }

 if (int1 == 104 || int1 == 106) {
 int2 = 0;
 }

 if (int1 == 105 || int1 == 107) {
 int2 = 1;
 }

 if (int1 == 108 || int1 == 110) {
 int2 = 4;
 }

 if (int1 == 109 || int1 == 111) {
 int2 = 5;
 }
 break;
 case 3:
 if (int1 == 72 || int1 == 74) {
 int2 = 0;
 }

 if (int1 == 73 || int1 == 75) {
 int2 = 1;
 }

 if (int1 == 76 || int1 == 78) {
 int2 = 4;
 }

 if (int1 == 77 || int1 == 79) {
 int2 = 5;
 }

 if (int1 == 102) {
 int2 = 70;
 }

 if (int1 == 103) {
 int2 = 71;
 }

 if (int1 == 104 || int1 == 106) {
 int2 = 0;
 }

 if (int1 == 105 || int1 == 107) {
 int2 = 1;
 }

 if (int1 == 108 || int1 == 110) {
 int2 = 4;
 }

 if (int1 == 109 || int1 == 111) {
 int2 = 5;
 }

 if (int1 >= 120 && int1 <= 127) {
 int2 = int1 - 16;
 }
 break;
 case 4:
 if (int1 == 48) {
 int2 = 106;
 }

 if (int1 == 49) {
 int2 = 107;
 }

 if (int1 == 50) {
 int2 = 108;
 }

 if (int1 == 51) {
 int2 = 109;
 }

 if (int1 == 72 || int1 == 74) {
 int2 = 0;
 }

 if (int1 == 73 || int1 == 75) {
 int2 = 1;
 }

 if (int1 == 76 || int1 == 78) {
 int2 = 4;
 }

 if (int1 == 77 || int1 == 79) {
 int2 = 5;
 }

 if (int1 == 102) {
 int2 = 70;
 }

 if (int1 == 103) {
 int2 = 71;
 }

 if (int1 == 104 || int1 == 106) {
 int2 = 0;
 }

 if (int1 == 105 || int1 == 107) {
 int2 = 1;
 }

 if (int1 == 108 || int1 == 110) {
 int2 = 4;
 }

 if (int1 == 109 || int1 == 111) {
 int2 = 5;
 }
 break;
 case 5:
 if (int1 >= 72 && int1 <= 79) {
 int2 = int1 - 8;
 }

 if (int1 == 104 || int1 == 106) {
 int2 = 0;
 }

 if (int1 == 105 || int1 == 107) {
 int2 = 1;
 }

 if (int1 == 108 || int1 == 110) {
 int2 = 4;
 }

 if (int1 == 109 || int1 == 111) {
 int2 = 5;
 }

 if (int1 >= 112 && int1 <= 119) {
 int2 = int1 - 32;
 }
 }

 std::string string0 = "roofs_0" + int0 + "_" + int1;
 std::string string1 = "e_roof_snow_1_" + int2;
 this->addSprite(string0, string1);
 }
 }

 uint8_t byte0 = 5;

 for (int int3 = 128; int3 < 176; int3++) {
 int int4;
 if (int3 == 136 || int3 == 138) {
 int4 = 0;
 } else if (int3 == 137 || int3 == 139) {
 int4 = 1;
 } else if (int3 == 140 || int3 == 142) {
 int4 = 4;
 } else if (int3 != 141 && int3 != 143) {
 if (int3 < 128 || int3 > 135) {
 continue;
 }

 int4 = int3 - 128 + 96;
 } else {
 int4 = 5;
 }

 std::string string2 = "roofs_0" + byte0 + "_" + int3;
 std::string string3 = "e_roof_snow_1_" + int4;
 this->addSprite(string2, string3);
 }
 }

 void setRoofSnowOneX() {
 for (int int0 = 1; int0 <= 5; int0++) {
 for (int int1 = 0; int1 < 128; int1++) {
 int int2 = int1;
 switch (int0) {
 case 1:
 if (int1 >= 96 && int1 <= 98) {
 int2 = int1 - 16;
 }

 if (int1 == 99) {
 int2 = int1 - 19;
 }

 if (int1 == 100) {
 int2 = int1 - 13;
 }

 if (int1 >= 101 && int1 <= 103) {
 int2 = int1 - 16;
 }

 if (int1 >= 112 && int1 <= 113) {
 int2 = int1 - 112;
 }

 if (int1 >= 114 && int1 <= 115) {
 int2 = int1 - 114;
 }

 if (int1 == 116 || int1 == 118) {
 int2 = 5;
 }

 if (int1 == 117 || int1 == 119) {
 int2 = 4;
 }
 break;
 case 2:
 if (int1 >= 96 && int1 <= 98) {
 int2 = int1 - 16;
 }

 if (int1 == 99) {
 int2 = int1 - 19;
 }

 if (int1 == 100) {
 int2 = int1 - 13;
 }

 if (int1 >= 101 && int1 <= 103) {
 int2 = int1 - 16;
 }

 if (int1 >= 104 && int1 <= 105) {
 int2 = int1 - 104;
 }

 if (int1 >= 106 && int1 <= 107) {
 int2 = int1 - 106;
 }

 if (int1 >= 108 && int1 <= 109) {
 int2 = int1 - 104;
 }

 if (int1 >= 110 && int1 <= 111) {
 int2 = int1 - 106;
 }
 break;
 case 3:
 if (int1 >= 18 && int1 <= 19) {
 int2 = int1 - 12;
 }

 if (int1 >= 50 && int1 <= 51) {
 int2 = int1 - 44;
 }

 if (int1 >= 72 && int1 <= 73) {
 int2 = int1 - 72;
 }

 if (int1 >= 74 && int1 <= 75) {
 int2 = int1 - 74;
 }

 if (int1 >= 76 && int1 <= 77) {
 int2 = int1 - 72;
 }

 if (int1 >= 78 && int1 <= 79) {
 int2 = int1 - 74;
 }

 if (int1 >= 102 && int1 <= 103) {
 int2 = int1 - 88;
 }

 if (int1 >= 122 && int1 <= 125) {
 int2 = int1 - 16;
 }
 break;
 case 4:
 if (int1 >= 18 && int1 <= 19) {
 int2 = int1 - 12;
 }
 break;
 case 5:
 if (int1 >= 72 && int1 <= 74) {
 int2 = int1 + 8;
 }

 if (int1 == 75) {
 int2 = int1 + 7;
 }

 if (int1 == 76) {
 int2 = int1 + 11;
 }

 if (int1 >= 77 && int1 <= 79) {
 int2 = int1 + 8;
 }

 if (int1 >= 112 && int1 <= 113) {
 int2 = int1 - 112;
 }

 if (int1 >= 114 && int1 <= 115) {
 int2 = int1 - 114;
 }

 if (int1 == 116 || int1 == 118) {
 int2 = 5;
 }

 if (int1 == 117 || int1 == 119) {
 int2 = 4;
 }
 }

 std::string string0 = "roofs_0" + int0 + "_" + int1;
 std::string string1 = "e_roof_snow_1_" + int2;
 this->addSprite(string0, string1);
 }
 }
 }

 static void Reset() {
 if (instance != nullptr) {
 instance.sprites.clear();
 instance = nullptr;
 }
 }

 private static class Sprite {
 IsoSprite sprite;
 std::string normal;
 std::string winter;

 public Sprite(IsoSprite sprite1, const std::string& string0, const std::string& string1) {
 this->sprite = sprite1;
 this->normal = string0;
 this->winter = string1;
 }
 }
}
} // namespace season
} // namespace erosion
} // namespace zombie
