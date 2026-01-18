#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/EmitterType.h"
#include "fmod/fmod/FMODAudio.h"
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMODSoundBank.h"
#include "fmod/fmod/FMODSoundEmitter.h"
#include "java/awt/Desktop.h"
#include "java/awt/Desktop/Action.h"
#include "java/net/URI.h"
#include "java/net/URISyntaxException.h"
#include "java/net/URL.h"
#include "java/text/SimpleDateFormat.h"
#include "javax/xml/parsers/DocumentBuilder.h"
#include "javax/xml/parsers/DocumentBuilderFactory.h"
#include "org/joml/Vector2f.h"
#include "org/joml/Vector3f.h"
#include "org/luaj/kahluafork/compiler/FuncState.h"
#include "org/lwjglx/input/Controller.h"
#include "org/lwjglx/input/Controllers.h"
#include "org/lwjglx/input/KeyCodes.h"
#include "org/lwjglx/input/Keyboard.h"
#include "org/w3c/dom/Document.h"
#include "org/w3c/dom/Element.h"
#include "org/w3c/dom/Node.h"
#include "org/w3c/dom/NodeList.h"
#include "org/xml/sax/InputSource.h"
#include "se/krka/kahlua/converter/KahluaConverterManager.h"
#include "se/krka/kahlua/integration/LuaCaller.h"
#include "se/krka/kahlua/integration/LuaReturn.h"
#include "se/krka/kahlua/integration/annotations/LuaMethod.h"
#include "se/krka/kahlua/integration/expose/LuaJavaClassExposer.h"
#include "se/krka/kahlua/j2se/J2SEPlatform.h"
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/luaj/compiler/LuaCompiler.h"
#include "se/krka/kahlua/vm/Coroutine.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "se/krka/kahlua/vm/KahluaThread.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "se/krka/kahlua/vm/Platform.h"
#include "zombie/AmbientStreamManager.h"
#include "zombie/BaseAmbientStreamManager.h"
#include "zombie/BaseSoundManager.h"
#include "zombie/DummySoundManager.h"
#include "zombie/GameSounds.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/MapGroups.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/ZomboidFileSystem.h"
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
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/audio/BaseSoundBank.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/DummySoundBank.h"
#include "zombie/audio/DummySoundEmitter.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/audio/parameters/ParameterRoomType.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/BloodClothingType.h"
#include "zombie/characters/AttachedItems/AttachedItem.h"
#include "zombie/characters/AttachedItems/AttachedItems.h"
#include "zombie/characters/AttachedItems/AttachedLocation.h"
#include "zombie/characters/AttachedItems/AttachedLocationGroup.h"
#include "zombie/characters/AttachedItems/AttachedLocations.h"
#include "zombie/characters/AttachedItems/AttachedWeaponDefinitions.h"
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/BodyDamage/Fitness.h"
#include "zombie/characters/BodyDamage/Metabolics.h"
#include "zombie/characters/BodyDamage/Nutrition.h"
#include "zombie/characters/BodyDamage/Thermoregulator.h"
#include "zombie/characters/CharacterActionAnims.h"
#include "zombie/characters/CharacterSoundEmitter.h"
#include "zombie/characters/CharacterTimedActions/LuaTimedAction.h"
#include "zombie/characters/CharacterTimedActions/LuaTimedActionNew.h"
#include "zombie/characters/DummyCharacterSoundEmitter.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/HairOutfitDefinitions.h"
#include "zombie/characters/HaloTextHelper.h"
#include "zombie/characters/IsoDummyCameraCharacter.h"
#include "zombie/characters/IsoGameCharacter.h"
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
#include "zombie/characters/WornItems/BodyLocation.h"
#include "zombie/characters/WornItems/BodyLocationGroup.h"
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/characters/WornItems/WornItem.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/characters/ZombiesZoneDefinition.h"
#include "zombie/characters/action/ActionGroup.h"
#include "zombie/characters/professions/ProfessionFactory.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/characters/traits/ObservationFactory.h"
#include "zombie/characters/traits/TraitCollection.h"
#include "zombie/characters/traits/TraitFactory.h"
#include "zombie/chat/ChatBase.h"
#include "zombie/chat/ChatManager.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/chat/ServerChatMessage.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/config/DoubleConfigOption.h"
#include "zombie/config/EnumConfigOption.h"
#include "zombie/config/IntegerConfigOption.h"
#include "zombie/config/StringConfigOption.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Clipboard.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/Core.h"
#include "zombie/core/GameVersion.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/IndieFileLoader.h"
#include "zombie/core/Language.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/Translator.h"
#include "zombie/core/fonts/AngelCodeFont.h"
#include "zombie/core/input/Input.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/logger/ZLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/physics/Bullet.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/raknet/VoiceManager.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimNodeAssetManager.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationSet.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/model/ModelAssetManager.h"
#include "zombie/core/skinnedmodel/model/WorldItemModelDrawer.h"
#include "zombie/core/skinnedmodel/population/BeardStyle.h"
#include "zombie/core/skinnedmodel/population/BeardStyles.h"
#include "zombie/core/skinnedmodel/population/ClothingDecalGroup.h"
#include "zombie/core/skinnedmodel/population/ClothingDecals.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/population/DefaultClothing.h"
#include "zombie/core/skinnedmodel/population/HairStyle.h"
#include "zombie/core/skinnedmodel/population/HairStyles.h"
#include "zombie/core/skinnedmodel/population/Outfit.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/stash/Stash.h"
#include "zombie/core/stash/StashBuilding.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/core/znet/GameServerDetails.h"
#include "zombie/core/znet/ISteamWorkshopCallback.h"
#include "zombie/core/znet/ServerBrowser.h"
#include "zombie/core/znet/SteamFriend.h"
#include "zombie/core/znet/SteamFriends.h"
#include "zombie/core/znet/SteamUGCDetails.h"
#include "zombie/core/znet/SteamUser.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/core/znet/SteamWorkshop.h"
#include "zombie/core/znet/SteamWorkshopItem.h"
#include "zombie/debug/BooleanDebugOption.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/erosion/ErosionConfig.h"
#include "zombie/erosion/ErosionData.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/erosion/season/ErosionSeason.h"
#include "zombie/gameStates/AnimationViewerState.h"
#include "zombie/gameStates/AttachmentEditorState.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ConnectToServerState.h"
#include "zombie/gameStates/DebugChunkState.h"
#include "zombie/gameStates/DebugGlobalObjectState.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/gameStates/GameState.h"
#include "zombie/gameStates/IngameState.h"
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
#include "zombie/input/JoypadManager.h"
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
#include "zombie/iso/CellLoader.h"
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
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaChunk.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoPuddles.h"
#include "zombie/iso/IsoPushableObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWaterGeometry.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LightingJNI.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/MetaObject.h"
#include "zombie/iso/MultiStageBuilding.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/SearchMode.h"
#include "zombie/iso/SliceY.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/TileOverlays.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include "zombie/iso/WorldMarkers.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/areas/isoregion/IsoRegionLogType.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/areas/isoregion/IsoRegionsLogger.h"
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
#include "zombie/iso/weather/ClimateHistory.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/ClimateMoon.h"
#include "zombie/iso/weather/ClimateValues.h"
#include "zombie/iso/weather/Temperature.h"
#include "zombie/iso/weather/ThunderStorm.h"
#include "zombie/iso/weather/WeatherPeriod.h"
#include "zombie/iso/weather/WorldFlares.h"
#include "zombie/iso/weather/fog/ImprovedFog.h"
#include "zombie/iso/weather/fx/IsoWeatherFX.h"
#include "zombie/modding/ActiveMods.h"
#include "zombie/modding/ActiveModsFile.h"
#include "zombie/modding/ModUtilsJava.h"
#include "zombie/network/ConnectionManager.h"
#include "zombie/network/CoopMaster.h"
#include "zombie/network/DBResult.h"
#include "zombie/network/DBTicket.h"
#include "zombie/network/DesktopBrowser.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ItemTransactionManager.h"
#include "zombie/network/MPStatistic.h"
#include "zombie/network/MPStatistics.h"
#include "zombie/network/NetChecksum.h"
#include "zombie/network/NetworkAIParams.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/Server.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/ServerSettings.h"
#include "zombie/network/ServerSettingsManager.h"
#include "zombie/network/ServerWorldDatabase.h"
#include "zombie/network/Userlog.h"
#include "zombie/network/chat/ChatServer.h"
#include "zombie/network/chat/ChatType.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include "zombie/popman/ZombiePopulationRenderer.h"
#include "zombie/profanity/ProfanityFilter.h"
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
#include "zombie/radio/media/RecordedMedia.h"
#include "zombie/radio/scripting/DynamicRadioChannel.h"
#include "zombie/radio/scripting/RadioBroadCast.h"
#include "zombie/radio/scripting/RadioChannel.h"
#include "zombie/radio/scripting/RadioLine.h"
#include "zombie/radio/scripting/RadioScript.h"
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
#include "zombie/savefile/ClientPlayerDB.h"
#include "zombie/savefile/PlayerDBHelper.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/EvolvedRecipe.h"
#include "zombie/scripting/objects/Fixing.h"
#include "zombie/scripting/objects/GameSoundScript.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/ItemRecipe.h"
#include "zombie/scripting/objects/MannequinScript.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/scripting/objects/MovableRecipe.h"
#include "zombie/scripting/objects/Recipe.h"
#include "zombie/scripting/objects/ScriptModule.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/spnetwork/SinglePlayerClient.h"
#include "zombie/text/templating/ReplaceProviderCharacter.h"
#include "zombie/text/templating/TemplateText.h"
#include "zombie/ui/ActionProgressBar.h"
#include "zombie/ui/Clock.h"
#include "zombie/ui/ModalDialog.h"
#include "zombie/ui/MoodlesUI.h"
#include "zombie/ui/NewHealthPanel.h"
#include "zombie/ui/ObjectTooltip.h"
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
#include "zombie/util/AddCoopPlayer.h"
#include "zombie/util/PZCalendar.h"
#include "zombie/util/PublicServerUtil.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayList.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/EditVehicleState.h"
#include "zombie/vehicles/PathFindBehavior2.h"
#include "zombie/vehicles/PathFindState2.h"
#include "zombie/vehicles/UI3DScene.h"
#include "zombie/vehicles/VehicleDoor.h"
#include "zombie/vehicles/VehicleLight.h"
#include "zombie/vehicles/VehicleManager.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/vehicles/VehicleType.h"
#include "zombie/vehicles/VehicleWindow.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include "zombie/world/moddata/ModData.h"
#include "zombie/worldMap/UIWorldMap.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace Lua {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LuaManager {
public:
 static KahluaConverterManager converterManager = new KahluaConverterManager();
 static J2SEPlatform platform = new J2SEPlatform();
 static KahluaTable env;
 static KahluaThread thread;
 static KahluaThread debugthread;
 static LuaCaller caller = new LuaCaller(converterManager);
 static LuaCaller debugcaller = new LuaCaller(converterManager);
 public static LuaManager.Exposer exposer;
 public static ArrayList<String> loaded = std::make_unique<ArrayList<>>();
 private static HashSet<String> loading = std::make_unique<HashSet<>>();
 public static HashMap<String, Object> loadedReturn = std::make_unique<HashMap<>>();
 static bool checksumDone = false;
 public static ArrayList<String> loadList = std::make_unique<ArrayList<>>();
 static ArrayList<String> paths = std::make_unique<ArrayList<>>();
 private static HashMap<String, Object> luaFunctionMap = std::make_unique<HashMap<>>();
 private static HashSet<KahluaTable> s_wiping = std::make_unique<HashSet<>>();

 static void outputTable(KahluaTable var0, int var1) {
 }

 static void wipeRecurse(KahluaTable table0) {
 if (!table0.empty()) {
 if (!s_wiping.contains(table0) {
 s_wiping.add(table0);
 KahluaTableIterator kahluaTableIterator = table0.iterator();

 while (kahluaTableIterator.advance()) {
 KahluaTable table1 = Type.tryCastTo(kahluaTableIterator.getValue(), KahluaTable.class);
 if (table1 != nullptr) {
 wipeRecurse(table1);
 }
 }

 s_wiping.remove(table0);
 table0.wipe();
 }
 }
 }

 static void init() {
 loaded.clear();
 loading.clear();
 loadedReturn.clear();
 paths.clear();
 luaFunctionMap.clear();
 platform = std::make_unique<J2SEPlatform>();
 if (env != nullptr) {
 s_wiping.clear();
 wipeRecurse(env);
 }

 env = platform.newEnvironment();
 converterManager = std::make_unique<KahluaConverterManager>();
 if (thread != nullptr) {
 thread.bReset = true;
 }

 thread = new KahluaThread(platform, env);
 debugthread = new KahluaThread(platform, env);
 UIManager.defaultthread = thread;
 caller = new LuaCaller(converterManager);
 debugcaller = new LuaCaller(converterManager);
 if (exposer != nullptr) {
 exposer.destroy();
 }

 exposer = new LuaManager.Exposer(converterManager, platform, env);
 loaded = std::make_unique<ArrayList<>>();
 checksumDone = false;
 GameClient.checksum = "";
 GameClient.checksumValid = false;
 KahluaNumberConverter.install(converterManager);
 LuaEventManager.register(platform, env);
 LuaHookManager.register(platform, env);
 if (CoopMaster.instance != nullptr) {
 CoopMaster.instance.register(platform, env);
 }

 if (VoiceManager.instance != nullptr) {
 VoiceManager.instance.LuaRegister(platform, env);
 }

 KahluaTable table = env;
 exposer.exposeAll();
 exposer.TypeMap.put("function", LuaClosure.class);
 exposer.TypeMap.put("table", KahluaTable.class);
 outputTable(env, 0);
 }

 static void LoadDir(const std::string& var0) {
 }

 static void LoadDirBase(const std::string& string) {
 LoadDirBase(string, false);
 }

 static void LoadDirBase(const std::string& string1, bool boolean0) {
 std::string string0 = "media/lua/" + string1 + "/";
 File file0 = ZomboidFileSystem.instance.getMediaFile("lua" + File.separator + string1);
 if (!paths.contains(string0) {
 paths.add(string0);
 }

 try {
 searchFolders(ZomboidFileSystem.instance.baseURI, file0);
 } catch (IOException iOException0) {
 ExceptionLogger.logException(iOException0);
 }

 std::vector arrayList0 = loadList;
 loadList = std::make_unique<ArrayList<>>();
 std::vector arrayList1 = ZomboidFileSystem.instance.getModIDs();

 for (int int0 = 0; int0 < arrayList1.size(); int0++) {
 std::string string2 = ZomboidFileSystem.instance.getModDir((String)arrayList1.get(int0);
 if (string2 != nullptr) {
 File file1 = new File(string2);
 URI uri = file1.getCanonicalFile().toURI();
 File file2 = ZomboidFileSystem.instance.getCanonicalFile(file1, "media");
 File file3 = ZomboidFileSystem.instance.getCanonicalFile(file2, "lua");
 File file4 = ZomboidFileSystem.instance.getCanonicalFile(file3, string1);
 File file5 = file4;

 try {
 searchFolders(uri, file5);
 } catch (IOException iOException1) {
 ExceptionLogger.logException(iOException1);
 }
 }
 }

 Collections.sort(arrayList0);
 Collections.sort(loadList);
 arrayList0.addAll(loadList);
 loadList.clear();
 loadList = arrayList0;
 std::unordered_set hashSet = new HashSet();

 for (auto& string3 : loadList) if (!hashSet.contains(string3) {
 hashSet.add(string3);
 std::string string4 = ZomboidFileSystem.instance.getAbsolutePath(string3);
 if (string4 == nullptr) {
 throw IllegalStateException("couldn't find \"" + string3 + "\"");
 }

 if (!boolean0) {
 RunLua(string4);
 }

 if (!checksumDone && !string3.contains("SandboxVars.lua") && (GameServer.bServer || GameClient.bClient) {
 NetChecksum.checksummer.addFile(string3, string4);
 }

 if (CoopMaster.instance != nullptr) {
 CoopMaster.instance.update();
 }
 }
 }

 loadList.clear();
 }

 static void initChecksum() {
 if (!checksumDone) {
 if (GameClient.bClient || GameServer.bServer) {
 NetChecksum.checksummer.reset(false);
 }
 }
 }

 static void finishChecksum() {
 if (GameServer.bServer) {
 GameServer.checksum = NetChecksum.checksummer.checksumToString();
 DebugLog.General.println("luaChecksum: " + GameServer.checksum);
 } else {
 if (!GameClient.bClient) {
 return;
 }

 GameClient.checksum = NetChecksum.checksummer.checksumToString();
 }

 NetChecksum.GroupOfFiles.finishChecksum();
 checksumDone = true;
 }

 static void LoadDirBase() {
 initChecksum();
 LoadDirBase("shared");
 LoadDirBase("client");
 }

 static void searchFolders(URI uri, File file) {
 if (file.isDirectory()) {
 String[] strings = file.list();

 for (int int0 = 0; int0 < strings.length; int0++) {
 searchFolders(uri, new File(file.getCanonicalFile().getAbsolutePath() + File.separator + strings[int0]));
 }
 } else if (file.getAbsolutePath().toLowerCase().endsWith(".lua")) {
 std::string string = ZomboidFileSystem.instance.getRelativeFile(uri, file.getAbsolutePath());
 string = string.toLowerCase(Locale.ENGLISH);
 loadList.add(string);
 }
 }

 static std::string getLuaCacheDir() {
 std::string string = ZomboidFileSystem.instance.getCacheDir() + File.separator + "Lua";
 File file = new File(string);
 if (!file.exists()) {
 file.mkdir();
 }

 return string;
 }

 static std::string getSandboxCacheDir() {
 std::string string = ZomboidFileSystem.instance.getCacheDir() + File.separator + "Sandbox Presets";
 File file = new File(string);
 if (!file.exists()) {
 file.mkdir();
 }

 return string;
 }

 static void fillContainer(ItemContainer container, IsoPlayer player) {
 ItemPickerJava.fillContainer(container, player);
 }

 static void updateOverlaySprite(IsoObject object) {
 ItemPickerJava.updateOverlaySprite(object);
 }

 static LuaClosure getDotDelimitedClosure(const std::string& string) {
 String[] strings = string.split("\\.");
 KahluaTable table = env;

 for (int int0 = 0; int0 < strings.length - 1; int0++) {
 table = (KahluaTable)env.rawget(strings[int0]);
 }

 return (LuaClosure)table.rawget(strings[strings.length - 1]);
 }

 static void transferItem(IsoGameCharacter character, InventoryItem item, ItemContainer container0, ItemContainer container1) {
 LuaClosure luaClosure = (LuaClosure)env.rawget("javaTransferItems");
 caller.pcall(thread, luaClosure, character, item, container0, container1);
 }

 static void dropItem(InventoryItem item) {
 LuaClosure luaClosure = getDotDelimitedClosure("ISInventoryPaneContextMenu.dropItem");
 caller.pcall(thread, luaClosure, item);
 }

 static IsoGridSquare AdjacentFreeTileFinder(IsoGridSquare square, IsoPlayer player) {
 KahluaTable table = (KahluaTable)env.rawget("AdjacentFreeTileFinder");
 LuaClosure luaClosure = (LuaClosure)table.rawget("Find");
 return (IsoGridSquare)caller.pcall(thread, luaClosure, square, player)[1];
 }

 static void* RunLua(const std::string& string) {
 return RunLua();
 }

 static void* RunLua(const std::string& string1, bool boolean0) {
 std::string string0 = string1.replace("\\", "/");
 if (loading.contains(string0) {
 DebugLog.Lua.warn("recursive require(): %s", string0);
 return nullptr;
 } else {
 loading.add(string0);

 void* object;
 try {
 object = RunLuaInternal(string1, boolean0);
 } finally {
 loading.remove(string0);
 }

 return object;
 }
 }

 static void* RunLuaInternal(const std::string& string, bool boolean0) {
 string = string.replace("\\", "/");
 if (loaded.contains(string) {
 return loadedReturn.get(string);
 } else {
 FuncState.currentFile = string.substring(string.lastIndexOf(47) + 1);
 FuncState.currentfullFile = string;
 string = ZomboidFileSystem.instance.getString(string.replace("\\", "/"));
 if (DebugLog.isEnabled(DebugType.Lua) {
 DebugLog.Lua.println("Loading: " + ZomboidFileSystem.instance.getRelativeFile(string);
 }

 InputStreamReader inputStreamReader;
 try {
 inputStreamReader = IndieFileLoader.getStreamReader(string);
 } catch (FileNotFoundException fileNotFoundException) {
 ExceptionLogger.logException(fileNotFoundException);
 return nullptr;
 }

 LuaCompiler.rewriteEvents = boolean0;

 LuaClosure luaClosure;
 try (BufferedReader bufferedReader = new BufferedReader(inputStreamReader) {
 luaClosure = LuaCompiler.loadis(bufferedReader, string.substring(string.lastIndexOf(47) + 1), env);
 } catch (Exception exception) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, "Error found in LUA file: " + string, nullptr);
 ExceptionLogger.logException(exception);
 thread.debugException(exception);
 return nullptr;
 }

 luaFunctionMap.clear();
 AttachedWeaponDefinitions.instance.m_dirty = true;
 DefaultClothing.instance.m_dirty = true;
 HairOutfitDefinitions.instance.m_dirty = true;
 ZombiesZoneDefinition.bDirty = true;
 LuaReturn luaReturn = caller.protectedCall(thread, luaClosure);
 if (!luaReturn.isSuccess()) {
 Logger.getLogger(IsoWorld.class.getName()).log(Level.SEVERE, luaReturn.getErrorString(), nullptr);
 if (luaReturn.getJavaException() != nullptr) {
 Logger.getLogger(IsoWorld.class.getName()).log(Level.SEVERE, luaReturn.getJavaException().toString(), nullptr);
 }

 Logger.getLogger(IsoWorld.class.getName()).log(Level.SEVERE, luaReturn.getLuaStackTrace(), nullptr);
 }

 loaded.add(string);
 void* object = luaReturn.isSuccess() && luaReturn.size() > 0 ? luaReturn.getFirst() : nullptr;
 if (object != nullptr) {
 loadedReturn.put(string, object);
 } else {
 loadedReturn.remove(string);
 }

 LuaCompiler.rewriteEvents = false;
 return object;
 }
 }

 static void* getFunctionObject(const std::string& string) {
 if (string != nullptr && !string.empty()) {
 void* object = luaFunctionMap.get(string);
 if (object != nullptr) {
 return object;
 } else {
 KahluaTable table0 = env;
 if (string.contains(".")) {
 String[] strings = string.split("\\.");

 for (int int0 = 0; int0 < strings.length - 1; int0++) {
 KahluaTable table1 = Type.tryCastTo(table0.rawget(strings[int0]), KahluaTable.class);
 if (table1 == nullptr) {
 DebugLog.General.error("no such function \"%s\"", string);
 return nullptr;
 }

 table0 = table1;
 }

 object = table0.rawget(strings[strings.length - 1]);
 } else {
 object = table0.rawget(string);
 }

 if (!(object instanceof JavaFunction) && !(object instanceof LuaClosure) {
 DebugLog.General.error("no such function \"%s\"", string);
 return nullptr;
 } else {
 luaFunctionMap.put(string, object);
 return object;
 }
 }
 } else {
 return nullptr;
 }
 }

 static void Test() {
 }

 static void* get(void* object) {
 return env.rawget(object);
 }

 static void call(const std::string& string, void* object) {
 caller.pcall(thread, env.rawget(string), object);
 }

 static void exposeKeyboardKeys(KahluaTable table1) {
 if (table1.rawget("Keyboard") instanceof KahluaTable table0) {
 Field[] fields = Keyboard.class.getFields();

 try {
 for (auto& field : fields) if (Modifier.isStatic(field.getModifiers())
 && Modifier.isPublic(field.getModifiers())
 && Modifier.isFinal(field.getModifiers())
 && field.getType() == int.class)
 && field.getName().startsWith("KEY_")
 && !field.getName().endsWith("WIN")) {
 table0.rawset(field.getName(), (double)field.getInt(nullptr);
 }
 }
 } catch (Exception exception) {
 }
 }
 }

 static void exposeLuaCalendar() {
 KahluaTable table = (KahluaTable)env.rawget("PZCalendar");
 if (table != nullptr) {
 Field[] fields = Calendar.class.getFields();

 try {
 for (auto& field : fields) if (Modifier.isStatic(field.getModifiers())
 && Modifier.isPublic(field.getModifiers())
 && Modifier.isFinal(field.getModifiers())
 && field.getType() == int.class) {
 table.rawset(field.getName(), BoxedStaticValues.toDouble(field.getInt(nullptr);
 }
 }
 } catch (Exception exception) {
 }

 env.rawset("Calendar", table);
 }
 }

 static std::string getHourMinuteJava() {
 std::string string = Calendar.getInstance().get(12) + "";
 if (Calendar.getInstance().get(12) < 10) {
 string = "0" + string;
 }

 return Calendar.getInstance().get(11) + ":" + string;
 }

 static KahluaTable copyTable(KahluaTable table) {
 return copyTable();
 }

 static KahluaTable copyTable(KahluaTable table0, KahluaTable table1) {
 if (table0 == nullptr) {
 table0 = platform.newTable();
 } else {
 table0.wipe();
 }

 if (table1 != nullptr && !table1.empty()) {
 KahluaTableIterator kahluaTableIterator = table1.iterator();

 while (kahluaTableIterator.advance()) {
 void* object0 = kahluaTableIterator.getKey();
 void* object1 = kahluaTableIterator.getValue();
 if (object1 instanceof KahluaTable) {
 table0.rawset(object0, copyTable(nullptr, (KahluaTable)object1);
 } else {
 table0.rawset(object0, object1);
 }
 }

 return table0;
 } else {
 return table0;
 }
 }

 public static class Exposer extends LuaJavaClassExposer {
 private HashSet<Class<?>> exposed = std::make_unique<HashSet<>>();

 public Exposer(KahluaConverterManager manager, Platform platform, KahluaTable environment) {
 super(manager, platform, environment);
 }

 void exposeAll() {
 this->setExposed(BufferedReader.class);
 this->setExposed(BufferedWriter.class);
 this->setExposed(DataInputStream.class);
 this->setExposed(DataOutputStream.class);
 this->setExposed(Double.class);
 this->setExposed(Long.class);
 this->setExposed(Float.class);
 this->setExposed(Integer.class);
 this->setExposed(Math.class);
 this->setExposed(Void.class);
 this->setExposed(SimpleDateFormat.class);
 this->setExposed(ArrayList.class);
 this->setExposed(EnumMap.class);
 this->setExposed(HashMap.class);
 this->setExposed(LinkedList.class);
 this->setExposed(Stack.class);
 this->setExposed(Vector.class);
 this->setExposed(Iterator.class);
 this->setExposed(EmitterType.class);
 this->setExposed(FMODAudio.class);
 this->setExposed(FMODSoundBank.class);
 this->setExposed(FMODSoundEmitter.class);
 this->setExposed(Vector2f.class);
 this->setExposed(Vector3f.class);
 this->setExposed(KahluaUtil.class);
 this->setExposed(DummySoundBank.class);
 this->setExposed(DummySoundEmitter.class);
 this->setExposed(BaseSoundEmitter.class);
 this->setExposed(GameSound.class);
 this->setExposed(GameSoundClip.class);
 this->setExposed(AttackState.class);
 this->setExposed(BurntToDeath.class);
 this->setExposed(ClimbDownSheetRopeState.class);
 this->setExposed(ClimbOverFenceState.class);
 this->setExposed(ClimbOverWallState.class);
 this->setExposed(ClimbSheetRopeState.class);
 this->setExposed(ClimbThroughWindowState.class);
 this->setExposed(CloseWindowState.class);
 this->setExposed(CrawlingZombieTurnState.class);
 this->setExposed(FakeDeadAttackState.class);
 this->setExposed(FakeDeadZombieState.class);
 this->setExposed(FishingState.class);
 this->setExposed(FitnessState.class);
 this->setExposed(IdleState.class);
 this->setExposed(LungeState.class);
 this->setExposed(OpenWindowState.class);
 this->setExposed(PathFindState.class);
 this->setExposed(PlayerActionsState.class);
 this->setExposed(PlayerAimState.class);
 this->setExposed(PlayerEmoteState.class);
 this->setExposed(PlayerExtState.class);
 this->setExposed(PlayerFallDownState.class);
 this->setExposed(PlayerFallingState.class);
 this->setExposed(PlayerGetUpState.class);
 this->setExposed(PlayerHitReactionPVPState.class);
 this->setExposed(PlayerHitReactionState.class);
 this->setExposed(PlayerKnockedDown.class);
 this->setExposed(PlayerOnGroundState.class);
 this->setExposed(PlayerSitOnGroundState.class);
 this->setExposed(PlayerStrafeState.class);
 this->setExposed(SmashWindowState.class);
 this->setExposed(StaggerBackState.class);
 this->setExposed(SwipeStatePlayer.class);
 this->setExposed(ThumpState.class);
 this->setExposed(WalkTowardState.class);
 this->setExposed(ZombieFallDownState.class);
 this->setExposed(ZombieGetDownState.class);
 this->setExposed(ZombieGetUpState.class);
 this->setExposed(ZombieIdleState.class);
 this->setExposed(ZombieOnGroundState.class);
 this->setExposed(ZombieReanimateState.class);
 this->setExposed(ZombieSittingState.class);
 this->setExposed(GameCharacterAIBrain.class);
 this->setExposed(MapKnowledge.class);
 this->setExposed(BodyPartType.class);
 this->setExposed(BodyPart.class);
 this->setExposed(BodyDamage.class);
 this->setExposed(Thermoregulator.class);
 this->setExposed(Thermoregulator.ThermalNode.class);
 this->setExposed(Metabolics.class);
 this->setExposed(Fitness.class);
 this->setExposed(GameKeyboard.class);
 this->setExposed(LuaTimedAction.class);
 this->setExposed(LuaTimedActionNew.class);
 this->setExposed(Moodle.class);
 this->setExposed(Moodles.class);
 this->setExposed(MoodleType.class);
 this->setExposed(ProfessionFactory.class);
 this->setExposed(ProfessionFactory.Profession.class);
 this->setExposed(PerkFactory.class);
 this->setExposed(PerkFactory.Perk.class);
 this->setExposed(PerkFactory.Perks.class);
 this->setExposed(ObservationFactory.class);
 this->setExposed(ObservationFactory.Observation.class);
 this->setExposed(TraitFactory.class);
 this->setExposed(TraitFactory.Trait.class);
 this->setExposed(IsoDummyCameraCharacter.class);
 this->setExposed(Stats.class);
 this->setExposed(SurvivorDesc.class);
 this->setExposed(SurvivorFactory.class);
 this->setExposed(SurvivorFactory.SurvivorType.class);
 this->setExposed(IsoGameCharacter.class);
 this->setExposed(IsoGameCharacter.Location.class);
 this->setExposed(IsoGameCharacter.PerkInfo.class);
 this->setExposed(IsoGameCharacter.XP.class);
 this->setExposed(IsoGameCharacter.CharacterTraits.class);
 this->setExposed(TraitCollection.TraitSlot.class);
 this->setExposed(TraitCollection.class);
 this->setExposed(IsoPlayer.class);
 this->setExposed(IsoSurvivor.class);
 this->setExposed(IsoZombie.class);
 this->setExposed(CharacterActionAnims.class);
 this->setExposed(HaloTextHelper.class);
 this->setExposed(HaloTextHelper.ColorRGB.class);
 this->setExposed(NetworkAIParams.class);
 this->setExposed(BloodBodyPartType.class);
 this->setExposed(Clipboard.class);
 this->setExposed(AngelCodeFont.class);
 this->setExposed(ZLogger.class);
 this->setExposed(PropertyContainer.class);
 this->setExposed(ClothingItem.class);
 this->setExposed(AnimatorDebugMonitor.class);
 this->setExposed(ColorInfo.class);
 this->setExposed(Texture.class);
 this->setExposed(SteamFriend.class);
 this->setExposed(SteamUGCDetails.class);
 this->setExposed(SteamWorkshopItem.class);
 this->setExposed(Color.class);
 this->setExposed(Colors.class);
 this->setExposed(Core.class);
 this->setExposed(GameVersion.class);
 this->setExposed(ImmutableColor.class);
 this->setExposed(Language.class);
 this->setExposed(PerformanceSettings.class);
 this->setExposed(SpriteRenderer.class);
 this->setExposed(Translator.class);
 this->setExposed(PZMath.class);
 this->setExposed(DebugLog.class);
 this->setExposed(DebugOptions.class);
 this->setExposed(BooleanDebugOption.class);
 this->setExposed(DebugType.class);
 this->setExposed(ErosionConfig.class);
 this->setExposed(ErosionConfig.Debug.class);
 this->setExposed(ErosionConfig.Season.class);
 this->setExposed(ErosionConfig.Seeds.class);
 this->setExposed(ErosionConfig.Time.class);
 this->setExposed(ErosionMain.class);
 this->setExposed(ErosionSeason.class);
 this->setExposed(AnimationViewerState.class);
 this->setExposed(AnimationViewerState.BooleanDebugOption.class);
 this->setExposed(AttachmentEditorState.class);
 this->setExposed(ChooseGameInfo.Mod.class);
 this->setExposed(DebugChunkState.class);
 this->setExposed(DebugChunkState.BooleanDebugOption.class);
 this->setExposed(DebugGlobalObjectState.class);
 this->setExposed(GameLoadingState.class);
 this->setExposed(LoadingQueueState.class);
 this->setExposed(MainScreenState.class);
 this->setExposed(TermsOfServiceState.class);
 this->setExposed(CGlobalObject.class);
 this->setExposed(CGlobalObjects.class);
 this->setExposed(CGlobalObjectSystem.class);
 this->setExposed(SGlobalObject.class);
 this->setExposed(SGlobalObjects.class);
 this->setExposed(SGlobalObjectSystem.class);
 this->setExposed(Mouse.class);
 this->setExposed(AlarmClock.class);
 this->setExposed(AlarmClockClothing.class);
 this->setExposed(Clothing.class);
 this->setExposed(Clothing.ClothingPatch.class);
 this->setExposed(Clothing.ClothingPatchFabricType.class);
 this->setExposed(ComboItem.class);
 this->setExposed(Drainable.class);
 this->setExposed(DrainableComboItem.class);
 this->setExposed(Food.class);
 this->setExposed(HandWeapon.class);
 this->setExposed(InventoryContainer.class);
 this->setExposed(Key.class);
 this->setExposed(KeyRing.class);
 this->setExposed(Literature.class);
 this->setExposed(MapItem.class);
 this->setExposed(Moveable.class);
 this->setExposed(Radio.class);
 this->setExposed(WeaponPart.class);
 this->setExposed(ItemContainer.class);
 this->setExposed(ItemPickerJava.class);
 this->setExposed(InventoryItem.class);
 this->setExposed(InventoryItemFactory.class);
 this->setExposed(FixingManager.class);
 this->setExposed(RecipeManager.class);
 this->setExposed(IsoRegions.class);
 this->setExposed(IsoRegionsLogger.class);
 this->setExposed(IsoRegionsLogger.IsoRegionLog.class);
 this->setExposed(IsoRegionLogType.class);
 this->setExposed(DataCell.class);
 this->setExposed(DataChunk.class);
 this->setExposed(IsoChunkRegion.class);
 this->setExposed(IsoWorldRegion.class);
 this->setExposed(IsoRegionsRenderer.class);
 this->setExposed(IsoRegionsRenderer.BooleanDebugOption.class);
 this->setExposed(IsoBuilding.class);
 this->setExposed(IsoRoom.class);
 this->setExposed(SafeHouse.class);
 this->setExposed(BarricadeAble.class);
 this->setExposed(IsoBarbecue.class);
 this->setExposed(IsoBarricade.class);
 this->setExposed(IsoBrokenGlass.class);
 this->setExposed(IsoClothingDryer.class);
 this->setExposed(IsoClothingWasher.class);
 this->setExposed(IsoCombinationWasherDryer.class);
 this->setExposed(IsoStackedWasherDryer.class);
 this->setExposed(IsoCurtain.class);
 this->setExposed(IsoCarBatteryCharger.class);
 this->setExposed(IsoDeadBody.class);
 this->setExposed(IsoDoor.class);
 this->setExposed(IsoFire.class);
 this->setExposed(IsoFireManager.class);
 this->setExposed(IsoFireplace.class);
 this->setExposed(IsoGenerator.class);
 this->setExposed(IsoJukebox.class);
 this->setExposed(IsoLightSwitch.class);
 this->setExposed(IsoMannequin.class);
 this->setExposed(IsoMolotovCocktail.class);
 this->setExposed(IsoWaveSignal.class);
 this->setExposed(IsoRadio.class);
 this->setExposed(IsoTelevision.class);
 this->setExposed(IsoStackedWasherDryer.class);
 this->setExposed(IsoStove.class);
 this->setExposed(IsoThumpable.class);
 this->setExposed(IsoTrap.class);
 this->setExposed(IsoTree.class);
 this->setExposed(IsoWheelieBin.class);
 this->setExposed(IsoWindow.class);
 this->setExposed(IsoWindowFrame.class);
 this->setExposed(IsoWorldInventoryObject.class);
 this->setExposed(IsoZombieGiblets.class);
 this->setExposed(RainManager.class);
 this->setExposed(ObjectRenderEffects.class);
 this->setExposed(HumanVisual.class);
 this->setExposed(ItemVisual.class);
 this->setExposed(ItemVisuals.class);
 this->setExposed(IsoSprite.class);
 this->setExposed(IsoSpriteInstance.class);
 this->setExposed(IsoSpriteManager.class);
 this->setExposed(IsoSpriteGrid.class);
 this->setExposed(IsoFlagType.class);
 this->setExposed(IsoObjectType.class);
 this->setExposed(ClimateManager.class);
 this->setExposed(ClimateManager.DayInfo.class);
 this->setExposed(ClimateManager.ClimateFloat.class);
 this->setExposed(ClimateManager.ClimateColor.class);
 this->setExposed(ClimateManager.ClimateBool.class);
 this->setExposed(WeatherPeriod.class);
 this->setExposed(WeatherPeriod.WeatherStage.class);
 this->setExposed(WeatherPeriod.StrLerpVal.class);
 this->setExposed(ClimateManager.AirFront.class);
 this->setExposed(ThunderStorm.class);
 this->setExposed(ThunderStorm.ThunderCloud.class);
 this->setExposed(IsoWeatherFX.class);
 this->setExposed(Temperature.class);
 this->setExposed(ClimateColorInfo.class);
 this->setExposed(ClimateValues.class);
 this->setExposed(ClimateForecaster.class);
 this->setExposed(ClimateForecaster.DayForecast.class);
 this->setExposed(ClimateForecaster.ForecastValue.class);
 this->setExposed(ClimateHistory.class);
 this->setExposed(WorldFlares.class);
 this->setExposed(WorldFlares.Flare.class);
 this->setExposed(ImprovedFog.class);
 this->setExposed(ClimateMoon.class);
 this->setExposed(IsoPuddles.class);
 this->setExposed(IsoPuddles.PuddlesFloat.class);
 this->setExposed(BentFences.class);
 this->setExposed(BrokenFences.class);
 this->setExposed(ContainerOverlays.class);
 this->setExposed(IsoChunk.class);
 this->setExposed(BuildingDef.class);
 this->setExposed(IsoCamera.class);
 this->setExposed(IsoCell.class);
 this->setExposed(IsoChunkMap.class);
 this->setExposed(IsoDirections.class);
 this->setExposed(IsoDirectionSet.class);
 this->setExposed(IsoGridSquare.class);
 this->setExposed(IsoHeatSource.class);
 this->setExposed(IsoLightSource.class);
 this->setExposed(IsoLot.class);
 this->setExposed(IsoLuaMover.class);
 this->setExposed(IsoMetaChunk.class);
 this->setExposed(IsoMetaCell.class);
 this->setExposed(IsoMetaGrid.class);
 this->setExposed(IsoMetaGrid.Trigger.class);
 this->setExposed(IsoMetaGrid.VehicleZone.class);
 this->setExposed(IsoMetaGrid.Zone.class);
 this->setExposed(IsoMovingObject.class);
 this->setExposed(IsoObject.class);
 this->setExposed(IsoObjectPicker.class);
 this->setExposed(IsoPushableObject.class);
 this->setExposed(IsoUtils.class);
 this->setExposed(IsoWorld.class);
 this->setExposed(LosUtil.class);
 this->setExposed(MetaObject.class);
 this->setExposed(RoomDef.class);
 this->setExposed(SliceY.class);
 this->setExposed(TileOverlays.class);
 this->setExposed(Vector2.class);
 this->setExposed(Vector3.class);
 this->setExposed(WorldMarkers.class);
 this->setExposed(WorldMarkers.DirectionArrow.class);
 this->setExposed(WorldMarkers.GridSquareMarker.class);
 this->setExposed(WorldMarkers.PlayerHomingPoint.class);
 this->setExposed(SearchMode.class);
 this->setExposed(SearchMode.PlayerSearchMode.class);
 this->setExposed(SearchMode.SearchModeFloat.class);
 this->setExposed(IsoMarkers.class);
 this->setExposed(IsoMarkers.IsoMarker.class);
 this->setExposed(IsoMarkers.CircleIsoMarker.class);
 this->setExposed(LuaEventManager.class);
 this->setExposed(MapObjects.class);
 this->setExposed(ActiveMods.class);
 this->setExposed(Server.class);
 this->setExposed(ServerOptions.class);
 this->setExposed(ServerOptions.BooleanServerOption.class);
 this->setExposed(ServerOptions.DoubleServerOption.class);
 this->setExposed(ServerOptions.IntegerServerOption.class);
 this->setExposed(ServerOptions.StringServerOption.class);
 this->setExposed(ServerOptions.TextServerOption.class);
 this->setExposed(ServerSettings.class);
 this->setExposed(ServerSettingsManager.class);
 this->setExposed(ZombiePopulationRenderer.class);
 this->setExposed(ZombiePopulationRenderer.BooleanDebugOption.class);
 this->setExposed(RadioAPI.class);
 this->setExposed(DeviceData.class);
 this->setExposed(DevicePresets.class);
 this->setExposed(PresetEntry.class);
 this->setExposed(ZomboidRadio.class);
 this->setExposed(RadioData.class);
 this->setExposed(RadioScriptManager.class);
 this->setExposed(DynamicRadioChannel.class);
 this->setExposed(RadioChannel.class);
 this->setExposed(RadioBroadCast.class);
 this->setExposed(RadioLine.class);
 this->setExposed(RadioScript.class);
 this->setExposed(RadioScript.ExitOption.class);
 this->setExposed(ChannelCategory.class);
 this->setExposed(SLSoundManager.class);
 this->setExposed(StorySound.class);
 this->setExposed(StorySoundEvent.class);
 this->setExposed(EventSound.class);
 this->setExposed(DataPoint.class);
 this->setExposed(RecordedMedia.class);
 this->setExposed(MediaData.class);
 this->setExposed(MediaData.MediaLineData.class);
 this->setExposed(EvolvedRecipe.class);
 this->setExposed(Fixing.class);
 this->setExposed(Fixing.Fixer.class);
 this->setExposed(Fixing.FixerSkill.class);
 this->setExposed(GameSoundScript.class);
 this->setExposed(Item.class);
 this->setExposed(Item.Type.class);
 this->setExposed(ItemRecipe.class);
 this->setExposed(MannequinScript.class);
 this->setExposed(ModelAttachment.class);
 this->setExposed(ModelScript.class);
 this->setExposed(MovableRecipe.class);
 this->setExposed(Recipe.class);
 this->setExposed(Recipe.RequiredSkill.class);
 this->setExposed(Recipe.Result.class);
 this->setExposed(Recipe.Source.class);
 this->setExposed(ScriptModule.class);
 this->setExposed(VehicleScript.class);
 this->setExposed(VehicleScript.Area.class);
 this->setExposed(VehicleScript.Model.class);
 this->setExposed(VehicleScript.Part.class);
 this->setExposed(VehicleScript.Passenger.class);
 this->setExposed(VehicleScript.PhysicsShape.class);
 this->setExposed(VehicleScript.Position.class);
 this->setExposed(VehicleScript.Wheel.class);
 this->setExposed(ScriptManager.class);
 this->setExposed(TemplateText.class);
 this->setExposed(ReplaceProviderCharacter.class);
 this->setExposed(ActionProgressBar.class);
 this->setExposed(Clock.class);
 this->setExposed(UIDebugConsole.class);
 this->setExposed(ModalDialog.class);
 this->setExposed(MoodlesUI.class);
 this->setExposed(NewHealthPanel.class);
 this->setExposed(ObjectTooltip.class);
 this->setExposed(ObjectTooltip.Layout.class);
 this->setExposed(ObjectTooltip.LayoutItem.class);
 this->setExposed(RadarPanel.class);
 this->setExposed(RadialMenu.class);
 this->setExposed(RadialProgressBar.class);
 this->setExposed(SpeedControls.class);
 this->setExposed(TextManager.class);
 this->setExposed(UI3DModel.class);
 this->setExposed(UIElement.class);
 this->setExposed(UIFont.class);
 this->setExposed(UITransition.class);
 this->setExposed(UIManager.class);
 this->setExposed(UIServerToolbox.class);
 this->setExposed(UITextBox2.class);
 this->setExposed(VehicleGauge.class);
 this->setExposed(TextDrawObject.class);
 this->setExposed(PZArrayList.class);
 this->setExposed(PZCalendar.class);
 this->setExposed(BaseVehicle.class);
 this->setExposed(EditVehicleState.class);
 this->setExposed(PathFindBehavior2.BehaviorResult.class);
 this->setExposed(PathFindBehavior2.class);
 this->setExposed(PathFindState2.class);
 this->setExposed(UI3DScene.class);
 this->setExposed(VehicleDoor.class);
 this->setExposed(VehicleLight.class);
 this->setExposed(VehiclePart.class);
 this->setExposed(VehicleType.class);
 this->setExposed(VehicleWindow.class);
 this->setExposed(AttachedItem.class);
 this->setExposed(AttachedItems.class);
 this->setExposed(AttachedLocation.class);
 this->setExposed(AttachedLocationGroup.class);
 this->setExposed(AttachedLocations.class);
 this->setExposed(WornItems.class);
 this->setExposed(WornItem.class);
 this->setExposed(BodyLocation.class);
 this->setExposed(BodyLocationGroup.class);
 this->setExposed(BodyLocations.class);
 this->setExposed(DummySoundManager.class);
 this->setExposed(GameSounds.class);
 this->setExposed(GameTime.class);
 this->setExposed(GameWindow.class);
 this->setExposed(SandboxOptions.class);
 this->setExposed(SandboxOptions.BooleanSandboxOption.class);
 this->setExposed(SandboxOptions.DoubleSandboxOption.class);
 this->setExposed(SandboxOptions.StringSandboxOption.class);
 this->setExposed(SandboxOptions.EnumSandboxOption.class);
 this->setExposed(SandboxOptions.IntegerSandboxOption.class);
 this->setExposed(SoundManager.class);
 this->setExposed(SystemDisabler.class);
 this->setExposed(VirtualZombieManager.class);
 this->setExposed(WorldSoundManager.class);
 this->setExposed(WorldSoundManager.WorldSound.class);
 this->setExposed(DummyCharacterSoundEmitter.class);
 this->setExposed(CharacterSoundEmitter.class);
 this->setExposed(SoundManager.AmbientSoundEffect.class);
 this->setExposed(BaseAmbientStreamManager.class);
 this->setExposed(AmbientStreamManager.class);
 this->setExposed(Nutrition.class);
 this->setExposed(BSFurnace.class);
 this->setExposed(MultiStageBuilding.class);
 this->setExposed(MultiStageBuilding.Stage.class);
 this->setExposed(SleepingEvent.class);
 this->setExposed(IsoCompost.class);
 this->setExposed(Userlog.class);
 this->setExposed(Userlog.UserlogType.class);
 this->setExposed(ConfigOption.class);
 this->setExposed(BooleanConfigOption.class);
 this->setExposed(DoubleConfigOption.class);
 this->setExposed(EnumConfigOption.class);
 this->setExposed(IntegerConfigOption.class);
 this->setExposed(StringConfigOption.class);
 this->setExposed(Faction.class);
 this->setExposed(LuaManager.GlobalObject.LuaFileWriter.class);
 this->setExposed(Keyboard.class);
 this->setExposed(DBResult.class);
 this->setExposed(NonPvpZone.class);
 this->setExposed(DBTicket.class);
 this->setExposed(StashSystem.class);
 this->setExposed(StashBuilding.class);
 this->setExposed(Stash.class);
 this->setExposed(ItemType.class);
 this->setExposed(RandomizedWorldBase.class);
 this->setExposed(RandomizedBuildingBase.class);
 this->setExposed(RBBurntFireman.class);
 this->setExposed(RBBasic.class);
 this->setExposed(RBBurnt.class);
 this->setExposed(RBOther.class);
 this->setExposed(RBStripclub.class);
 this->setExposed(RBSchool.class);
 this->setExposed(RBSpiffo.class);
 this->setExposed(RBPizzaWhirled.class);
 this->setExposed(RBOffice.class);
 this->setExposed(RBHairSalon.class);
 this->setExposed(RBClinic.class);
 this->setExposed(RBPileOCrepe.class);
 this->setExposed(RBCafe.class);
 this->setExposed(RBBar.class);
 this->setExposed(RBLooted.class);
 this->setExposed(RBSafehouse.class);
 this->setExposed(RBBurntCorpse.class);
 this->setExposed(RBShopLooted.class);
 this->setExposed(RBKateAndBaldspot.class);
 this->setExposed(RandomizedDeadSurvivorBase.class);
 this->setExposed(RDSZombiesEating.class);
 this->setExposed(RDSBleach.class);
 this->setExposed(RDSDeadDrunk.class);
 this->setExposed(RDSGunmanInBathroom.class);
 this->setExposed(RDSGunslinger.class);
 this->setExposed(RDSZombieLockedBathroom.class);
 this->setExposed(RDSBandPractice.class);
 this->setExposed(RDSBathroomZed.class);
 this->setExposed(RDSBedroomZed.class);
 this->setExposed(RDSFootballNight.class);
 this->setExposed(RDSHenDo.class);
 this->setExposed(RDSStagDo.class);
 this->setExposed(RDSStudentNight.class);
 this->setExposed(RDSPokerNight.class);
 this->setExposed(RDSSuicidePact.class);
 this->setExposed(RDSPrisonEscape.class);
 this->setExposed(RDSPrisonEscapeWithPolice.class);
 this->setExposed(RDSSkeletonPsycho.class);
 this->setExposed(RDSCorpsePsycho.class);
 this->setExposed(RDSSpecificProfession.class);
 this->setExposed(RDSPoliceAtHouse.class);
 this->setExposed(RDSHouseParty.class);
 this->setExposed(RDSTinFoilHat.class);
 this->setExposed(RDSHockeyPsycho.class);
 this->setExposed(RandomizedVehicleStoryBase.class);
 this->setExposed(RVSCarCrash.class);
 this->setExposed(RVSBanditRoad.class);
 this->setExposed(RVSAmbulanceCrash.class);
 this->setExposed(RVSCrashHorde.class);
 this->setExposed(RVSCarCrashCorpse.class);
 this->setExposed(RVSPoliceBlockade.class);
 this->setExposed(RVSPoliceBlockadeShooting.class);
 this->setExposed(RVSBurntCar.class);
 this->setExposed(RVSConstructionSite.class);
 this->setExposed(RVSUtilityVehicle.class);
 this->setExposed(RVSChangingTire.class);
 this->setExposed(RVSFlippedCrash.class);
 this->setExposed(RVSTrailerCrash.class);
 this->setExposed(RandomizedZoneStoryBase.class);
 this->setExposed(RZSForestCamp.class);
 this->setExposed(RZSForestCampEaten.class);
 this->setExposed(RZSBuryingCamp.class);
 this->setExposed(RZSBeachParty.class);
 this->setExposed(RZSFishingTrip.class);
 this->setExposed(RZSBBQParty.class);
 this->setExposed(RZSHunterCamp.class);
 this->setExposed(RZSSexyTime.class);
 this->setExposed(RZSTrapperCamp.class);
 this->setExposed(RZSBaseball.class);
 this->setExposed(RZSMusicFestStage.class);
 this->setExposed(RZSMusicFest.class);
 this->setExposed(MapGroups.class);
 this->setExposed(BeardStyles.class);
 this->setExposed(BeardStyle.class);
 this->setExposed(HairStyles.class);
 this->setExposed(HairStyle.class);
 this->setExposed(BloodClothingType.class);
 this->setExposed(WeaponType.class);
 this->setExposed(IsoWaterGeometry.class);
 this->setExposed(ModData.class);
 this->setExposed(WorldMarkers.class);
 this->setExposed(ChatMessage.class);
 this->setExposed(ChatBase.class);
 this->setExposed(ServerChatMessage.class);
 this->setExposed(Safety.class);
 if (Core.bDebug) {
 this->setExposed(Field.class);
 this->setExposed(Method.class);
 this->setExposed(Coroutine.class);
 }

 UIWorldMap.setExposed(this);
 if (Core.bDebug) {
 try {
 this->exposeMethod(Class.class, Class.class.getMethod("getName"), LuaManager.env);
 this->exposeMethod(Class.class, Class.class.getMethod("getSimpleName"), LuaManager.env);
 } catch (NoSuchMethodException noSuchMethodException) {
 noSuchMethodException.printStackTrace();
 }
 }

 for (Class clazz : this->exposed) {
 this->exposeLikeJavaRecursively(clazz, LuaManager.env);
 }

 this->exposeGlobalFunctions(new LuaManager.GlobalObject());
 LuaManager.exposeKeyboardKeys(LuaManager.env);
 LuaManager.exposeLuaCalendar();
 }

 void setExposed(Class<?> clazz) {
 this->exposed.add(clazz);
 }

 bool shouldExpose(Class<?> clazz) {
 return clazz = = nullptr ? false : this->exposed.contains(clazz);
 }
 }

 /**
 * Object containing global Lua functions. The methods in this class can be called from Lua using ``methodName()``, instead of qualifying them with the class name, even if they are not static: the instance is state of the Lua environment.
 */
 public static class GlobalObject {
 static FileOutputStream outStream;
 static FileInputStream inStream;
 static FileReader inFileReader = nullptr;
 static BufferedReader inBufferedReader = nullptr;
 static long timeLastRefresh = 0L;
 private static LuaManager.GlobalObject.TimSortComparator timSortComparator = new LuaManager.GlobalObject.TimSortComparator();

 name = "loadVehicleModel",
 global = true
 )
 static Model loadVehicleModel(const std::string& name, const std::string& loc, const std::string& tex) {
 return loadZomboidModel();
 }

 name = "loadStaticZomboidModel",
 global = true
 )
 static Model loadStaticZomboidModel(const std::string& name, const std::string& loc, const std::string& tex) {
 return loadZomboidModel();
 }

 name = "loadSkinnedZomboidModel",
 global = true
 )
 static Model loadSkinnedZomboidModel(const std::string& name, const std::string& loc, const std::string& tex) {
 return loadZomboidModel();
 }

 name = "loadZomboidModel",
 global = true
 )
 static Model loadZomboidModel(const std::string& name, const std::string& mesh, const std::string& tex, const std::string& shader, bool bStatic) {
 try {
 if (mesh.startsWith("/")) {
 mesh = mesh.substring(1);
 }

 if (tex.startsWith("/")) {
 tex = tex.substring(1);
 }

 if (StringUtils.isNullOrWhitespace(shader) {
 shader = "basicEffect";
 }

 if ("vehicle" == shader) && !Core.getInstance().getPerfReflectionsOnLoad()) {
 shader = shader + "_noreflect";
 }

 Model model = ModelManager.instance.tryGetLoadedModel(mesh, tex, bStatic, shader, false);
 if (model != nullptr) {
 return model;
 } else {
 ModelManager.instance.setModelMetaData(name, mesh, tex, shader, bStatic);
 Model.ModelAssetParams modelAssetParams = new Model.ModelAssetParams();
 modelAssetParams.bStatic = bStatic;
 modelAssetParams.meshName = mesh;
 modelAssetParams.shaderName = shader;
 modelAssetParams.textureName = tex;
 modelAssetParams.textureFlags = ModelManager.instance.getTextureFlags();
 model = (Model)ModelAssetManager.instance.load(new AssetPath(name), modelAssetParams);
 if (model != nullptr) {
 ModelManager.instance.putLoadedModel(mesh, tex, bStatic, shader, model);
 }

 return model;
 }
 } catch (Exception exception) {
 DebugLog.General
 .error(
 "LuaManager.loadZomboidModel> Exception thrown loading model: "
 + name
 + " mesh:"
 + mesh
 + " tex:"
 + tex
 + " shader:"
 + shader
 + " isStatic:"
 + bStatic
 );
 exception.printStackTrace();
 return nullptr;
 }
 }

 name = "setModelMetaData",
 global = true
 )
 static void setModelMetaData(const std::string& name, const std::string& mesh, const std::string& tex, const std::string& shader, bool bStatic) {
 if (mesh.startsWith("/")) {
 mesh = mesh.substring(1);
 }

 if (tex.startsWith("/")) {
 tex = tex.substring(1);
 }

 ModelManager.instance.setModelMetaData(name, mesh, tex, shader, bStatic);
 }

 name = "reloadModelsMatching",
 global = true
 )
 static void reloadModelsMatching(const std::string& meshName) {
 ModelManager.instance.reloadModelsMatching(meshName);
 }

 name = "getSLSoundManager",
 global = true
 )
 static SLSoundManager getSLSoundManager() {
 return nullptr;
 }

 name = "getRadioAPI",
 global = true
 )
 static RadioAPI getRadioAPI() {
 return RadioAPI.hasInstance() ? RadioAPI.getInstance() : nullptr;
 }

 name = "getRadioTranslators",
 global = true
 )
 public static ArrayList<String> getRadioTranslators(Language language) {
 return RadioData.getTranslatorNames(language);
 }

 name = "getTranslatorCredits",
 global = true
 )
 public static ArrayList<String> getTranslatorCredits(Language language) {
 File file = new File(ZomboidFileSystem.instance.getString("media/lua/shared/Translate/" + language.name() + "/credits.txt"));

 try {
 std::vector arrayList0;
 try (
 FileReader fileReader = new FileReader(file, Charset.forName(language.charset()));
 BufferedReader bufferedReader = new BufferedReader(fileReader);
 ) {
 std::vector arrayList1 = new ArrayList();

 std::string string;
 while ((string = bufferedReader.readLine()) != nullptr) {
 if (!StringUtils.isNullOrWhitespace(string) {
 arrayList1.add(string.trim());
 }
 }

 arrayList0 = arrayList1;
 }

 return arrayList0;
 } catch (FileNotFoundException fileNotFoundException) {
 return nullptr;
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 return nullptr;
 }
 }

 name = "getBehaviourDebugPlayer",
 global = true
 )
 static IsoGameCharacter getBehaviourDebugPlayer() {
 return nullptr;
 }

 name = "setBehaviorStep",
 global = true
 )
 static void setBehaviorStep(bool b) {
 }

 name = "getPuddlesManager",
 global = true
 )
 static IsoPuddles getPuddlesManager() {
 return IsoPuddles.getInstance();
 }

 name = "setPuddles",
 global = true
 )
 static void setPuddles(float initialPuddles) {
 IsoPuddles.PuddlesFloat puddlesFloat = IsoPuddles.getInstance().getPuddlesFloat(3);
 puddlesFloat.setEnableAdmin(true);
 puddlesFloat.setAdminValue(initialPuddles);
 puddlesFloat = IsoPuddles.getInstance().getPuddlesFloat(1);
 puddlesFloat.setEnableAdmin(true);
 puddlesFloat.setAdminValue(PZMath.clamp_01(initialPuddles * 1.2F);
 }

 name = "getZomboidRadio",
 global = true
 )
 static ZomboidRadio getZomboidRadio() {
 return ZomboidRadio.hasInstance() ? ZomboidRadio.getInstance() : nullptr;
 }

 name = "getRandomUUID",
 global = true
 )
 static std::string getRandomUUID() {
 return ModUtilsJava.getRandomUUID();
 }

 name = "sendItemListNet",
 global = true
 )
 static bool sendItemListNet(IsoPlayer sender, ArrayList<InventoryItem> items, IsoPlayer receiver, const std::string& transferID, const std::string& custom) {
 return ModUtilsJava.sendItemListNet(sender, items, receiver, transferID, custom);
 }

 name = "instanceof",
 global = true
 )
 static bool instof(void* obj, const std::string& name) {
 if ("PZKey" == name) {
 bool boolean0 = false;
 }

 if (obj == nullptr) {
 return false;
 } else if (LuaManager.exposer.TypeMap.containsKey(name) {
 Class clazz = LuaManager.exposer.TypeMap.get(name);
 return clazz.isInstance(obj);
 } else {
 return name == "LuaClosure") && obj instanceof LuaClosure ? true : name == "KahluaTableImpl") && obj instanceof KahluaTableImpl;
 }
 }

 name = "serverConnect",
 global = true
 )
 public static void serverConnect(
 String string0, String string1, String string2, String string3, String string4, String string5, String string6, boolean boolean0
 ) {
 Core.GameMode = "Multiplayer";
 Core.setDifficulty("Hardcore");
 if (GameClient.connection != nullptr) {
 GameClient.connection.forceDisconnect("lua-connect");
 }

 GameClient.instance.resetDisconnectTimer();
 GameClient.bClient = true;
 GameClient.bCoopInvite = false;
 ZomboidFileSystem.instance.cleanMultiplayerSaves();
 GameClient.instance.doConnect(string0, string1, string2, string3, string4, string5, string6, boolean0);
 }

 name = "serverConnectCoop",
 global = true
 )
 static void serverConnectCoop(const std::string& serverSteamID) {
 Core.GameMode = "Multiplayer";
 Core.setDifficulty("Hardcore");
 if (GameClient.connection != nullptr) {
 GameClient.connection.forceDisconnect("lua-connect-coop");
 }

 GameClient.bClient = true;
 GameClient.bCoopInvite = true;
 GameClient.instance.doConnectCoop(serverSteamID);
 }

 name = "sendPing",
 global = true
 )
 static void sendPing() {
 if (GameClient.bClient) {
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPingPacket();
 PacketTypes.doPingPacket(byteBufferWriter);
 byteBufferWriter.putLong(System.currentTimeMillis());
 GameClient.connection.endPingPacket();
 }
 }

 name = "connectionManagerLog",
 global = true
 )
 static void connectionManagerLog(const std::string& string0, const std::string& string1) {
 ConnectionManager.log(string0, string1, nullptr);
 }

 name = "forceDisconnect",
 global = true
 )
 static void forceDisconnect() {
 if (GameClient.connection != nullptr) {
 GameClient.connection.forceDisconnect("lua-force-disconnect");
 }
 }

 name = "backToSinglePlayer",
 global = true
 )
 static void backToSinglePlayer() {
 if (GameClient.bClient) {
 GameClient.instance.doDisconnect("going back to single-player");
 GameClient.bClient = false;
 timeLastRefresh = 0L;
 }
 }

 name = "isIngameState",
 global = true
 )
 static bool isIngameState() {
 return GameWindow.states.current == IngameState.instance;
 }

 name = "requestPacketCounts",
 global = true
 )
 static void requestPacketCounts() {
 if (GameClient.bClient) {
 GameClient.instance.requestPacketCounts();
 }
 }

 name = "canConnect",
 global = true
 )
 static bool canConnect() {
 return GameClient.instance.canConnect();
 }

 name = "getReconnectCountdownTimer",
 global = true
 )
 static std::string getReconnectCountdownTimer() {
 return GameClient.instance.getReconnectCountdownTimer();
 }

 name = "getPacketCounts",
 global = true
 )
 static KahluaTable getPacketCounts(int category) {
 return GameClient.bClient ? PacketTypes.getPacketCounts(category) : nullptr;
 }

 name = "getAllItems",
 global = true
 )
 public static ArrayList<Item> getAllItems() {
 return ScriptManager.instance.getAllItems();
 }

 name = "scoreboardUpdate",
 global = true
 )
 static void scoreboardUpdate() {
 GameClient.instance.scoreboardUpdate();
 }

 name = "save",
 global = true
 )
 static void save(bool doCharacter) {
 try {
 GameWindow.save(doCharacter);
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 }
 }

 name = "saveGame",
 global = true
 )
 static void saveGame() {
 save(true);
 }

 name = "getAllRecipes",
 global = true
 )
 public static ArrayList<Recipe> getAllRecipes() {
 return new ArrayList<>(ScriptManager.instance.getAllRecipes());
 }

 name = "requestUserlog",
 global = true
 )
 static void requestUserlog(const std::string& user) {
 if (GameClient.bClient) {
 GameClient.instance.requestUserlog(user);
 }
 }

 name = "addUserlog",
 global = true
 )
 static void addUserlog(const std::string& user, const std::string& type, const std::string& text) {
 if (GameClient.bClient) {
 GameClient.instance.addUserlog(user, type, text);
 }
 }

 name = "removeUserlog",
 global = true
 )
 static void removeUserlog(const std::string& user, const std::string& type, const std::string& text) {
 if (GameClient.bClient) {
 GameClient.instance.removeUserlog(user, type, text);
 }
 }

 name = "tabToX",
 global = true
 )
 static std::string tabToX(const std::string& a, int tabX) {
 while (a.length() < tabX) {
 a = a + " ";
 }

 return a;
 }

 name = "istype",
 global = true
 )
 static bool isType(void* obj, const std::string& name) {
 if (LuaManager.exposer.TypeMap.containsKey(name) {
 Class clazz = LuaManager.exposer.TypeMap.get(name);
 return clazz == obj.getClass());
 } else {
 return false;
 }
 }

 name = "isoToScreenX",
 global = true
 )
 static float isoToScreenX(int player, float x, float y, float z) {
 float float0 = IsoUtils.XToScreen(x, y, z, 0) - IsoCamera.cameras[player].getOffX();
 float0 /= Core.getInstance().getZoom(player);
 return IsoCamera.getScreenLeft(player) + float0;
 }

 name = "isoToScreenY",
 global = true
 )
 static float isoToScreenY(int player, float x, float y, float z) {
 float float0 = IsoUtils.YToScreen(x, y, z, 0) - IsoCamera.cameras[player].getOffY();
 float0 /= Core.getInstance().getZoom(player);
 return IsoCamera.getScreenTop(player) + float0;
 }

 name = "screenToIsoX",
 global = true
 )
 static float screenToIsoX(int player, float x, float y, float z) {
 float float0 = Core.getInstance().getZoom(player);
 x -= IsoCamera.getScreenLeft(player);
 y -= IsoCamera.getScreenTop(player);
 return IsoCamera.cameras[player].XToIso(x * float0, y * float0, z);
 }

 name = "screenToIsoY",
 global = true
 )
 static float screenToIsoY(int player, float x, float y, float z) {
 float float0 = Core.getInstance().getZoom(player);
 x -= IsoCamera.getScreenLeft(player);
 y -= IsoCamera.getScreenTop(player);
 return IsoCamera.cameras[player].YToIso(x * float0, y * float0, z);
 }

 name = "getAmbientStreamManager",
 global = true
 )
 static BaseAmbientStreamManager getAmbientStreamManager() {
 return AmbientStreamManager.instance;
 }

 name = "getSleepingEvent",
 global = true
 )
 static SleepingEvent getSleepingEvent() {
 return SleepingEvent.instance;
 }

 name = "setPlayerMovementActive",
 global = true
 )
 static void setPlayerMovementActive(int id, bool bActive) {
 IsoPlayer.players[id].bJoypadMovementActive = bActive;
 }

 name = "setActivePlayer",
 global = true
 )
 static void setActivePlayer(int id) {
 if (!GameClient.bClient) {
 IsoPlayer.setInstance(IsoPlayer.players[id]);
 IsoCamera.CamCharacter = IsoPlayer.getInstance();
 }
 }

 /**
 * Gets the current player. To support splitscreen, getSpecificPlayer() should be preferred instead.
 * @return The current player.
 */
 name = "getPlayer",
 global = true
 )
 static IsoPlayer getPlayer() {
 return IsoPlayer.getInstance();
 }

 name = "getNumActivePlayers",
 global = true
 )
 static int getNumActivePlayers() {
 return IsoPlayer.numPlayers;
 }

 name = "playServerSound",
 global = true
 )
 static void playServerSound(const std::string& sound, IsoGridSquare sq) {
 GameServer.PlayWorldSoundServer(sound, false, sq, 0.2F, 5.0F, 1.1F, true);
 }

 name = "getMaxActivePlayers",
 global = true
 )
 static int getMaxActivePlayers() {
 return 4;
 }

 name = "getPlayerScreenLeft",
 global = true
 )
 static int getPlayerScreenLeft(int player) {
 return IsoCamera.getScreenLeft(player);
 }

 name = "getPlayerScreenTop",
 global = true
 )
 static int getPlayerScreenTop(int player) {
 return IsoCamera.getScreenTop(player);
 }

 name = "getPlayerScreenWidth",
 global = true
 )
 static int getPlayerScreenWidth(int player) {
 return IsoCamera.getScreenWidth(player);
 }

 name = "getPlayerScreenHeight",
 global = true
 )
 static int getPlayerScreenHeight(int player) {
 return IsoCamera.getScreenHeight(player);
 }

 name = "getPlayerByOnlineID",
 global = true
 )
 static IsoPlayer getPlayerByOnlineID(int id) {
 if (GameServer.bServer) {
 return GameServer.IDToPlayerMap.get((short)id);
 } else {
 return GameClient.bClient ? GameClient.IDToPlayerMap.get((short)id) : nullptr;
 }
 }

 name = "initUISystem",
 global = true
 )
 static void initUISystem() {
 UIManager.init();
 LuaEventManager.triggerEvent("OnCreatePlayer", 0, IsoPlayer.players[0]);
 }

 name = "getPerformance",
 global = true
 )
 static PerformanceSettings getPerformance() {
 return PerformanceSettings.instance;
 }

 name = "getDBSchema",
 global = true
 )
 static void getDBSchema() {
 GameClient.instance.getDBSchema();
 }

 name = "getTableResult",
 global = true
 )
 static void getTableResult(const std::string& tableName, int numberPerPages) {
 GameClient.instance.getTableResult(tableName, numberPerPages);
 }

 name = "getWorldSoundManager",
 global = true
 )
 static WorldSoundManager getWorldSoundManager() {
 return WorldSoundManager.instance;
 }

 name = "AddWorldSound",
 global = true
 )
 static void AddWorldSound(IsoPlayer player, int radius, int volume) {
 WorldSoundManager.instance.addSound(nullptr, (int)player.getX(), (int)player.getY(), (int)player.getZ(), radius, volume, false);
 }

 name = "AddNoiseToken",
 global = true
 )
 static void AddNoiseToken(IsoGridSquare sq, int radius) {
 }

 name = "pauseSoundAndMusic",
 global = true
 )
 static void pauseSoundAndMusic() {
 DebugLog.log("EXITDEBUG: pauseSoundAndMusic 1");
 SoundManager.instance.pauseSoundAndMusic();
 DebugLog.log("EXITDEBUG: pauseSoundAndMusic 2");
 }

 name = "resumeSoundAndMusic",
 global = true
 )
 static void resumeSoundAndMusic() {
 SoundManager.instance.resumeSoundAndMusic();
 }

 name = "isDemo",
 global = true
 )
 static bool isDemo() {
 Core.getInstance();
 return false;
 }

 name = "getTimeInMillis",
 global = true
 )
 static long getTimeInMillis() {
 return System.currentTimeMillis();
 }

 name = "getCurrentCoroutine",
 global = true
 )
 static Coroutine getCurrentCoroutine() {
 return LuaManager.thread.getCurrentCoroutine();
 }

 name = "reloadLuaFile",
 global = true
 )
 static void reloadLuaFile(const std::string& filename) {
 LuaManager.loaded.remove(filename);
 LuaManager.RunLua(filename, true);
 }

 name = "reloadServerLuaFile",
 global = true
 )
 static void reloadServerLuaFile(const std::string& filename) {
 if (GameServer.bServer) {
 filename = ZomboidFileSystem.instance.getCacheDir() + File.separator + "Server" + File.separator + filename;
 LuaManager.loaded.remove(filename);
 LuaManager.RunLua(filename, true);
 }
 }

 name = "getServerSpawnRegions",
 global = true
 )
 static KahluaTable getServerSpawnRegions() {
 return !GameClient.bClient ? nullptr : GameClient.instance.getServerSpawnRegions();
 }

 name = "getServerOptions",
 global = true
 )
 static ServerOptions getServerOptions() {
 return ServerOptions.instance;
 }

 name = "getServerName",
 global = true
 )
 static std::string getServerName() {
 if (GameServer.bServer) {
 return GameServer.ServerName;
 } else {
 return GameClient.bClient ? GameClient.ServerName : "";
 }
 }

 name = "getServerIP",
 global = true
 )
 static std::string getServerIP() {
 if (GameServer.bServer) {
 return GameServer.IPCommandline == nullptr ? GameServer.ip : GameServer.IPCommandline;
 } else {
 return GameClient.bClient ? GameClient.ip : "";
 }
 }

 name = "getServerPort",
 global = true
 )
 static std::string getServerPort() {
 if (GameServer.bServer) {
 return String.valueOf(GameServer.DEFAULT_PORT);
 } else {
 return GameClient.bClient ? String.valueOf(GameClient.port) : "";
 }
 }

 name = "isShowConnectionInfo",
 global = true
 )
 static bool isShowConnectionInfo() {
 return NetworkAIParams.isShowConnectionInfo();
 }

 name = "setShowConnectionInfo",
 global = true
 )
 static void setShowConnectionInfo(bool enabled) {
 NetworkAIParams.setShowConnectionInfo(enabled);
 }

 name = "isShowServerInfo",
 global = true
 )
 static bool isShowServerInfo() {
 return NetworkAIParams.isShowServerInfo();
 }

 name = "setShowServerInfo",
 global = true
 )
 static void setShowServerInfo(bool enabled) {
 NetworkAIParams.setShowServerInfo(enabled);
 }

 name = "isShowPingInfo",
 global = true
 )
 static bool isShowPingInfo() {
 return NetworkAIParams.isShowPingInfo();
 }

 name = "setShowPingInfo",
 global = true
 )
 static void setShowPingInfo(bool enabled) {
 NetworkAIParams.setShowPingInfo(enabled);
 }

 name = "getSpecificPlayer",
 global = true
 )
 static IsoPlayer getSpecificPlayer(int player) {
 return IsoPlayer.players[player];
 }

 name = "getCameraOffX",
 global = true
 )
 static float getCameraOffX() {
 return IsoCamera.getOffX();
 }

 name = "getLatestSave",
 global = true
 )
 static KahluaTable getLatestSave() {
 KahluaTable table = LuaManager.platform.newTable();
 BufferedReader bufferedReader = nullptr;

 try {
 bufferedReader = new BufferedReader(new FileReader(new File(ZomboidFileSystem.instance.getCacheDir() + File.separator + "latestSave.ini")));
 } catch (FileNotFoundException fileNotFoundException) {
 return table;
 }

 try {
 void* object = nullptr;

 for (int int0 = 1; (object = bufferedReader.readLine()) != nullptr; int0++) {
 table.rawset(int0, object);
 }

 bufferedReader.close();
 return table;
 } catch (Exception exception) {
 return table;
 }
 }

 name = "isCurrentExecutionPoint",
 global = true
 )
 static bool isCurrentExecutionPoint(const std::string& file, int line) {
 int int0 = LuaManager.thread.currentCoroutine.getCallframeTop() - 1;
 if (int0 < 0) {
 int0 = 0;
 }

 LuaCallFrame luaCallFrame = LuaManager.thread.currentCoroutine.getCallFrame(int0);
 return luaCallFrame.closure == nullptr
 ? false
 : luaCallFrame.closure.prototype.lines[luaCallFrame.pc] == line && file == luaCallFrame.closure.prototype.filename);
 }

 name = "toggleBreakOnChange",
 global = true
 )
 static void toggleBreakOnChange(KahluaTable table, void* key) {
 if (Core.bDebug) {
 LuaManager.thread.toggleBreakOnChange(table, key);
 }
 }

 name = "isDebugEnabled",
 global = true
 )
 static bool isDebugEnabled() {
 return Core.bDebug;
 }

 name = "toggleBreakOnRead",
 global = true
 )
 static void toggleBreakOnRead(KahluaTable table, void* key) {
 if (Core.bDebug) {
 LuaManager.thread.toggleBreakOnRead(table, key);
 }
 }

 name = "toggleBreakpoint",
 global = true
 )
 static void toggleBreakpoint(const std::string& file, int line) {
 file = file.replace("\\", "/");
 if (Core.bDebug) {
 LuaManager.thread.breakpointToggle(file, line);
 }
 }

 name = "sendVisual",
 global = true
 )
 static void sendVisual(IsoPlayer player) {
 if (GameClient.bClient) {
 GameClient.instance.sendVisual(player);
 }
 }

 name = "sendClothing",
 global = true
 )
 static void sendClothing(IsoPlayer player) {
 if (GameClient.bClient) {
 GameClient.instance.sendClothing(player, "", nullptr);
 }
 }

 name = "hasDataReadBreakpoint",
 global = true
 )
 static bool hasDataReadBreakpoint(KahluaTable table, void* key) {
 return LuaManager.thread.hasReadDataBreakpoint(table, key);
 }

 name = "hasDataBreakpoint",
 global = true
 )
 static bool hasDataBreakpoint(KahluaTable table, void* key) {
 return LuaManager.thread.hasDataBreakpoint(table, key);
 }

 name = "hasBreakpoint",
 global = true
 )
 static bool hasBreakpoint(const std::string& file, int line) {
 return LuaManager.thread.hasBreakpoint(file, line);
 }

 name = "getLoadedLuaCount",
 global = true
 )
 static int getLoadedLuaCount() {
 return LuaManager.loaded.size();
 }

 name = "getLoadedLua",
 global = true
 )
 static std::string getLoadedLua(int n) {
 return LuaManager.loaded.get(n);
 }

 name = "isServer",
 global = true
 )
 static bool isServer() {
 return GameServer.bServer;
 }

 name = "isServerSoftReset",
 global = true
 )
 static bool isServerSoftReset() {
 return GameServer.bServer && GameServer.bSoftReset;
 }

 name = "isClient",
 global = true
 )
 static bool isClient() {
 return GameClient.bClient;
 }

 name = "canModifyPlayerStats",
 global = true
 )
 static bool canModifyPlayerStats() {
 return !GameClient.bClient ? true : GameClient.canModifyPlayerStats();
 }

 name = "executeQuery",
 global = true
 )
 static void executeQuery(const std::string& query, KahluaTable params) {
 GameClient.instance.executeQuery(query, params);
 }

 name = "canSeePlayerStats",
 global = true
 )
 static bool canSeePlayerStats() {
 return GameClient.canSeePlayerStats();
 }

 name = "getAccessLevel",
 global = true
 )
 static std::string getAccessLevel() {
 return PlayerType.toString(GameClient.connection.accessLevel);
 }

 name = "getOnlinePlayers",
 global = true
 )
 public static ArrayList<IsoPlayer> getOnlinePlayers() {
 if (GameServer.bServer) {
 return GameServer.getPlayers();
 } else {
 return GameClient.bClient ? GameClient.instance.getPlayers() : nullptr;
 }
 }

 name = "getDebug",
 global = true
 )
 static bool getDebug() {
 return Core.bDebug || GameServer.bServer && GameServer.bDebug;
 }

 name = "getCameraOffY",
 global = true
 )
 static float getCameraOffY() {
 return IsoCamera.getOffY();
 }

 /**
 * Create a dynamic table containing all spawnpoints.lua we find in vanilla folder + in loaded mods
 */
 name = "createRegionFile",
 global = true
 )
 static KahluaTable createRegionFile() {
 KahluaTable table0 = LuaManager.platform.newTable();
 std::string string0 = IsoWorld.instance.getMap();
 if (string0 == "DEFAULT")) {
 MapGroups mapGroups = new MapGroups();
 mapGroups.createGroups();
 if (mapGroups.getNumberOfGroups() != 1) {
 throw RuntimeException("GameMap is DEFAULT but there are multiple worlds to choose from");
 }

 mapGroups.setWorld(0);
 string0 = IsoWorld.instance.getMap();
 }

 if (!GameClient.bClient && !GameServer.bServer) {
 string0 = MapGroups.addMissingVanillaDirectories(string0);
 }

 String[] strings = string0.split(";");
 int int0 = 1;

 for (auto& string1 : strings) string1 = string1.trim();
 if (!string1.empty()) {
 File file = new File(ZomboidFileSystem.instance.getString("media/maps/" + string1 + "/spawnpoints.lua"));
 if (file.exists()) {
 KahluaTable table1 = LuaManager.platform.newTable();
 table1.rawset("name", string1);
 table1.rawset("file", "media/maps/" + string1 + "/spawnpoints.lua");
 table0.rawset(int0, table1);
 int0++;
 }
 }
 }

 return table0;
 }

 name = "getMapDirectoryTable",
 global = true
 )
 static KahluaTable getMapDirectoryTable() {
 KahluaTable table = LuaManager.platform.newTable();
 File file = ZomboidFileSystem.instance.getMediaFile("maps");
 String[] strings = file.list();
 if (strings == nullptr) {
 return table;
 } else {
 int int0 = 1;

 for (int int1 = 0; int1 < strings.length; int1++) {
 std::string string0 = strings[int1];
 if (!string0 == "challengemaps")) {
 table.rawset(int0, string0);
 int0++;
 }
 }

 for (String string1 : ZomboidFileSystem.instance.getModIDs()) {
 ChooseGameInfo.Mod mod = nullptr;

 try {
 mod = ChooseGameInfo.getAvailableModDetails(string1);
 } catch (Exception exception) {
 }

 if (mod != nullptr) {
 file = new File(mod.getDir() + "/media/maps/");
 if (file.exists()) {
 strings = file.list();
 if (strings != nullptr) {
 for (int int2 = 0; int2 < strings.length; int2++) {
 std::string string2 = strings[int2];
 ChooseGameInfo.Map map = ChooseGameInfo.getMapDetails(string2);
 if (map.getLotDirectories() != nullptr && !map.getLotDirectories().empty() && !string2 == "challengemaps")) {
 table.rawset(int0, string2);
 int0++;
 }
 }
 }
 }
 }
 }

 return table;
 }
 }

 name = "deleteSave",
 global = true
 )
 static void deleteSave(const std::string& file) {
 if (StringUtils.containsDoubleDot(file) {
 DebugLog.Lua.warn("relative paths not allowed");
 } else {
 File file0 = new File(ZomboidFileSystem.instance.getSaveDirSub(file);
 String[] strings = file0.list();
 if (strings != nullptr) {
 for (int int0 = 0; int0 < strings.length; int0++) {
 File file1 = new File(ZomboidFileSystem.instance.getSaveDirSub(file + File.separator + strings[int0]));
 if (file1.isDirectory()) {
 deleteSave(file + File.separator + file1.getName());
 }

 file1.delete();
 }

 file0.delete();
 }
 }
 }

 name = "sendPlayerExtraInfo",
 global = true
 )
 static void sendPlayerExtraInfo(IsoPlayer p) {
 GameClient.sendPlayerExtraInfo(p);
 }

 name = "getServerAddressFromArgs",
 global = true
 )
 static std::string getServerAddressFromArgs() {
 if (System.getProperty("args.server.connect") != nullptr) {
 std::string string = System.getProperty("args.server.connect");
 System.clearProperty("args.server.connect");
 return string;
 } else {
 return nullptr;
 }
 }

 name = "getServerPasswordFromArgs",
 global = true
 )
 static std::string getServerPasswordFromArgs() {
 if (System.getProperty("args.server.password") != nullptr) {
 std::string string = System.getProperty("args.server.password");
 System.clearProperty("args.server.password");
 return string;
 } else {
 return nullptr;
 }
 }

 name = "getServerListFile",
 global = true
 )
 static std::string getServerListFile() {
 return SteamUtils.isSteamModeEnabled() ? "ServerListSteam.txt" : "ServerList.txt";
 }

 name = "getServerList",
 global = true
 )
 static KahluaTable getServerList() {
 std::vector arrayList = new ArrayList();
 KahluaTable table = LuaManager.platform.newTable();
 BufferedReader bufferedReader = nullptr;

 try {
 File file = new File(LuaManager.getLuaCacheDir() + File.separator + getServerListFile());
 if (!file.exists()) {
 file.createNewFile();
 }

 bufferedReader = new BufferedReader(new FileReader(file, StandardCharsets.UTF_8);
 void* object = nullptr;
 Server server0 = nullptr;

 while ((object = bufferedReader.readLine()) != nullptr) {
 if (object.startsWith("name=")) {
 server0 = std::make_unique<Server>();
 arrayList.add(server0);
 server0.setName(object.replaceFirst("name=", ""));
 } else if (object.startsWith("ip=")) {
 server0.setIp(object.replaceFirst("ip=", ""));
 } else if (object.startsWith("localip=")) {
 server0.setLocalIP(object.replaceFirst("localip=", ""));
 } else if (object.startsWith("description=")) {
 server0.setDescription(object.replaceFirst("description=", ""));
 } else if (object.startsWith("port=")) {
 server0.setPort(object.replaceFirst("port=", ""));
 } else if (object.startsWith("user=")) {
 server0.setUserName(object.replaceFirst("user=", ""));
 } else if (object.startsWith("password=")) {
 server0.setPwd(object.replaceFirst("password=", ""));
 } else if (object.startsWith("serverpassword=")) {
 server0.setServerPassword(object.replaceFirst("serverpassword=", ""));
 } else if (object.startsWith("usesteamrelay=")) {
 server0.setUseSteamRelay(Boolean.parseBoolean(object.replaceFirst("usesteamrelay=", "")));
 }
 }

 int int0 = 1;

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 Server server1 = (Server)arrayList.get(int1);
 double double0 = (double)int0;
 table.rawset(double0, server1);
 int0++;
 }
 } catch (Exception exception0) {
 exception0.printStackTrace();
 } finally {
 try {
 bufferedReader.close();
 } catch (Exception exception1) {
 }
 }

 return table;
 }

 name = "ping",
 global = true
 )
 static void ping(const std::string& username, const std::string& pwd, const std::string& ip, const std::string& port) {
 GameClient.askPing = true;
 serverConnect(username, pwd, ip, "", port, "", "", false);
 }

 name = "stopPing",
 global = true
 )
 static void stopPing() {
 GameClient.askPing = false;
 }

 name = "transformIntoKahluaTable",
 global = true
 )
 static KahluaTable transformIntoKahluaTable(Object> map) {
 KahluaTable table = LuaManager.platform.newTable();

 for (Entry entry : map.entrySet()) {
 table.rawset(entry.getKey(), entry.getValue());
 }

 return table;
 }

 name = "getSaveDirectory",
 global = true
 )
 public static ArrayList<File> getSaveDirectory(String folder) {
 File file0 = new File(folder + File.separator);
 if (!file0.exists() && !Core.getInstance().isNoSave()) {
 file0.mkdir();
 }

 String[] strings = file0.list();
 if (strings == nullptr) {
 return nullptr;
 } else {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < strings.length; int0++) {
 File file1 = new File(folder + File.separator + strings[int0]);
 if (file1.isDirectory()) {
 arrayList.add(file1);
 }
 }

 return arrayList;
 }
 }

 name = "getFullSaveDirectoryTable",
 global = true
 )
 static KahluaTable getFullSaveDirectoryTable() {
 KahluaTable table = LuaManager.platform.newTable();
 File file0 = new File(ZomboidFileSystem.instance.getSaveDir() + File.separator);
 if (!file0.exists()) {
 file0.mkdir();
 }

 String[] strings = file0.list();
 if (strings == nullptr) {
 return table;
 } else {
 std::vector arrayList0 = new ArrayList();

 for (int int0 = 0; int0 < strings.length; int0++) {
 File file1 = new File(ZomboidFileSystem.instance.getSaveDir() + File.separator + strings[int0]);
 if (file1.isDirectory() && !"Multiplayer" == strings[int0])) {
 std::vector arrayList1 = getSaveDirectory(ZomboidFileSystem.instance.getSaveDir() + File.separator + strings[int0]);
 arrayList0.addAll(arrayList1);
 }
 }

 Collections.sort(arrayList0, std::make_unique<Comparator<File>>() {
 int compare(File file0, File file1) {
 return Long.valueOf(file1.lastModified()).compareTo(file0.lastModified());
 }
 });
 int int1 = 1;

 for (int int2 = 0; int2 < arrayList0.size(); int2++) {
 File file2 = (File)arrayList0.get(int2);
 std::string string = getSaveName(file2);
 double double0 = (double)int1;
 table.rawset(double0, string);
 int1++;
 }

 return table;
 }
 }

 static std::string getSaveName(File file) {
 String[] strings = file.getAbsolutePath().split("\\" + File.separator);
 return strings[strings.length - 2] + File.separator + file.getName();
 }

 name = "getSaveDirectoryTable",
 global = true
 )
 static KahluaTable getSaveDirectoryTable() {
 return LuaManager.platform.newTable();
 }

 public static List<String> getMods() {
 std::vector arrayList = new ArrayList();
 ZomboidFileSystem.instance.getAllModFolders(arrayList);
 return arrayList;
 }

 name = "doChallenge",
 global = true
 )
 static void doChallenge(KahluaTable challenge) {
 Core.GameMode = challenge.rawget("gameMode").toString();
 Core.ChallengeID = challenge.rawget("id").toString();
 Core.bLastStand = Core.GameMode == "LastStand");
 Core.getInstance().setChallenge(true);
 getWorld().setMap(challenge.getString("world"));
 int integer = Rand.Next(100000000);
 IsoWorld.instance.setWorld(integer.toString());
 getWorld().bDoChunkMapUpdate = false;
 }

 name = "doTutorial",
 global = true
 )
 static void doTutorial(KahluaTable tutorial) {
 Core.GameMode = "Tutorial";
 Core.bLastStand = false;
 Core.ChallengeID = nullptr;
 Core.getInstance().setChallenge(false);
 Core.bTutorial = true;
 getWorld().setMap(tutorial.getString("world"));
 getWorld().bDoChunkMapUpdate = false;
 }

 name = "deleteAllGameModeSaves",
 global = true
 )
 static void deleteAllGameModeSaves(const std::string& gameMode) {
 std::string string = Core.GameMode;
 Core.GameMode = gameMode;
 Path path = Paths.get(ZomboidFileSystem.instance.getGameModeCacheDir());
 if (!Files.exists(path) {
 Core.GameMode = string;
 } else {
 try {
 Files.walkFileTree(path, std::make_unique<FileVisitor<Path>>() {
 FileVisitResult preVisitDirectory(Path var1, BasicFileAttributes var2) {
 return FileVisitResult.CONTINUE;
 }

 FileVisitResult visitFile(Path path, BasicFileAttributes var2) {
 Files.delete(path);
 return FileVisitResult.CONTINUE;
 }

 FileVisitResult visitFileFailed(Path var1, std::ios_base::failure iOExceptionx) {
 iOExceptionx.printStackTrace();
 return FileVisitResult.CONTINUE;
 }

 FileVisitResult postVisitDirectory(Path path, std::ios_base::failure var2) {
 Files.delete(path);
 return FileVisitResult.CONTINUE;
 }
 });
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }

 Core.GameMode = string;
 }
 }

 name = "sledgeDestroy",
 global = true
 )
 static void sledgeDestroy(IsoObject object) {
 if (GameClient.bClient) {
 GameClient.destroy(object);
 }
 }

 name = "getTickets",
 global = true
 )
 static void getTickets(const std::string& author) {
 if (GameClient.bClient) {
 GameClient.getTickets(author);
 }
 }

 name = "addTicket",
 global = true
 )
 static void addTicket(const std::string& author, const std::string& message, int ticketID) {
 if (GameClient.bClient) {
 GameClient.addTicket(author, message, ticketID);
 }
 }

 name = "removeTicket",
 global = true
 )
 static void removeTicket(int ticketID) {
 if (GameClient.bClient) {
 GameClient.removeTicket(ticketID);
 }
 }

 name = "sendFactionInvite",
 global = true
 )
 static void sendFactionInvite(Faction faction, IsoPlayer host, const std::string& invited) {
 if (GameClient.bClient) {
 GameClient.sendFactionInvite(faction, host, invited);
 }
 }

 name = "acceptFactionInvite",
 global = true
 )
 static void acceptFactionInvite(Faction faction, const std::string& host) {
 if (GameClient.bClient) {
 GameClient.acceptFactionInvite(faction, host);
 }
 }

 name = "sendSafehouseInvite",
 global = true
 )
 static void sendSafehouseInvite(SafeHouse safehouse, IsoPlayer host, const std::string& invited) {
 if (GameClient.bClient) {
 GameClient.sendSafehouseInvite(safehouse, host, invited);
 }
 }

 name = "acceptSafehouseInvite",
 global = true
 )
 static void acceptSafehouseInvite(SafeHouse safehouse, const std::string& host) {
 if (GameClient.bClient) {
 GameClient.acceptSafehouseInvite(safehouse, host);
 }
 }

 name = "createHordeFromTo",
 global = true
 )
 static void createHordeFromTo(float spawnX, float spawnY, float targetX, float targetY, int count) {
 ZombiePopulationManager.instance.createHordeFromTo((int)spawnX, (int)spawnY, (int)targetX, (int)targetY, count);
 }

 name = "createHordeInAreaTo",
 global = true
 )
 static void createHordeInAreaTo(int spawnX, int spawnY, int spawnW, int spawnH, int targetX, int targetY, int count) {
 ZombiePopulationManager.instance.createHordeInAreaTo(spawnX, spawnY, spawnW, spawnH, targetX, targetY, count);
 }

 name = "spawnHorde",
 global = true
 )
 static void spawnHorde(float x, float y, float x2, float y2, float z, int count) {
 for (int int0 = 0; int0 < count; int0++) {
 VirtualZombieManager.instance.choices.clear();
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare((double)Rand.Next(x, x2), (double)Rand.Next(y, y2), (double)z);
 if (square != nullptr) {
 VirtualZombieManager.instance.choices.add(square);
 IsoZombie zombie0 = VirtualZombieManager.instance
 .createRealZombieAlways(IsoDirections.fromIndex(Rand.Next(IsoDirections.Max.index())).index(), false);
 zombie0.dressInRandomOutfit();
 ZombieSpawnRecorder.instance.record(zombie0, "LuaManager.spawnHorde");
 }
 }
 }

 name = "createZombie",
 global = true
 )
 static IsoZombie createZombie(float x, float y, float z, SurvivorDesc desc, int palette, IsoDirections dir) {
 VirtualZombieManager.instance.choices.clear();
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare((double)x, (double)y, (double)z);
 VirtualZombieManager.instance.choices.add(square);
 IsoZombie zombie0 = VirtualZombieManager.instance.createRealZombieAlways(dir.index(), false);
 ZombieSpawnRecorder.instance.record(zombie0, "LuaManager.createZombie");
 return zombie0;
 }

 name = "triggerEvent",
 global = true
 )
 static void triggerEvent(const std::string& event) {
 LuaEventManager.triggerEvent(event);
 }

 name = "triggerEvent",
 global = true
 )
 static void triggerEvent(const std::string& event, void* param) {
 LuaEventManager.triggerEventGarbage(event, param);
 }

 name = "triggerEvent",
 global = true
 )
 static void triggerEvent(const std::string& event, void* param, void* param2) {
 LuaEventManager.triggerEventGarbage(event, param, param2);
 }

 name = "triggerEvent",
 global = true
 )
 static void triggerEvent(const std::string& event, void* param, void* param2, void* param3) {
 LuaEventManager.triggerEventGarbage(event, param, param2, param3);
 }

 name = "triggerEvent",
 global = true
 )
 static void triggerEvent(const std::string& event, void* param, void* param2, void* param3, void* param4) {
 LuaEventManager.triggerEventGarbage(event, param, param2, param3, param4);
 }

 name = "debugLuaTable",
 global = true
 )
 static void debugLuaTable(void* param, int depth) {
 if (depth <= 1) {
 if (param instanceof KahluaTable table) {
 KahluaTableIterator kahluaTableIterator = table.iterator();
 void* object0 = "";

 for (int int0 = 0; int0 < depth; int0++) {
 object0 = object0 + "\t";
 }

 do {
 void* object1 = kahluaTableIterator.getKey();
 void* object2 = kahluaTableIterator.getValue();
 if (object1 != nullptr) {
 if (object2 != nullptr) {
 DebugLog.Lua.debugln(object0 + object1 + " : " + object2.toString());
 }

 if (object2 instanceof KahluaTable) {
 debugLuaTable(object2, depth + 1);
 }
 }
 } while (kahluaTableIterator.advance());

 if (table.getMetatable() != nullptr) {
 debugLuaTable(table.getMetatable(), depth);
 }
 }
 }
 }

 name = "debugLuaTable",
 global = true
 )
 static void debugLuaTable(void* param) {
 debugLuaTable(param, 0);
 }

 name = "sendItemsInContainer",
 global = true
 )
 static void sendItemsInContainer(IsoObject obj, ItemContainer container) {
 GameServer.sendItemsInContainer(obj, container == nullptr ? obj.getContainer() : container);
 }

 name = "getModDirectoryTable",
 global = true
 )
 static KahluaTable getModDirectoryTable() {
 KahluaTable table = LuaManager.platform.newTable();
 std::vector list = getMods();
 int int0 = 1;

 for (int int1 = 0; int1 < list.size(); int1++) {
 std::string string = (String)list.get(int1);
 double double0 = (double)int0;
 table.rawset(double0, string);
 int0++;
 }

 return table;
 }

 name = "getModInfoByID",
 global = true
 )
 public static ChooseGameInfo.Mod getModInfoByID(String modID) {
 try {
 return ChooseGameInfo.getModDetails(modID);
 } catch (Exception exception) {
 exception.printStackTrace();
 return nullptr;
 }
 }

 name = "getModInfo",
 global = true
 )
 public static ChooseGameInfo.Mod getModInfo(String modDir) {
 try {
 return ChooseGameInfo.readModInfo(modDir);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 return nullptr;
 }
 }

 name = "getMapFoldersForMod",
 global = true
 )
 public static ArrayList<String> getMapFoldersForMod(String modID) {
 try {
 ChooseGameInfo.Mod mod = ChooseGameInfo.getModDetails(modID);
 if (mod == nullptr) {
 return nullptr;
 } else {
 std::string string = mod.getDir() + File.separator + "media" + File.separator + "maps";
 File file = new File(string);
 if (file.exists() && file.isDirectory()) {
 std::vector arrayList = nullptr;

 try (DirectoryStream directoryStream = Files.newDirectoryStream(file.toPath())) {
 for (auto& path : directoryStream) if (Files.isDirectory(path) {
 file = new File(string + File.separator + path.getFileName().toString() + File.separator + "map.info");
 if (file.exists()) {
 if (arrayList == nullptr) {
 arrayList = std::make_unique<ArrayList>();
 }

 arrayList.add(path.getFileName().toString());
 }
 }
 }
 }

 return arrayList;
 } else {
 return nullptr;
 }
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 return nullptr;
 }
 }

 name = "spawnpointsExistsForMod",
 global = true
 )
 static bool spawnpointsExistsForMod(const std::string& modID, const std::string& mapFolder) {
 try {
 ChooseGameInfo.Mod mod = ChooseGameInfo.getModDetails(modID);
 if (mod == nullptr) {
 return false;
 } else {
 String string = mod.getDir()
 + File.separator
 + "media"
 + File.separator
 + "maps"
 + File.separator
 + mapFolder
 + File.separator
 + "spawnpoints.lua";
 return new File(string).exists();
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 return false;
 }
 }

 /**
 * Returns the OS-defined file separator. It is not generally needed to use this, as most functions that expect a filepath string will parse them in an OS-independent way.
 * @return The file separator.
 */
 name = "getFileSeparator",
 global = true
 )
 static std::string getFileSeparator() {
 return File.separator;
 }

 name = "getScriptManager",
 global = true
 )
 static ScriptManager getScriptManager() {
 return ScriptManager.instance;
 }

 name = "checkSaveFolderExists",
 global = true
 )
 static bool checkSaveFolderExists(const std::string& f) {
 File file = new File(ZomboidFileSystem.instance.getSaveDir() + File.separator + f);
 return file.exists();
 }

 name = "getAbsoluteSaveFolderName",
 global = true
 )
 static std::string getAbsoluteSaveFolderName(const std::string& f) {
 File file = new File(ZomboidFileSystem.instance.getSaveDir() + File.separator + f);
 return file.getAbsolutePath();
 }

 name = "checkSaveFileExists",
 global = true
 )
 static bool checkSaveFileExists(const std::string& f) {
 File file = new File(ZomboidFileSystem.instance.getFileNameInCurrentSave(f);
 return file.exists();
 }

 name = "checkSavePlayerExists",
 global = true
 )
 static bool checkSavePlayerExists() {
 if (!GameClient.bClient) {
 return PlayerDBHelper.isPlayerAlive(ZomboidFileSystem.instance.getCurrentSaveDir(), 1);
 } else {
 return ClientPlayerDB.getInstance() == nullptr
 ? false
 : ClientPlayerDB.getInstance().clientLoadNetworkPlayer() && ClientPlayerDB.getInstance().isAliveMainNetworkPlayer();
 }
 }

 name = "fileExists",
 global = true
 )
 static bool fileExists(const std::string& filename) {
 std::string string = filename.replace("/", File.separator);
 string = string.replace("\\", File.separator);
 File file = new File(ZomboidFileSystem.instance.getString(string);
 return file.exists();
 }

 name = "serverFileExists",
 global = true
 )
 static bool serverFileExists(const std::string& filename) {
 std::string string = filename.replace("/", File.separator);
 string = string.replace("\\", File.separator);
 File file = new File(ZomboidFileSystem.instance.getCacheDir() + File.separator + "Server" + File.separator + string);
 return file.exists();
 }

 name = "takeScreenshot",
 global = true
 )
 static void takeScreenshot() {
 Core.getInstance().TakeFullScreenshot(nullptr);
 }

 name = "takeScreenshot",
 global = true
 )
 static void takeScreenshot(const std::string& fileName) {
 Core.getInstance().TakeFullScreenshot(fileName);
 }

 name = "checkStringPattern",
 global = true
 )
 static bool checkStringPattern(const std::string& pattern) {
 return !pattern.contains("[");
 }

 name = "instanceItem",
 global = true
 )
 static InventoryItem instanceItem(Item item) {
 return InventoryItemFactory.CreateItem(item.moduleDotType);
 }

 name = "instanceItem",
 global = true
 )
 static InventoryItem instanceItem(const std::string& item) {
 return InventoryItemFactory.CreateItem(item);
 }

 name = "createNewScriptItem",
 global = true
 )
 static Item createNewScriptItem(const std::string& base, const std::string& name, const std::string& display, const std::string& type, const std::string& icon) {
 Item item = new Item();
 item.module = ScriptManager.instance.getModule(base);
 item.module.ItemMap.put(name, item);
 item.Icon = "Item_" + icon;
 item.DisplayName = display;
 item.name = name;
 item.moduleDotType = item.module.name + "." + name;

 try {
 item.type = Item.Type.valueOf(type);
 } catch (Exception exception) {
 }

 return item;
 }

 name = "cloneItemType",
 global = true
 )
 static Item cloneItemType(const std::string& newName, const std::string& oldName) {
 Item item0 = ScriptManager.instance.FindItem(oldName);
 Item item1 = new Item();
 item1.module = item0.getModule();
 item1.module.ItemMap.put(newName, item1);
 return item1;
 }

 name = "moduleDotType",
 global = true
 )
 static std::string moduleDotType(const std::string& module, const std::string& type) {
 return StringUtils.moduleDotType(module, type);
 }

 name = "require",
 global = true
 )
 static void* require(const std::string& f) {
 std::string string0 = f;
 if (!f.endsWith(".lua")) {
 string0 = f + ".lua";
 }

 for (int int0 = 0; int0 < LuaManager.paths.size(); int0++) {
 std::string string1 = LuaManager.paths.get(int0);
 std::string string2 = ZomboidFileSystem.instance.getAbsolutePath(string1 + string0);
 if (string2 != nullptr) {
 return LuaManager.RunLua(ZomboidFileSystem.instance.getString(string2);
 }
 }

 DebugLog.Lua.warn("require(\"" + f + "\") failed");
 return nullptr;
 }

 name = "getRenderer",
 global = true
 )
 static SpriteRenderer getRenderer() {
 return SpriteRenderer.instance;
 }

 name = "getGameTime",
 global = true
 )
 static GameTime getGameTime() {
 return GameTime.instance;
 }

 name = "getMPStatistics",
 global = true
 )
 static KahluaTable getStatistics() {
 return MPStatistics.getLuaStatistics();
 }

 name = "getMPStatus",
 global = true
 )
 static KahluaTable getMPStatus() {
 return MPStatistics.getLuaStatus();
 }

 name = "getMaxPlayers",
 global = true
 )
 static double getMaxPlayers() {
 return (double)GameClient.connection.maxPlayers;
 }

 name = "getWorld",
 global = true
 )
 static IsoWorld getWorld() {
 return IsoWorld.instance;
 }

 name = "getCell",
 global = true
 )
 static IsoCell getCell() {
 return IsoWorld.instance.getCell();
 }

 name = "getSandboxOptions",
 global = true
 )
 static SandboxOptions getSandboxOptions() {
 return SandboxOptions.instance;
 }

 /**
 * Gets an output stream for a file in the Lua cache.
 * 
 * @param filename Path, relative to the Lua cache root, to write to. '..' is not allowed.
 * @return The output stream, or nullptr if the path was not valid.
 */
 name = "getFileOutput",
 global = true
 )
 static DataOutputStream getFileOutput(const std::string& filename) {
 if (StringUtils.containsDoubleDot(filename) {
 DebugLog.Lua.warn("relative paths not allowed");
 return nullptr;
 } else {
 std::string string0 = LuaManager.getLuaCacheDir() + File.separator + filename;
 string0 = string0.replace("/", File.separator);
 string0 = string0.replace("\\", File.separator);
 std::string string1 = string0.substring(0, string0.lastIndexOf(File.separator);
 string1 = string1.replace("\\", "/");
 File file0 = new File(string1);
 if (!file0.exists()) {
 file0.mkdirs();
 }

 File file1 = new File(string0);

 try {
 outStream = new FileOutputStream(file1);
 } catch (FileNotFoundException fileNotFoundException) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, fileNotFoundException);
 }

 return new DataOutputStream(outStream);
 }
 }

 name = "getLastStandPlayersDirectory",
 global = true
 )
 static std::string getLastStandPlayersDirectory() {
 return "LastStand";
 }

 name = "getLastStandPlayerFileNames",
 global = true
 )
 public static List<String> getLastStandPlayerFileNames() throws IOException {
 std::vector arrayList = new ArrayList();
 std::string string = LuaManager.getLuaCacheDir() + File.separator + getLastStandPlayersDirectory();
 string = string.replace("/", File.separator);
 string = string.replace("\\", File.separator);
 File file0 = new File(string);
 if (!file0.exists()) {
 file0.mkdir();
 }

 for (File file1 : file0.listFiles()) {
 if (!file1.isDirectory() && file1.getName().endsWith(".txt")) {
 arrayList.add(getLastStandPlayersDirectory() + File.separator + file1.getName());
 }
 }

 return arrayList;
 }

 name = "getAllSavedPlayers",
 global = true
 )
 public static List<BufferedReader> getAllSavedPlayers() throws IOException {
 std::vector arrayList = new ArrayList();
 std::string string = LuaManager.getLuaCacheDir() + File.separator + getLastStandPlayersDirectory();
 string = string.replace("/", File.separator);
 string = string.replace("\\", File.separator);
 File file0 = new File(string);
 if (!file0.exists()) {
 file0.mkdir();
 }

 for (File file1 : file0.listFiles()) {
 arrayList.add(new BufferedReader(new FileReader(file1);
 }

 return arrayList;
 }

 name = "getSandboxPresets",
 global = true
 )
 public static List<String> getSandboxPresets() throws IOException {
 std::vector arrayList = new ArrayList();
 std::string string = LuaManager.getSandboxCacheDir();
 File file0 = new File(string);
 if (!file0.exists()) {
 file0.mkdir();
 }

 for (File file1 : file0.listFiles()) {
 if (file1.getName().endsWith(".cfg")) {
 arrayList.add(file1.getName().replace(".cfg", ""));
 }
 }

 Collections.sort(arrayList);
 return arrayList;
 }

 name = "deleteSandboxPreset",
 global = true
 )
 static void deleteSandboxPreset(const std::string& name) {
 if (StringUtils.containsDoubleDot(name) {
 DebugLog.Lua.warn("relative paths not allowed");
 } else {
 std::string string = LuaManager.getSandboxCacheDir() + File.separator + name + ".cfg";
 File file = new File(string);
 if (file.exists()) {
 file.delete();
 }
 }
 }

 /**
 * Gets a file reader for a file in the Lua cache.
 * 
 * @param filename Path, relative to the Lua cache root, to read from. '..' is not allowed.
 * @param createIfNull Whether to create the file if it does not exist. The created file will be empty.
 * @return The file reader, or nullptr if the path was not valid.
 */
 name = "getFileReader",
 global = true
 )
 static BufferedReader getFileReader(const std::string& filename, bool createIfNull) {
 if (StringUtils.containsDoubleDot(filename) {
 DebugLog.Lua.warn("relative paths not allowed");
 return nullptr;
 } else {
 std::string string = LuaManager.getLuaCacheDir() + File.separator + filename;
 string = string.replace("/", File.separator);
 string = string.replace("\\", File.separator);
 File file = new File(string);
 if (!file.exists() && createIfNull) {
 file.createNewFile();
 }

 if (file.exists()) {
 BufferedReader bufferedReader = nullptr;

 try {
 FileInputStream fileInputStream = new FileInputStream(file);
 InputStreamReader inputStreamReader = new InputStreamReader(fileInputStream, StandardCharsets.UTF_8);
 bufferedReader = new BufferedReader(inputStreamReader);
 } catch (IOException iOException) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, iOException);
 }

 return bufferedReader;
 } else {
 return nullptr;
 }
 }
 }

 /**
 * Gets a file reader for a file in a mod's directory.
 * 
 * @param modId ID of the target mod. If nullptr, the path will be relative to the local mods directory.
 * @param filename Path, relative to the mod's common folder, to read from. '..' is not allowed.
 * @param createIfNull Whether to create the file if it does not exist. The created file will be empty.
 * @return The file reader, or nullptr if the path or mod was not valid.
 */
 name = "getModFileReader",
 global = true
 )
 static BufferedReader getModFileReader(const std::string& modId, const std::string& filename, bool createIfNull) {
 if (!filename.empty() && !StringUtils.containsDoubleDot(filename) && !new File(filename).isAbsolute()) {
 std::string string0 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "mods" + File.separator + filename;
 if (modId != nullptr) {
 ChooseGameInfo.Mod mod = ChooseGameInfo.getModDetails(modId);
 if (mod == nullptr) {
 return nullptr;
 }

 string0 = mod.getDir() + File.separator + filename;
 }

 string0 = string0.replace("/", File.separator);
 string0 = string0.replace("\\", File.separator);
 File file0 = new File(string0);
 if (!file0.exists() && createIfNull) {
 std::string string1 = string0.substring(0, string0.lastIndexOf(File.separator);
 File file1 = new File(string1);
 if (!file1.exists()) {
 file1.mkdirs();
 }

 file0.createNewFile();
 }

 if (file0.exists()) {
 BufferedReader bufferedReader = nullptr;

 try {
 FileInputStream fileInputStream = new FileInputStream(file0);
 InputStreamReader inputStreamReader = new InputStreamReader(fileInputStream, StandardCharsets.UTF_8);
 bufferedReader = new BufferedReader(inputStreamReader);
 } catch (IOException iOException) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, iOException);
 }

 return bufferedReader;
 } else {
 return nullptr;
 }
 } else {
 return nullptr;
 }
 }

 static void refreshAnimSets(bool reload) {
 try {
 if (reload) {
 AnimationSet.Reset();

 for (Asset asset : AnimNodeAssetManager.instance.getAssetTable().values()) {
 AnimNodeAssetManager.instance.reload(asset);
 }
 }

 AnimationSet.GetAnimationSet("player", true);
 AnimationSet.GetAnimationSet("player-vehicle", true);
 AnimationSet.GetAnimationSet("zombie", true);
 AnimationSet.GetAnimationSet("zombie-crawler", true);

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr) {
 player.advancedAnimator.OnAnimDataChanged(reload);
 }
 }

 for (IsoZombie zombie0 : IsoWorld.instance.CurrentCell.getZombieList()) {
 zombie0.advancedAnimator.OnAnimDataChanged(reload);
 }
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }

 static void reloadActionGroups() {
 try {
 ActionGroup.reloadAll();
 } catch (Exception exception) {
 }
 }

 /**
 * Gets a file writer for a file in a mod's directory. Note: it is generally unwise to write to a mod's lua or scripts directories, as this will change the checksum.
 * 
 * @param modId ID of the target mod. If nullptr, the path will be relative to the local mods directory.
 * @param filename Path, relative to the mod's common folder, to write to. '..' is not allowed.
 * @param createIfNull Whether to create the file if it does not exist. The created file will be empty.
 * @param append Whether to open the file in append mode. If true, the writer will write after the file's current contents. If false, the current contents of the file will be erased.
 * @return The file writer, or nullptr if the path or mod was not valid.
 */
 name = "getModFileWriter",
 global = true
 )
 public static LuaManager.GlobalObject.LuaFileWriter getModFileWriter(String modId, String filename, boolean createIfNull, boolean append) {
 if (!filename.empty() && !StringUtils.containsDoubleDot(filename) && !new File(filename).isAbsolute()) {
 ChooseGameInfo.Mod mod = ChooseGameInfo.getModDetails(modId);
 if (mod == nullptr) {
 return nullptr;
 } else {
 std::string string0 = mod.getDir() + File.separator + filename;
 string0 = string0.replace("/", File.separator);
 string0 = string0.replace("\\", File.separator);
 std::string string1 = string0.substring(0, string0.lastIndexOf(File.separator);
 File file0 = new File(string1);
 if (!file0.exists()) {
 file0.mkdirs();
 }

 File file1 = new File(string0);
 if (!file1.exists() && createIfNull) {
 try {
 file1.createNewFile();
 } catch (IOException iOException0) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, iOException0);
 }
 }

 PrintWriter printWriter = nullptr;

 try {
 FileOutputStream fileOutputStream = new FileOutputStream(file1, append);
 OutputStreamWriter outputStreamWriter = new OutputStreamWriter(fileOutputStream, StandardCharsets.UTF_8);
 printWriter = new PrintWriter(outputStreamWriter);
 } catch (IOException iOException1) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, iOException1);
 }

 return new LuaManager.GlobalObject.LuaFileWriter(printWriter);
 }
 } else {
 return nullptr;
 }
 }

 name = "updateFire",
 global = true
 )
 static void updateFire() {
 IsoFireManager.Update();
 }

 name = "deletePlayerSave",
 global = true
 )
 static void deletePlayerSave(const std::string& fileName) {
 std::string string = LuaManager.getLuaCacheDir() + File.separator + "Players" + File.separator + "player" + fileName + ".txt";
 string = string.replace("/", File.separator);
 string = string.replace("\\", File.separator);
 File file = new File(string);
 file.delete();
 }

 name = "getControllerCount",
 global = true
 )
 static int getControllerCount() {
 return GameWindow.GameInput.getControllerCount();
 }

 name = "isControllerConnected",
 global = true
 )
 static bool isControllerConnected(int index) {
 return index >= 0 && index <= GameWindow.GameInput.getControllerCount() ? GameWindow.GameInput.getController(index) != nullptr : false;
 }

 name = "getControllerGUID",
 global = true
 )
 static std::string getControllerGUID(int joypad) {
 if (joypad >= 0 && joypad < GameWindow.GameInput.getControllerCount()) {
 Controller controller = GameWindow.GameInput.getController(joypad);
 return controller != nullptr ? controller.getGUID() : "???";
 } else {
 return "???";
 }
 }

 name = "getControllerName",
 global = true
 )
 static std::string getControllerName(int joypad) {
 if (joypad >= 0 && joypad < GameWindow.GameInput.getControllerCount()) {
 Controller controller = GameWindow.GameInput.getController(joypad);
 return controller != nullptr ? controller.getGamepadName() : "???";
 } else {
 return "???";
 }
 }

 name = "getControllerAxisCount",
 global = true
 )
 static int getControllerAxisCount(int c) {
 if (c >= 0 && c < GameWindow.GameInput.getControllerCount()) {
 Controller controller = GameWindow.GameInput.getController(c);
 return controller = = nullptr ? 0 : controller.getAxisCount();
 } else {
 return 0;
 }
 }

 name = "getControllerAxisValue",
 global = true
 )
 static float getControllerAxisValue(int c, int axis) {
 if (c >= 0 && c < GameWindow.GameInput.getControllerCount()) {
 Controller controller = GameWindow.GameInput.getController(c);
 if (controller == nullptr) {
 return 0.0F;
 } else {
 return axis >= 0 && axis < controller.getAxisCount() ? controller.getAxisValue(axis) : 0.0F;
 }
 } else {
 return 0.0F;
 }
 }

 name = "getControllerDeadZone",
 global = true
 )
 static float getControllerDeadZone(int c, int axis) {
 if (c < 0 || c >= GameWindow.GameInput.getControllerCount()) {
 return 0.0F;
 } else {
 return axis >= 0 && axis < GameWindow.GameInput.getAxisCount(c) ? JoypadManager.instance.getDeadZone(c, axis) : 0.0F;
 }
 }

 name = "setControllerDeadZone",
 global = true
 )
 static void setControllerDeadZone(int c, int axis, float value) {
 if (c >= 0 && c < GameWindow.GameInput.getControllerCount()) {
 if (axis >= 0 && axis < GameWindow.GameInput.getAxisCount(c) {
 JoypadManager.instance.setDeadZone(c, axis, value);
 }
 }
 }

 name = "saveControllerSettings",
 global = true
 )
 static void saveControllerSettings(int c) {
 if (c >= 0 && c < GameWindow.GameInput.getControllerCount()) {
 JoypadManager.instance.saveControllerSettings(c);
 }
 }

 name = "getControllerButtonCount",
 global = true
 )
 static int getControllerButtonCount(int c) {
 if (c >= 0 && c < GameWindow.GameInput.getControllerCount()) {
 Controller controller = GameWindow.GameInput.getController(c);
 return controller = = nullptr ? 0 : controller.getButtonCount();
 } else {
 return 0;
 }
 }

 name = "getControllerPovX",
 global = true
 )
 static float getControllerPovX(int c) {
 if (c >= 0 && c < GameWindow.GameInput.getControllerCount()) {
 Controller controller = GameWindow.GameInput.getController(c);
 return controller = = nullptr ? 0.0F : controller.getPovX();
 } else {
 return 0.0F;
 }
 }

 name = "getControllerPovY",
 global = true
 )
 static float getControllerPovY(int c) {
 if (c >= 0 && c < GameWindow.GameInput.getControllerCount()) {
 Controller controller = GameWindow.GameInput.getController(c);
 return controller = = nullptr ? 0.0F : controller.getPovY();
 } else {
 return 0.0F;
 }
 }

 name = "reloadControllerConfigFiles",
 global = true
 )
 static void reloadControllerConfigFiles() {
 JoypadManager.instance.reloadControllerFiles();
 }

 name = "isJoypadPressed",
 global = true
 )
 static bool isJoypadPressed(int joypad, int button) {
 return GameWindow.GameInput.isButtonPressedD(button, joypad);
 }

 name = "isJoypadDown",
 global = true
 )
 static bool isJoypadDown(int joypad) {
 return JoypadManager.instance.isDownPressed(joypad);
 }

 name = "isJoypadLTPressed",
 global = true
 )
 static bool isJoypadLTPressed(int joypad) {
 return JoypadManager.instance.isLTPressed(joypad);
 }

 name = "isJoypadRTPressed",
 global = true
 )
 static bool isJoypadRTPressed(int joypad) {
 return JoypadManager.instance.isRTPressed(joypad);
 }

 name = "isJoypadLeftStickButtonPressed",
 global = true
 )
 static bool isJoypadLeftStickButtonPressed(int joypad) {
 return JoypadManager.instance.isL3Pressed(joypad);
 }

 name = "isJoypadRightStickButtonPressed",
 global = true
 )
 static bool isJoypadRightStickButtonPressed(int joypad) {
 return JoypadManager.instance.isR3Pressed(joypad);
 }

 name = "getJoypadAimingAxisX",
 global = true
 )
 static float getJoypadAimingAxisX(int joypad) {
 return JoypadManager.instance.getAimingAxisX(joypad);
 }

 name = "getJoypadAimingAxisY",
 global = true
 )
 static float getJoypadAimingAxisY(int joypad) {
 return JoypadManager.instance.getAimingAxisY(joypad);
 }

 name = "getJoypadMovementAxisX",
 global = true
 )
 static float getJoypadMovementAxisX(int joypad) {
 return JoypadManager.instance.getMovementAxisX(joypad);
 }

 name = "getJoypadMovementAxisY",
 global = true
 )
 static float getJoypadMovementAxisY(int joypad) {
 return JoypadManager.instance.getMovementAxisY(joypad);
 }

 name = "getJoypadAButton",
 global = true
 )
 static int getJoypadAButton(int joypad) {
 JoypadManager.Joypad _joypad = JoypadManager.instance.getFromControllerID(joypad);
 return _joypad != nullptr ? _joypad.getAButton() : -1;
 }

 name = "getJoypadBButton",
 global = true
 )
 static int getJoypadBButton(int joypad) {
 JoypadManager.Joypad _joypad = JoypadManager.instance.getFromControllerID(joypad);
 return _joypad != nullptr ? _joypad.getBButton() : -1;
 }

 name = "getJoypadXButton",
 global = true
 )
 static int getJoypadXButton(int joypad) {
 JoypadManager.Joypad _joypad = JoypadManager.instance.getFromControllerID(joypad);
 return _joypad != nullptr ? _joypad.getXButton() : -1;
 }

 name = "getJoypadYButton",
 global = true
 )
 static int getJoypadYButton(int joypad) {
 JoypadManager.Joypad _joypad = JoypadManager.instance.getFromControllerID(joypad);
 return _joypad != nullptr ? _joypad.getYButton() : -1;
 }

 name = "getJoypadLBumper",
 global = true
 )
 static int getJoypadLBumper(int joypad) {
 JoypadManager.Joypad _joypad = JoypadManager.instance.getFromControllerID(joypad);
 return _joypad != nullptr ? _joypad.getLBumper() : -1;
 }

 name = "getJoypadRBumper",
 global = true
 )
 static int getJoypadRBumper(int joypad) {
 JoypadManager.Joypad _joypad = JoypadManager.instance.getFromControllerID(joypad);
 return _joypad != nullptr ? _joypad.getRBumper() : -1;
 }

 name = "getJoypadBackButton",
 global = true
 )
 static int getJoypadBackButton(int joypad) {
 JoypadManager.Joypad _joypad = JoypadManager.instance.getFromControllerID(joypad);
 return _joypad != nullptr ? _joypad.getBackButton() : -1;
 }

 name = "getJoypadStartButton",
 global = true
 )
 static int getJoypadStartButton(int joypad) {
 JoypadManager.Joypad _joypad = JoypadManager.instance.getFromControllerID(joypad);
 return _joypad != nullptr ? _joypad.getStartButton() : -1;
 }

 name = "getJoypadLeftStickButton",
 global = true
 )
 static int getJoypadLeftStickButton(int joypad) {
 JoypadManager.Joypad _joypad = JoypadManager.instance.getFromControllerID(joypad);
 return _joypad != nullptr ? _joypad.getL3() : -1;
 }

 name = "getJoypadRightStickButton",
 global = true
 )
 static int getJoypadRightStickButton(int joypad) {
 JoypadManager.Joypad _joypad = JoypadManager.instance.getFromControllerID(joypad);
 return _joypad != nullptr ? _joypad.getR3() : -1;
 }

 name = "wasMouseActiveMoreRecentlyThanJoypad",
 global = true
 )
 static bool wasMouseActiveMoreRecentlyThanJoypad() {
 if (IsoPlayer.players[0] == nullptr) {
 JoypadManager.Joypad joypad = GameWindow.ActivatedJoyPad;
 return joypad != nullptr && !joypad.isDisabled() ? JoypadManager.instance.getLastActivity(joypad.getID()) < Mouse.lastActivity : true;
 } else {
 int int0 = IsoPlayer.players[0].getJoypadBind();
 return int0 = = -1 ? true : JoypadManager.instance.getLastActivity(int0) < Mouse.lastActivity;
 }
 }

 name = "activateJoypadOnSteamDeck",
 global = true
 )
 static void activateJoypadOnSteamDeck() {
 if (GameWindow.ActivatedJoyPad == nullptr) {
 JoypadManager.instance.isAPressed(0);
 if (JoypadManager.instance.JoypadList.empty()) {
 return;
 }

 JoypadManager.Joypad joypad = JoypadManager.instance.JoypadList.get(0);
 GameWindow.ActivatedJoyPad = joypad;
 }

 if (IsoPlayer.getInstance() != nullptr) {
 LuaEventManager.triggerEvent("OnJoypadActivate", GameWindow.ActivatedJoyPad.getID());
 } else {
 LuaEventManager.triggerEvent("OnJoypadActivateUI", GameWindow.ActivatedJoyPad.getID());
 }
 }

 name = "reactivateJoypadAfterResetLua",
 global = true
 )
 static bool reactivateJoypadAfterResetLua() {
 if (GameWindow.ActivatedJoyPad != nullptr) {
 LuaEventManager.triggerEvent("OnJoypadActivateUI", GameWindow.ActivatedJoyPad.getID());
 return true;
 } else {
 return false;
 }
 }

 name = "isJoypadConnected",
 global = true
 )
 static bool isJoypadConnected(int index) {
 return JoypadManager.instance.isJoypadConnected(index);
 }

 static void addPlayerToWorld(int int0, IsoPlayer player, bool boolean0) {
 if (IsoPlayer.players[int0] != nullptr) {
 IsoPlayer.players[int0].getEmitter().stopAll();
 IsoPlayer.players[int0].getEmitter().unregister();
 IsoPlayer.players[int0].updateUsername();
 IsoPlayer.players[int0].setSceneCulled(true);
 IsoPlayer.players[int0] = nullptr;
 }

 player.PlayerIndex = int0;
 if (GameClient.bClient && int0 != 0 && player.serverPlayerIndex != 1) {
 ClientPlayerDB.getInstance().forgetPlayer(player.serverPlayerIndex);
 }

 if (GameClient.bClient && int0 != 0 && player.serverPlayerIndex == 1) {
 player.serverPlayerIndex = ClientPlayerDB.getInstance().getNextServerPlayerIndex();
 }

 if (int0 == 0) {
 player.sqlID = 1;
 }

 if (boolean0) {
 player.applyTraits(IsoWorld.instance.getLuaTraits());
 player.createKeyRing();
 ProfessionFactory.Profession profession = ProfessionFactory.getProfession(player.getDescriptor().getProfession());
 if (profession != nullptr && !profession.getFreeRecipes().empty()) {
 for (String string0 : profession.getFreeRecipes()) {
 player.getKnownRecipes().add(string0);
 }
 }

 for (String string1 : IsoWorld.instance.getLuaTraits()) {
 TraitFactory.Trait trait = TraitFactory.getTrait(string1);
 if (trait != nullptr && !trait.getFreeRecipes().empty()) {
 for (String string2 : trait.getFreeRecipes()) {
 player.getKnownRecipes().add(string2);
 }
 }
 }

 player.setDir(IsoDirections.SE);
 LuaEventManager.triggerEvent("OnNewGame", player, player.getCurrentSquare());
 }

 IsoPlayer.numPlayers = Math.max(IsoPlayer.numPlayers, int0 + 1);
 IsoWorld.instance.AddCoopPlayers.add(new AddCoopPlayer(player);
 if (int0 == 0) {
 IsoPlayer.setInstance(player);
 }
 }

 name = "toInt",
 global = true
 )
 static int toInt(double val) {
 return (int)val;
 }

 name = "getClientUsername",
 global = true
 )
 static std::string getClientUsername() {
 return GameClient.bClient ? GameClient.username : nullptr;
 }

 name = "setPlayerJoypad",
 global = true
 )
 static void setPlayerJoypad(int player, int joypad, IsoPlayer playerObj, const std::string& username) {
 if (IsoPlayer.players[player] == nullptr || IsoPlayer.players[player].isDead()) {
 bool boolean0 = playerObj == nullptr;
 if (playerObj == nullptr) {
 IsoPlayer _player = IsoPlayer.getInstance();
 IsoWorld world = IsoWorld.instance;
 int int0 = world.getLuaPosX() + 300 * world.getLuaSpawnCellX();
 int int1 = world.getLuaPosY() + 300 * world.getLuaSpawnCellY();
 int int2 = world.getLuaPosZ();
 DebugLog.Lua.debugln("coop player spawning at " + int0 + "," + int1 + "," + int2);
 playerObj = new IsoPlayer(world.CurrentCell, world.getLuaPlayerDesc(), int0, int1, int2);
 IsoPlayer.setInstance(_player);
 world.CurrentCell.getAddList().remove(playerObj);
 world.CurrentCell.getObjectList().remove(playerObj);
 playerObj.SaveFileName = IsoPlayer.getUniqueFileName();
 }

 if (GameClient.bClient) {
 if (username != nullptr) {
 assert player != 0;

 playerObj.username = username;
 playerObj.getModData().rawset("username", username);
 } else {
 assert player = = 0;

 playerObj.username = GameClient.username;
 }
 }

 addPlayerToWorld(player, playerObj, boolean0);
 }

 playerObj.JoypadBind = joypad;
 JoypadManager.instance.assignJoypad(joypad, player);
 }

 name = "setPlayerMouse",
 global = true
 )
 static void setPlayerMouse(IsoPlayer playerObj) {
 uint8_t byte0 = 0;
 bool boolean0 = playerObj == nullptr;
 if (playerObj == nullptr) {
 IsoPlayer player = IsoPlayer.getInstance();
 IsoWorld world = IsoWorld.instance;
 int int0 = world.getLuaPosX() + 300 * world.getLuaSpawnCellX();
 int int1 = world.getLuaPosY() + 300 * world.getLuaSpawnCellY();
 int int2 = world.getLuaPosZ();
 DebugLog.Lua.debugln("coop player spawning at " + int0 + "," + int1 + "," + int2);
 playerObj = new IsoPlayer(world.CurrentCell, world.getLuaPlayerDesc(), int0, int1, int2);
 IsoPlayer.setInstance(player);
 world.CurrentCell.getAddList().remove(playerObj);
 world.CurrentCell.getObjectList().remove(playerObj);
 playerObj.SaveFileName = nullptr;
 }

 if (GameClient.bClient) {
 playerObj.username = GameClient.username;
 }

 addPlayerToWorld(byte0, playerObj, boolean0);
 }

 name = "revertToKeyboardAndMouse",
 global = true
 )
 static void revertToKeyboardAndMouse() {
 JoypadManager.instance.revertToKeyboardAndMouse();
 }

 name = "isJoypadUp",
 global = true
 )
 static bool isJoypadUp(int joypad) {
 return JoypadManager.instance.isUpPressed(joypad);
 }

 name = "isJoypadLeft",
 global = true
 )
 static bool isJoypadLeft(int joypad) {
 return JoypadManager.instance.isLeftPressed(joypad);
 }

 name = "isJoypadRight",
 global = true
 )
 static bool isJoypadRight(int joypad) {
 return JoypadManager.instance.isRightPressed(joypad);
 }

 name = "isJoypadLBPressed",
 global = true
 )
 static bool isJoypadLBPressed(int joypad) {
 return JoypadManager.instance.isLBPressed(joypad);
 }

 name = "isJoypadRBPressed",
 global = true
 )
 static bool isJoypadRBPressed(int joypad) {
 return JoypadManager.instance.isRBPressed(joypad);
 }

 name = "getButtonCount",
 global = true
 )
 static int getButtonCount(int joypad) {
 if (joypad >= 0 && joypad < GameWindow.GameInput.getControllerCount()) {
 Controller controller = GameWindow.GameInput.getController(joypad);
 return controller = = nullptr ? 0 : controller.getButtonCount();
 } else {
 return 0;
 }
 }

 name = "setDebugToggleControllerPluggedIn",
 global = true
 )
 static void setDebugToggleControllerPluggedIn(int index) {
 Controllers.setDebugToggleControllerPluggedIn(index);
 }

 /**
 * Gets a file writer for a file in the Lua cache.
 * 
 * @param filename Path, relative to the Lua cache root, to write to. '..' is not allowed.
 * @param createIfNull Whether to create the file if it does not exist.
 * @param append Whether to open the file in append mode. If true, the writer will write after the file's current contents. If false, the current contents of the file will be erased.
 * @return The file writer, or nullptr if the path was not valid.
 */
 name = "getFileWriter",
 global = true
 )
 public static LuaManager.GlobalObject.LuaFileWriter getFileWriter(String filename, boolean createIfNull, boolean append) {
 if (StringUtils.containsDoubleDot(filename) {
 DebugLog.Lua.warn("relative paths not allowed");
 return nullptr;
 } else {
 std::string string0 = LuaManager.getLuaCacheDir() + File.separator + filename;
 string0 = string0.replace("/", File.separator);
 string0 = string0.replace("\\", File.separator);
 std::string string1 = string0.substring(0, string0.lastIndexOf(File.separator);
 string1 = string1.replace("\\", "/");
 File file0 = new File(string1);
 if (!file0.exists()) {
 file0.mkdirs();
 }

 File file1 = new File(string0);
 if (!file1.exists() && createIfNull) {
 try {
 file1.createNewFile();
 } catch (IOException iOException0) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, iOException0);
 }
 }

 PrintWriter printWriter = nullptr;

 try {
 FileOutputStream fileOutputStream = new FileOutputStream(file1, append);
 OutputStreamWriter outputStreamWriter = new OutputStreamWriter(fileOutputStream, StandardCharsets.UTF_8);
 printWriter = new PrintWriter(outputStreamWriter);
 } catch (IOException iOException1) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, iOException1);
 }

 return new LuaManager.GlobalObject.LuaFileWriter(printWriter);
 }
 }

 name = "getSandboxFileWriter",
 global = true
 )
 public static LuaManager.GlobalObject.LuaFileWriter getSandboxFileWriter(String filename, boolean createIfNull, boolean append) {
 if (StringUtils.containsDoubleDot(filename) {
 DebugLog.Lua.warn("relative paths not allowed");
 return nullptr;
 } else {
 std::string string0 = LuaManager.getSandboxCacheDir() + File.separator + filename;
 string0 = string0.replace("/", File.separator);
 string0 = string0.replace("\\", File.separator);
 std::string string1 = string0.substring(0, string0.lastIndexOf(File.separator);
 string1 = string1.replace("\\", "/");
 File file0 = new File(string1);
 if (!file0.exists()) {
 file0.mkdirs();
 }

 File file1 = new File(string0);
 if (!file1.exists() && createIfNull) {
 try {
 file1.createNewFile();
 } catch (IOException iOException0) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, iOException0);
 }
 }

 PrintWriter printWriter = nullptr;

 try {
 FileOutputStream fileOutputStream = new FileOutputStream(file1, append);
 OutputStreamWriter outputStreamWriter = new OutputStreamWriter(fileOutputStream, StandardCharsets.UTF_8);
 printWriter = new PrintWriter(outputStreamWriter);
 } catch (IOException iOException1) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, iOException1);
 }

 return new LuaManager.GlobalObject.LuaFileWriter(printWriter);
 }
 }

 name = "createStory",
 global = true
 )
 static void createStory(const std::string& storyName) {
 Core.GameMode = storyName;
 std::string string = ZomboidFileSystem.instance.getGameModeCacheDir();
 string = string.replace("/", File.separator);
 string = string.replace("\\", File.separator);
 int int0 = 1;
 void* object = nullptr;
 bool boolean0 = false;

 while (!boolean0) {
 object = new File(string + File.separator + "Game" + int0);
 if (!object.exists()) {
 boolean0 = true;
 } else {
 int0++;
 }
 }

 Core.GameSaveWorld = "newstory";
 }

 name = "createWorld",
 global = true
 )
 static void createWorld(const std::string& worldName) {
 if (worldName == nullptr || worldName.empty()) {
 worldName = "blah";
 }

 worldName = sanitizeWorldName(worldName);
 std::string string0 = ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + worldName + File.separator;
 string0 = string0.replace("/", File.separator);
 string0 = string0.replace("\\", File.separator);
 std::string string1 = string0.substring(0, string0.lastIndexOf(File.separator);
 string1 = string1.replace("\\", "/");
 File file = new File(string1);
 if (!file.exists() && !Core.getInstance().isNoSave()) {
 file.mkdirs();
 }

 Core.GameSaveWorld = worldName;
 }

 name = "sanitizeWorldName",
 global = true
 )
 static std::string sanitizeWorldName(const std::string& worldName) {
 return worldName.replace(" ", "_")
 .replace("/", "")
 .replace("\\", "")
 .replace("?", "")
 .replace("*", "")
 .replace("<", "")
 .replace(">", "")
 .replace(":", "")
 .replace("|", "")
 .trim();
 }

 name = "forceChangeState",
 global = true
 )
 static void forceChangeState(GameState state) {
 GameWindow.states.forceNextState(state);
 }

 name = "endFileOutput",
 global = true
 )
 static void endFileOutput() {
 if (outStream != nullptr) {
 try {
 outStream.close();
 } catch (IOException iOException) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, iOException);
 }
 }

 outStream = nullptr;
 }

 /**
 * Gets an input stream for a file in the Lua cache.
 * 
 * @param filename Path, relative to the Lua cache root, to write to. '..' is not allowed.
 * @return The input stream, or nullptr if the path was not valid.
 */
 name = "getFileInput",
 global = true
 )
 static DataInputStream getFileInput(const std::string& filename) {
 if (StringUtils.containsDoubleDot(filename) {
 DebugLog.Lua.warn("relative paths not allowed");
 return nullptr;
 } else {
 std::string string = LuaManager.getLuaCacheDir() + File.separator + filename;
 string = string.replace("/", File.separator);
 string = string.replace("\\", File.separator);
 File file = new File(string);
 if (file.exists()) {
 try {
 inStream = new FileInputStream(file);
 } catch (FileNotFoundException fileNotFoundException) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, fileNotFoundException);
 }

 return new DataInputStream(inStream);
 } else {
 return nullptr;
 }
 }
 }

 name = "getGameFilesInput",
 global = true
 )
 static DataInputStream getGameFilesInput(const std::string& filename) {
 std::string string = filename.replace("/", File.separator);
 string = string.replace("\\", File.separator);
 if (!ZomboidFileSystem.instance.isKnownFile(string) {
 return nullptr;
 } else {
 File file = new File(ZomboidFileSystem.instance.getString(string);
 if (file.exists()) {
 try {
 inStream = new FileInputStream(file);
 } catch (FileNotFoundException fileNotFoundException) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, fileNotFoundException);
 }

 return new DataInputStream(inStream);
 } else {
 return nullptr;
 }
 }
 }

 name = "getGameFilesTextInput",
 global = true
 )
 static BufferedReader getGameFilesTextInput(const std::string& filename) {
 if (!Core.getInstance().getDebug()) {
 return nullptr;
 } else {
 std::string string = filename.replace("/", File.separator);
 string = string.replace("\\", File.separator);
 if (!ZomboidFileSystem.instance.isKnownFile(string) {
 return nullptr;
 } else {
 File file = new File(ZomboidFileSystem.instance.getString(string);
 if (file.exists()) {
 try {
 inFileReader = new FileReader(filename);
 inBufferedReader = new BufferedReader(inFileReader);
 return inBufferedReader;
 } catch (FileNotFoundException fileNotFoundException) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, fileNotFoundException);
 }
 }

 return nullptr;
 }
 }
 }

 name = "endTextFileInput",
 global = true
 )
 static void endTextFileInput() {
 if (inBufferedReader != nullptr) {
 try {
 inBufferedReader.close();
 inFileReader.close();
 } catch (IOException iOException) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, iOException);
 }
 }

 inBufferedReader = nullptr;
 inFileReader = nullptr;
 }

 name = "endFileInput",
 global = true
 )
 static void endFileInput() {
 if (inStream != nullptr) {
 try {
 inStream.close();
 } catch (IOException iOException) {
 Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, nullptr, iOException);
 }
 }

 inStream = nullptr;
 }

 name = "getLineNumber",
 global = true
 )
 static int getLineNumber(LuaCallFrame c) {
 if (c.closure == nullptr) {
 return 0;
 } else {
 int int0 = c.pc;
 if (int0 < 0) {
 int0 = 0;
 }

 if (int0 >= c.closure.prototype.lines.length) {
 int0 = c.closure.prototype.lines.length - 1;
 }

 return c.closure.prototype.lines[int0];
 }
 }

 /**
 * Returns a pseudorandom integer between 0 and max - 1.
 * 
 * @param max Exclusive upper bound of the integer value.
 * @return The random integer.
 */
 name = "ZombRand",
 global = true
 )
 static double ZombRand(double max) {
 if (max == 0.0) {
 return 0.0;
 } else {
 return max < 0.0 ? -Rand.Next(-((long)max), Rand.randlua) : Rand.Next((long)max, Rand.randlua);
 }
 }

 /**
 * Returns a pseudorandom integer between min and max - 1. No difference from ZombRand(min, max).
 * 
 * @param min The inclusive lower bound of the random integer.
 * @param max The exclusive upper bound of the random integer.
 * @return The random integer.
 */
 name = "ZombRandBetween",
 global = true
 )
 static double ZombRandBetween(double min, double max) {
 return Rand.Next((long)min, (long)max, Rand.randlua);
 }

 /**
 * Returns a pseudorandom integer between min and max - 1.
 * 
 * @param min The inclusive lower bound of the random integer.
 * @param max The exclusive upper bound of the random integer.
 * @return The random integer.
 */
 name = "ZombRand",
 global = true
 )
 static double ZombRand(double min, double max) {
 return Rand.Next((int)min, (int)max, Rand.randlua);
 }

 /**
 * Returns a pseudorandom float between min and max.
 * 
 * @param min The lower bound of the random float.
 * @param max The upper bound of the random float.
 * @return The random float.
 */
 name = "ZombRandFloat",
 global = true
 )
 static float ZombRandFloat(float min, float max) {
 return Rand.Next(min, max, Rand.randlua);
 }

 name = "getShortenedFilename",
 global = true
 )
 static std::string getShortenedFilename(const std::string& str) {
 return str.substring(str.indexOf("lua/") + 4);
 }

 name = "isKeyDown",
 global = true
 )
 static bool isKeyDown(int key) {
 return GameKeyboard.isKeyDown(key);
 }

 name = "wasKeyDown",
 global = true
 )
 static bool wasKeyDown(int key) {
 return GameKeyboard.wasKeyDown(key);
 }

 name = "isKeyPressed",
 global = true
 )
 static bool isKeyPressed(int key) {
 return GameKeyboard.isKeyPressed(key);
 }

 name = "getFMODSoundBank",
 global = true
 )
 static BaseSoundBank getFMODSoundBank() {
 return BaseSoundBank.instance;
 }

 name = "isSoundPlaying",
 global = true
 )
 static bool isSoundPlaying(void* sound) {
 return sound instanceof Double ? FMODManager.instance.isPlaying(((Double)sound).longValue()) : false;
 }

 name = "stopSound",
 global = true
 )
 static void stopSound(long sound) {
 FMODManager.instance.stopSound(sound);
 }

 name = "isShiftKeyDown",
 global = true
 )
 static bool isShiftKeyDown() {
 return GameKeyboard.isKeyDown(42) || GameKeyboard.isKeyDown(54);
 }

 name = "isCtrlKeyDown",
 global = true
 )
 static bool isCtrlKeyDown() {
 return GameKeyboard.isKeyDown(29) || GameKeyboard.isKeyDown(157);
 }

 name = "isAltKeyDown",
 global = true
 )
 static bool isAltKeyDown() {
 return GameKeyboard.isKeyDown(56) || GameKeyboard.isKeyDown(184);
 }

 name = "getCore",
 global = true
 )
 static Core getCore() {
 return Core.getInstance();
 }

 name = "getGameVersion",
 global = true
 )
 static std::string getGameVersion() {
 return Core.getInstance().getGameVersion().toString();
 }

 name = "getSquare",
 global = true
 )
 static IsoGridSquare getSquare(double x, double y, double z) {
 return IsoCell.getInstance().getGridSquare(x, y, z);
 }

 name = "getDebugOptions",
 global = true
 )
 static DebugOptions getDebugOptions() {
 return DebugOptions.instance;
 }

 name = "setShowPausedMessage",
 global = true
 )
 static void setShowPausedMessage(bool b) {
 DebugLog.log("EXITDEBUG: setShowPausedMessage 1");
 UIManager.setShowPausedMessage(b);
 DebugLog.log("EXITDEBUG: setShowPausedMessage 2");
 }

 name = "getFilenameOfCallframe",
 global = true
 )
 static std::string getFilenameOfCallframe(LuaCallFrame c) {
 return c.closure == nullptr ? nullptr : c.closure.prototype.filename;
 }

 name = "getFilenameOfClosure",
 global = true
 )
 static std::string getFilenameOfClosure(LuaClosure c) {
 return c = = nullptr ? nullptr : c.prototype.filename;
 }

 name = "getFirstLineOfClosure",
 global = true
 )
 static int getFirstLineOfClosure(LuaClosure c) {
 return c = = nullptr ? 0 : c.prototype.lines[0];
 }

 name = "getLocalVarCount",
 global = true
 )
 static int getLocalVarCount(Coroutine c) {
 LuaCallFrame luaCallFrame = c.currentCallFrame();
 return luaCallFrame = = nullptr ? 0 : luaCallFrame.LocalVarNames.size();
 }

 name = "isSystemLinux",
 global = true
 )
 static bool isSystemLinux() {
 return !isSystemMacOS() && !isSystemWindows();
 }

 name = "isSystemMacOS",
 global = true
 )
 static bool isSystemMacOS() {
 return System.getProperty("os.name").contains("OS X");
 }

 name = "isSystemWindows",
 global = true
 )
 static bool isSystemWindows() {
 return System.getProperty("os.name").startsWith("Win");
 }

 name = "isModActive",
 global = true
 )
 static bool isModActive(ChooseGameInfo.Mod mod) {
 std::string string = mod.getDir();
 if (!StringUtils.isNullOrWhitespace(mod.getId())) {
 string = mod.getId();
 }

 return ZomboidFileSystem.instance.getModIDs().contains(string);
 }

 name = "openUrl",
 global = true
 )
 static void openURl(const std::string& url) {
 Desktop desktop = Desktop.isDesktopSupported() ? Desktop.getDesktop() : nullptr;
 if (desktop != nullptr && desktop.isSupported(Action.BROWSE) {
 try {
 URI uri = new URI(url);
 desktop.browse(uri);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 } else {
 DesktopBrowser.openURL(url);
 }
 }

 name = "isDesktopOpenSupported",
 global = true
 )
 static bool isDesktopOpenSupported() {
 return !Desktop.isDesktopSupported() ? false : Desktop.getDesktop().isSupported(Action.OPEN);
 }

 name = "showFolderInDesktop",
 global = true
 )
 static void showFolderInDesktop(const std::string& folder) {
 File file = new File(folder);
 if (file.exists() && file.isDirectory()) {
 Desktop desktop = Desktop.isDesktopSupported() ? Desktop.getDesktop() : nullptr;
 if (desktop != nullptr && desktop.isSupported(Action.OPEN) {
 try {
 desktop.open(file);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }
 }
 }

 /**
 * Gets the list of currently activated mods. Remember that in B42+, mod ids are prefixed with a \ character.
 */
 name = "getActivatedMods",
 global = true
 )
 public static ArrayList<String> getActivatedMods() {
 return ZomboidFileSystem.instance.getModIDs();
 }

 name = "toggleModActive",
 global = true
 )
 static void toggleModActive(ChooseGameInfo.Mod mod, bool active) {
 std::string string = mod.getDir();
 if (!StringUtils.isNullOrWhitespace(mod.getId())) {
 string = mod.getId();
 }

 ActiveMods.getById("default").setModActive(string, active);
 }

 name = "saveModsFile",
 global = true
 )
 static void saveModsFile() {
 ZomboidFileSystem.instance.saveModsFile();
 }

 static void deleteSavefileFilesMatching(File file, const std::string& string) {
 Filter filter = pathx -> pathx.getFileName().toString().matches(string);

 try (DirectoryStream directoryStream = Files.newDirectoryStream(file.toPath(), filter) {
 for (auto& path : directoryStream) System.out.println("DELETE " + path);
 Files.deleteIfExists(path);
 }
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }

 name = "manipulateSavefile",
 global = true
 )
 static void manipulateSavefile(const std::string& folder, const std::string& action) {
 if (!StringUtils.isNullOrWhitespace(folder) {
 if (!StringUtils.containsDoubleDot(folder) {
 std::string string = ZomboidFileSystem.instance.getSaveDir() + File.separator + folder;
 File file = new File(string);
 if (file.exists() && file.isDirectory()) {
 switch (action) {
 case "DeleteChunkDataXYBin":
 deleteSavefileFilesMatching(file, "chunkdata_[0-9]+_[0-9]+\\.bin");
 break;
 case "DeleteMapXYBin":
 deleteSavefileFilesMatching(file, "map_[0-9]+_[0-9]+\\.bin");
 break;
 case "DeleteMapMetaBin":
 deleteSavefileFilesMatching(file, "map_meta\\.bin");
 break;
 case "DeleteMapTBin":
 deleteSavefileFilesMatching(file, "map_t\\.bin");
 break;
 case "DeleteMapZoneBin":
 deleteSavefileFilesMatching(file, "map_zone\\.bin");
 break;
 case "DeletePlayersDB":
 deleteSavefileFilesMatching(file, "players\\.db");
 break;
 case "DeleteReanimatedBin":
 deleteSavefileFilesMatching(file, "reanimated\\.bin");
 break;
 case "DeleteVehiclesDB":
 deleteSavefileFilesMatching(file, "vehicles\\.db");
 break;
 case "DeleteZOutfitsBin":
 deleteSavefileFilesMatching(file, "z_outfits\\.bin");
 break;
 case "DeleteZPopVirtualBin":
 deleteSavefileFilesMatching(file, "zpop_virtual\\.bin");
 break;
 case "DeleteZPopXYBin":
 deleteSavefileFilesMatching(file, "zpop_[0-9]+_[0-9]+\\.bin");
 break;
 case "WriteModsDotTxt":
 ActiveMods activeMods = ActiveMods.getById("currentGame");
 ActiveModsFile activeModsFile = new ActiveModsFile();
 activeModsFile.write(string + File.separator + "mods.txt", activeMods);
 break;
 default:
 throw IllegalArgumentException("unknown action \"" + action + "\"");
 }
 }
 }
 }
 }

 name = "getLocalVarName",
 global = true
 )
 static std::string getLocalVarName(Coroutine c, int n) {
 LuaCallFrame luaCallFrame = c.currentCallFrame();
 return luaCallFrame.LocalVarNames.get(n);
 }

 name = "getLocalVarStack",
 global = true
 )
 static int getLocalVarStack(Coroutine c, int n) {
 LuaCallFrame luaCallFrame = c.currentCallFrame();
 return (Integer)luaCallFrame.LocalVarToStackMap.get(luaCallFrame.LocalVarNames.get(n);
 }

 name = "getCallframeTop",
 global = true
 )
 static int getCallframeTop(Coroutine c) {
 return c.getCallframeTop();
 }

 name = "getCoroutineTop",
 global = true
 )
 static int getCoroutineTop(Coroutine c) {
 return c.getTop();
 }

 name = "getCoroutineObjStack",
 global = true
 )
 static void* getCoroutineObjStack(Coroutine c, int n) {
 return c.getObjectFromStack(n);
 }

 name = "getCoroutineObjStackWithBase",
 global = true
 )
 static void* getCoroutineObjStackWithBase(Coroutine c, int n) {
 return c.getObjectFromStack(n - c.currentCallFrame().localBase);
 }

 name = "localVarName",
 global = true
 )
 static std::string localVarName(Coroutine c, int n) {
 int int0 = c.getCallframeTop() - 1;
 if (int0 < 0) {
 bool boolean0 = false;
 }

 return "";
 }

 name = "getCoroutineCallframeStack",
 global = true
 )
 static LuaCallFrame getCoroutineCallframeStack(Coroutine c, int n) {
 return c.getCallFrame(n);
 }

 name = "createTile",
 global = true
 )
 static void createTile(const std::string& tile, IsoGridSquare square) {
 synchronized (IsoSpriteManager.instance.NamedMap) {
 IsoSprite sprite = IsoSpriteManager.instance.NamedMap.get(tile);
 if (sprite != nullptr) {
 int int0 = 0;
 int int1 = 0;
 int int2 = 0;
 if (square != nullptr) {
 int0 = square.getX();
 int1 = square.getY();
 int2 = square.getZ();
 }

 CellLoader.DoTileObjectCreation(sprite, sprite.getType(), square, IsoWorld.instance.CurrentCell, int0, int1, int2, tile);
 }
 }
 }

 name = "getNumClassFunctions",
 global = true
 )
 static int getNumClassFunctions(void* o) {
 return o.getClass().getDeclaredMethods().length;
 }

 name = "getClassFunction",
 global = true
 )
 static Method getClassFunction(void* o, int i) {
 return o.getClass().getDeclaredMethods()[i];
 }

 name = "getNumClassFields",
 global = true
 )
 static int getNumClassFields(void* o) {
 return o.getClass().getDeclaredFields().length;
 }

 name = "getClassField",
 global = true
 )
 static Field getClassField(void* o, int i) {
 Field field = o.getClass().getDeclaredFields()[i];
 field.setAccessible(true);
 return field;
 }

 name = "getDirectionTo",
 global = true
 )
 static IsoDirections getDirectionTo(IsoGameCharacter chara, IsoObject objTarget) {
 Vector2 vector = new Vector2(objTarget.getX(), objTarget.getY());
 vector.x = vector.x - chara.x;
 vector.y = vector.y - chara.y;
 return IsoDirections.fromAngle(vector);
 }

 name = "translatePointXInOverheadMapToWindow",
 global = true
 )
 static float translatePointXInOverheadMapToWindow(float x, UIElement ui, float zoom, float xpos) {
 IngameState.draww = ui.getWidth().intValue();
 return IngameState.translatePointX(x, xpos, zoom, 0.0F);
 }

 name = "translatePointYInOverheadMapToWindow",
 global = true
 )
 static float translatePointYInOverheadMapToWindow(float y, UIElement ui, float zoom, float ypos) {
 IngameState.drawh = ui.getHeight().intValue();
 return IngameState.translatePointY(y, ypos, zoom, 0.0F);
 }

 name = "translatePointXInOverheadMapToWorld",
 global = true
 )
 static float translatePointXInOverheadMapToWorld(float x, UIElement ui, float zoom, float xpos) {
 IngameState.draww = ui.getWidth().intValue();
 return IngameState.invTranslatePointX(x, xpos, zoom, 0.0F);
 }

 name = "translatePointYInOverheadMapToWorld",
 global = true
 )
 static float translatePointYInOverheadMapToWorld(float y, UIElement ui, float zoom, float ypos) {
 IngameState.drawh = ui.getHeight().intValue();
 return IngameState.invTranslatePointY(y, ypos, zoom, 0.0F);
 }

 name = "drawOverheadMap",
 global = true
 )
 static void drawOverheadMap(UIElement ui, float zoom, float xpos, float ypos) {
 IngameState.renderDebugOverhead2(
 getCell(), 0, zoom, ui.getAbsoluteX().intValue(), ui.getAbsoluteY().intValue(), xpos, ypos, ui.getWidth().intValue(), ui.getHeight().intValue()
 );
 }

 name = "assaultPlayer",
 global = true
 )
 static void assaultPlayer() {
 assert false;
 }

 name = "isoRegionsRenderer",
 global = true
 )
 static IsoRegionsRenderer isoRegionsRenderer() {
 return std::make_unique<IsoRegionsRenderer>();
 }

 name = "zpopNewRenderer",
 global = true
 )
 static ZombiePopulationRenderer zpopNewRenderer() {
 return std::make_unique<ZombiePopulationRenderer>();
 }

 name = "zpopSpawnTimeToZero",
 global = true
 )
 static void zpopSpawnTimeToZero(int cellX, int cellY) {
 ZombiePopulationManager.instance.dbgSpawnTimeToZero(cellX, cellY);
 }

 name = "zpopClearZombies",
 global = true
 )
 static void zpopClearZombies(int cellX, int cellY) {
 ZombiePopulationManager.instance.dbgClearZombies(cellX, cellY);
 }

 name = "zpopSpawnNow",
 global = true
 )
 static void zpopSpawnNow(int cellX, int cellY) {
 ZombiePopulationManager.instance.dbgSpawnNow(cellX, cellY);
 }

 name = "addVirtualZombie",
 global = true
 )
 static void addVirtualZombie(int x, int y) {
 }

 name = "luaDebug",
 global = true
 )
 static void luaDebug() {
 try {
 throw Exception("LuaDebug");
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 name = "setAggroTarget",
 global = true
 )
 static void setAggroTarget(int id, int x, int y) {
 ZombiePopulationManager.instance.setAggroTarget(id, x, y);
 }

 name = "debugFullyStreamedIn",
 global = true
 )
 static void debugFullyStreamedIn(int x, int y) {
 IngameState.instance.debugFullyStreamedIn(x, y);
 }

 name = "getClassFieldVal",
 global = true
 )
 static void* getClassFieldVal(void* o, Field field) {
 try {
 return field.get(o);
 } catch (Exception exception) {
 return "<private>";
 }
 }

 name = "getMethodParameter",
 global = true
 )
 static std::string getMethodParameter(Method o, int i) {
 return o.getParameterTypes()[i].getSimpleName();
 }

 name = "getMethodParameterCount",
 global = true
 )
 static int getMethodParameterCount(Method o) {
 return o.getParameterTypes().length;
 }

 name = "breakpoint",
 global = true
 )
 static void breakpoint() {
 bool boolean0 = false;
 }

 name = "getLuaDebuggerErrorCount",
 global = true
 )
 static int getLuaDebuggerErrorCount() {
 return KahluaThread.m_error_count;
 }

 name = "getLuaDebuggerErrors",
 global = true
 )
 public static ArrayList<String> getLuaDebuggerErrors() {
 return new ArrayList<>(KahluaThread.m_errors_list);
 }

 name = "doLuaDebuggerAction",
 global = true
 )
 static void doLuaDebuggerAction(const std::string& action) {
 UIManager.luaDebuggerAction = action;
 }

 name = "getGameSpeed",
 global = true
 )
 static int getGameSpeed() {
 return UIManager.getSpeedControls() != nullptr ? UIManager.getSpeedControls().getCurrentGameSpeed() : 0;
 }

 name = "setGameSpeed",
 global = true
 )
 static void setGameSpeed(int NewSpeed) {
 DebugLog.log("EXITDEBUG: setGameSpeed 1");
 if (UIManager.getSpeedControls() == nullptr) {
 DebugLog.log("EXITDEBUG: setGameSpeed 2");
 } else {
 UIManager.getSpeedControls().SetCurrentGameSpeed(NewSpeed);
 DebugLog.log("EXITDEBUG: setGameSpeed 3");
 }
 }

 name = "isGamePaused",
 global = true
 )
 static bool isGamePaused() {
 return GameTime.isGamePaused();
 }

 name = "getMouseXScaled",
 global = true
 )
 static int getMouseXScaled() {
 return Mouse.getX();
 }

 name = "getMouseYScaled",
 global = true
 )
 static int getMouseYScaled() {
 return Mouse.getY();
 }

 name = "getMouseX",
 global = true
 )
 static int getMouseX() {
 return Mouse.getXA();
 }

 name = "setMouseXY",
 global = true
 )
 static void setMouseXY(int x, int y) {
 Mouse.setXY(x, y);
 }

 name = "isMouseButtonDown",
 global = true
 )
 static bool isMouseButtonDown(int number) {
 return Mouse.isButtonDown(number);
 }

 name = "getMouseY",
 global = true
 )
 static int getMouseY() {
 return Mouse.getYA();
 }

 name = "getSoundManager",
 global = true
 )
 static BaseSoundManager getSoundManager() {
 return SoundManager.instance;
 }

 name = "getLastPlayedDate",
 global = true
 )
 static std::string getLastPlayedDate(const std::string& filename) {
 File file = new File(ZomboidFileSystem.instance.getSaveDir() + File.separator + filename);
 if (!file.exists()) {
 return Translator.getText("UI_LastPlayed") + "???";
 } else {
 Date date = new Date(file.lastModified());
 SimpleDateFormat simpleDateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm");
 std::string string = simpleDateFormat.format(date);
 return Translator.getText("UI_LastPlayed") + string;
 }
 }

 name = "getTextureFromSaveDir",
 global = true
 )
 static Texture getTextureFromSaveDir(const std::string& filename, const std::string& saveName) {
 TextureID.UseFiltering = true;
 std::string string = ZomboidFileSystem.instance.getSaveDir() + File.separator + saveName + File.separator + filename;
 Texture texture = Texture.getSharedTexture(string);
 TextureID.UseFiltering = false;
 return texture;
 }

 name = "getSaveInfo",
 global = true
 )
 static KahluaTable getSaveInfo(const std::string& saveDir) {
 if (!saveDir.contains(File.separator) {
 saveDir = IsoWorld.instance.getGameMode() + File.separator + saveDir;
 }

 KahluaTable table0 = LuaManager.platform.newTable();
 File file = new File(ZomboidFileSystem.instance.getSaveDir() + File.separator + saveDir);
 if (file.exists()) {
 Date date = new Date(file.lastModified());
 SimpleDateFormat simpleDateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm");
 std::string string0 = simpleDateFormat.format(date);
 table0.rawset("lastPlayed", string0);
 String[] strings = saveDir.split("\\" + File.separator);
 table0.rawset("saveName", file.getName());
 table0.rawset("gameMode", strings[strings.length - 2]);
 }

 file = new File(ZomboidFileSystem.instance.getSaveDir() + File.separator + saveDir + File.separator + "map_ver.bin");
 if (file.exists()) {
 try (
 FileInputStream fileInputStream = new FileInputStream(file);
 DataInputStream dataInputStream = new DataInputStream(fileInputStream);
 ) {
 int int0 = dataInputStream.readInt();
 table0.rawset("worldVersion", (double)int0);
 if (int0 >= 18) {
 try {
 std::string string1 = GameWindow.ReadString(dataInputStream);
 if (string1 == "DEFAULT")) {
 string1 = "Muldraugh, KY";
 }

 table0.rawset("mapName", string1);
 } catch (Exception exception0) {
 }
 }

 if (int0 >= 74) {
 try {
 std::string string2 = GameWindow.ReadString(dataInputStream);
 table0.rawset("difficulty", string2);
 } catch (Exception exception1) {
 }
 }
 } catch (Exception exception2) {
 ExceptionLogger.logException(exception2);
 }
 }

 std::string string3 = ZomboidFileSystem.instance.getSaveDir() + File.separator + saveDir + File.separator + "mods.txt";
 ActiveMods activeMods = new ActiveMods(saveDir);
 ActiveModsFile activeModsFile = new ActiveModsFile();
 if (activeModsFile.read(string3, activeMods) {
 table0.rawset("activeMods", activeMods);
 }

 std::string string4 = ZomboidFileSystem.instance.getSaveDir() + File.separator + saveDir;
 table0.rawset("playerAlive", PlayerDBHelper.isPlayerAlive(string4, 1);
 KahluaTable table1 = LuaManager.platform.newTable();

 try {
 std::vector arrayList = PlayerDBHelper.getPlayers(string4);

 for (byte byte0 = 0; byte0 < arrayList.size(); byte0 += 3) {
 double double0 = (Double)arrayList.get(byte0);
 std::string string5 = (String)arrayList.get(byte0 + 1);
 bool boolean0 = (Boolean)arrayList.get(byte0 + 2);
 KahluaTable table2 = LuaManager.platform.newTable();
 table2.rawset("sqlID", double0);
 table2.rawset("name", string5);
 table2.rawset("isDead", boolean0);
 table1.rawset(byte0 / 3 + 1, table2);
 }
 } catch (Exception exception3) {
 ExceptionLogger.logException(exception3);
 }

 table0.rawset("players", table1);
 return table0;
 }

 name = "renameSavefile",
 global = true
 )
 static bool renameSaveFile(const std::string& gameMode, const std::string& oldName, const std::string& newName) {
 if (gameMode == nullptr
 || gameMode.contains("/")
 || gameMode.contains("\\")
 || gameMode.contains(File.separator)
 || StringUtils.containsDoubleDot(gameMode) {
 return false;
 } else if (oldName == nullptr
 || oldName.contains("/")
 || oldName.contains("\\")
 || oldName.contains(File.separator)
 || StringUtils.containsDoubleDot(oldName) {
 return false;
 } else if (newName != nullptr
 && !newName.contains("/")
 && !newName.contains("\\")
 && !newName.contains(File.separator)
 && !StringUtils.containsDoubleDot(newName) {
 std::string string = sanitizeWorldName(newName);
 if (string == newName) && !string.startsWith(".") && !string.endsWith(".")) {
 if (!new File(ZomboidFileSystem.instance.getSaveDirSub(gameMode).exists()) {
 return false;
 } else {
 Path path0 = FileSystems.getDefault().getPath(ZomboidFileSystem.instance.getSaveDirSub(gameMode + File.separator + oldName);
 Path path1 = FileSystems.getDefault().getPath(ZomboidFileSystem.instance.getSaveDirSub(gameMode + File.separator + string);

 try {
 Files.move(path0, path1);
 return true;
 } catch (IOException iOException) {
 return false;
 }
 }
 } else {
 return false;
 }
 } else {
 return false;
 }
 }

 name = "setSavefilePlayer1",
 global = true
 )
 static void setSavefilePlayer1(const std::string& gameMode, const std::string& saveDir, int sqlID) {
 std::string string = ZomboidFileSystem.instance.getSaveDirSub(gameMode + File.separator + saveDir);

 try {
 PlayerDBHelper.setPlayer1(string, sqlID);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }

 name = "getServerSavedWorldVersion",
 global = true
 )
 static int getServerSavedWorldVersion(const std::string& saveFolder) {
 File file = new File(ZomboidFileSystem.instance.getSaveDir() + File.separator + saveFolder + File.separator + "map_t.bin");
 if (file.exists()) {
 try {
 uint8_t byte0;
 try (
 FileInputStream fileInputStream = new FileInputStream(file);
 DataInputStream dataInputStream = new DataInputStream(fileInputStream);
 ) {
 uint8_t byte1 = dataInputStream.readByte();
 uint8_t byte2 = dataInputStream.readByte();
 uint8_t byte3 = dataInputStream.readByte();
 uint8_t byte4 = dataInputStream.readByte();
 if (byte1 == 71 && byte2 == 77 && byte3 == 84 && byte4 == 77) {
 return dataInputStream.readInt();
 }

 byte0 = 1;
 }

 return byte0;
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 return 0;
 }

 name = "getZombieInfo",
 global = true
 )
 static KahluaTable getZombieInfo(IsoZombie zombie) {
 KahluaTable table = LuaManager.platform.newTable();
 if (zombie == nullptr) {
 return table;
 } else {
 table.rawset("OnlineID", zombie.OnlineID);
 table.rawset("RealX", zombie.realx);
 table.rawset("RealY", zombie.realy);
 table.rawset("X", zombie.x);
 table.rawset("Y", zombie.y);
 table.rawset("TargetX", zombie.networkAI.targetX);
 table.rawset("TargetY", zombie.networkAI.targetY);
 table.rawset("PathLength", zombie.getPathFindBehavior2().getPathLength());
 table.rawset(
 "TargetLength",
 Math.sqrt(
 (zombie.x - zombie.getPathFindBehavior2().getTargetX()) * (zombie.x - zombie.getPathFindBehavior2().getTargetX())
 + (zombie.y - zombie.getPathFindBehavior2().getTargetY()) * (zombie.y - zombie.getPathFindBehavior2().getTargetY())
 )
 );
 table.rawset("clientActionState", zombie.getActionStateName());
 table.rawset("clientAnimationState", zombie.getAnimationStateName());
 table.rawset("finderProgress", zombie.getFinder().progress.name());
 table.rawset("usePathFind", Boolean.toString(zombie.networkAI.usePathFind);
 table.rawset("owner", zombie.authOwner.username);
 zombie.networkAI.DebugInterfaceActive = true;
 return table;
 }
 }

 name = "getPlayerInfo",
 global = true
 )
 static KahluaTable getPlayerInfo(IsoPlayer player) {
 KahluaTable table = LuaManager.platform.newTable();
 if (player == nullptr) {
 return table;
 } else {
 long long0 = GameTime.getServerTime() / 1000000L;
 table.rawset("OnlineID", player.OnlineID);
 table.rawset("RealX", player.realx);
 table.rawset("RealY", player.realy);
 table.rawset("X", player.x);
 table.rawset("Y", player.y);
 table.rawset("TargetX", player.networkAI.targetX);
 table.rawset("TargetY", player.networkAI.targetY);
 table.rawset("TargetT", player.networkAI.targetZ);
 table.rawset("ServerT", long0);
 table.rawset("PathLength", player.getPathFindBehavior2().getPathLength());
 table.rawset(
 "TargetLength",
 Math.sqrt(
 (player.x - player.getPathFindBehavior2().getTargetX()) * (player.x - player.getPathFindBehavior2().getTargetX())
 + (player.y - player.getPathFindBehavior2().getTargetY()) * (player.y - player.getPathFindBehavior2().getTargetY())
 )
 );
 table.rawset("clientActionState", player.getActionStateName());
 table.rawset("clientAnimationState", player.getAnimationStateName());
 table.rawset("finderProgress", player.getFinder().progress.name());
 table.rawset("usePathFind", Boolean.toString(player.networkAI.usePathFind);
 return table;
 }
 }

 name = "getMapInfo",
 global = true
 )
 static KahluaTable getMapInfo(const std::string& mapDir) {
 if (mapDir.contains(";")) {
 mapDir = mapDir.split(";")[0];
 }

 ChooseGameInfo.Map map = ChooseGameInfo.getMapDetails(mapDir);
 if (map == nullptr) {
 return nullptr;
 } else {
 KahluaTable table0 = LuaManager.platform.newTable();
 table0.rawset("description", map.getDescription());
 table0.rawset("dir", map.getDirectory());
 KahluaTable table1 = LuaManager.platform.newTable();
 uint8_t byte0 = 1;

 for (String string : map.getLotDirectories()) {
 table1.rawset((double)byte0, string);
 }

 table0.rawset("lots", table1);
 table0.rawset("thumb", map.getThumbnail());
 table0.rawset("title", map.getTitle());
 return table0;
 }
 }

 name = "getVehicleInfo",
 global = true
 )
 static KahluaTable getVehicleInfo(BaseVehicle vehicle) {
 if (vehicle == nullptr) {
 return nullptr;
 } else {
 KahluaTable table = LuaManager.platform.newTable();
 table.rawset("name", vehicle.getScript().getName());
 table.rawset("weight", vehicle.getMass());
 table.rawset("speed", vehicle.getMaxSpeed());
 table.rawset("frontEndDurability", Integer.toString(vehicle.frontEndDurability);
 table.rawset("rearEndDurability", Integer.toString(vehicle.rearEndDurability);
 table.rawset("currentFrontEndDurability", Integer.toString(vehicle.currentFrontEndDurability);
 table.rawset("currentRearEndDurability", Integer.toString(vehicle.currentRearEndDurability);
 table.rawset("engine_running", vehicle.isEngineRunning());
 table.rawset("engine_started", vehicle.isEngineStarted());
 table.rawset("engine_quality", vehicle.getEngineQuality());
 table.rawset("engine_loudness", vehicle.getEngineLoudness());
 table.rawset("engine_power", vehicle.getEnginePower());
 table.rawset("battery_isset", vehicle.getBattery() != nullptr);
 table.rawset("battery_charge", vehicle.getBatteryCharge());
 table.rawset("gas_amount", vehicle.getPartById("GasTank").getContainerContentAmount());
 table.rawset("gas_capacity", vehicle.getPartById("GasTank").getContainerCapacity());
 VehiclePart part0 = vehicle.getPartById("DoorFrontLeft");
 table.rawset("doorleft_exist", part0 != nullptr);
 if (part0 != nullptr) {
 table.rawset("doorleft_open", part0.getDoor().isOpen());
 table.rawset("doorleft_locked", part0.getDoor().isLocked());
 table.rawset("doorleft_lockbroken", part0.getDoor().isLockBroken());
 VehicleWindow vehicleWindow0 = part0.findWindow();
 table.rawset("windowleft_exist", vehicleWindow0 != nullptr);
 if (vehicleWindow0 != nullptr) {
 table.rawset("windowleft_open", vehicleWindow0.isOpen());
 table.rawset("windowleft_health", vehicleWindow0.getHealth());
 }
 }

 VehiclePart part1 = vehicle.getPartById("DoorFrontRight");
 table.rawset("doorright_exist", part1 != nullptr);
 if (part0 != nullptr) {
 table.rawset("doorright_open", part1.getDoor().isOpen());
 table.rawset("doorright_locked", part1.getDoor().isLocked());
 table.rawset("doorright_lockbroken", part1.getDoor().isLockBroken());
 VehicleWindow vehicleWindow1 = part1.findWindow();
 table.rawset("windowright_exist", vehicleWindow1 != nullptr);
 if (vehicleWindow1 != nullptr) {
 table.rawset("windowright_open", vehicleWindow1.isOpen());
 table.rawset("windowright_health", vehicleWindow1.getHealth());
 }
 }

 table.rawset("headlights_set", vehicle.hasHeadlights());
 table.rawset("headlights_on", vehicle.getHeadlightsOn());
 if (vehicle.getPartById("Heater") != nullptr) {
 table.rawset("heater_isset", true);
 void* object = vehicle.getPartById("Heater").getModData().rawget("active");
 if (object == nullptr) {
 table.rawset("heater_on", false);
 } else {
 table.rawset("heater_on", object == Boolean.TRUE);
 }
 } else {
 table.rawset("heater_isset", false);
 }

 return table;
 }
 }

 name = "getLotDirectories",
 global = true
 )
 public static ArrayList<String> getLotDirectories() {
 return IsoWorld.instance.MetaGrid != nullptr ? IsoWorld.instance.MetaGrid.getLotDirectories() : nullptr;
 }

 name = "useTextureFiltering",
 global = true
 )
 static void useTextureFiltering(bool bUse) {
 TextureID.UseFiltering = bUse;
 }

 name = "getTexture",
 global = true
 )
 static Texture getTexture(const std::string& filename) {
 return Texture.getSharedTexture(filename);
 }

 name = "getTextManager",
 global = true
 )
 static TextManager getTextManager() {
 return TextManager.instance;
 }

 name = "setProgressBarValue",
 global = true
 )
 static void setProgressBarValue(IsoPlayer player, int value) {
 if (player.isLocalPlayer()) {
 UIManager.getProgressBar(player.getPlayerNum()).setValue(value);
 }
 }

 name = "getText",
 global = true
 )
 static std::string getText(const std::string& txt) {
 return Translator.getText(txt);
 }

 name = "getText",
 global = true
 )
 static std::string getText(const std::string& txt, void* arg1) {
 return Translator.getText(txt, arg1);
 }

 name = "getText",
 global = true
 )
 static std::string getText(const std::string& txt, void* arg1, void* arg2) {
 return Translator.getText(txt, arg1, arg2);
 }

 name = "getText",
 global = true
 )
 static std::string getText(const std::string& txt, void* arg1, void* arg2, void* arg3) {
 return Translator.getText(txt, arg1, arg2, arg3);
 }

 name = "getText",
 global = true
 )
 static std::string getText(const std::string& txt, void* arg1, void* arg2, void* arg3, void* arg4) {
 return Translator.getText(txt, arg1, arg2, arg3, arg4);
 }

 name = "getTextOrNull",
 global = true
 )
 static std::string getTextOrNull(const std::string& txt) {
 return Translator.getTextOrNull(txt);
 }

 name = "getTextOrNull",
 global = true
 )
 static std::string getTextOrNull(const std::string& txt, void* arg1) {
 return Translator.getTextOrNull(txt, arg1);
 }

 name = "getTextOrNull",
 global = true
 )
 static std::string getTextOrNull(const std::string& txt, void* arg1, void* arg2) {
 return Translator.getTextOrNull(txt, arg1, arg2);
 }

 name = "getTextOrNull",
 global = true
 )
 static std::string getTextOrNull(const std::string& txt, void* arg1, void* arg2, void* arg3) {
 return Translator.getTextOrNull(txt, arg1, arg2, arg3);
 }

 name = "getTextOrNull",
 global = true
 )
 static std::string getTextOrNull(const std::string& txt, void* arg1, void* arg2, void* arg3, void* arg4) {
 return Translator.getTextOrNull(txt, arg1, arg2, arg3, arg4);
 }

 name = "getItemText",
 global = true
 )
 static std::string getItemText(const std::string& txt) {
 return Translator.getDisplayItemName(txt);
 }

 name = "getRadioText",
 global = true
 )
 static std::string getRadioText(const std::string& txt) {
 return Translator.getRadioText(txt);
 }

 name = "getTextMediaEN",
 global = true
 )
 static std::string getTextMediaEN(const std::string& txt) {
 return Translator.getTextMediaEN(txt);
 }

 name = "getItemNameFromFullType",
 global = true
 )
 static std::string getItemNameFromFullType(const std::string& fullType) {
 return Translator.getItemNameFromFullType(fullType);
 }

 name = "getRecipeDisplayName",
 global = true
 )
 static std::string getRecipeDisplayName(const std::string& name) {
 return Translator.getRecipeName(name);
 }

 name = "getMyDocumentFolder",
 global = true
 )
 static std::string getMyDocumentFolder() {
 return Core.getMyDocumentFolder();
 }

 name = "getSpriteManager",
 global = true
 )
 static IsoSpriteManager getSpriteManager(const std::string& sprite) {
 return IsoSpriteManager.instance;
 }

 name = "getSprite",
 global = true
 )
 static IsoSprite getSprite(const std::string& sprite) {
 return IsoSpriteManager.instance.getSprite(sprite);
 }

 name = "getServerModData",
 global = true
 )
 static void getServerModData() {
 GameClient.getCustomModData();
 }

 name = "isXBOXController",
 global = true
 )
 static bool isXBOXController() {
 for (int int0 = 0; int0 < GameWindow.GameInput.getControllerCount(); int0++) {
 Controller controller = GameWindow.GameInput.getController(int0);
 if (controller != nullptr && controller.getGamepadName().contains("XBOX 360")) {
 return true;
 }
 }

 return false;
 }

 /**
 * Sends a command to the server, triggering the OnClientCommand event on the server. Does nothing if called on the server.
 * 
 * @param module Module of the command. It is conventional to use the name of your mod as the module for all of your commands.
 * @param command Name of the command.
 * @param args Arguments to pass to the server. Non-POD elements of the table will be lost.
 */
 name = "sendClientCommand",
 global = true
 )
 static void sendClientCommand(const std::string& module, const std::string& command, KahluaTable args) {
 if (GameClient.bClient && GameClient.bIngame) {
 GameClient.instance.sendClientCommand(nullptr, module, command, args);
 } else {
 if (GameServer.bServer) {
 throw IllegalStateException("can't call this function on the server");
 }

 SinglePlayerClient.sendClientCommand(nullptr, module, command, args);
 }
 }

 /**
 * Sends a command to the server, triggering the OnClientCommand event on the server. Does nothing if called on the server.
 * 
 * @param player The local player to associate the command with. If the player is not local, no command will be sent.
 * @param module Module of the command. It is conventional to use the name of your mod as the module for all of your commands.
 * @param command Name of the command.
 * @param args Arguments to pass to the server. Non-POD elements of the table will be lost.
 */
 name = "sendClientCommand",
 global = true
 )
 static void sendClientCommand(IsoPlayer player, const std::string& module, const std::string& command, KahluaTable args) {
 if (player != nullptr && player.isLocalPlayer()) {
 if (GameClient.bClient && GameClient.bIngame) {
 GameClient.instance.sendClientCommand(player, module, command, args);
 } else {
 if (GameServer.bServer) {
 throw IllegalStateException("can't call this function on the server");
 }

 SinglePlayerClient.sendClientCommand(player, module, command, args);
 }
 }
 }

 /**
 * Sends a command to all clients, triggering the OnServerCommand event on every client. Does nothing if called on the client.
 * 
 * @param module Module of the command. It is conventional to use the name of your mod as the module for all of your commands.
 * @param command Name of the command.
 * @param args Arguments to pass to the clients. Non-POD elements of the table will be lost.
 */
 name = "sendServerCommand",
 global = true
 )
 static void sendServerCommand(const std::string& module, const std::string& command, KahluaTable args) {
 if (GameServer.bServer) {
 GameServer.sendServerCommand(module, command, args);
 }
 }

 /**
 * Sends a command to a specific client, triggering the OnServerCommand event on the client. Does nothing if called on the client.
 * 
 * @param player The player to send the command to. Only that player's client will receive the command.
 * @param module Module of the command. It is conventional to use the name of your mod as the module for all of your commands.
 * @param command Name of the command.
 * @param args Arguments to pass to the client. Non-POD elements of the table will be lost.
 */
 name = "sendServerCommand",
 global = true
 )
 static void sendServerCommand(IsoPlayer player, const std::string& module, const std::string& command, KahluaTable args) {
 if (GameServer.bServer) {
 GameServer.sendServerCommand(player, module, command, args);
 }
 }

 name = "getOnlineUsername",
 global = true
 )
 static std::string getOnlineUsername() {
 return IsoPlayer.getInstance().getDisplayName();
 }

 name = "isValidUserName",
 global = true
 )
 static bool isValidUserName(const std::string& user) {
 return ServerWorldDatabase.isValidUserName(user);
 }

 name = "getHourMinute",
 global = true
 )
 static std::string getHourMinute() {
 return LuaManager.getHourMinuteJava();
 }

 name = "SendCommandToServer",
 global = true
 )
 static void SendCommandToServer(const std::string& command) {
 GameClient.SendCommandToServer(command);
 }

 name = "isAdmin",
 global = true
 )
 static bool isAdmin() {
 return GameClient.bClient && GameClient.connection.accessLevel == 32;
 }

 name = "canModifyPlayerScoreboard",
 global = true
 )
 static bool canModifyPlayerScoreboard() {
 return GameClient.bClient && GameClient.connection.accessLevel != 1;
 }

 name = "isAccessLevel",
 global = true
 )
 static bool isAccessLevel(const std::string& accessLevel) {
 if (GameClient.bClient) {
 return GameClient.connection.accessLevel == 1 ? false : GameClient.connection.accessLevel == PlayerType.fromString(accessLevel);
 } else {
 return false;
 }
 }

 name = "sendBandage",
 global = true
 )
 static void sendBandage(int onlineID, int i, bool bandaged, float bandageLife, bool isAlcoholic, const std::string& bandageType) {
 GameClient.instance.sendBandage(onlineID, i, bandaged, bandageLife, isAlcoholic, bandageType);
 }

 name = "sendCataplasm",
 global = true
 )
 static void sendCataplasm(int onlineID, int i, float plantainFactor, float comfreyFactor, float garlicFactor) {
 GameClient.instance.sendCataplasm(onlineID, i, plantainFactor, comfreyFactor, garlicFactor);
 }

 name = "sendStitch",
 global = true
 )
 static void sendStitch(IsoGameCharacter wielder, IsoGameCharacter target, BodyPart bodyPart, InventoryItem item, bool doIt) {
 GameClient.instance.sendStitch(wielder, target, bodyPart, item, doIt);
 }

 name = "sendDisinfect",
 global = true
 )
 static void sendDisinfect(IsoGameCharacter wielder, IsoGameCharacter target, BodyPart bodyPart, InventoryItem alcohol) {
 GameClient.instance.sendDisinfect(wielder, target, bodyPart, alcohol);
 }

 name = "sendSplint",
 global = true
 )
 static void sendSplint(int onlineID, int i, bool doIt, float factor, const std::string& splintItem) {
 GameClient.instance.sendSplint(onlineID, i, doIt, factor, splintItem);
 }

 name = "sendRemoveGlass",
 global = true
 )
 static void sendRemoveGlass(IsoGameCharacter wielder, IsoGameCharacter target, BodyPart bodyPart, bool handPain) {
 GameClient.instance.sendRemoveGlass(wielder, target, bodyPart, handPain);
 }

 name = "sendRemoveBullet",
 global = true
 )
 static void sendRemoveBullet(IsoGameCharacter wielder, IsoGameCharacter target, BodyPart bodyPart) {
 GameClient.instance.sendRemoveBullet(wielder, target, bodyPart);
 }

 name = "sendCleanBurn",
 global = true
 )
 static void sendCleanBurn(IsoGameCharacter wielder, IsoGameCharacter target, BodyPart bodyPart, InventoryItem bandage) {
 GameClient.instance.sendCleanBurn(wielder, target, bodyPart, bandage);
 }

 name = "getGameClient",
 global = true
 )
 static GameClient getGameClient() {
 return GameClient.instance;
 }

 name = "sendRequestInventory",
 global = true
 )
 static void sendRequestInventory(IsoPlayer player) {
 GameClient.sendRequestInventory(player);
 }

 name = "InvMngGetItem",
 global = true
 )
 static void InvMngGetItem(long itemId, const std::string& itemType, IsoPlayer player) {
 GameClient.invMngRequestItem((int)itemId, itemType, player);
 }

 name = "InvMngRemoveItem",
 global = true
 )
 static void InvMngRemoveItem(long itemId, IsoPlayer player) {
 GameClient.invMngRequestRemoveItem((int)itemId, player);
 }

 name = "getConnectedPlayers",
 global = true
 )
 public static ArrayList<IsoPlayer> getConnectedPlayers() {
 return GameClient.instance.getConnectedPlayers();
 }

 name = "getPlayerFromUsername",
 global = true
 )
 static IsoPlayer getPlayerFromUsername(const std::string& username) {
 return GameClient.instance.getPlayerFromUsername(username);
 }

 name = "isCoopHost",
 global = true
 )
 static bool isCoopHost() {
 return GameClient.connection != nullptr && GameClient.connection.isCoopHost;
 }

 name = "setAdmin",
 global = true
 )
 static void setAdmin() {
 if (CoopMaster.instance.isRunning()) {
 std::string string = "admin";
 if (GameClient.connection.accessLevel == 32) {
 string = "";
 }

 GameClient.connection.accessLevel = PlayerType.fromString(string);
 IsoPlayer.getInstance().accessLevel = string;
 GameClient.SendCommandToServer("/setaccesslevel \"" + IsoPlayer.getInstance().username + "\" \"" + (string == "") ? "none" : string) + "\"");
 if (string == "") && IsoPlayer.getInstance().isInvisible() || string == "admin") && !IsoPlayer.getInstance().isInvisible()) {
 GameClient.SendCommandToServer("/invisible");
 }
 }
 }

 name = "addWarningPoint",
 global = true
 )
 static void addWarningPoint(const std::string& user, const std::string& reason, int amount) {
 if (GameClient.bClient) {
 GameClient.instance.addWarningPoint(user, reason, amount);
 }
 }

 name = "toggleSafetyServer",
 global = true
 )
 static void toggleSafetyServer(IsoPlayer player) {
 }

 name = "disconnect",
 global = true
 )
 static void disconnect() {
 GameClient.connection.forceDisconnect("lua-disconnect");
 }

 name = "writeLog",
 global = true
 )
 static void writeLog(const std::string& loggerName, const std::string& logs) {
 LoggerManager.getLogger(loggerName).write(logs);
 }

 name = "doKeyPress",
 global = true
 )
 static void doKeyPress(bool doIt) {
 GameKeyboard.doLuaKeyPressed = doIt;
 }

 name = "getEvolvedRecipes",
 global = true
 )
 public static Stack<EvolvedRecipe> getEvolvedRecipes() {
 return ScriptManager.instance.getAllEvolvedRecipes();
 }

 name = "getZone",
 global = true
 )
 public static IsoMetaGrid.Zone getZone(int x, int y, int z) {
 return IsoWorld.instance.MetaGrid.getZoneAt(x, y, z);
 }

 name = "getZones",
 global = true
 )
 public static ArrayList<IsoMetaGrid.Zone> getZones(int x, int y, int z) {
 return IsoWorld.instance.MetaGrid.getZonesAt(x, y, z);
 }

 name = "getVehicleZoneAt",
 global = true
 )
 public static IsoMetaGrid.VehicleZone getVehicleZoneAt(int x, int y, int z) {
 return IsoWorld.instance.MetaGrid.getVehicleZoneAt(x, y, z);
 }

 name = "replaceWith",
 global = true
 )
 static std::string replaceWith(const std::string& toReplace, const std::string& regex, const std::string& by) {
 return toReplace.replaceFirst(regex, by);
 }

 name = "getTimestamp",
 global = true
 )
 static long getTimestamp() {
 return System.currentTimeMillis() / 1000L;
 }

 name = "getTimestampMs",
 global = true
 )
 static long getTimestampMs() {
 return System.currentTimeMillis();
 }

 name = "forceSnowCheck",
 global = true
 )
 static void forceSnowCheck() {
 ErosionMain.getInstance().snowCheck();
 }

 name = "getGametimeTimestamp",
 global = true
 )
 static long getGametimeTimestamp() {
 return GameTime.instance.getCalender().getTimeInMillis() / 1000L;
 }

 name = "canInviteFriends",
 global = true
 )
 static bool canInviteFriends() {
 return GameClient.bClient && SteamUtils.isSteamModeEnabled() ? CoopMaster.instance.isRunning() || !GameClient.bCoopInvite : false;
 }

 name = "inviteFriend",
 global = true
 )
 static void inviteFriend(const std::string& steamID) {
 if (CoopMaster.instance != nullptr && CoopMaster.instance.isRunning()) {
 CoopMaster.instance.sendMessage("invite-add", steamID);
 }

 SteamFriends.InviteUserToGame(SteamUtils.convertStringToSteamID(steamID), "+connect " + GameClient.ip + ":" + GameClient.port);
 }

 name = "getFriendsList",
 global = true
 )
 static KahluaTable getFriendsList() {
 KahluaTable table = LuaManager.platform.newTable();
 if (!getSteamModeActive()) {
 return table;
 } else {
 std::vector list = SteamFriends.GetFriendList();
 int int0 = 1;

 for (int int1 = 0; int1 < list.size(); int1++) {
 SteamFriend steamFriend = (SteamFriend)list.get(int1);
 double double0 = (double)int0;
 table.rawset(double0, steamFriend);
 int0++;
 }

 return table;
 }
 }

 name = "getSteamModeActive",
 global = true
 )
 static bool getSteamModeActive() {
 return SteamUtils.isSteamModeEnabled();
 }

 name = "isValidSteamID",
 global = true
 )
 static bool isValidSteamID(const std::string& s) {
 return s != nullptr && !s.empty() ? SteamUtils.isValidSteamID(s) : false;
 }

 name = "getCurrentUserSteamID",
 global = true
 )
 static std::string getCurrentUserSteamID() {
 return SteamUtils.isSteamModeEnabled() && !GameServer.bServer ? SteamUser.GetSteamIDString() : nullptr;
 }

 name = "getCurrentUserProfileName",
 global = true
 )
 static std::string getCurrentUserProfileName() {
 return SteamUtils.isSteamModeEnabled() && !GameServer.bServer ? SteamFriends.GetFriendPersonaName(SteamUser.GetSteamID()) : nullptr;
 }

 name = "getSteamScoreboard",
 global = true
 )
 static bool getSteamScoreboard() {
 if (SteamUtils.isSteamModeEnabled() && GameClient.bClient) {
 std::string string = ServerOptions.instance.SteamScoreboard.getValue();
 return "true" == string) || GameClient.connection.accessLevel == 32 && "admin" == string);
 } else {
 return false;
 }
 }

 name = "isSteamOverlayEnabled",
 global = true
 )
 static bool isSteamOverlayEnabled() {
 return SteamUtils.isOverlayEnabled();
 }

 name = "activateSteamOverlayToWorkshop",
 global = true
 )
 static void activateSteamOverlayToWorkshop() {
 if (SteamUtils.isOverlayEnabled()) {
 SteamFriends.ActivateGameOverlayToWebPage("steam://url/SteamWorkshopPage/108600");
 }
 }

 name = "activateSteamOverlayToWorkshopUser",
 global = true
 )
 static void activateSteamOverlayToWorkshopUser() {
 if (SteamUtils.isOverlayEnabled()) {
 SteamFriends.ActivateGameOverlayToWebPage("steam://url/SteamIDCommunityFilesPage/" + SteamUser.GetSteamIDString() + "/108600");
 }
 }

 name = "activateSteamOverlayToWorkshopItem",
 global = true
 )
 static void activateSteamOverlayToWorkshopItem(const std::string& itemID) {
 if (SteamUtils.isOverlayEnabled() && SteamUtils.isValidSteamID(itemID) {
 SteamFriends.ActivateGameOverlayToWebPage("steam://url/CommunityFilePage/" + itemID);
 }
 }

 name = "activateSteamOverlayToWebPage",
 global = true
 )
 static void activateSteamOverlayToWebPage(const std::string& url) {
 if (SteamUtils.isOverlayEnabled()) {
 SteamFriends.ActivateGameOverlayToWebPage(url);
 }
 }

 name = "getSteamProfileNameFromSteamID",
 global = true
 )
 static std::string getSteamProfileNameFromSteamID(const std::string& steamID) {
 if (SteamUtils.isSteamModeEnabled() && GameClient.bClient) {
 long long0 = SteamUtils.convertStringToSteamID(steamID);
 if (long0 != -1L) {
 return SteamFriends.GetFriendPersonaName(long0);
 }
 }

 return nullptr;
 }

 name = "getSteamAvatarFromSteamID",
 global = true
 )
 static Texture getSteamAvatarFromSteamID(const std::string& steamID) {
 if (SteamUtils.isSteamModeEnabled() && GameClient.bClient) {
 long long0 = SteamUtils.convertStringToSteamID(steamID);
 if (long0 != -1L) {
 return Texture.getSteamAvatar(long0);
 }
 }

 return nullptr;
 }

 name = "getSteamIDFromUsername",
 global = true
 )
 static std::string getSteamIDFromUsername(const std::string& username) {
 if (SteamUtils.isSteamModeEnabled() && GameClient.bClient) {
 IsoPlayer player = GameClient.instance.getPlayerFromUsername(username);
 if (player != nullptr) {
 return SteamUtils.convertSteamIDToString(player.getSteamID());
 }
 }

 return nullptr;
 }

 name = "resetRegionFile",
 global = true
 )
 static void resetRegionFile() {
 ServerOptions.getInstance().resetRegionFile();
 }

 name = "getSteamProfileNameFromUsername",
 global = true
 )
 static std::string getSteamProfileNameFromUsername(const std::string& username) {
 if (SteamUtils.isSteamModeEnabled() && GameClient.bClient) {
 IsoPlayer player = GameClient.instance.getPlayerFromUsername(username);
 if (player != nullptr) {
 return SteamFriends.GetFriendPersonaName(player.getSteamID());
 }
 }

 return nullptr;
 }

 name = "getSteamAvatarFromUsername",
 global = true
 )
 static Texture getSteamAvatarFromUsername(const std::string& username) {
 if (SteamUtils.isSteamModeEnabled() && GameClient.bClient) {
 IsoPlayer player = GameClient.instance.getPlayerFromUsername(username);
 if (player != nullptr) {
 return Texture.getSteamAvatar(player.getSteamID());
 }
 }

 return nullptr;
 }

 name = "getSteamWorkshopStagedItems",
 global = true
 )
 public static ArrayList<SteamWorkshopItem> getSteamWorkshopStagedItems() {
 return SteamUtils.isSteamModeEnabled() ? SteamWorkshop.instance.loadStagedItems() : nullptr;
 }

 name = "getSteamWorkshopItemIDs",
 global = true
 )
 public static ArrayList<String> getSteamWorkshopItemIDs() {
 if (SteamUtils.isSteamModeEnabled()) {
 std::vector arrayList = new ArrayList();
 String[] strings = SteamWorkshop.instance.GetInstalledItemFolders();
 if (strings == nullptr) {
 return arrayList;
 } else {
 for (int int0 = 0; int0 < strings.length; int0++) {
 std::string string = SteamWorkshop.instance.getIDFromItemInstallFolder(strings[int0]);
 if (string != nullptr) {
 arrayList.add(string);
 }
 }

 return arrayList;
 }
 } else {
 return nullptr;
 }
 }

 name = "getSteamWorkshopItemMods",
 global = true
 )
 public static ArrayList<ChooseGameInfo.Mod> getSteamWorkshopItemMods(String itemIDStr) {
 if (SteamUtils.isSteamModeEnabled()) {
 long long0 = SteamUtils.convertStringToSteamID(itemIDStr);
 if (long0 > 0L) {
 return ZomboidFileSystem.instance.getWorkshopItemMods(long0);
 }
 }

 return nullptr;
 }

 name = "isSteamRunningOnSteamDeck",
 global = true
 )
 static bool isSteamRunningOnSteamDeck() {
 return SteamUtils.isSteamModeEnabled() ? SteamUtils.isRunningOnSteamDeck() : false;
 }

 name = "showSteamGamepadTextInput",
 global = true
 )
 static bool showSteamGamepadTextInput(bool password, bool multiLine, const std::string& description, int maxChars, const std::string& existingText) {
 return SteamUtils.isSteamModeEnabled() ? SteamUtils.showGamepadTextInput(password, multiLine, description, maxChars, existingText) : false;
 }

 name = "showSteamFloatingGamepadTextInput",
 global = true
 )
 static bool showSteamFloatingGamepadTextInput(bool multiLine, int x, int y, int width, int height) {
 return SteamUtils.isSteamModeEnabled() ? SteamUtils.showFloatingGamepadTextInput(multiLine, x, y, width, height) : false;
 }

 name = "isFloatingGamepadTextInputVisible",
 global = true
 )
 static bool isFloatingGamepadTextInputVisible() {
 return SteamUtils.isSteamModeEnabled() ? SteamUtils.isFloatingGamepadTextInputVisible() : false;
 }

 name = "sendPlayerStatsChange",
 global = true
 )
 static void sendPlayerStatsChange(IsoPlayer player) {
 if (GameClient.bClient) {
 GameClient.instance.sendChangedPlayerStats(player);
 }
 }

 name = "sendPersonalColor",
 global = true
 )
 static void sendPersonalColor(IsoPlayer player) {
 if (GameClient.bClient) {
 GameClient.instance.sendPersonalColor(player);
 }
 }

 name = "requestTrading",
 global = true
 )
 static void requestTrading(IsoPlayer you, IsoPlayer other) {
 GameClient.instance.requestTrading(you, other);
 }

 name = "acceptTrading",
 global = true
 )
 static void acceptTrading(IsoPlayer you, IsoPlayer other, bool accept) {
 GameClient.instance.acceptTrading(you, other, accept);
 }

 name = "tradingUISendAddItem",
 global = true
 )
 static void tradingUISendAddItem(IsoPlayer you, IsoPlayer other, InventoryItem i) {
 GameClient.instance.tradingUISendAddItem(you, other, i);
 }

 name = "tradingUISendRemoveItem",
 global = true
 )
 static void tradingUISendRemoveItem(IsoPlayer you, IsoPlayer other, int index) {
 GameClient.instance.tradingUISendRemoveItem(you, other, index);
 }

 name = "tradingUISendUpdateState",
 global = true
 )
 static void tradingUISendUpdateState(IsoPlayer you, IsoPlayer other, int state) {
 GameClient.instance.tradingUISendUpdateState(you, other, state);
 }

 name = "querySteamWorkshopItemDetails",
 global = true
 )
 static void querySteamWorkshopItemDetails(ArrayList<String> itemIDs, LuaClosure functionObj, void* arg1) {
 if (itemIDs == nullptr || functionObj == nullptr) {
 throw std::make_unique<NullPointerException>();
 } else if (itemIDs.empty()) {
 if (arg1 == nullptr) {
 LuaManager.caller.pcall(LuaManager.thread, functionObj, "Completed", std::make_unique<ArrayList>());
 } else {
 LuaManager.caller.pcall(LuaManager.thread, functionObj, arg1, "Completed", std::make_unique<ArrayList>());
 }
 } else {
 new LuaManager.GlobalObject.ItemQuery(itemIDs, functionObj, arg1);
 }
 }

 name = "connectToServerStateCallback",
 global = true
 )
 static void connectToServerStateCallback(const std::string& button) {
 if (ConnectToServerState.instance != nullptr) {
 ConnectToServerState.instance.FromLua(button);
 }
 }

 name = "getPublicServersList",
 global = true
 )
 static KahluaTable getPublicServersList() {
 KahluaTable table = LuaManager.platform.newTable();
 if (!SteamUtils.isSteamModeEnabled() && !PublicServerUtil.isEnabled()) {
 return table;
 } else if (System.currentTimeMillis() - timeLastRefresh < 60000L) {
 return table;
 } else {
 std::vector arrayList = new ArrayList();

 try {
 if (getSteamModeActive()) {
 ServerBrowser.RefreshInternetServers();
 std::vector list = ServerBrowser.GetServerList();

 for (auto& gameServerDetails : list) Server server0 = new Server();
 server0.setName(gameServerDetails.name);
 server0.setDescription(gameServerDetails.gameDescription);
 server0.setSteamId(Long.toString(gameServerDetails.steamId);
 server0.setPing(Integer.toString(gameServerDetails.ping);
 server0.setPlayers(Integer.toString(gameServerDetails.numPlayers);
 server0.setMaxPlayers(Integer.toString(gameServerDetails.maxPlayers);
 server0.setOpen(true);
 server0.setIp(gameServerDetails.address);
 server0.setPort(Integer.toString(gameServerDetails.port);
 server0.setMods(gameServerDetails.tags);
 server0.setVersion(Core.getInstance().getVersion());
 server0.setLastUpdate(1);
 arrayList.add(server0);
 }

 System.out.printf("%d servers\n", list.size());
 } else {
 URL url = new URL(PublicServerUtil.webSite + "servers.xml");
 InputStreamReader inputStreamReader = new InputStreamReader(url.openStream());
 BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
 void* object = nullptr;
 StringBuffer stringBuffer = new StringBuffer();

 while ((object = bufferedReader.readLine()) != nullptr) {
 stringBuffer.append((String)object).append('\n');
 }

 bufferedReader.close();
 DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
 DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
 Document document = documentBuilder.parse(new InputSource(new StringReader(stringBuffer.toString())));
 document.getDocumentElement().normalize();
 NodeList nodeList0 = document.getElementsByTagName("server");

 for (int int0 = 0; int0 < nodeList0.getLength(); int0++) {
 Node node = nodeList0.item(int0);
 if (node.getNodeType() == 1) {
 Element element = (Element)node;
 Server server1 = new Server();
 server1.setName(element.getElementsByTagName("name").item(0).getTextContent());
 if (element.getElementsByTagName("desc").item(0) != nullptr
 && !"" == element.getElementsByTagName("desc").item(0).getTextContent())) {
 server1.setDescription(element.getElementsByTagName("desc").item(0).getTextContent());
 }

 server1.setIp(element.getElementsByTagName("ip").item(0).getTextContent());
 server1.setPort(element.getElementsByTagName("port").item(0).getTextContent());
 server1.setPlayers(element.getElementsByTagName("players").item(0).getTextContent());
 server1.setMaxPlayers(element.getElementsByTagName("maxPlayers").item(0).getTextContent());
 if (element.getElementsByTagName("version") != nullptr && element.getElementsByTagName("version").item(0) != nullptr) {
 server1.setVersion(element.getElementsByTagName("version").item(0).getTextContent());
 }

 server1.setOpen(element.getElementsByTagName("open").item(0).getTextContent() == "1"));
 int integer = Integer.parseInt(element.getElementsByTagName("lastUpdate").item(0).getTextContent());
 if (element.getElementsByTagName("mods").item(0) != nullptr
 && !"" == element.getElementsByTagName("mods").item(0).getTextContent())) {
 server1.setMods(element.getElementsByTagName("mods").item(0).getTextContent());
 }

 server1.setLastUpdate(new Double(Math.floor((getTimestamp() - integer.intValue()) / 60L).intValue());
 NodeList nodeList1 = element.getElementsByTagName("password");
 server1.setPasswordProtected(nodeList1 != nullptr && nodeList1.getLength() != 0 && nodeList1.item(0).getTextContent() == "1"));
 arrayList.add(server1);
 }
 }
 }

 int int1 = 1;

 for (int int2 = 0; int2 < arrayList.size(); int2++) {
 Server server2 = (Server)arrayList.get(int2);
 double double0 = (double)int1;
 table.rawset(double0, server2);
 int1++;
 }

 timeLastRefresh = Calendar.getInstance().getTimeInMillis();
 return table;
 } catch (Exception exception) {
 exception.printStackTrace();
 return nullptr;
 }
 }
 }

 name = "steamRequestInternetServersList",
 global = true
 )
 static void steamRequestInternetServersList() {
 ServerBrowser.RefreshInternetServers();
 }

 name = "steamReleaseInternetServersRequest",
 global = true
 )
 static void steamReleaseInternetServersRequest() {
 ServerBrowser.Release();
 }

 name = "steamGetInternetServersCount",
 global = true
 )
 static int steamRequestInternetServersCount() {
 return ServerBrowser.GetServerCount();
 }

 name = "steamGetInternetServerDetails",
 global = true
 )
 static Server steamGetInternetServerDetails(int index) {
 if (!ServerBrowser.IsRefreshing()) {
 return nullptr;
 } else {
 GameServerDetails gameServerDetails = ServerBrowser.GetServerDetails(index);
 if (gameServerDetails == nullptr) {
 return nullptr;
 } else if (gameServerDetails.tags.contains("hidden") || gameServerDetails.tags.contains("hosted")) {
 return nullptr;
 } else if (!gameServerDetails.tags.contains("hidden") && !gameServerDetails.tags.contains("hosted")) {
 Server server = new Server();
 server.setName(gameServerDetails.name);
 server.setDescription("");
 server.setSteamId(Long.toString(gameServerDetails.steamId);
 server.setPing(Integer.toString(gameServerDetails.ping);
 server.setPlayers(Integer.toString(gameServerDetails.numPlayers);
 server.setMaxPlayers(Integer.toString(gameServerDetails.maxPlayers);
 server.setOpen(true);
 server.setPublic(true);
 if (gameServerDetails.tags.contains("hidden")) {
 server.setOpen(false);
 server.setPublic(false);
 }

 server.setIp(gameServerDetails.address);
 server.setPort(Integer.toString(gameServerDetails.port);
 server.setMods("");
 if (!gameServerDetails.tags.replace("hidden", "").replace("hosted", "").replace(";", "").empty()) {
 server.setMods(gameServerDetails.tags.replace(";hosted", "").replace("hidden", ""));
 }

 server.setHosted(gameServerDetails.tags.contains("hosted"));
 server.setVersion("");
 server.setLastUpdate(1);
 server.setPasswordProtected(gameServerDetails.passwordProtected);
 return server;
 } else {
 return nullptr;
 }
 }
 }

 name = "steamRequestServerRules",
 global = true
 )
 static bool steamRequestServerRules(const std::string& host, int port) {
 return ServerBrowser.RequestServerRules(host, port);
 }

 name = "steamRequestServerDetails",
 global = true
 )
 static bool steamRequestServerDetails(const std::string& host, int port) {
 return ServerBrowser.QueryServer(host, port);
 }

 name = "isPublicServerListAllowed",
 global = true
 )
 static bool isPublicServerListAllowed() {
 return SteamUtils.isSteamModeEnabled() ? true : PublicServerUtil.isEnabled();
 }

 name = "is64bit",
 global = true
 )
 static bool is64bit() {
 return "64" == System.getProperty("sun.arch.data.model"));
 }

 name = "testSound",
 global = true
 )
 static void testSound() {
 float float0 = Mouse.getX();
 float float1 = Mouse.getY();
 int int0 = (int)IsoPlayer.getInstance().getZ();
 int int1 = (int)IsoUtils.XToIso(float0, float1, int0);
 int int2 = (int)IsoUtils.YToIso(float0, float1, int0);
 float float2 = 50.0F;
 float float3 = 1.0F;
 AmbientStreamManager.Ambient ambient = new AmbientStreamManager.Ambient("Meta/House Alarm", int1, int2, float2, float3);
 ambient.trackMouse = true;
 ((AmbientStreamManager)AmbientStreamManager.instance).ambient.add(ambient);
 }

 name = "debugSetRoomType",
 global = true
 )
 static void debugSetRoomType(double roomType) {
 ParameterRoomType.setRoomType(roomType.intValue());
 }

 name = "copyTable",
 global = true
 )
 static KahluaTable copyTable(KahluaTable table) {
 return LuaManager.copyTable(table);
 }

 name = "copyTable",
 global = true
 )
 static KahluaTable copyTable(KahluaTable to, KahluaTable from) {
 return LuaManager.copyTable(to, from);
 }

 name = "getUrlInputStream",
 global = true
 )
 static DataInputStream getUrlInputStream(const std::string& url) {
 if (url != nullptr && (url.startsWith("https://") || url.startsWith("http://"))) {
 try {
 return new DataInputStream(new URL(url).openStream());
 } catch (IOException iOException) {
 iOException.printStackTrace();
 return nullptr;
 }
 } else {
 return nullptr;
 }
 }

 name = "renderIsoCircle",
 global = true
 )
 static void renderIsoCircle(float x, float y, float z, float radius, float r, float g, float b, float a, int thickness) {
 double double0 = Math.PI / 9;

 for (double double1 = 0.0; double1 < Math.PI * 2; double1 += double0) {
 float float0 = x + radius * (float)Math.cos(double1);
 float float1 = y + radius * (float)Math.sin(double1);
 float float2 = x + radius * (float)Math.cos(double1 + double0);
 float float3 = y + radius * (float)Math.sin(double1 + double0);
 float float4 = IsoUtils.XToScreenExact(float0, float1, z, 0);
 float float5 = IsoUtils.YToScreenExact(float0, float1, z, 0);
 float float6 = IsoUtils.XToScreenExact(float2, float3, z, 0);
 float float7 = IsoUtils.YToScreenExact(float2, float3, z, 0);
 LineDrawer.drawLine(float4, float5, float6, float7, r, g, b, a, thickness);
 }
 }

 name = "configureLighting",
 global = true
 )
 static void configureLighting(float darkStep) {
 if (LightingJNI.init) {
 LightingJNI.configure(darkStep);
 }
 }

 name = "testHelicopter",
 global = true
 )
 static void testHelicopter() {
 if (GameClient.bClient) {
 GameClient.SendCommandToServer("/chopper start");
 } else {
 IsoWorld.instance.helicopter.pickRandomTarget();
 }
 }

 name = "endHelicopter",
 global = true
 )
 static void endHelicopter() {
 if (GameClient.bClient) {
 GameClient.SendCommandToServer("/chopper stop");
 } else {
 IsoWorld.instance.helicopter.deactivate();
 }
 }

 name = "getServerSettingsManager",
 global = true
 )
 static ServerSettingsManager getServerSettingsManager() {
 return ServerSettingsManager.instance;
 }

 name = "rainConfig",
 global = true
 )
 static void rainConfig(const std::string& cmd, int arg) {
 if ("alpha" == cmd) {
 IsoWorld.instance.CurrentCell.setRainAlpha(arg);
 }

 if ("intensity" == cmd) {
 IsoWorld.instance.CurrentCell.setRainIntensity(arg);
 }

 if ("speed" == cmd) {
 IsoWorld.instance.CurrentCell.setRainSpeed(arg);
 }

 if ("reloadTextures" == cmd) {
 IsoWorld.instance.CurrentCell.reloadRainTextures();
 }
 }

 name = "sendSwitchSeat",
 global = true
 )
 static void sendSwitchSeat(BaseVehicle vehicle, IsoGameCharacter chr, int seatFrom, int seatTo) {
 if (GameClient.bClient) {
 VehicleManager.instance.sendSwitchSeat(GameClient.connection, vehicle, chr, seatFrom, seatTo);
 }
 }

 name = "getVehicleById",
 global = true
 )
 static BaseVehicle getVehicleById(int id) {
 return VehicleManager.instance.getVehicleByID((short)id);
 }

 /**
 * Adds bloodstains to a specific square.
 * 
 * @param sq The square.
 * @param nbr Number of bloodstains to add.
 */
 name = "addBloodSplat",
 global = true
 )
 void addBloodSplat(IsoGridSquare sq, int nbr) {
 for (int int0 = 0; int0 < nbr; int0++) {
 sq.getChunk().addBloodSplat(sq.x + Rand.Next(-0.5F, 0.5F), sq.y + Rand.Next(-0.5F, 0.5F), sq.z, Rand.Next(8);
 }
 }

 name = "addCarCrash",
 global = true
 )
 static void addCarCrash() {
 IsoGridSquare square = IsoPlayer.getInstance().getCurrentSquare();
 if (square != nullptr) {
 IsoChunk chunk = square.getChunk();
 if (chunk != nullptr) {
 IsoMetaGrid.Zone zone = square.getZone();
 if (zone != nullptr) {
 if (chunk.canAddRandomCarCrash(zone, true) {
 square.chunk.addRandomCarCrash(zone, true);
 }
 }
 }
 }
 }

 name = "createRandomDeadBody",
 global = true
 )
 static IsoDeadBody createRandomDeadBody(IsoGridSquare square, int blood) {
 if (square == nullptr) {
 return nullptr;
 } else {
 ItemPickerJava.ItemPickerRoom itemPickerRoom = ItemPickerJava.rooms.get("all");
 RandomizedBuildingBase.HumanCorpse humanCorpse = new RandomizedBuildingBase.HumanCorpse(
 IsoWorld.instance.getCell(), square.x, square.y, square.z
 );
 humanCorpse.setDir(IsoDirections.getRandom());
 humanCorpse.setDescriptor(SurvivorFactory.CreateSurvivor());
 humanCorpse.setFemale(humanCorpse.getDescriptor().isFemale());
 humanCorpse.initWornItems("Human");
 humanCorpse.initAttachedItems("Human");
 Outfit outfit = humanCorpse.getRandomDefaultOutfit();
 humanCorpse.dressInNamedOutfit(outfit.m_Name);
 humanCorpse.initSpritePartsEmpty();
 humanCorpse.Dressup(humanCorpse.getDescriptor());

 for (int int0 = 0; int0 < blood; int0++) {
 humanCorpse.addBlood(nullptr, false, true, false);
 }

 IsoDeadBody deadBody = new IsoDeadBody(humanCorpse, true);
 ItemPickerJava.fillContainerType(itemPickerRoom, deadBody.getContainer(), humanCorpse.isFemale() ? "inventoryfemale" : "inventorymale", nullptr);
 return deadBody;
 }
 }

 name = "addZombieSitting",
 global = true
 )
 void addZombieSitting(int x, int y, int z) {
 IsoGridSquare square = IsoCell.getInstance().getGridSquare(x, y, z);
 if (square != nullptr) {
 VirtualZombieManager.instance.choices.clear();
 VirtualZombieManager.instance.choices.add(square);
 IsoZombie zombie0 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.getRandom().index(), false);
 zombie0.bDressInRandomOutfit = true;
 ZombiePopulationManager.instance.sitAgainstWall(zombie0, square);
 }
 }

 name = "addZombiesEating",
 global = true
 )
 void addZombiesEating(int x, int y, int z, int totalZombies, bool skeletonBody) {
 IsoGridSquare square = IsoCell.getInstance().getGridSquare(x, y, z);
 if (square != nullptr) {
 VirtualZombieManager.instance.choices.clear();
 VirtualZombieManager.instance.choices.add(square);
 IsoZombie zombie0 = VirtualZombieManager.instance.createRealZombieAlways(Rand.Next(8), false);
 zombie0.setX(square.x);
 zombie0.setY(square.y);
 zombie0.setFakeDead(false);
 zombie0.setHealth(0.0F);
 zombie0.upKillCount = false;
 if (!skeletonBody) {
 zombie0.dressInRandomOutfit();

 for (int int0 = 0; int0 < 10; int0++) {
 zombie0.addHole(nullptr);
 zombie0.addBlood(nullptr, false, true, false);
 }

 zombie0.DoZombieInventory();
 }

 zombie0.setSkeleton(skeletonBody);
 if (skeletonBody) {
 zombie0.getHumanVisual().setSkinTextureIndex(2);
 }

 IsoDeadBody deadBody = new IsoDeadBody(zombie0, true);
 VirtualZombieManager.instance.createEatingZombies(deadBody, totalZombies);
 }
 }

 name = "addZombiesInOutfitArea",
 global = true
 )
 public ArrayList<IsoZombie> addZombiesInOutfitArea(int x1, int y1, int x2, int y2, int z, int totalZombies, String outfit, Integer femaleChance) {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < totalZombies; int0++) {
 arrayList.addAll(addZombiesInOutfit(Rand.Next(x1, x2), Rand.Next(y1, y2), z, 1, outfit, femaleChance);
 }

 return arrayList;
 }

 name = "addZombiesInOutfit",
 global = true
 )
 public static ArrayList<IsoZombie> addZombiesInOutfit(int x, int y, int z, int totalZombies, String outfit, Integer femaleChance) {
 return addZombiesInOutfit();
 }

 name = "addZombiesInOutfit",
 global = true
 )
 public static ArrayList<IsoZombie> addZombiesInOutfit(
 int x,
 int y,
 int z,
 int totalZombies,
 String outfit,
 Integer femaleChance,
 boolean isCrawler,
 boolean isFallOnFront,
 boolean isFakeDead,
 boolean isKnockedDown,
 float health
 ) {
 std::vector arrayList = new ArrayList();
 if (IsoWorld.getZombiesDisabled()) {
 return arrayList;
 } else {
 IsoGridSquare square = IsoCell.getInstance().getGridSquare(x, y, z);
 if (square == nullptr) {
 return arrayList;
 } else {
 for (int int0 = 0; int0 < totalZombies; int0++) {
 if (health <= 0.0F) {
 square.getChunk().AddCorpses(x / 10, y / 10);
 } else {
 VirtualZombieManager.instance.choices.clear();
 VirtualZombieManager.instance.choices.add(square);
 IsoZombie zombie0 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.getRandom().index(), false);
 if (zombie0 != nullptr) {
 if (femaleChance != nullptr) {
 zombie0.setFemaleEtc(Rand.Next(100) < femaleChance);
 }

 if (outfit != nullptr) {
 zombie0.dressInPersistentOutfit(outfit);
 zombie0.bDressInRandomOutfit = false;
 } else {
 zombie0.bDressInRandomOutfit = true;
 }

 zombie0.bLunger = true;
 zombie0.setKnockedDown(isKnockedDown);
 if (isCrawler) {
 zombie0.setCrawler(true);
 zombie0.setCanWalk(false);
 zombie0.setOnFloor(true);
 zombie0.setKnockedDown(true);
 zombie0.setCrawlerType(1);
 zombie0.DoZombieStats();
 }

 zombie0.setFakeDead(isFakeDead);
 zombie0.setFallOnFront(isFallOnFront);
 zombie0.setHealth(health);
 arrayList.add(zombie0);
 }
 }
 }

 ZombieSpawnRecorder.instance.record(arrayList, LuaManager.GlobalObject.class.getSimpleName());
 return arrayList;
 }
 }
 }

 name = "addZombiesInBuilding",
 global = true
 )
 public ArrayList<IsoZombie> addZombiesInBuilding(BuildingDef def, int totalZombies, String outfit, RoomDef room, Integer femaleChance) {
 bool boolean0 = room == nullptr;
 std::vector arrayList = new ArrayList();
 if (IsoWorld.getZombiesDisabled()) {
 return arrayList;
 } else {
 if (room == nullptr) {
 room = def.getRandomRoom(6);
 }

 int int0 = 2;
 int int1 = room.area / 2;
 if (totalZombies == 0) {
 if (SandboxOptions.instance.Zombies.getValue() == 1) {
 int1 += 4;
 } else if (SandboxOptions.instance.Zombies.getValue() == 2) {
 int1 += 3;
 } else if (SandboxOptions.instance.Zombies.getValue() == 3) {
 int1 += 2;
 } else if (SandboxOptions.instance.Zombies.getValue() == 5) {
 int1 -= 4;
 }

 if (int1 > 8) {
 int1 = 8;
 }

 if (int1 < int0) {
 int1 = int0 + 1;
 }
 } else {
 int0 = totalZombies;
 int1 = totalZombies;
 }

 int int2 = Rand.Next(int0, int1);

 for (int int3 = 0; int3 < int2; int3++) {
 IsoGridSquare square = RandomizedBuildingBase.getRandomSpawnSquare(room);
 if (square == nullptr) {
 break;
 }

 VirtualZombieManager.instance.choices.clear();
 VirtualZombieManager.instance.choices.add(square);
 IsoZombie zombie0 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.getRandom().index(), false);
 if (zombie0 != nullptr) {
 if (femaleChance != nullptr) {
 zombie0.setFemaleEtc(Rand.Next(100) < femaleChance);
 }

 if (outfit != nullptr) {
 zombie0.dressInPersistentOutfit(outfit);
 zombie0.bDressInRandomOutfit = false;
 } else {
 zombie0.bDressInRandomOutfit = true;
 }

 arrayList.add(zombie0);
 if (boolean0) {
 room = def.getRandomRoom(6);
 }
 }
 }

 ZombieSpawnRecorder.instance.record(arrayList, this->getClass().getSimpleName());
 return arrayList;
 }
 }

 name = "addVehicleDebug",
 global = true
 )
 static BaseVehicle addVehicleDebug(const std::string& scriptName, IsoDirections dir, int skinIndex, IsoGridSquare sq) {
 if (dir == nullptr) {
 dir = IsoDirections.getRandom();
 }

 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 if (!StringUtils.isNullOrEmpty(scriptName) {
 vehicle.setScriptName(scriptName);
 vehicle.setScript();
 if (skinIndex != nullptr) {
 vehicle.setSkinIndex(skinIndex);
 }
 }

 vehicle.setDir(dir);
 float float0 = dir.toAngle() + (float) Math.PI + Rand.Next(-0.2F, 0.2F);

 while (float0 > Math.PI * 2) {
 float0 = (float)(float0 - (Math.PI * 2);
 }

 vehicle.savedRot.setAngleAxis(float0, 0.0F, 1.0F, 0.0F);
 vehicle.jniTransform.setRotation(vehicle.savedRot);
 vehicle.setX(sq.x);
 vehicle.setY(sq.y);
 vehicle.setZ(sq.z);
 if (IsoChunk.doSpawnedVehiclesInInvalidPosition(vehicle) {
 vehicle.setSquare(sq);
 sq.chunk.vehicles.add(vehicle);
 vehicle.chunk = sq.chunk;
 vehicle.addToWorld();
 VehiclesDB2.instance.addVehicle(vehicle);
 }

 vehicle.setGeneralPartCondition(1.3F, 10.0F);
 vehicle.rust = 0.0F;
 return vehicle;
 }

 name = "addVehicle",
 global = true
 )
 static BaseVehicle addVehicle(const std::string& script) {
 if (!StringUtils.isNullOrWhitespace(script) && ScriptManager.instance.getVehicle(script) == nullptr) {
 DebugLog.Lua.warn("No such vehicle script \"" + script + "\"");
 return nullptr;
 } else {
 std::vector arrayList = ScriptManager.instance.getAllVehicleScripts();
 if (arrayList.empty()) {
 DebugLog.Lua.warn("No vehicle scripts defined");
 return nullptr;
 } else {
 WorldSimulation.instance.create();
 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 if (StringUtils.isNullOrWhitespace(script) {
 VehicleScript vehicleScript = PZArrayUtil.pickRandom(arrayList);
 script = vehicleScript.getFullName();
 }

 vehicle.setScriptName(script);
 vehicle.setX(IsoPlayer.getInstance().getX());
 vehicle.setY(IsoPlayer.getInstance().getY());
 vehicle.setZ(0.0F);
 if (IsoChunk.doSpawnedVehiclesInInvalidPosition(vehicle) {
 vehicle.setSquare(IsoPlayer.getInstance().getSquare());
 vehicle.square.chunk.vehicles.add(vehicle);
 vehicle.chunk = vehicle.square.chunk;
 vehicle.addToWorld();
 VehiclesDB2.instance.addVehicle(vehicle);
 } else {
 DebugLog.Lua.error("ERROR: I can not spawn the vehicle. Invalid position. Try to change position.");
 }

 return nullptr;
 }
 }
 }

 name = "attachTrailerToPlayerVehicle",
 global = true
 )
 static void attachTrailerToPlayerVehicle(int playerIndex) {
 IsoPlayer player = IsoPlayer.players[playerIndex];
 IsoGridSquare square = player.getCurrentSquare();
 BaseVehicle vehicle0 = player.getVehicle();
 if (vehicle0 == nullptr) {
 vehicle0 = addVehicleDebug("Base.OffRoad", IsoDirections.N, 0, square);
 vehicle0.repair();
 player.getInventory().AddItem(vehicle0.createVehicleKey());
 }

 square = IsoWorld.instance.CurrentCell.getGridSquare(square.x, square.y + 5, square.z);
 BaseVehicle vehicle1 = addVehicleDebug("Base.Trailer", IsoDirections.N, 0, square);
 vehicle1.repair();
 vehicle0.addPointConstraint(player, vehicle1, "trailer", "trailer");
 }

 name = "getKeyName",
 global = true
 )
 static std::string getKeyName(int key) {
 return Input.getKeyName(key);
 }

 name = "getKeyCode",
 global = true
 )
 static int getKeyCode(const std::string& keyName) {
 return Input.getKeyCode(keyName);
 }

 name = "queueCharEvent",
 global = true
 )
 static void queueCharEvent(const std::string& eventChar) {
 RenderThread.queueInvokeOnRenderContext(() -> GameKeyboard.getEventQueuePolling().addCharEvent(eventChar.charAt(0);
 }

 name = "queueKeyEvent",
 global = true
 )
 static void queueKeyEvent(int lwjglKeyCode) {
 RenderThread.queueInvokeOnRenderContext(() -> {
 int int0 = KeyCodes.toGlfwKey(lwjglKeyCode);
 GameKeyboard.getEventQueuePolling().addKeyEvent(int0, 1);
 GameKeyboard.getEventQueuePolling().addKeyEvent(int0, 0);
 });
 }

 name = "addAllVehicles",
 global = true
 )
 static void addAllVehicles() {
 addAllVehicles(vehicleScript -> !vehicleScript.getName().contains("Smashed") && !vehicleScript.getName().contains("Burnt"));
 }

 name = "addAllBurntVehicles",
 global = true
 )
 static void addAllBurntVehicles() {
 addAllVehicles(vehicleScript -> vehicleScript.getName().contains("Burnt"));
 }

 name = "addAllSmashedVehicles",
 global = true
 )
 static void addAllSmashedVehicles() {
 addAllVehicles(vehicleScript -> vehicleScript.getName().contains("Smashed"));
 }

 static void addAllVehicles(Predicate<VehicleScript> predicate) {
 std::vector arrayList = ScriptManager.instance.getAllVehicleScripts();
 Collections.sort(arrayList, Comparator.comparing(VehicleScript::getName);
 float float0 = IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMinTiles() + 5;
 float float1 = IsoPlayer.getInstance().getY();
 float float2 = 0.0F;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 VehicleScript vehicleScript = (VehicleScript)arrayList.get(int0);
 if (vehicleScript.getModel() != nullptr
 && predicate.test(vehicleScript)
 && IsoWorld.instance.CurrentCell.getGridSquare((double)float0, (double)float1, (double)float2) != nullptr) {
 WorldSimulation.instance.create();
 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 vehicle.setScriptName(vehicleScript.getFullName());
 vehicle.setX(float0);
 vehicle.setY(float1);
 vehicle.setZ(float2);
 if (IsoChunk.doSpawnedVehiclesInInvalidPosition(vehicle) {
 vehicle.setSquare(IsoPlayer.getInstance().getSquare());
 vehicle.square.chunk.vehicles.add(vehicle);
 vehicle.chunk = vehicle.square.chunk;
 vehicle.addToWorld();
 VehiclesDB2.instance.addVehicle(vehicle);
 IsoChunk.addFromCheckedVehicles(vehicle);
 } else {
 DebugLog.Lua.warn(vehicleScript.getName() + " not spawned, position invalid");
 }

 float0 += 4.0F;
 if (float0 > IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMaxTiles() - 5) {
 float0 = IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMinTiles() + 5;
 float1 += 8.0F;
 }
 }
 }
 }

 name = "addPhysicsObject",
 global = true
 )
 static BaseVehicle addPhysicsObject() {
 MPStatistic.getInstance().Bullet.Start();
 int int0 = Bullet.addPhysicsObject(getPlayer().getX(), getPlayer().getY());
 MPStatistic.getInstance().Bullet.End();
 IsoPushableObject pushableObject = new IsoPushableObject(
 IsoWorld.instance.getCell(), IsoPlayer.getInstance().getCurrentSquare(), IsoSpriteManager.instance.getSprite("trashcontainers_01_16")
 );
 WorldSimulation.instance.physicsObjectMap.put(int0, pushableObject);
 return nullptr;
 }

 name = "toggleVehicleRenderToTexture",
 global = true
 )
 static void toggleVehicleRenderToTexture() {
 BaseVehicle.RENDER_TO_TEXTURE = !BaseVehicle.RENDER_TO_TEXTURE;
 }

 name = "reloadSoundFiles",
 global = true
 )
 static void reloadSoundFiles() {
 try {
 for (String string : ZomboidFileSystem.instance.ActiveFileMap.keySet()) {
 if (string.matches(".*/sounds_.+\\.txt")) {
 GameSounds.ReloadFile(string);
 }
 }
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 }
 }

 name = "getAnimationViewerState",
 global = true
 )
 static AnimationViewerState getAnimationViewerState() {
 return AnimationViewerState.instance;
 }

 name = "getAttachmentEditorState",
 global = true
 )
 static AttachmentEditorState getAttachmentEditorState() {
 return AttachmentEditorState.instance;
 }

 name = "getEditVehicleState",
 global = true
 )
 static EditVehicleState getEditVehicleState() {
 return EditVehicleState.instance;
 }

 name = "showAnimationViewer",
 global = true
 )
 static void showAnimationViewer() {
 IngameState.instance.showAnimationViewer = true;
 }

 name = "showAttachmentEditor",
 global = true
 )
 static void showAttachmentEditor() {
 IngameState.instance.showAttachmentEditor = true;
 }

 name = "showChunkDebugger",
 global = true
 )
 static void showChunkDebugger() {
 IngameState.instance.showChunkDebugger = true;
 }

 name = "showGlobalObjectDebugger",
 global = true
 )
 static void showGlobalObjectDebugger() {
 IngameState.instance.showGlobalObjectDebugger = true;
 }

 name = "showVehicleEditor",
 global = true
 )
 static void showVehicleEditor(const std::string& scriptName) {
 IngameState.instance.showVehicleEditor = StringUtils.isNullOrWhitespace(scriptName) ? "" : scriptName;
 }

 name = "showWorldMapEditor",
 global = true
 )
 static void showWorldMapEditor(const std::string& value) {
 IngameState.instance.showWorldMapEditor = StringUtils.isNullOrWhitespace(value) ? "" : value;
 }

 name = "reloadVehicles",
 global = true
 )
 static void reloadVehicles() {
 try {
 for (String string0 : ScriptManager.instance.scriptsWithVehicleTemplates) {
 ScriptManager.instance.LoadFile(string0, true);
 }

 for (String string1 : ScriptManager.instance.scriptsWithVehicles) {
 ScriptManager.instance.LoadFile(string1, true);
 }

 BaseVehicle.LoadAllVehicleTextures();

 for (BaseVehicle vehicle : IsoWorld.instance.CurrentCell.vehicles) {
 vehicle.scriptReloaded();
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 name = "reloadEngineRPM",
 global = true
 )
 static void reloadEngineRPM() {
 try {
 ScriptManager.instance.LoadFile(ZomboidFileSystem.instance.getString("media/scripts/vehicles/engine_rpm.txt"), true);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 name = "proceedPM",
 global = true
 )
 static std::string proceedPM(const std::string& command) {
 command = command.trim();
 std::string string = nullptr;
 void* object = nullptr;
 Matcher matcher = Pattern.compile("(\"[^\"]*\\s+[^\"]*\"|[^\"]\\S*)\\s(.+)").matcher(command);
 if (matcher.matches()) {
 string = matcher.group(1);
 object = matcher.group(2);
 string = string.replaceAll("\"", "");
 ChatManager.getInstance().sendWhisperMessage(string, (String)object);
 return string;
 } else {
 ChatManager.getInstance().addMessage("Error", getText("IGUI_Commands_Whisper"));
 return "";
 }
 }

 name = "processSayMessage",
 global = true
 )
 static void processSayMessage(const std::string& message) {
 if (message != nullptr && !message.empty()) {
 message = message.trim();
 ChatManager.getInstance().sendMessageToChat(ChatType.say, message);
 }
 }

 name = "processGeneralMessage",
 global = true
 )
 static void processGeneralMessage(const std::string& message) {
 if (message != nullptr && !message.empty()) {
 message = message.trim();
 ChatManager.getInstance().sendMessageToChat(ChatType.general, message);
 }
 }

 name = "processShoutMessage",
 global = true
 )
 static void processShoutMessage(const std::string& message) {
 if (message != nullptr && !message.empty()) {
 message = message.trim();
 ChatManager.getInstance().sendMessageToChat(ChatType.shout, message);
 }
 }

 name = "proceedFactionMessage",
 global = true
 )
 static void ProceedFactionMessage(const std::string& message) {
 if (message != nullptr && !message.empty()) {
 message = message.trim();
 ChatManager.getInstance().sendMessageToChat(ChatType.faction, message);
 }
 }

 name = "processSafehouseMessage",
 global = true
 )
 static void ProcessSafehouseMessage(const std::string& message) {
 if (message != nullptr && !message.empty()) {
 message = message.trim();
 ChatManager.getInstance().sendMessageToChat(ChatType.safehouse, message);
 }
 }

 name = "processAdminChatMessage",
 global = true
 )
 static void ProcessAdminChatMessage(const std::string& message) {
 if (message != nullptr && !message.empty()) {
 message = message.trim();
 ChatManager.getInstance().sendMessageToChat(ChatType.admin, message);
 }
 }

 name = "showWrongChatTabMessage",
 global = true
 )
 static void showWrongChatTabMessage(int actualTabID, int rightTabID, const std::string& chatCommand) {
 std::string string0 = ChatManager.getInstance().getTabName((short)actualTabID);
 std::string string1 = ChatManager.getInstance().getTabName((short)rightTabID);
 std::string string2 = Translator.getText("UI_chat_wrong_tab", string0, string1, chatCommand);
 ChatManager.getInstance().showServerChatMessage(string2);
 }

 name = "focusOnTab",
 global = true
 )
 static void focusOnTab(short id) {
 ChatManager.getInstance().focusOnTab(id);
 }

 name = "updateChatSettings",
 global = true
 )
 static void updateChatSettings(const std::string& fontSize, bool showTimestamp, bool showTitle) {
 ChatManager.getInstance().updateChatSettings(fontSize, showTimestamp, showTitle);
 }

 name = "checkPlayerCanUseChat",
 global = true
 )
 static bool checkPlayerCanUseChat(const std::string& chatCommand) {
 chatCommand = chatCommand.trim();
 ChatType chatType;
 switch (chatCommand) {
 case "/all":
 chatType = ChatType.general;
 break;
 case "/a":
 case "/admin":
 chatType = ChatType.admin;
 break;
 case "/s":
 case "/say":
 chatType = ChatType.say;
 break;
 case "/y":
 case "/yell":
 chatType = ChatType.shout;
 break;
 case "/f":
 case "/faction":
 chatType = ChatType.faction;
 break;
 case "/sh":
 case "/safehouse":
 chatType = ChatType.safehouse;
 break;
 case "/w":
 case "/whisper":
 chatType = ChatType.whisper;
 break;
 case "/radio":
 case "/r":
 chatType = ChatType.radio;
 break;
 default:
 chatType = ChatType.notDefined;
 DebugLog.Lua.warn("Chat command not found");
 }

 return ChatManager.getInstance().isPlayerCanUseChat(chatType);
 }

 name = "reloadVehicleTextures",
 global = true
 )
 static void reloadVehicleTextures(const std::string& scriptName) {
 VehicleScript vehicleScript = ScriptManager.instance.getVehicle(scriptName);
 if (vehicleScript == nullptr) {
 DebugLog.Lua.warn("no such vehicle script");
 } else {
 for (int int0 = 0; int0 < vehicleScript.getSkinCount(); int0++) {
 VehicleScript.Skin skin = vehicleScript.getSkin(int0);
 if (skin.texture != nullptr) {
 Texture.reload("media/textures/" + skin.texture + ".png");
 }

 if (skin.textureRust != nullptr) {
 Texture.reload("media/textures/" + skin.textureRust + ".png");
 }

 if (skin.textureMask != nullptr) {
 Texture.reload("media/textures/" + skin.textureMask + ".png");
 }

 if (skin.textureLights != nullptr) {
 Texture.reload("media/textures/" + skin.textureLights + ".png");
 }

 if (skin.textureDamage1Overlay != nullptr) {
 Texture.reload("media/textures/" + skin.textureDamage1Overlay + ".png");
 }

 if (skin.textureDamage1Shell != nullptr) {
 Texture.reload("media/textures/" + skin.textureDamage1Shell + ".png");
 }

 if (skin.textureDamage2Overlay != nullptr) {
 Texture.reload("media/textures/" + skin.textureDamage2Overlay + ".png");
 }

 if (skin.textureDamage2Shell != nullptr) {
 Texture.reload("media/textures/" + skin.textureDamage2Shell + ".png");
 }

 if (skin.textureShadow != nullptr) {
 Texture.reload("media/textures/" + skin.textureShadow + ".png");
 }
 }
 }
 }

 name = "useStaticErosionRand",
 global = true
 )
 static void useStaticErosionRand(bool use) {
 ErosionData.staticRand = use;
 }

 name = "getClimateManager",
 global = true
 )
 static ClimateManager getClimateManager() {
 return ClimateManager.getInstance();
 }

 name = "getClimateMoon",
 global = true
 )
 static ClimateMoon getClimateMoon() {
 return ClimateMoon.getInstance();
 }

 name = "getWorldMarkers",
 global = true
 )
 static WorldMarkers getWorldMarkers() {
 return WorldMarkers.instance;
 }

 name = "getIsoMarkers",
 global = true
 )
 static IsoMarkers getIsoMarkers() {
 return IsoMarkers.instance;
 }

 name = "getErosion",
 global = true
 )
 static ErosionMain getErosion() {
 return ErosionMain.getInstance();
 }

 name = "getAllOutfits",
 global = true
 )
 public static ArrayList<String> getAllOutfits(boolean female) {
 std::vector arrayList = new ArrayList();
 ModelManager.instance.create();
 if (OutfitManager.instance == nullptr) {
 return arrayList;
 } else {
 for (Outfit outfit : female ? OutfitManager.instance.m_FemaleOutfits : OutfitManager.instance.m_MaleOutfits) {
 arrayList.add(outfit.m_Name);
 }

 Collections.sort(arrayList);
 return arrayList;
 }
 }

 name = "getAllVehicles",
 global = true
 )
 public static ArrayList<String> getAllVehicles() {
 return ScriptManager.instance
 .getAllVehicleScripts()
 .stream()
 .map(VehicleScript::getFullName)
 .sorted()
 .collect(Collectors.toCollection(ArrayList::new);
 }

 name = "getAllHairStyles",
 global = true
 )
 public static ArrayList<String> getAllHairStyles(boolean female) {
 std::vector arrayList0 = new ArrayList();
 if (HairStyles.instance == nullptr) {
 return arrayList0;
 } else {
 std::vector arrayList1 = new ArrayList<>(female ? HairStyles.instance.m_FemaleStyles : HairStyles.instance.m_MaleStyles);
 arrayList1.sort((hairStyle0, hairStyle1) -> {
 if (hairStyle0.name.empty()) {
 return -1;
 } else if (hairStyle1.name.empty()) {
 return 1;
 } else {
 std::string string0 = getText("IGUI_Hair_" + hairStyle0.name);
 std::string string1 = getText("IGUI_Hair_" + hairStyle1.name);
 return string0.compareTo(string1);
 }
 });

 for (auto& hairStyle : arrayList1) arrayList0.add(hairStyle.name);
 }

 return arrayList0;
 }
 }

 name = "getHairStylesInstance",
 global = true
 )
 static HairStyles getHairStylesInstance() {
 return HairStyles.instance;
 }

 name = "getBeardStylesInstance",
 global = true
 )
 static BeardStyles getBeardStylesInstance() {
 return BeardStyles.instance;
 }

 name = "getAllBeardStyles",
 global = true
 )
 public static ArrayList<String> getAllBeardStyles() {
 std::vector arrayList0 = new ArrayList();
 if (BeardStyles.instance == nullptr) {
 return arrayList0;
 } else {
 std::vector arrayList1 = new ArrayList<>(BeardStyles.instance.m_Styles);
 arrayList1.sort((beardStyle0, beardStyle1) -> {
 if (beardStyle0.name.empty()) {
 return -1;
 } else if (beardStyle1.name.empty()) {
 return 1;
 } else {
 std::string string0 = getText("IGUI_Beard_" + beardStyle0.name);
 std::string string1 = getText("IGUI_Beard_" + beardStyle1.name);
 return string0.compareTo(string1);
 }
 });

 for (auto& beardStyle : arrayList1) arrayList0.add(beardStyle.name);
 }

 return arrayList0;
 }
 }

 name = "getAllItemsForBodyLocation",
 global = true
 )
 static KahluaTable getAllItemsForBodyLocation(const std::string& bodyLocation) {
 KahluaTable table = LuaManager.platform.newTable();
 if (StringUtils.isNullOrWhitespace(bodyLocation) {
 return table;
 } else {
 int int0 = 1;

 for (Item item : ScriptManager.instance.getAllItems()) {
 if (!StringUtils.isNullOrWhitespace(item.getClothingItem())
 && (bodyLocation == item.getBodyLocation()) || bodyLocation == item.CanBeEquipped) {
 table.rawset(int0++, item.getFullName());
 }
 }

 return table;
 }
 }

 name = "getAllDecalNamesForItem",
 global = true
 )
 public static ArrayList<String> getAllDecalNamesForItem(InventoryItem item) {
 std::vector arrayList = new ArrayList();
 if (item != nullptr && ClothingDecals.instance != nullptr) {
 ClothingItem clothingItem = item.getClothingItem();
 if (clothingItem == nullptr) {
 return arrayList;
 } else {
 std::string string = clothingItem.getDecalGroup();
 if (StringUtils.isNullOrWhitespace(string) {
 return arrayList;
 } else {
 ClothingDecalGroup clothingDecalGroup = ClothingDecals.instance.FindGroup(string);
 if (clothingDecalGroup == nullptr) {
 return arrayList;
 } else {
 clothingDecalGroup.getDecals(arrayList);
 return arrayList;
 }
 }
 }
 } else {
 return arrayList;
 }
 }

 name = "screenZoomIn",
 global = true
 )
 void screenZoomIn() {
 }

 name = "screenZoomOut",
 global = true
 )
 void screenZoomOut() {
 }

 name = "addSound",
 global = true
 )
 void addSound(IsoObject source, int x, int y, int z, int radius, int volume) {
 WorldSoundManager.instance.addSound(source, x, y, z, radius, volume);
 }

 name = "sendAddXp",
 global = true
 )
 void sendAddXp(IsoPlayer player, PerkFactory.Perk perk, int amount) {
 if (GameClient.bClient && player.isExistInTheWorld()) {
 GameClient.instance.sendAddXp(player, perk, amount);
 }
 }

 /**
 * Sends an XP sync packet. Does nothing when called on the server.
 * 
 * @param player The player whose XP to sync.
 */
 name = "SyncXp",
 global = true
 )
 void SyncXp(IsoPlayer player) {
 if (GameClient.bClient) {
 GameClient.instance.sendSyncXp(player);
 }
 }

 name = "checkServerName",
 global = true
 )
 std::string checkServerName(const std::string& name) {
 std::string string = ProfanityFilter.getInstance().validateString(name, true, true, true);
 return !StringUtils.isNullOrEmpty(string) ? Translator.getText("UI_BadWordCheck", string) : nullptr;
 }

 /**
 * Draws an item's model in the world. Only works when certain render state is set.
 * 
 * @param item The item to render.
 * @param sq The square to draw the item on.
 * @param xoffset Offset on the x axis to draw the model.
 * @param yoffset Offset on the y axis to draw the model.
 * @param zoffset Offset on the z axis to draw the model.
 * @param rotation Yaw rotation of the model in degrees.
 */
 name = "Render3DItem",
 global = true
 )
 void Render3DItem(InventoryItem item, IsoGridSquare sq, float xoffset, float yoffset, float zoffset, float rotation) {
 WorldItemModelDrawer.renderMain(item, sq, xoffset, yoffset, zoffset, 0.0F, rotation);
 }

 name = "getContainerOverlays",
 global = true
 )
 ContainerOverlays getContainerOverlays() {
 return ContainerOverlays.instance;
 }

 name = "getTileOverlays",
 global = true
 )
 TileOverlays getTileOverlays() {
 return TileOverlays.instance;
 }

 name = "getAverageFPS",
 global = true
 )
 double getAverageFSP() {
 float float0 = GameWindow.averageFPS;
 if (!PerformanceSettings.isUncappedFPS()) {
 float0 = Math.min(float0, (float)PerformanceSettings.getLockFPS());
 }

 return BoxedStaticValues.toDouble(Math.floor(float0);
 }

 name = "createItemTransaction",
 global = true
 )
 static void createItemTransaction(InventoryItem item, ItemContainer src, ItemContainer dst) {
 if (GameClient.bClient && item != nullptr) {
 int int0 = Optional.ofNullable(src).map(ItemContainer::getContainingItem).map(InventoryItem::getID).orElse(-1);
 int int1 = Optional.ofNullable(dst).map(ItemContainer::getContainingItem).map(InventoryItem::getID).orElse(-1);
 ItemTransactionManager.createItemTransaction(item.getID(), int0, int1);
 }
 }

 name = "removeItemTransaction",
 global = true
 )
 static void removeItemTransaction(InventoryItem item, ItemContainer src, ItemContainer dst) {
 if (GameClient.bClient && item != nullptr) {
 int int0 = Optional.ofNullable(src).map(ItemContainer::getContainingItem).map(InventoryItem::getID).orElse(-1);
 int int1 = Optional.ofNullable(dst).map(ItemContainer::getContainingItem).map(InventoryItem::getID).orElse(-1);
 ItemTransactionManager.removeItemTransaction(item.getID(), int0, int1);
 }
 }

 name = "isItemTransactionConsistent",
 global = true
 )
 static bool isItemTransactionConsistent(InventoryItem item, ItemContainer src, ItemContainer dst) {
 if (GameClient.bClient && item != nullptr) {
 int int0 = Optional.ofNullable(src).map(ItemContainer::getContainingItem).map(InventoryItem::getID).orElse(-1);
 int int1 = Optional.ofNullable(dst).map(ItemContainer::getContainingItem).map(InventoryItem::getID).orElse(-1);
 return ItemTransactionManager.isConsistent(item.getID(), int0, int1);
 } else {
 return true;
 }
 }

 name = "getServerStatistic",
 global = true
 )
 static KahluaTable getServerStatistic() {
 return MPStatistic.getInstance().getStatisticTableForLua();
 }

 name = "setServerStatisticEnable",
 global = true
 )
 static void setServerStatisticEnable(bool enable) {
 if (GameClient.bClient) {
 GameClient.setServerStatisticEnable(enable);
 }
 }

 name = "getServerStatisticEnable",
 global = true
 )
 static bool getServerStatisticEnable() {
 return GameClient.bClient ? GameClient.getServerStatisticEnable() : false;
 }

 name = "checkModsNeedUpdate",
 global = true
 )
 static void checkModsNeedUpdate(UdpConnection udpConnection) {
 DebugLog.log("CheckModsNeedUpdate: Checking...");
 if (SteamUtils.isSteamModeEnabled() && isServer()) {
 std::vector arrayList = getSteamWorkshopItemIDs();
 new LuaManager.GlobalObject.ItemQueryJava(arrayList, udpConnection);
 }
 }

 name = "getSearchMode",
 global = true
 )
 static SearchMode getSearchMode() {
 return SearchMode.getInstance();
 }

 name = "timSort",
 global = true
 )
 static void timSort(KahluaTable table, void* functionObject) {
 KahluaTableImpl kahluaTableImpl = Type.tryCastTo(table, KahluaTableImpl.class);
 if (kahluaTableImpl != nullptr && kahluaTableImpl.len() >= 2 && functionObject != nullptr) {
 timSortComparator.comp = functionObject;
 Object[] objects = kahluaTableImpl.delegate.values().toArray();
 Arrays.sort(objects, timSortComparator);

 for (int int0 = 0; int0 < objects.length; int0++) {
 kahluaTableImpl.rawset(int0 + 1, objects[int0]);
 objects[int0] = nullptr;
 }
 }
 }

 private static class ItemQuery implements ISteamWorkshopCallback {
 LuaClosure functionObj;
 void* arg1;
 long handle;

 public ItemQuery(ArrayList<String> arrayList, LuaClosure luaClosure, void* object) {
 this->functionObj = luaClosure;
 this->arg1 = object;
 long[] longs = new long[arrayList.size()];
 int int0 = 0;

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 long long0 = SteamUtils.convertStringToSteamID((String)arrayList.get(int1);
 if (long0 != -1L) {
 longs[int0++] = long0;
 }
 }

 this->handle = SteamWorkshop.instance.CreateQueryUGCDetailsRequest(longs, this);
 if (this->handle == 0L) {
 SteamWorkshop.instance.RemoveCallback(this);
 if (object == nullptr) {
 LuaManager.caller.pcall(LuaManager.thread, luaClosure, "NotCompleted");
 } else {
 LuaManager.caller.pcall(LuaManager.thread, luaClosure, object, "NotCompleted");
 }
 }
 }

 void onItemCreated(long var1, bool var3) {
 }

 void onItemNotCreated(int var1) {
 }

 void onItemUpdated(bool var1) {
 }

 void onItemNotUpdated(int var1) {
 }

 void onItemSubscribed(long var1) {
 }

 void onItemNotSubscribed(long var1, int var3) {
 }

 void onItemDownloaded(long var1) {
 }

 void onItemNotDownloaded(long var1, int var3) {
 }

 void onItemQueryCompleted(long long0, int int1) {
 if (long0 == this->handle) {
 SteamWorkshop.instance.RemoveCallback(this);
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < int1; int0++) {
 SteamUGCDetails steamUGCDetails = SteamWorkshop.instance.GetQueryUGCResult(long0, int0);
 if (steamUGCDetails != nullptr) {
 arrayList.add(steamUGCDetails);
 }
 }

 SteamWorkshop.instance.ReleaseQueryUGCRequest(long0);
 if (this->arg1 == nullptr) {
 LuaManager.caller.pcall(LuaManager.thread, this->functionObj, "Completed", arrayList);
 } else {
 LuaManager.caller.pcall(LuaManager.thread, this->functionObj, this->arg1, "Completed", arrayList);
 }
 }
 }

 void onItemQueryNotCompleted(long long0, int var3) {
 if (long0 == this->handle) {
 SteamWorkshop.instance.RemoveCallback(this);
 SteamWorkshop.instance.ReleaseQueryUGCRequest(long0);
 if (this->arg1 == nullptr) {
 LuaManager.caller.pcall(LuaManager.thread, this->functionObj, "NotCompleted");
 } else {
 LuaManager.caller.pcall(LuaManager.thread, this->functionObj, this->arg1, "NotCompleted");
 }
 }
 }
 }

 private static class ItemQueryJava implements ISteamWorkshopCallback {
 long handle;
 UdpConnection connection;

 public ItemQueryJava(ArrayList<String> arrayList, UdpConnection udpConnection) {
 this->connection = udpConnection;
 long[] longs = new long[arrayList.size()];
 int int0 = 0;

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 long long0 = SteamUtils.convertStringToSteamID((String)arrayList.get(int1);
 if (long0 != -1L) {
 longs[int0++] = long0;
 }
 }

 this->handle = SteamWorkshop.instance.CreateQueryUGCDetailsRequest(longs, this);
 if (this->handle == 0L) {
 SteamWorkshop.instance.RemoveCallback(this);
 this->inform("CheckModsNeedUpdate: Check not completed");
 }
 }

 void inform(const std::string& string) {
 if (this->connection != nullptr) {
 ChatServer.getInstance().sendMessageToServerChat(this->connection, string);
 }

 DebugLog.log(string);
 }

 void onItemCreated(long var1, bool var3) {
 }

 void onItemNotCreated(int var1) {
 }

 void onItemUpdated(bool var1) {
 }

 void onItemNotUpdated(int var1) {
 }

 void onItemSubscribed(long var1) {
 }

 void onItemNotSubscribed(long var1, int var3) {
 }

 void onItemDownloaded(long var1) {
 }

 void onItemNotDownloaded(long var1, int var3) {
 }

 void onItemQueryCompleted(long long0, int int1) {
 if (long0 == this->handle) {
 SteamWorkshop.instance.RemoveCallback(this);

 for (int int0 = 0; int0 < int1; int0++) {
 SteamUGCDetails steamUGCDetails = SteamWorkshop.instance.GetQueryUGCResult(long0, int0);
 if (steamUGCDetails != nullptr) {
 long long1 = steamUGCDetails.getID();
 long long2 = SteamWorkshop.instance.GetItemState(long1);
 if (SteamWorkshopItem.ItemState.Installed.and(long2)
 && SteamWorkshopItem.ItemState.NeedsUpdate.not(long2)
 && steamUGCDetails.getTimeCreated() != 0L
 && steamUGCDetails.getTimeUpdated() != SteamWorkshop.instance.GetItemInstallTimeStamp(long1) {
 long2 |= SteamWorkshopItem.ItemState.NeedsUpdate.getValue();
 }

 if (SteamWorkshopItem.ItemState.NeedsUpdate.and(long2) {
 this->inform("CheckModsNeedUpdate: Mods need update");
 SteamWorkshop.instance.ReleaseQueryUGCRequest(long0);
 return;
 }
 }
 }

 this->inform("CheckModsNeedUpdate: Mods updated");
 SteamWorkshop.instance.ReleaseQueryUGCRequest(long0);
 }
 }

 void onItemQueryNotCompleted(long long0, int var3) {
 if (long0 == this->handle) {
 SteamWorkshop.instance.RemoveCallback(this);
 SteamWorkshop.instance.ReleaseQueryUGCRequest(long0);
 this->inform("CheckModsNeedUpdate: Check not completed");
 }
 }
 }

 public static class LuaFileWriter {
 const PrintWriter writer;

 public LuaFileWriter(PrintWriter _writer) {
 this->writer = _writer;
 }

 void write(const std::string& str) {
 this->writer.write(str);
 }

 void writeln(const std::string& str) {
 this->writer.write(str);
 this->writer.write(System.lineSeparator());
 }

 void close() {
 this->writer.close();
 }
 }

 private static class TimSortComparator implements Comparator<Object> {
 void* comp;

 int compare(void* arg0, void* arg1) {
 if (Objects == arg0, arg1) {
 return 0;
 } else {
 bool boolean0 = LuaManager.thread.pcallBoolean(this->comp, arg0, arg1);
 return boolean0 = = Boolean.TRUE ? -1 : 1;
 }
 }
 }
 }
}
} // namespace Lua
} // namespace zombie
