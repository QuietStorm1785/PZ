#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/scripting/ScriptParser.h"

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GameSoundScript : public BaseScriptObject {
public:
 const GameSound gameSound = new GameSound();

 void Load(const std::string& name, const std::string& totalFile) {
 this->gameSound.name = name;
 ScriptParser.Block block0 = ScriptParser.parse(totalFile);
 block0 = block0.children.get(0);

 for (ScriptParser.Value value : block0.values) {
 String[] strings = value.string.split("=");
 std::string string0 = strings[0].trim();
 std::string string1 = strings[1].trim();
 if ("category" == string0) {
 this->gameSound.category = string1;
 } else if ("is3D" == string0) {
 this->gameSound.is3D = Boolean.parseBoolean(string1);
 } else if ("loop" == string0) {
 this->gameSound.loop = Boolean.parseBoolean(string1);
 } else if ("master" == string0) {
 this->gameSound.master = GameSound.MasterVolume.valueOf(string1);
 } else if ("maxInstancesPerEmitter" == string0) {
 this->gameSound.maxInstancesPerEmitter = PZMath.tryParseInt(string1, -1);
 }
 }

 for (ScriptParser.Block block1 : block0.children) {
 if ("clip" == block1.type) {
 GameSoundClip gameSoundClip = this->LoadClip(block1);
 this->gameSound.clips.add(gameSoundClip);
 }
 }
 }

 GameSoundClip LoadClip(ScriptParser.Block block) {
 GameSoundClip gameSoundClip = new GameSoundClip(this->gameSound);

 for (ScriptParser.Value value : block.values) {
 String[] strings = value.string.split("=");
 std::string string0 = strings[0].trim();
 std::string string1 = strings[1].trim();
 if ("distanceMax" == string0) {
 gameSoundClip.distanceMax = Integer.parseInt(string1);
 gameSoundClip.initFlags = (short)(gameSoundClip.initFlags | GameSoundClip.INIT_FLAG_DISTANCE_MAX);
 } else if ("distanceMin" == string0) {
 gameSoundClip.distanceMin = Integer.parseInt(string1);
 gameSoundClip.initFlags = (short)(gameSoundClip.initFlags | GameSoundClip.INIT_FLAG_DISTANCE_MIN);
 } else if ("event" == string0) {
 gameSoundClip.event = string1;
 } else if ("file" == string0) {
 gameSoundClip.file = string1;
 } else if ("pitch" == string0) {
 gameSoundClip.pitch = Float.parseFloat(string1);
 } else if ("volume" == string0) {
 gameSoundClip.volume = Float.parseFloat(string1);
 } else if ("reverbFactor" == string0) {
 gameSoundClip.reverbFactor = Float.parseFloat(string1);
 } else if ("reverbMaxRange" == string0) {
 gameSoundClip.reverbMaxRange = Float.parseFloat(string1);
 }
 }

 return gameSoundClip;
 }

 void reset() {
 this->gameSound.reset();
 }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
