#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/Rectangle.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/Mouse.h"
#include <algorithm>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class MoodlesUI : public UIElement {
public:
 float clientH = 0.0F;
 float clientW = 0.0F;
 bool Movable = false;
 int ncclientH = 0;
 int ncclientW = 0;
 static MoodlesUI instance = nullptr;
 static const float OFFSCREEN_Y = 10000.0F;
 public Stack<Rectangle> nestedItems = std::make_unique<Stack<>>();
 float alpha = 1.0F;
 Texture Back_Bad_1 = nullptr;
 Texture Back_Bad_2 = nullptr;
 Texture Back_Bad_3 = nullptr;
 Texture Back_Bad_4 = nullptr;
 Texture Back_Good_1 = nullptr;
 Texture Back_Good_2 = nullptr;
 Texture Back_Good_3 = nullptr;
 Texture Back_Good_4 = nullptr;
 Texture Back_Neutral = nullptr;
 Texture Endurance = nullptr;
 Texture Bleeding = nullptr;
 Texture Angry = nullptr;
 Texture Stress = nullptr;
 Texture Thirst = nullptr;
 Texture Panic = nullptr;
 Texture Hungry = nullptr;
 Texture Injured = nullptr;
 Texture Pain = nullptr;
 Texture Sick = nullptr;
 Texture Bored = nullptr;
 Texture Unhappy = nullptr;
 Texture Tired = nullptr;
 Texture HeavyLoad = nullptr;
 Texture Drunk = nullptr;
 Texture Wet = nullptr;
 Texture HasACold = nullptr;
 Texture Dead = nullptr;
 Texture Zombie = nullptr;
 Texture Windchill = nullptr;
 Texture CantSprint = nullptr;
 Texture FoodEaten = nullptr;
 Texture Hyperthermia = nullptr;
 Texture Hypothermia = nullptr;
 static Texture plusRed;
 static Texture plusGreen;
 static Texture minusRed;
 static Texture minusGreen;
 static Texture chevronUp;
 static Texture chevronUpBorder;
 static Texture chevronDown;
 static Texture chevronDownBorder;
 float MoodleDistY = 36.0F;
 bool MouseOver = false;
 int MouseOverSlot = 0;
 int NumUsedSlots = 0;
 int DebugKeyDelay = 0;
 int DistFromRighEdge = 46;
 private int[] GoodBadNeutral = new int[MoodleType.ToIndex(MoodleType.MAX)];
 private int[] MoodleLevel = new int[MoodleType.ToIndex(MoodleType.MAX)];
 private float[] MoodleOscilationLevel = new float[MoodleType.ToIndex(MoodleType.MAX)];
 private float[] MoodleSlotsDesiredPos = new float[MoodleType.ToIndex(MoodleType.MAX)];
 private float[] MoodleSlotsPos = new float[MoodleType.ToIndex(MoodleType.MAX)];
 private int[] MoodleTypeInSlot = new int[MoodleType.ToIndex(MoodleType.MAX)];
 float Oscilator = 0.0F;
 float OscilatorDecelerator = 0.96F;
 float OscilatorRate = 0.8F;
 float OscilatorScalar = 15.6F;
 float OscilatorStartLevel = 1.0F;
 float OscilatorStep = 0.0F;
 IsoGameCharacter UseCharacter = nullptr;
 bool alphaIncrease = true;

 public MoodlesUI() {
 this->x = Core.getInstance().getScreenWidth() - this->DistFromRighEdge;
 this->y = 100.0;
 this->width = 32.0F;
 this->height = 500.0F;
 this->Back_Bad_1 = Texture.getSharedTexture("media/ui/Moodles/Moodle_Bkg_Bad_1.png");
 this->Back_Bad_2 = Texture.getSharedTexture("media/ui/Moodles/Moodle_Bkg_Bad_2.png");
 this->Back_Bad_3 = Texture.getSharedTexture("media/ui/Moodles/Moodle_Bkg_Bad_3.png");
 this->Back_Bad_4 = Texture.getSharedTexture("media/ui/Moodles/Moodle_Bkg_Bad_4.png");
 this->Back_Good_1 = Texture.getSharedTexture("media/ui/Moodles/Moodle_Bkg_Good_1.png");
 this->Back_Good_2 = Texture.getSharedTexture("media/ui/Moodles/Moodle_Bkg_Good_2.png");
 this->Back_Good_3 = Texture.getSharedTexture("media/ui/Moodles/Moodle_Bkg_Good_3.png");
 this->Back_Good_4 = Texture.getSharedTexture("media/ui/Moodles/Moodle_Bkg_Good_4.png");
 this->Back_Neutral = Texture.getSharedTexture("media/ui/Moodles/Moodle_Bkg_Bad_1.png");
 this->Endurance = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Endurance.png");
 this->Tired = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Tired.png");
 this->Hungry = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Hungry.png");
 this->Panic = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Panic.png");
 this->Sick = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Sick.png");
 this->Bored = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Bored.png");
 this->Unhappy = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Unhappy.png");
 this->Bleeding = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Bleeding.png");
 this->Wet = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Wet.png");
 this->HasACold = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Cold.png");
 this->Angry = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Angry.png");
 this->Stress = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Stressed.png");
 this->Thirst = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Thirsty.png");
 this->Injured = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Injured.png");
 this->Pain = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Pain.png");
 this->HeavyLoad = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_HeavyLoad.png");
 this->Drunk = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Drunk.png");
 this->Dead = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Dead.png");
 this->Zombie = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Zombie.png");
 this->FoodEaten = Texture.getSharedTexture("media/ui/Moodles/Moodle_Icon_Hungry.png");
 this->Hyperthermia = Texture.getSharedTexture("media/ui/weather/Moodle_Icon_TempHot.png");
 this->Hypothermia = Texture.getSharedTexture("media/ui/weather/Moodle_Icon_TempCold.png");
 this->Windchill = Texture.getSharedTexture("media/ui/Moodle_Icon_Windchill.png");
 this->CantSprint = Texture.getSharedTexture("media/ui/Moodle_Icon_CantSprint.png");
 plusRed = Texture.getSharedTexture("media/ui/Moodle_internal_plus_red.png");
 minusRed = Texture.getSharedTexture("media/ui/Moodle_internal_minus_red.png");
 plusGreen = Texture.getSharedTexture("media/ui/Moodle_internal_plus_green.png");
 minusGreen = Texture.getSharedTexture("media/ui/Moodle_internal_minus_green.png");
 chevronUp = Texture.getSharedTexture("media/ui/Moodle_chevron_up.png");
 chevronUpBorder = Texture.getSharedTexture("media/ui/Moodle_chevron_up_border.png");
 chevronDown = Texture.getSharedTexture("media/ui/Moodle_chevron_down.png");
 chevronDownBorder = Texture.getSharedTexture("media/ui/Moodle_chevron_down_border.png");

 for (int int0 = 0; int0 < MoodleType.ToIndex(MoodleType.MAX); int0++) {
 this->MoodleSlotsPos[int0] = 10000.0F;
 this->MoodleSlotsDesiredPos[int0] = 10000.0F;
 }

 this->clientW = this->width;
 this->clientH = this->height;
 instance = this;
 }

 bool CurrentlyAnimating() {
 bool boolean0 = false;

 for (int int0 = 0; int0 < MoodleType.ToIndex(MoodleType.MAX); int0++) {
 if (this->MoodleSlotsPos[int0] != this->MoodleSlotsDesiredPos[int0]) {
 boolean0 = true;
 }
 }

 return boolean0;
 }

 void Nest(UIElement el, int t, int r, int b, int l) {
 this->AddChild(el);
 this->nestedItems.add(new Rectangle(l, t, r, b);
 }

 bool onMouseMove(double dx, double dy) {
 if (!this->isVisible()) {
 return Boolean.FALSE;
 } else {
 this->MouseOver = true;
 super.onMouseMove(dx, dy);
 this->MouseOverSlot = (int)((Mouse.getYA() - this->getY()) / this->MoodleDistY);
 if (this->MouseOverSlot >= this->NumUsedSlots) {
 this->MouseOverSlot = 1000;
 }

 return Boolean.TRUE;
 }
 }

 void onMouseMoveOutside(double dx, double dy) {
 super.onMouseMoveOutside(dx, dy);
 this->MouseOverSlot = 1000;
 this->MouseOver = false;
 }

 void render() {
 if (this->UseCharacter != nullptr) {
 float float0 = (float)(UIManager.getMillisSinceLastRender() / 33.3);
 this->OscilatorStep = this->OscilatorStep + this->OscilatorRate * float0 * 0.5F;
 this->Oscilator = (float)Math.sin(this->OscilatorStep);
 int int0 = 0;

 for (int int1 = 0; int1 < MoodleType.ToIndex(MoodleType.MAX); int1++) {
 if (this->MoodleSlotsPos[int1] != 10000.0F) {
 float float1;
 Texture texture0;
 Texture texture1;
 float1 = this->Oscilator * this->OscilatorScalar * this->MoodleOscilationLevel[int1];
 texture0 = this->Back_Neutral;
 texture1 = this->Tired;
 label90:
 switch (this->GoodBadNeutral[int1]) {
 case 0:
 texture0 = this->Back_Neutral;
 break;
 case 1:
 switch (this->MoodleLevel[int1]) {
 case 1:
 texture0 = this->Back_Good_1;
 break label90;
 case 2:
 texture0 = this->Back_Good_2;
 break label90;
 case 3:
 texture0 = this->Back_Good_3;
 break label90;
 case 4:
 texture0 = this->Back_Good_4;
 default:
 break label90;
 }
 case 2:
 switch (this->MoodleLevel[int1]) {
 case 1:
 texture0 = this->Back_Bad_1;
 break;
 case 2:
 texture0 = this->Back_Bad_2;
 break;
 case 3:
 texture0 = this->Back_Bad_3;
 break;
 case 4:
 texture0 = this->Back_Bad_4;
 }
 }

 switch (int1) {
 case 0:
 texture1 = this->Endurance;
 break;
 case 1:
 texture1 = this->Tired;
 break;
 case 2:
 texture1 = this->Hungry;
 break;
 case 3:
 texture1 = this->Panic;
 break;
 case 4:
 texture1 = this->Sick;
 break;
 case 5:
 texture1 = this->Bored;
 break;
 case 6:
 texture1 = this->Unhappy;
 break;
 case 7:
 texture1 = this->Bleeding;
 break;
 case 8:
 texture1 = this->Wet;
 break;
 case 9:
 texture1 = this->HasACold;
 break;
 case 10:
 texture1 = this->Angry;
 break;
 case 11:
 texture1 = this->Stress;
 break;
 case 12:
 texture1 = this->Thirst;
 break;
 case 13:
 texture1 = this->Injured;
 break;
 case 14:
 texture1 = this->Pain;
 break;
 case 15:
 texture1 = this->HeavyLoad;
 break;
 case 16:
 texture1 = this->Drunk;
 break;
 case 17:
 texture1 = this->Dead;
 break;
 case 18:
 texture1 = this->Zombie;
 break;
 case 19:
 texture1 = this->FoodEaten;
 break;
 case 20:
 texture1 = this->Hyperthermia;
 break;
 case 21:
 texture1 = this->Hypothermia;
 break;
 case 22:
 texture1 = this->Windchill;
 break;
 case 23:
 texture1 = this->CantSprint;
 }

 if (MoodleType.FromIndex(int1).name() == Core.getInstance().getBlinkingMoodle())) {
 if (this->alphaIncrease) {
 this->alpha = this->alpha + 0.1F * (30.0F / PerformanceSettings.instance.getUIRenderFPS());
 if (this->alpha > 1.0F) {
 this->alpha = 1.0F;
 this->alphaIncrease = false;
 }
 } else {
 this->alpha = this->alpha - 0.1F * (30.0F / PerformanceSettings.instance.getUIRenderFPS());
 if (this->alpha < 0.0F) {
 this->alpha = 0.0F;
 this->alphaIncrease = true;
 }
 }
 }

 if (Core.getInstance().getBlinkingMoodle() == nullptr) {
 this->alpha = 1.0F;
 }

 this->DrawTexture(texture0, (int)float1, (int)this->MoodleSlotsPos[int1], this->alpha);
 this->DrawTexture(texture1, (int)float1, (int)this->MoodleSlotsPos[int1], this->alpha);
 if (this->UseCharacter.getMoodles().getMoodleChevronCount(int1) > 0) {
 bool boolean0 = this->UseCharacter.getMoodles().getMoodleChevronIsUp(int1);
 Color color = this->UseCharacter.getMoodles().getMoodleChevronColor(int1);
 color.a = this->alpha;

 for (int int2 = 0; int2 < this->UseCharacter.getMoodles().getMoodleChevronCount(int1); int2++) {
 int int3 = int2 * 4;
 this->DrawTextureCol(boolean0 ? chevronUp : chevronDown, (int)float1 + 16, (int)this->MoodleSlotsPos[int1] + 20 - int3, color);
 this->DrawTextureCol(
 boolean0 ? chevronUpBorder : chevronDownBorder, (int)float1 + 16, (int)this->MoodleSlotsPos[int1] + 20 - int3, color
 );
 }
 }

 if (this->MouseOver && int0 == this->MouseOverSlot) {
 std::string string0 = this->UseCharacter.getMoodles().getMoodleDisplayString(int1);
 std::string string1 = this->UseCharacter.getMoodles().getMoodleDescriptionString(int1);
 int int4 = TextManager.instance.font.getWidth(string0);
 int int5 = TextManager.instance.font.getWidth(string1);
 int int6 = Math.max(int4, int5);
 int int7 = TextManager.instance.font.getLineHeight();
 int int8 = (int)this->MoodleSlotsPos[int1] + 1;
 int int9 = (2 + int7) * 2;
 this->DrawTextureScaledColor(nullptr, -10.0 - int6 - 6.0, int8 - 2.0, int6 + 12.0, (double)int9, 0.0, 0.0, 0.0, 0.6);
 this->DrawTextRight(string0, -10.0, int8, 1.0, 1.0, 1.0, 1.0);
 this->DrawTextRight(string1, -10.0, int8 + int7, 0.8F, 0.8F, 0.8F, 1.0);
 }

 int0++;
 }
 }

 super.render();
 }
 }

 void wiggle(MoodleType Moodle) {
 this->MoodleOscilationLevel[MoodleType.ToIndex(Moodle)] = this->OscilatorStartLevel;
 }

 void update() {
 super.update();
 if (this->UseCharacter != nullptr) {
 if (!this->CurrentlyAnimating()) {
 if (this->DebugKeyDelay > 0) {
 this->DebugKeyDelay--;
 } else if (GameKeyboard.isKeyDown(57) {
 this->DebugKeyDelay = 10;
 }
 }

 float float0 = PerformanceSettings.getLockFPS() / 30.0F;

 for (int int0 = 0; int0 < MoodleType.ToIndex(MoodleType.MAX); int0++) {
 this->MoodleOscilationLevel[int0] = this->MoodleOscilationLevel[int0]
 - this->MoodleOscilationLevel[int0] * (1.0F - this->OscilatorDecelerator) / float0;
 if (this->MoodleOscilationLevel[int0] < 0.01) {
 this->MoodleOscilationLevel[int0] = 0.0F;
 }
 }

 if (this->UseCharacter.getMoodles().UI_RefreshNeeded()) {
 int int1 = 0;

 for (int int2 = 0; int2 < MoodleType.ToIndex(MoodleType.MAX); int2++) {
 if (this->UseCharacter.getMoodles().getMoodleLevel(int2) > 0) {
 bool boolean0 = false;
 if (this->MoodleLevel[int2] != this->UseCharacter.getMoodles().getMoodleLevel(int2) {
 boolean0 = true;
 this->MoodleLevel[int2] = this->UseCharacter.getMoodles().getMoodleLevel(int2);
 this->MoodleOscilationLevel[int2] = this->OscilatorStartLevel;
 }

 this->MoodleSlotsDesiredPos[int2] = this->MoodleDistY * int1;
 if (boolean0) {
 if (this->MoodleSlotsPos[int2] == 10000.0F) {
 this->MoodleSlotsPos[int2] = this->MoodleSlotsDesiredPos[int2] + 500.0F;
 this->MoodleOscilationLevel[int2] = 0.0F;
 }

 this->GoodBadNeutral[int2] = this->UseCharacter.getMoodles().getGoodBadNeutral(int2);
 } else {
 this->MoodleOscilationLevel[int2] = 0.0F;
 }

 this->MoodleTypeInSlot[int1] = int2;
 int1++;
 } else {
 this->MoodleSlotsPos[int2] = 10000.0F;
 this->MoodleSlotsDesiredPos[int2] = 10000.0F;
 this->MoodleOscilationLevel[int2] = 0.0F;
 this->MoodleLevel[int2] = 0;
 }
 }

 this->NumUsedSlots = int1;
 }

 for (int int3 = 0; int3 < MoodleType.ToIndex(MoodleType.MAX); int3++) {
 if (Math.abs(this->MoodleSlotsPos[int3] - this->MoodleSlotsDesiredPos[int3]) > 0.8F) {
 this->MoodleSlotsPos[int3] = this->MoodleSlotsPos[int3] + (this->MoodleSlotsDesiredPos[int3] - this->MoodleSlotsPos[int3]) * 0.15F;
 } else {
 this->MoodleSlotsPos[int3] = this->MoodleSlotsDesiredPos[int3];
 }
 }
 }
 }

 void setCharacter(IsoGameCharacter chr) {
 if (chr != this->UseCharacter) {
 this->UseCharacter = chr;
 if (this->UseCharacter != nullptr && this->UseCharacter.getMoodles() != nullptr) {
 this->UseCharacter.getMoodles().setMoodlesStateChanged(true);
 }
 }
 }

 static MoodlesUI getInstance() {
 return instance;
 }
}
} // namespace ui
} // namespace zombie
