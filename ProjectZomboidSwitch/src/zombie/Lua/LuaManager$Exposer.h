#pragma once
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/EmitterType.h"
#include "fmod/fmod/FMODAudio.h"
#include "fmod/fmod/FMODSoundBank.h"
#include "fmod/fmod/FMODSoundEmitter.h"
#include "java/text/SimpleDateFormat.h"
#include "org/joml/Vector2f.h"
#include "org/joml/Vector3f.h"
#include "org/lwjglx/input/Keyboard.h"
#include "se/krka/kahlua/converter/KahluaConverterManager.h"
#include "se/krka/kahlua/integration/expose/LuaJavaClassExposer.h"
#include "se/krka/kahlua/vm/Coroutine.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "se/krka/kahlua/vm/Platform.h"
#include "zombie/AmbientStreamManager.h"
#include "zombie/BaseAmbientStreamManager.h"
#include "zombie/DummySoundManager.h"
#include "zombie/GameSounds.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager/GlobalObject.h"
#include "zombie/Lua/LuaManager/GlobalObject/LuaFileWriter.h"
#include "zombie/MapGroups.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SandboxOptions/BooleanSandboxOption.h"
#include "zombie/SandboxOptions/DoubleSandboxOption.h"
#include "zombie/SandboxOptions/EnumSandboxOption.h"
#include "zombie/SandboxOptions/IntegerSandboxOption.h"
#include "zombie/SandboxOptions/StringSandboxOption.h"
#include "zombie/SoundManager.h"
#include "zombie/SoundManager/AmbientSoundEffect.h"
#include "zombie/SystemDisabler.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/WorldSoundManager/WorldSound.h"
#include "zombie/ai/GameCharacterAIBrain.h"
#include "zombie/ai/MapKnowledge.h"
#include "zombie/ai/sadisticAIDirector/SleepingEvent.h"
#include "zombie/ai/states/AttackState.h"
#include "zombie/ai/states/BurntToDeath.h"
#include "zombie/ai/states/ClimbDownSheetRopeState.h"
#include "zombie/ai/states/ClimbOverFenceState.h"
#include "zombie/ai/states/ClimbOverWallState.h"
#include "zombie/ai/states/ClimbSheetRopeState.h"
#include "zombie/ai/states/ClimbThroughWindowState.h"
#include "zombie/ai/states/CloseWindowState.h"
#include "zombie/ai/states/CrawlingZombieTurnState.h"
#include "zombie/ai/states/FakeDeadAttackState.h"
#include "zombie/ai/states/FakeDeadZombieState.h"
#include "zombie/ai/states/FishingState.h"
#include "zombie/ai/states/FitnessState.h"
#include "zombie/ai/states/IdleState.h"
#include "zombie/ai/states/LungeState.h"
#include "zombie/ai/states/OpenWindowState.h"
#include "zombie/ai/states/PathFindState.h"
#include "zombie/ai/states/PlayerActionsState.h"
#include "zombie/ai/states/PlayerAimState.h"
#include "zombie/ai/states/PlayerEmoteState.h"
#include "zombie/ai/states/PlayerExtState.h"
#include "zombie/ai/states/PlayerFallDownState.h"
#include "zombie/ai/states/PlayerFallingState.h"
#include "zombie/ai/states/PlayerGetUpState.h"
#include "zombie/ai/states/PlayerHitReactionPVPState.h"
#include "zombie/ai/states/PlayerHitReactionState.h"
#include "zombie/ai/states/PlayerKnockedDown.h"
#include "zombie/ai/states/PlayerOnGroundState.h"
#include "zombie/ai/states/PlayerSitOnGroundState.h"
#include "zombie/ai/states/PlayerStrafeState.h"
#include "zombie/ai/states/SmashWindowState.h"
#include "zombie/ai/states/StaggerBackState.h"
#include "zombie/ai/states/SwipeStatePlayer.h"
#include "zombie/ai/states/ThumpState.h"
#include "zombie/ai/states/WalkTowardState.h"
#include "zombie/ai/states/ZombieFallDownState.h"
#include "zombie/ai/states/ZombieGetDownState.h"
#include "zombie/ai/states/ZombieGetUpState.h"
#include "zombie/ai/states/ZombieIdleState.h"
#include "zombie/ai/states/ZombieOnGroundState.h"
#include "zombie/ai/states/ZombieReanimateState.h"
#include "zombie/ai/states/ZombieSittingState.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/DummySoundBank.h"
#include "zombie/audio/DummySoundEmitter.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/BloodClothingType.h"
#include "zombie/characters/AttachedItems/AttachedItem.h"
#include "zombie/characters/AttachedItems/AttachedItems.h"
#include "zombie/characters/AttachedItems/AttachedLocation.h"
#include "zombie/characters/AttachedItems/AttachedLocationGroup.h"
#include "zombie/characters/AttachedItems/AttachedLocations.h"
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/BodyDamage/Fitness.h"
#include "zombie/characters/BodyDamage/Metabolics.h"
#include "zombie/characters/BodyDamage/Nutrition.h"
#include "zombie/characters/BodyDamage/Thermoregulator.h"
#include "zombie/characters/BodyDamage/Thermoregulator/ThermalNode.h"
#include "zombie/characters/CharacterActionAnims.h"
#include "zombie/characters/CharacterSoundEmitter.h"
#include "zombie/characters/CharacterTimedActions/LuaTimedAction.h"
#include "zombie/characters/CharacterTimedActions/LuaTimedActionNew.h"
#include "zombie/characters/DummyCharacterSoundEmitter.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/HaloTextHelper.h"
#include "zombie/characters/HaloTextHelper/ColorRGB.h"
#include "zombie/characters/IsoDummyCameraCharacter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoGameCharacter/CharacterTraits.h"
#include "zombie/characters/IsoGameCharacter/Location.h"
#include "zombie/characters/IsoGameCharacter/PerkInfo.h"
#include "zombie/characters/IsoGameCharacter/XP.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/Moodles/Moodle.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/Moodles/Moodles.h"
#include "zombie/characters/Safety.h"
#include "zombie/characters/Stats.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/SurvivorFactory.h"
#include "zombie/characters/SurvivorFactory/SurvivorType.h"
#include "zombie/characters/WornItems/BodyLocation.h"
#include "zombie/characters/WornItems/BodyLocationGroup.h"
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/characters/WornItems/WornItem.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/characters/professions/ProfessionFactory.h"
#include "zombie/characters/professions/ProfessionFactory/Profession.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/characters/skills/PerkFactory/Perk.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/characters/traits/ObservationFactory.h"
#include "zombie/characters/traits/ObservationFactory/Observation.h"
#include "zombie/characters/traits/TraitCollection.h"
#include "zombie/characters/traits/TraitCollection/TraitSlot.h"
#include "zombie/characters/traits/TraitFactory.h"
#include "zombie/characters/traits/TraitFactory/Trait.h"
#include "zombie/chat/ChatBase.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/chat/ServerChatMessage.h"
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/config/DoubleConfigOption.h"
#include "zombie/config/EnumConfigOption.h"
#include "zombie/config/IntegerConfigOption.h"
#include "zombie/config/StringConfigOption.h"
#include "zombie/core/Clipboard.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/Core.h"
#include "zombie/core/GameVersion.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/Language.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/Translator.h"
#include "zombie/core/fonts/AngelCodeFont.h"
#include "zombie/core/logger/ZLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor.h"
#include "zombie/core/skinnedmodel/population/BeardStyle.h"
#include "zombie/core/skinnedmodel/population/BeardStyles.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/population/HairStyle.h"
#include "zombie/core/skinnedmodel/population/HairStyles.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/stash/Stash.h"
#include "zombie/core/stash/StashBuilding.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/znet/SteamFriend.h"
#include "zombie/core/znet/SteamUGCDetails.h"
#include "zombie/core/znet/SteamWorkshopItem.h"
#include "zombie/debug/BooleanDebugOption.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/erosion/ErosionConfig.h"
#include "zombie/erosion/ErosionConfig/Debug.h"
#include "zombie/erosion/ErosionConfig/Season.h"
#include "zombie/erosion/ErosionConfig/Seeds.h"
#include "zombie/erosion/ErosionConfig/Time.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/erosion/season/ErosionSeason.h"
#include "zombie/gameStates/AnimationViewerState.h"
#include "zombie/gameStates/AttachmentEditorState.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/gameStates/DebugChunkState.h"
#include "zombie/gameStates/DebugGlobalObjectState.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/gameStates/LoadingQueueState.h"
#include "zombie/gameStates/MainScreenState.h"
#include "zombie/gameStates/TermsOfServiceState.h"
#include "zombie/globalObjects/CGlobalObject.h"
#include "zombie/globalObjects/CGlobalObjectSystem.h"
#include "zombie/globalObjects/CGlobalObjects.h"
#include "zombie/globalObjects/SGlobalObject.h"
#include "zombie/globalObjects/SGlobalObjectSystem.h"
#include "zombie/globalObjects/SGlobalObjects.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/Mouse.h"
#include "zombie/inventory/FixingManager.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/inventory/RecipeManager.h"
#include "zombie/inventory/types/AlarmClock.h"
#include "zombie/inventory/types/AlarmClockClothing.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/Clothing/ClothingPatch.h"
#include "zombie/inventory/types/Clothing/ClothingPatchFabricType.h"
#include "zombie/inventory/types/ComboItem.h"
#include "zombie/inventory/types/Drainable.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/Key.h"
#include "zombie/inventory/types/KeyRing.h"
#include "zombie/inventory/types/Literature.h"
#include "zombie/inventory/types/MapItem.h"
#include "zombie/inventory/types/Moveable.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/inventory/types/WeaponPart.h"
#include "zombie/inventory/types/WeaponType.h"
#include "zombie/iso/BentFences.h"
#include "zombie/iso/BrokenFences.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/ContainerOverlays.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoDirectionSet.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoHeatSource.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoLot.h"
#include "zombie/iso/IsoLuaMover.h"
#include "zombie/iso/IsoMarkers.h"
#include "zombie/iso/IsoMarkers/CircleIsoMarker.h"
#include "zombie/iso/IsoMarkers/IsoMarker.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaChunk.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoMetaGrid/Trigger.h"
#include "zombie/iso/IsoMetaGrid/VehicleZone.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoPuddles.h"
#include "zombie/iso/IsoPuddles/PuddlesFloat.h"
#include "zombie/iso/IsoPushableObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWaterGeometry.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/MetaObject.h"
#include "zombie/iso/MultiStageBuilding.h"
#include "zombie/iso/MultiStageBuilding/Stage.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/SearchMode.h"
#include "zombie/iso/SearchMode/PlayerSearchMode.h"
#include "zombie/iso/SearchMode/SearchModeFloat.h"
#include "zombie/iso/SliceY.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/TileOverlays.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include "zombie/iso/WorldMarkers.h"
#include "zombie/iso/WorldMarkers/DirectionArrow.h"
#include "zombie/iso/WorldMarkers/GridSquareMarker.h"
#include "zombie/iso/WorldMarkers/PlayerHomingPoint.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/areas/isoregion/IsoRegionLogType.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/areas/isoregion/IsoRegionsLogger.h"
#include "zombie/iso/areas/isoregion/IsoRegionsLogger/IsoRegionLog.h"
#include "zombie/iso/areas/isoregion/IsoRegionsRenderer.h"
#include "zombie/iso/areas/isoregion/data/DataCell.h"
#include "zombie/iso/areas/isoregion/data/DataChunk.h"
#include "zombie/iso/areas/isoregion/regions/IsoChunkRegion.h"
#include "zombie/iso/areas/isoregion/regions/IsoWorldRegion.h"
#include "zombie/iso/objects/BSFurnace.h"
#include "zombie/iso/objects/IsoBarbecue.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoBrokenGlass.h"
#include "zombie/iso/objects/IsoCarBatteryCharger.h"
#include "zombie/iso/objects/IsoClothingDryer.h"
#include "zombie/iso/objects/IsoClothingWasher.h"
#include "zombie/iso/objects/IsoCombinationWasherDryer.h"
#include "zombie/iso/objects/IsoCompost.h"
#include "zombie/iso/objects/IsoCurtain.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoFire.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/iso/objects/IsoFireplace.h"
#include "zombie/iso/objects/IsoGenerator.h"
#include "zombie/iso/objects/IsoJukebox.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoMannequin.h"
#include "zombie/iso/objects/IsoMolotovCocktail.h"
#include "zombie/iso/objects/IsoRadio.h"
#include "zombie/iso/objects/IsoStackedWasherDryer.h"
#include "zombie/iso/objects/IsoStove.h"
#include "zombie/iso/objects/IsoTelevision.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoTrap.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWaveSignal.h"
#include "zombie/iso/objects/IsoWheelieBin.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/iso/objects/ObjectRenderEffects.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/iso/objects/interfaces/BarricadeAble.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteGrid.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/iso/weather/ClimateColorInfo.h"
#include "zombie/iso/weather/ClimateForecaster.h"
#include "zombie/iso/weather/ClimateForecaster/DayForecast.h"
#include "zombie/iso/weather/ClimateForecaster/ForecastValue.h"
#include "zombie/iso/weather/ClimateHistory.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/ClimateManager/AirFront.h"
#include "zombie/iso/weather/ClimateManager/ClimateBool.h"
#include "zombie/iso/weather/ClimateManager/ClimateColor.h"
#include "zombie/iso/weather/ClimateManager/ClimateFloat.h"
#include "zombie/iso/weather/ClimateManager/DayInfo.h"
#include "zombie/iso/weather/ClimateMoon.h"
#include "zombie/iso/weather/ClimateValues.h"
#include "zombie/iso/weather/Temperature.h"
#include "zombie/iso/weather/ThunderStorm.h"
#include "zombie/iso/weather/ThunderStorm/ThunderCloud.h"
#include "zombie/iso/weather/WeatherPeriod.h"
#include "zombie/iso/weather/WeatherPeriod/StrLerpVal.h"
#include "zombie/iso/weather/WeatherPeriod/WeatherStage.h"
#include "zombie/iso/weather/WorldFlares.h"
#include "zombie/iso/weather/WorldFlares/Flare.h"
#include "zombie/iso/weather/fog/ImprovedFog.h"
#include "zombie/iso/weather/fx/IsoWeatherFX.h"
#include "zombie/modding/ActiveMods.h"
#include "zombie/network/DBResult.h"
#include "zombie/network/DBTicket.h"
#include "zombie/network/NetworkAIParams.h"
#include "zombie/network/Server.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/ServerOptions/BooleanServerOption.h"
#include "zombie/network/ServerOptions/DoubleServerOption.h"
#include "zombie/network/ServerOptions/IntegerServerOption.h"
#include "zombie/network/ServerOptions/StringServerOption.h"
#include "zombie/network/ServerOptions/TextServerOption.h"
#include "zombie/network/ServerSettings.h"
#include "zombie/network/ServerSettingsManager.h"
#include "zombie/network/Userlog.h"
#include "zombie/network/Userlog/UserlogType.h"
#include "zombie/popman/ZombiePopulationRenderer.h"
#include "zombie/radio/ChannelCategory.h"
#include "zombie/radio/RadioAPI.h"
#include "zombie/radio/RadioData.h"
#include "zombie/radio/StorySounds/DataPoint.h"
#include "zombie/radio/StorySounds/EventSound.h"
#include "zombie/radio/StorySounds/SLSoundManager.h"
#include "zombie/radio/StorySounds/StorySound.h"
#include "zombie/radio/StorySounds/StorySoundEvent.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/devices/DeviceData.h"
#include "zombie/radio/devices/DevicePresets.h"
#include "zombie/radio/devices/PresetEntry.h"
#include "zombie/radio/media/MediaData.h"
#include "zombie/radio/media/MediaData/MediaLineData.h"
#include "zombie/radio/media/RecordedMedia.h"
#include "zombie/radio/scripting/DynamicRadioChannel.h"
#include "zombie/radio/scripting/RadioBroadCast.h"
#include "zombie/radio/scripting/RadioChannel.h"
#include "zombie/radio/scripting/RadioLine.h"
#include "zombie/radio/scripting/RadioScript.h"
#include "zombie/radio/scripting/RadioScript/ExitOption.h"
#include "zombie/radio/scripting/RadioScriptManager.h"
#include "zombie/randomizedWorld/RandomizedWorldBase.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBBar.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBBasic.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBBurnt.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBBurntCorpse.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBBurntFireman.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBCafe.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBClinic.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBHairSalon.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBKateAndBaldspot.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBLooted.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBOffice.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBOther.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBPileOCrepe.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBPizzaWhirled.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBSafehouse.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBSchool.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBShopLooted.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBSpiffo.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBStripclub.h"
#include "zombie/randomizedWorld/randomizedBuilding/RandomizedBuildingBase.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSBandPractice.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSBathroomZed.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSBedroomZed.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSBleach.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSCorpsePsycho.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSDeadDrunk.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSFootballNight.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSGunmanInBathroom.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSGunslinger.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSHenDo.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSHockeyPsycho.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSHouseParty.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSPokerNight.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSPoliceAtHouse.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSPrisonEscape.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSPrisonEscapeWithPolice.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSSkeletonPsycho.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSSpecificProfession.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSStagDo.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSStudentNight.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSSuicidePact.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSTinFoilHat.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSZombieLockedBathroom.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSZombiesEating.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RandomizedDeadSurvivorBase.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSAmbulanceCrash.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSBanditRoad.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSBurntCar.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSCarCrash.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSCarCrashCorpse.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSChangingTire.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSConstructionSite.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSCrashHorde.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSFlippedCrash.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSPoliceBlockade.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSPoliceBlockadeShooting.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSTrailerCrash.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSUtilityVehicle.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RandomizedVehicleStoryBase.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSBBQParty.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSBaseball.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSBeachParty.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSBuryingCamp.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSFishingTrip.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSForestCamp.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSForestCampEaten.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSHunterCamp.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSMusicFest.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSMusicFestStage.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSSexyTime.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSTrapperCamp.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RandomizedZoneStoryBase.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/EvolvedRecipe.h"
#include "zombie/scripting/objects/Fixing.h"
#include "zombie/scripting/objects/Fixing/Fixer.h"
#include "zombie/scripting/objects/Fixing/FixerSkill.h"
#include "zombie/scripting/objects/GameSoundScript.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/scripting/objects/ItemRecipe.h"
#include "zombie/scripting/objects/MannequinScript.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/scripting/objects/MovableRecipe.h"
#include "zombie/scripting/objects/Recipe.h"
#include "zombie/scripting/objects/Recipe/RequiredSkill.h"
#include "zombie/scripting/objects/Recipe/Result.h"
#include "zombie/scripting/objects/Recipe/Source.h"
#include "zombie/scripting/objects/ScriptModule.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/scripting/objects/VehicleScript/Area.h"
#include "zombie/scripting/objects/VehicleScript/Model.h"
#include "zombie/scripting/objects/VehicleScript/Part.h"
#include "zombie/scripting/objects/VehicleScript/Passenger.h"
#include "zombie/scripting/objects/VehicleScript/PhysicsShape.h"
#include "zombie/scripting/objects/VehicleScript/Position.h"
#include "zombie/scripting/objects/VehicleScript/Wheel.h"
#include "zombie/text/templating/ReplaceProviderCharacter.h"
#include "zombie/text/templating/TemplateText.h"
#include "zombie/ui/ActionProgressBar.h"
#include "zombie/ui/Clock.h"
#include "zombie/ui/ModalDialog.h"
#include "zombie/ui/MoodlesUI.h"
#include "zombie/ui/NewHealthPanel.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/ui/ObjectTooltip/Layout.h"
#include "zombie/ui/ObjectTooltip/LayoutItem.h"
#include "zombie/ui/RadarPanel.h"
#include "zombie/ui/RadialMenu.h"
#include "zombie/ui/RadialProgressBar.h"
#include "zombie/ui/SpeedControls.h"
#include "zombie/ui/TextDrawObject.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UI3DModel.h"
#include "zombie/ui/UIDebugConsole.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"
#include "zombie/ui/UIServerToolbox.h"
#include "zombie/ui/UITextBox2.h"
#include "zombie/ui/UITransition.h"
#include "zombie/ui/VehicleGauge.h"
#include "zombie/util/PZCalendar.h"
#include "zombie/util/list/PZArrayList.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/EditVehicleState.h"
#include "zombie/vehicles/PathFindBehavior2.h"
#include "zombie/vehicles/PathFindBehavior2/BehaviorResult.h"
#include "zombie/vehicles/PathFindState2.h"
#include "zombie/vehicles/UI3DScene.h"
#include "zombie/vehicles/VehicleDoor.h"
#include "zombie/vehicles/VehicleLight.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/vehicles/VehicleType.h"
#include "zombie/vehicles/VehicleWindow.h"
#include "zombie/world/moddata/ModData.h"
#include "zombie/worldMap/UIWorldMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace Lua {


