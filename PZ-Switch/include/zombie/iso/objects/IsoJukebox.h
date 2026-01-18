#pragma once
#include "fmod/fmod/Audio.h"
#include "zombie/SoundManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoJukebox : public IsoObject {
public:
 Audio JukeboxTrack = nullptr;
 bool IsPlaying = false;
 float MusicRadius = 30.0F;
 bool Activated = false;
 int WorldSoundPulseRate = 150;
 int WorldSoundPulseDelay = 0;

public
 IsoJukebox(IsoCell cell, IsoGridSquare sq, IsoSprite spr) {
 super(cell, sq, spr);
 }

 std::string getObjectName() { return "Jukebox"; }

public
 IsoJukebox(IsoCell cell) { super(cell); }

public
 IsoJukebox(IsoCell cell, IsoGridSquare sq, const std::string &gid) {
 super(cell, sq, gid);
 this->JukeboxTrack = nullptr;
 this->IsPlaying = false;
 this->Activated = false;
 this->WorldSoundPulseDelay = 0;
 }

 void addToWorld() {
 super.addToWorld();
 this->getCell().addToStaticUpdaterObjectList(this);
 }

 void SetPlaying(bool ShouldPlay) {
 if (this->IsPlaying != ShouldPlay) {
 this->IsPlaying = ShouldPlay;
 if (this->IsPlaying && this->JukeboxTrack.empty()) {
 std::string string = nullptr;
 switch (Rand.Next(4) {
 case 0:
 string = "paws1";
 break;
 case 1:
 string = "paws2";
 break;
 case 2:
 string = "paws3";
 break;
 case 3:
 string = "paws4";
 }

 this->JukeboxTrack =
 SoundManager.instance.PlaySound(string, false, 0.0F);
 }
 }
 }

 bool onMouseLeftClick(int x, int y) {
 IsoPlayer player = IsoPlayer.getInstance();
 if (player.empty() || player.isDead()) {
 return false;
 } else if (IsoPlayer.getInstance().getCurrentSquare() == nullptr) {
 return false;
 } else {
 float float0 = 0.0F;
 int int0 =
 Math.abs(this->square.getX() -
 IsoPlayer.getInstance().getCurrentSquare().getX()) +
 Math.abs(this->square.getY() -
 IsoPlayer.getInstance().getCurrentSquare().getY() +
 Math.abs(this->square.getZ() -
 IsoPlayer.getInstance().getCurrentSquare().getZ()));
 if (int0 < 4) {
 if (!this->Activated) {
 if (Core.NumJukeBoxesActive < Core.MaxJukeBoxesActive) {
 this->WorldSoundPulseDelay = 0;
 this->Activated = true;
 this->SetPlaying(true);
 Core.NumJukeBoxesActive++;
 }
 } else {
 this->WorldSoundPulseDelay = 0;
 this->SetPlaying(false);
 this->Activated = false;
 if (this->JukeboxTrack != nullptr) {
 SoundManager.instance.StopSound(this->JukeboxTrack);
 this->JukeboxTrack.stop();
 this->JukeboxTrack = nullptr;
 }

 Core.NumJukeBoxesActive--;
 }
 }

 return true;
 }
 }

 void update() {
 if (IsoPlayer.getInstance() != nullptr) {
 if (IsoPlayer.getInstance().getCurrentSquare() != nullptr) {
 if (this->Activated) {
 float float0 = 0.0F;
 int int0 =
 Math.abs(this->square.getX() -
 IsoPlayer.getInstance().getCurrentSquare().getX()) +
 Math.abs(
 this->square.getY() -
 IsoPlayer.getInstance().getCurrentSquare().getY() +
 Math.abs(this->square.getZ() -
 IsoPlayer.getInstance().getCurrentSquare().getZ()));
 if (int0 < this->MusicRadius) {
 this->SetPlaying(true);
 float0 = (this->MusicRadius - int0) / this->MusicRadius;
 }

 if (this->JukeboxTrack != nullptr) {
 float float1 = float0 + 0.2F;
 if (float1 > 1.0F) {
 float1 = 1.0F;
 }

 SoundManager.instance.BlendVolume(this->JukeboxTrack, float0);
 if (this->WorldSoundPulseDelay > 0) {
 this->WorldSoundPulseDelay--;
 }

 if (this->WorldSoundPulseDelay == 0) {
 WorldSoundManager.instance.addSound(
 IsoPlayer.getInstance(), this->square.getX(),
 this->square.getY(), this->square.getZ(), 70, 70, true);
 this->WorldSoundPulseDelay = this->WorldSoundPulseRate;
 }

 if (!this->JukeboxTrack.isPlaying()) {
 this->WorldSoundPulseDelay = 0;
 this->SetPlaying(false);
 this->Activated = false;
 if (this->JukeboxTrack != nullptr) {
 SoundManager.instance.StopSound(this->JukeboxTrack);
 this->JukeboxTrack.stop();
 this->JukeboxTrack = nullptr;
 }

 Core.NumJukeBoxesActive--;
 }
 }
 }
 }
 }
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