class LuaManager {
public:
   private const std::unordered_set<Class<?>> exposed = std::make_unique<std::unordered_set<>>();

   public LuaManager$Exposer(KahluaConverterManager var1, Platform var2, KahluaTable var3) {
      super(var1, var2, var3);
   }

    void exposeAll() {
      this.setExposed(BufferedReader.class);
      this.setExposed(BufferedWriter.class);
      this.setExposed(DataInputStream.class);
      this.setExposed(DataOutputStream.class);
      this.setExposed(double.class);
      this.setExposed(int64_t.class);
      this.setExposed(float.class);
      this.setExposed(int.class);
      this.setExposed(Math.class);
      this.setExposed(Void.class);
      this.setExposed(SimpleDateFormat.class);
      this.setExposed(std::vector.class);
      this.setExposed(EnumMap.class);
      this.setExposed(std::unordered_map.class);
      this.setExposed(std::list.class);
      this.setExposed(std::stack.class);
      this.setExposed(Vector.class);
      this.setExposed(Iterator.class);
      this.setExposed(EmitterType.class);
      this.setExposed(FMODAudio.class);
      this.setExposed(FMODSoundBank.class);
      this.setExposed(FMODSoundEmitter.class);
      this.setExposed(Vector2f.class);
      this.setExposed(Vector3f.class);
      this.setExposed(KahluaUtil.class);
      this.setExposed(DummySoundBank.class);
      this.setExposed(DummySoundEmitter.class);
      this.setExposed(BaseSoundEmitter.class);
      this.setExposed(GameSound.class);
      this.setExposed(GameSoundClip.class);
      this.setExposed(AttackState.class);
      this.setExposed(BurntToDeath.class);
      this.setExposed(ClimbDownSheetRopeState.class);
      this.setExposed(ClimbOverFenceState.class);
      this.setExposed(ClimbOverWallState.class);
      this.setExposed(ClimbSheetRopeState.class);
      this.setExposed(ClimbThroughWindowState.class);
      this.setExposed(CloseWindowState.class);
      this.setExposed(CrawlingZombieTurnState.class);
      this.setExposed(FakeDeadAttackState.class);
      this.setExposed(FakeDeadZombieState.class);
      this.setExposed(FishingState.class);
      this.setExposed(FitnessState.class);
      this.setExposed(IdleState.class);
      this.setExposed(LungeState.class);
      this.setExposed(OpenWindowState.class);
      this.setExposed(PathFindState.class);
      this.setExposed(PlayerActionsState.class);
      this.setExposed(PlayerAimState.class);
      this.setExposed(PlayerEmoteState.class);
      this.setExposed(PlayerExtState.class);
      this.setExposed(PlayerFallDownState.class);
      this.setExposed(PlayerFallingState.class);
      this.setExposed(PlayerGetUpState.class);
      this.setExposed(PlayerHitReactionPVPState.class);
      this.setExposed(PlayerHitReactionState.class);
      this.setExposed(PlayerKnockedDown.class);
      this.setExposed(PlayerOnGroundState.class);
      this.setExposed(PlayerSitOnGroundState.class);
      this.setExposed(PlayerStrafeState.class);
      this.setExposed(SmashWindowState.class);
      this.setExposed(StaggerBackState.class);
      this.setExposed(SwipeStatePlayer.class);
      this.setExposed(ThumpState.class);
      this.setExposed(WalkTowardState.class);
      this.setExposed(ZombieFallDownState.class);
      this.setExposed(ZombieGetDownState.class);
      this.setExposed(ZombieGetUpState.class);
      this.setExposed(ZombieIdleState.class);
      this.setExposed(ZombieOnGroundState.class);
      this.setExposed(ZombieReanimateState.class);
      this.setExposed(ZombieSittingState.class);
      this.setExposed(GameCharacterAIBrain.class);
      this.setExposed(MapKnowledge.class);
      this.setExposed(BodyPartType.class);
      this.setExposed(BodyPart.class);
      this.setExposed(BodyDamage.class);
      this.setExposed(Thermoregulator.class);
      this.setExposed(ThermalNode.class);
      this.setExposed(Metabolics.class);
      this.setExposed(Fitness.class);
      this.setExposed(GameKeyboard.class);
      this.setExposed(LuaTimedAction.class);
      this.setExposed(LuaTimedActionNew.class);
      this.setExposed(Moodle.class);
      this.setExposed(Moodles.class);
      this.setExposed(MoodleType.class);
      this.setExposed(ProfessionFactory.class);
      this.setExposed(Profession.class);
      this.setExposed(PerkFactory.class);
      this.setExposed(Perk.class);
      this.setExposed(Perks.class);
      this.setExposed(ObservationFactory.class);
      this.setExposed(Observation.class);
      this.setExposed(TraitFactory.class);
      this.setExposed(Trait.class);
      this.setExposed(IsoDummyCameraCharacter.class);
      this.setExposed(Stats.class);
      this.setExposed(SurvivorDesc.class);
      this.setExposed(SurvivorFactory.class);
      this.setExposed(SurvivorType.class);
      this.setExposed(IsoGameCharacter.class);
      this.setExposed(Location.class);
      this.setExposed(PerkInfo.class);
      this.setExposed(XP.class);
      this.setExposed(CharacterTraits.class);
      this.setExposed(TraitSlot.class);
      this.setExposed(TraitCollection.class);
      this.setExposed(IsoPlayer.class);
      this.setExposed(IsoSurvivor.class);
      this.setExposed(IsoZombie.class);
      this.setExposed(CharacterActionAnims.class);
      this.setExposed(HaloTextHelper.class);
      this.setExposed(ColorRGB.class);
      this.setExposed(NetworkAIParams.class);
      this.setExposed(BloodBodyPartType.class);
      this.setExposed(Clipboard.class);
      this.setExposed(AngelCodeFont.class);
      this.setExposed(ZLogger.class);
      this.setExposed(PropertyContainer.class);
      this.setExposed(ClothingItem.class);
      this.setExposed(AnimatorDebugMonitor.class);
      this.setExposed(ColorInfo.class);
      this.setExposed(Texture.class);
      this.setExposed(SteamFriend.class);
      this.setExposed(SteamUGCDetails.class);
      this.setExposed(SteamWorkshopItem.class);
      this.setExposed(Color.class);
      this.setExposed(Colors.class);
      this.setExposed(Core.class);
      this.setExposed(GameVersion.class);
      this.setExposed(ImmutableColor.class);
      this.setExposed(Language.class);
      this.setExposed(PerformanceSettings.class);
      this.setExposed(SpriteRenderer.class);
      this.setExposed(Translator.class);
      this.setExposed(PZMath.class);
      this.setExposed(DebugLog.class);
      this.setExposed(DebugOptions.class);
      this.setExposed(BooleanDebugOption.class);
      this.setExposed(DebugType.class);
      this.setExposed(ErosionConfig.class);
      this.setExposed(Debug.class);
      this.setExposed(Season.class);
      this.setExposed(Seeds.class);
      this.setExposed(Time.class);
      this.setExposed(ErosionMain.class);
      this.setExposed(ErosionSeason.class);
      this.setExposed(AnimationViewerState.class);
      this.setExposed(zombie.gameStates.AnimationViewerState.BooleanDebugOption.class);
      this.setExposed(AttachmentEditorState.class);
      this.setExposed(Mod.class);
      this.setExposed(DebugChunkState.class);
      this.setExposed(zombie.gameStates.DebugChunkState.BooleanDebugOption.class);
      this.setExposed(DebugGlobalObjectState.class);
      this.setExposed(GameLoadingState.class);
      this.setExposed(LoadingQueueState.class);
      this.setExposed(MainScreenState.class);
      this.setExposed(TermsOfServiceState.class);
      this.setExposed(CGlobalObject.class);
      this.setExposed(CGlobalObjects.class);
      this.setExposed(CGlobalObjectSystem.class);
      this.setExposed(SGlobalObject.class);
      this.setExposed(SGlobalObjects.class);
      this.setExposed(SGlobalObjectSystem.class);
      this.setExposed(Mouse.class);
      this.setExposed(AlarmClock.class);
      this.setExposed(AlarmClockClothing.class);
      this.setExposed(Clothing.class);
      this.setExposed(ClothingPatch.class);
      this.setExposed(ClothingPatchFabricType.class);
      this.setExposed(ComboItem.class);
      this.setExposed(Drainable.class);
      this.setExposed(DrainableComboItem.class);
      this.setExposed(Food.class);
      this.setExposed(HandWeapon.class);
      this.setExposed(InventoryContainer.class);
      this.setExposed(Key.class);
      this.setExposed(KeyRing.class);
      this.setExposed(Literature.class);
      this.setExposed(MapItem.class);
      this.setExposed(Moveable.class);
      this.setExposed(Radio.class);
      this.setExposed(WeaponPart.class);
      this.setExposed(ItemContainer.class);
      this.setExposed(ItemPickerJava.class);
      this.setExposed(InventoryItem.class);
      this.setExposed(InventoryItemFactory.class);
      this.setExposed(FixingManager.class);
      this.setExposed(RecipeManager.class);
      this.setExposed(IsoRegions.class);
      this.setExposed(IsoRegionsLogger.class);
      this.setExposed(IsoRegionLog.class);
      this.setExposed(IsoRegionLogType.class);
      this.setExposed(DataCell.class);
      this.setExposed(DataChunk.class);
      this.setExposed(IsoChunkRegion.class);
      this.setExposed(IsoWorldRegion.class);
      this.setExposed(IsoRegionsRenderer.class);
      this.setExposed(zombie.iso.areas.isoregion.IsoRegionsRenderer.BooleanDebugOption.class);
      this.setExposed(IsoBuilding.class);
      this.setExposed(IsoRoom.class);
      this.setExposed(SafeHouse.class);
      this.setExposed(BarricadeAble.class);
      this.setExposed(IsoBarbecue.class);
      this.setExposed(IsoBarricade.class);
      this.setExposed(IsoBrokenGlass.class);
      this.setExposed(IsoClothingDryer.class);
      this.setExposed(IsoClothingWasher.class);
      this.setExposed(IsoCombinationWasherDryer.class);
      this.setExposed(IsoStackedWasherDryer.class);
      this.setExposed(IsoCurtain.class);
      this.setExposed(IsoCarBatteryCharger.class);
      this.setExposed(IsoDeadBody.class);
      this.setExposed(IsoDoor.class);
      this.setExposed(IsoFire.class);
      this.setExposed(IsoFireManager.class);
      this.setExposed(IsoFireplace.class);
      this.setExposed(IsoGenerator.class);
      this.setExposed(IsoJukebox.class);
      this.setExposed(IsoLightSwitch.class);
      this.setExposed(IsoMannequin.class);
      this.setExposed(IsoMolotovCocktail.class);
      this.setExposed(IsoWaveSignal.class);
      this.setExposed(IsoRadio.class);
      this.setExposed(IsoTelevision.class);
      this.setExposed(IsoStackedWasherDryer.class);
      this.setExposed(IsoStove.class);
      this.setExposed(IsoThumpable.class);
      this.setExposed(IsoTrap.class);
      this.setExposed(IsoTree.class);
      this.setExposed(IsoWheelieBin.class);
      this.setExposed(IsoWindow.class);
      this.setExposed(IsoWindowFrame.class);
      this.setExposed(IsoWorldInventoryObject.class);
      this.setExposed(IsoZombieGiblets.class);
      this.setExposed(RainManager.class);
      this.setExposed(ObjectRenderEffects.class);
      this.setExposed(HumanVisual.class);
      this.setExposed(ItemVisual.class);
      this.setExposed(ItemVisuals.class);
      this.setExposed(IsoSprite.class);
      this.setExposed(IsoSpriteInstance.class);
      this.setExposed(IsoSpriteManager.class);
      this.setExposed(IsoSpriteGrid.class);
      this.setExposed(IsoFlagType.class);
      this.setExposed(IsoObjectType.class);
      this.setExposed(ClimateManager.class);
      this.setExposed(DayInfo.class);
      this.setExposed(ClimateFloat.class);
      this.setExposed(ClimateColor.class);
      this.setExposed(ClimateBool.class);
      this.setExposed(WeatherPeriod.class);
      this.setExposed(WeatherStage.class);
      this.setExposed(StrLerpVal.class);
      this.setExposed(AirFront.class);
      this.setExposed(ThunderStorm.class);
      this.setExposed(ThunderCloud.class);
      this.setExposed(IsoWeatherFX.class);
      this.setExposed(Temperature.class);
      this.setExposed(ClimateColorInfo.class);
      this.setExposed(ClimateValues.class);
      this.setExposed(ClimateForecaster.class);
      this.setExposed(DayForecast.class);
      this.setExposed(ForecastValue.class);
      this.setExposed(ClimateHistory.class);
      this.setExposed(WorldFlares.class);
      this.setExposed(Flare.class);
      this.setExposed(ImprovedFog.class);
      this.setExposed(ClimateMoon.class);
      this.setExposed(IsoPuddles.class);
      this.setExposed(PuddlesFloat.class);
      this.setExposed(BentFences.class);
      this.setExposed(BrokenFences.class);
      this.setExposed(ContainerOverlays.class);
      this.setExposed(IsoChunk.class);
      this.setExposed(BuildingDef.class);
      this.setExposed(IsoCamera.class);
      this.setExposed(IsoCell.class);
      this.setExposed(IsoChunkMap.class);
      this.setExposed(IsoDirections.class);
      this.setExposed(IsoDirectionSet.class);
      this.setExposed(IsoGridSquare.class);
      this.setExposed(IsoHeatSource.class);
      this.setExposed(IsoLightSource.class);
      this.setExposed(IsoLot.class);
      this.setExposed(IsoLuaMover.class);
      this.setExposed(IsoMetaChunk.class);
      this.setExposed(IsoMetaCell.class);
      this.setExposed(IsoMetaGrid.class);
      this.setExposed(Trigger.class);
      this.setExposed(VehicleZone.class);
      this.setExposed(Zone.class);
      this.setExposed(IsoMovingObject.class);
      this.setExposed(IsoObject.class);
      this.setExposed(IsoObjectPicker.class);
      this.setExposed(IsoPushableObject.class);
      this.setExposed(IsoUtils.class);
      this.setExposed(IsoWorld.class);
      this.setExposed(LosUtil.class);
      this.setExposed(MetaObject.class);
      this.setExposed(RoomDef.class);
      this.setExposed(SliceY.class);
      this.setExposed(TileOverlays.class);
      this.setExposed(Vector2.class);
      this.setExposed(Vector3.class);
      this.setExposed(WorldMarkers.class);
      this.setExposed(DirectionArrow.class);
      this.setExposed(GridSquareMarker.class);
      this.setExposed(PlayerHomingPoint.class);
      this.setExposed(SearchMode.class);
      this.setExposed(PlayerSearchMode.class);
      this.setExposed(SearchModeFloat.class);
      this.setExposed(IsoMarkers.class);
      this.setExposed(IsoMarker.class);
      this.setExposed(CircleIsoMarker.class);
      this.setExposed(LuaEventManager.class);
      this.setExposed(MapObjects.class);
      this.setExposed(ActiveMods.class);
      this.setExposed(Server.class);
      this.setExposed(ServerOptions.class);
      this.setExposed(BooleanServerOption.class);
      this.setExposed(DoubleServerOption.class);
      this.setExposed(IntegerServerOption.class);
      this.setExposed(StringServerOption.class);
      this.setExposed(TextServerOption.class);
      this.setExposed(ServerSettings.class);
      this.setExposed(ServerSettingsManager.class);
      this.setExposed(ZombiePopulationRenderer.class);
      this.setExposed(zombie.popman.ZombiePopulationRenderer.BooleanDebugOption.class);
      this.setExposed(RadioAPI.class);
      this.setExposed(DeviceData.class);
      this.setExposed(DevicePresets.class);
      this.setExposed(PresetEntry.class);
      this.setExposed(ZomboidRadio.class);
      this.setExposed(RadioData.class);
      this.setExposed(RadioScriptManager.class);
      this.setExposed(DynamicRadioChannel.class);
      this.setExposed(RadioChannel.class);
      this.setExposed(RadioBroadCast.class);
      this.setExposed(RadioLine.class);
      this.setExposed(RadioScript.class);
      this.setExposed(ExitOption.class);
      this.setExposed(ChannelCategory.class);
      this.setExposed(SLSoundManager.class);
      this.setExposed(StorySound.class);
      this.setExposed(StorySoundEvent.class);
      this.setExposed(EventSound.class);
      this.setExposed(DataPoint.class);
      this.setExposed(RecordedMedia.class);
      this.setExposed(MediaData.class);
      this.setExposed(MediaLineData.class);
      this.setExposed(EvolvedRecipe.class);
      this.setExposed(Fixing.class);
      this.setExposed(Fixer.class);
      this.setExposed(FixerSkill.class);
      this.setExposed(GameSoundScript.class);
      this.setExposed(Item.class);
      this.setExposed(Type.class);
      this.setExposed(ItemRecipe.class);
      this.setExposed(MannequinScript.class);
      this.setExposed(ModelAttachment.class);
      this.setExposed(ModelScript.class);
      this.setExposed(MovableRecipe.class);
      this.setExposed(Recipe.class);
      this.setExposed(RequiredSkill.class);
      this.setExposed(Result.class);
      this.setExposed(Source.class);
      this.setExposed(ScriptModule.class);
      this.setExposed(VehicleScript.class);
      this.setExposed(Area.class);
      this.setExposed(Model.class);
      this.setExposed(Part.class);
      this.setExposed(Passenger.class);
      this.setExposed(PhysicsShape.class);
      this.setExposed(Position.class);
      this.setExposed(Wheel.class);
      this.setExposed(ScriptManager.class);
      this.setExposed(TemplateText.class);
      this.setExposed(ReplaceProviderCharacter.class);
      this.setExposed(ActionProgressBar.class);
      this.setExposed(Clock.class);
      this.setExposed(UIDebugConsole.class);
      this.setExposed(ModalDialog.class);
      this.setExposed(MoodlesUI.class);
      this.setExposed(NewHealthPanel.class);
      this.setExposed(ObjectTooltip.class);
      this.setExposed(Layout.class);
      this.setExposed(LayoutItem.class);
      this.setExposed(RadarPanel.class);
      this.setExposed(RadialMenu.class);
      this.setExposed(RadialProgressBar.class);
      this.setExposed(SpeedControls.class);
      this.setExposed(TextManager.class);
      this.setExposed(UI3DModel.class);
      this.setExposed(UIElement.class);
      this.setExposed(UIFont.class);
      this.setExposed(UITransition.class);
      this.setExposed(UIManager.class);
      this.setExposed(UIServerToolbox.class);
      this.setExposed(UITextBox2.class);
      this.setExposed(VehicleGauge.class);
      this.setExposed(TextDrawObject.class);
      this.setExposed(PZArrayList.class);
      this.setExposed(PZCalendar.class);
      this.setExposed(BaseVehicle.class);
      this.setExposed(EditVehicleState.class);
      this.setExposed(BehaviorResult.class);
      this.setExposed(PathFindBehavior2.class);
      this.setExposed(PathFindState2.class);
      this.setExposed(UI3DScene.class);
      this.setExposed(VehicleDoor.class);
      this.setExposed(VehicleLight.class);
      this.setExposed(VehiclePart.class);
      this.setExposed(VehicleType.class);
      this.setExposed(VehicleWindow.class);
      this.setExposed(AttachedItem.class);
      this.setExposed(AttachedItems.class);
      this.setExposed(AttachedLocation.class);
      this.setExposed(AttachedLocationGroup.class);
      this.setExposed(AttachedLocations.class);
      this.setExposed(WornItems.class);
      this.setExposed(WornItem.class);
      this.setExposed(BodyLocation.class);
      this.setExposed(BodyLocationGroup.class);
      this.setExposed(BodyLocations.class);
      this.setExposed(DummySoundManager.class);
      this.setExposed(GameSounds.class);
      this.setExposed(GameTime.class);
      this.setExposed(GameWindow.class);
      this.setExposed(SandboxOptions.class);
      this.setExposed(BooleanSandboxOption.class);
      this.setExposed(DoubleSandboxOption.class);
      this.setExposed(StringSandboxOption.class);
      this.setExposed(EnumSandboxOption.class);
      this.setExposed(IntegerSandboxOption.class);
      this.setExposed(SoundManager.class);
      this.setExposed(SystemDisabler.class);
      this.setExposed(VirtualZombieManager.class);
      this.setExposed(WorldSoundManager.class);
      this.setExposed(WorldSound.class);
      this.setExposed(DummyCharacterSoundEmitter.class);
      this.setExposed(CharacterSoundEmitter.class);
      this.setExposed(AmbientSoundEffect.class);
      this.setExposed(BaseAmbientStreamManager.class);
      this.setExposed(AmbientStreamManager.class);
      this.setExposed(Nutrition.class);
      this.setExposed(BSFurnace.class);
      this.setExposed(MultiStageBuilding.class);
      this.setExposed(Stage.class);
      this.setExposed(SleepingEvent.class);
      this.setExposed(IsoCompost.class);
      this.setExposed(Userlog.class);
      this.setExposed(UserlogType.class);
      this.setExposed(ConfigOption.class);
      this.setExposed(BooleanConfigOption.class);
      this.setExposed(DoubleConfigOption.class);
      this.setExposed(EnumConfigOption.class);
      this.setExposed(IntegerConfigOption.class);
      this.setExposed(StringConfigOption.class);
      this.setExposed(Faction.class);
      this.setExposed(LuaFileWriter.class);
      this.setExposed(Keyboard.class);
      this.setExposed(DBResult.class);
      this.setExposed(NonPvpZone.class);
      this.setExposed(DBTicket.class);
      this.setExposed(StashSystem.class);
      this.setExposed(StashBuilding.class);
      this.setExposed(Stash.class);
      this.setExposed(ItemType.class);
      this.setExposed(RandomizedWorldBase.class);
      this.setExposed(RandomizedBuildingBase.class);
      this.setExposed(RBBurntFireman.class);
      this.setExposed(RBBasic.class);
      this.setExposed(RBBurnt.class);
      this.setExposed(RBOther.class);
      this.setExposed(RBStripclub.class);
      this.setExposed(RBSchool.class);
      this.setExposed(RBSpiffo.class);
      this.setExposed(RBPizzaWhirled.class);
      this.setExposed(RBOffice.class);
      this.setExposed(RBHairSalon.class);
      this.setExposed(RBClinic.class);
      this.setExposed(RBPileOCrepe.class);
      this.setExposed(RBCafe.class);
      this.setExposed(RBBar.class);
      this.setExposed(RBLooted.class);
      this.setExposed(RBSafehouse.class);
      this.setExposed(RBBurntCorpse.class);
      this.setExposed(RBShopLooted.class);
      this.setExposed(RBKateAndBaldspot.class);
      this.setExposed(RandomizedDeadSurvivorBase.class);
      this.setExposed(RDSZombiesEating.class);
      this.setExposed(RDSBleach.class);
      this.setExposed(RDSDeadDrunk.class);
      this.setExposed(RDSGunmanInBathroom.class);
      this.setExposed(RDSGunslinger.class);
      this.setExposed(RDSZombieLockedBathroom.class);
      this.setExposed(RDSBandPractice.class);
      this.setExposed(RDSBathroomZed.class);
      this.setExposed(RDSBedroomZed.class);
      this.setExposed(RDSFootballNight.class);
      this.setExposed(RDSHenDo.class);
      this.setExposed(RDSStagDo.class);
      this.setExposed(RDSStudentNight.class);
      this.setExposed(RDSPokerNight.class);
      this.setExposed(RDSSuicidePact.class);
      this.setExposed(RDSPrisonEscape.class);
      this.setExposed(RDSPrisonEscapeWithPolice.class);
      this.setExposed(RDSSkeletonPsycho.class);
      this.setExposed(RDSCorpsePsycho.class);
      this.setExposed(RDSSpecificProfession.class);
      this.setExposed(RDSPoliceAtHouse.class);
      this.setExposed(RDSHouseParty.class);
      this.setExposed(RDSTinFoilHat.class);
      this.setExposed(RDSHockeyPsycho.class);
      this.setExposed(RandomizedVehicleStoryBase.class);
      this.setExposed(RVSCarCrash.class);
      this.setExposed(RVSBanditRoad.class);
      this.setExposed(RVSAmbulanceCrash.class);
      this.setExposed(RVSCrashHorde.class);
      this.setExposed(RVSCarCrashCorpse.class);
      this.setExposed(RVSPoliceBlockade.class);
      this.setExposed(RVSPoliceBlockadeShooting.class);
      this.setExposed(RVSBurntCar.class);
      this.setExposed(RVSConstructionSite.class);
      this.setExposed(RVSUtilityVehicle.class);
      this.setExposed(RVSChangingTire.class);
      this.setExposed(RVSFlippedCrash.class);
      this.setExposed(RVSTrailerCrash.class);
      this.setExposed(RandomizedZoneStoryBase.class);
      this.setExposed(RZSForestCamp.class);
      this.setExposed(RZSForestCampEaten.class);
      this.setExposed(RZSBuryingCamp.class);
      this.setExposed(RZSBeachParty.class);
      this.setExposed(RZSFishingTrip.class);
      this.setExposed(RZSBBQParty.class);
      this.setExposed(RZSHunterCamp.class);
      this.setExposed(RZSSexyTime.class);
      this.setExposed(RZSTrapperCamp.class);
      this.setExposed(RZSBaseball.class);
      this.setExposed(RZSMusicFestStage.class);
      this.setExposed(RZSMusicFest.class);
      this.setExposed(MapGroups.class);
      this.setExposed(BeardStyles.class);
      this.setExposed(BeardStyle.class);
      this.setExposed(HairStyles.class);
      this.setExposed(HairStyle.class);
      this.setExposed(BloodClothingType.class);
      this.setExposed(WeaponType.class);
      this.setExposed(IsoWaterGeometry.class);
      this.setExposed(ModData.class);
      this.setExposed(WorldMarkers.class);
      this.setExposed(ChatMessage.class);
      this.setExposed(ChatBase.class);
      this.setExposed(ServerChatMessage.class);
      this.setExposed(Safety.class);
      if (Core.bDebug) {
         this.setExposed(Field.class);
         this.setExposed(Method.class);
         this.setExposed(Coroutine.class);
      }

      UIWorldMap.setExposed(this);
      if (Core.bDebug) {
         try {
            this.exposeMethod(Class.class, Class.class.getMethod("getName"), LuaManager.env);
            this.exposeMethod(Class.class, Class.class.getMethod("getSimpleName"), LuaManager.env);
         } catch (NoSuchMethodException var3) {
            var3.printStackTrace();
         }
      }

      for (Class var2 : this.exposed) {
         this.exposeLikeJavaRecursively(var2, LuaManager.env);
      }

      this.exposeGlobalFunctions(std::make_unique<GlobalObject>());
      LuaManager.exposeKeyboardKeys(LuaManager.env);
      LuaManager.exposeLuaCalendar();
   }

    void setExposed(Class<?> var1) {
      this.exposed.push_back(var1);
   }

    bool shouldExpose(Class<?> var1) {
    return var1 = = nullptr ? false : this.exposed.contains(var1);
   }
}
} // namespace Lua
} // namespace zombie
