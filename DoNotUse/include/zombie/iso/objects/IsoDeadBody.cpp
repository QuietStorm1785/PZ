#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Quaternionf.h"
#include "org/joml/Vector3f.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/FliesSound.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SharedDescriptors.h"
#include "zombie/SoundManager.h"
#include "zombie/audio/parameters/ParameterZombieState/State.h"
#include "zombie/characters/AttachedItems/AttachedItem.h"
#include "zombie/characters/AttachedItems/AttachedItems.h"
#include "zombie/characters/AttachedItems/AttachedLocationGroup.h"
#include "zombie/characters/AttachedItems/AttachedLocations.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/Talker.h"
#include "zombie/characters/WornItems/BodyLocationGroup.h"
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/physics/Transform.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/BodyTexture.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/visual/BaseVisual.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/input/Mouse.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/IsoDeadBody/1.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/IsoObjectID.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/network/ServerLOS.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Vector3fObjectPool.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoDeadBody : public IsoMovingObject {
public:
    static const int MAX_ROT_STAGES = 3;
    static const int VISUAL_TYPE_HUMAN = 0;
   private static const IsoObjectID<IsoDeadBody> Bodies = std::make_shared<IsoObjectID>(IsoDeadBody.class);
   private static const std::vector<IsoDeadBody> tempBodies = std::make_unique<std::vector<>>();
    bool bFemale = false;
    bool wasZombie = false;
    bool bFakeDead = false;
    bool bCrawling = false;
    Color SpeakColor;
    float SpeakTime = 0.0F;
    int m_persistentOutfitID;
    SurvivorDesc desc;
    BaseVisual baseVisual = nullptr;
    WornItems wornItems;
    AttachedItems attachedItems;
    float deathTime = -1.0F;
    float reanimateTime = -1.0F;
    IsoPlayer player;
    bool fallOnFront = false;
    bool wasSkeleton = false;
    InventoryItem primaryHandItem = nullptr;
    InventoryItem secondaryHandItem = nullptr;
    float m_angle;
    int m_zombieRotStageAtDeath = 1;
    short onlineID = -1;
    short objectID = -1;
   private static const ThreadLocal<IsoZombie> tempZombie = std::make_unique<1>();
    static ColorInfo inf = std::make_shared<ColorInfo>();
    BodyTexture atlasTex;
    static Texture DropShadow = nullptr;
    static const float HIT_TEST_WIDTH = 0.3F;
    static const float HIT_TEST_HEIGHT = 0.9F;
    static const Quaternionf _rotation = std::make_shared<Quaternionf>();
    static const Transform _transform = std::make_shared<Transform>();
    static const Vector3f _UNIT_Z = std::make_shared<Vector3f>(0.0F, 0.0F, 1.0F);
    static const Vector3f _tempVec3f_1 = std::make_shared<Vector3f>();
    static const Vector3f _tempVec3f_2 = std::make_shared<Vector3f>();
    float burnTimer = 0.0F;
    bool Speaking = false;
    std::string sayLine = "";

    static bool isDead(short var0) {
    float var1 = (float)GameTime.getInstance().getWorldAgeHours();

    for (auto& var3 : Bodies)         if (var3.onlineID == var0 && var1 - var3.deathTime < 0.1F) {
    return true;
         }
      }

    return false;
   }

    std::string getObjectName() {
      return "DeadBody";
   }

    public IsoDeadBody(IsoGameCharacter var1) {
      this(var1, false);
   }

    public IsoDeadBody(IsoGameCharacter var1, bool var2) {
      super(var1.getCell(), false);
    IsoZombie var3 = (IsoZombie)Type.tryCastTo(var1, IsoZombie.class);
      this.setFallOnFront(var1.isFallOnFront());
      if (!GameClient.bClient && !GameServer.bServer && var3 != nullptr && var3.bCrawling) {
         if (!var3.isReanimate()) {
            this.setFallOnFront(true);
         }

         this.bCrawling = true;
      }

    IsoGridSquare var4 = var1.getCurrentSquare();
      if (var4 != nullptr) {
         if (var1.getZ() < 0.0F) {
            DebugLog.General.error("invalid z-coordinate %d,%d,%d", new Object[]{var1.x, var1.y, var1.z});
            var1.setZ(0.0F);
         }

         this.square = var4;
         this.current = var4;
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
            ((IsoPlayer)var1).removeSaveFile();
         }

         var4.getStaticMovingObjects().push_back(this);
         if (dynamic_cast<IsoSurvivor*>(var1) != nullptr) {
            IsoWorld.instance.TotalSurvivorNights = IsoWorld.instance.TotalSurvivorNights + ((IsoSurvivor)var1).nightsSurvived;
            IsoWorld.instance.TotalSurvivorsDead++;
            if (IsoWorld.instance.SurvivorSurvivalRecord < ((IsoSurvivor)var1).nightsSurvived) {
               IsoWorld.instance.SurvivorSurvivalRecord = ((IsoSurvivor)var1).nightsSurvived;
            }
         }

         this.bFemale = var1.isFemale();
         this.wasZombie = var3 != nullptr;
         if (this.wasZombie) {
            this.bFakeDead = var3.isFakeDead();
            this.wasSkeleton = var3.isSkeleton();
         }

         this.dir = var1.dir;
         this.m_angle = var1.getAnimAngleRadians();
         this.Collidable = false;
         this.x = var1.getX();
         this.y = var1.getY();
         this.z = var1.getZ();
         this.nx = this.x;
         this.ny = this.y;
         this.offsetX = var1.offsetX;
         this.offsetY = var1.offsetY;
         this.solid = false;
         this.shootable = false;
         this.onlineID = var1.getOnlineID();
         this.OutlineOnMouseover = true;
         this.setContainer(var1.getInventory());
         this.setWornItems(var1.getWornItems());
         this.setAttachedItems(var1.getAttachedItems());
         if (dynamic_cast<IHumanVisual*>(var1) != nullptr) {
            this.baseVisual = std::make_shared<HumanVisual>(this);
            this.baseVisual.copyFrom(((IHumanVisual)var1).getHumanVisual());
            this.m_zombieRotStageAtDeath = this.getHumanVisual().zombieRotStage;
         }

         var1.setInventory(std::make_unique<ItemContainer>());
         var1.clearWornItems();
         var1.clearAttachedItems();
         if (!this.container.bExplored) {
            this.container.setExplored(dynamic_cast<IsoPlayer*>(var1) != nullptr || dynamic_cast<IsoZombie*>(var1) != nullptr && ((IsoZombie)var1).isReanimatedPlayer());
         }

    bool var5 = var1.isOnFire();
         if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
            this.m_persistentOutfitID = var1.getPersistentOutfitID();
            if (!var2 && !GameServer.bServer) {
               for (int var6 = 0; var6 < IsoPlayer.numPlayers; var6++) {
    IsoPlayer var7 = IsoPlayer.players[var6];
                  if (var7 != nullptr && var7.ReanimatedCorpse == var1) {
                     var7.ReanimatedCorpse = nullptr;
                     var7.ReanimatedCorpseID = -1;
                  }
               }

               if (!GameClient.bClient && var1.emitter != nullptr) {
                  var1.emitter.tick();
               }
            }
         } else {
            if (dynamic_cast<IsoSurvivor*>(var1) != nullptr) {
               this.getCell().getSurvivorList().remove(var1);
            }

            this.desc = std::make_shared<SurvivorDesc>(var1.getDescriptor());
            if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
               if (GameServer.bServer) {
                  this.player = (IsoPlayer)var1;
               } else if (!GameClient.bClient && ((IsoPlayer)var1).isLocalPlayer()) {
                  this.player = (IsoPlayer)var1;
               }
            }
         }

         LuaManager.copyTable(this.getModData(), var1.getModData());
         var1.removeFromWorld();
         var1.removeFromSquare();
         this.sayLine = var1.getSayLine();
         this.SpeakColor = var1.getSpeakColour();
         this.SpeakTime = var1.getSpeakTime();
         this.Speaking = var1.isSpeaking();
         if (var5) {
            if (!GameClient.bClient && SandboxOptions.instance.FireSpread.getValue()) {
               IsoFireManager.StartFire(this.getCell(), this.getSquare(), true, 100, 500);
            }

            this.container.setExplored(true);
         }

         if (!var2 && !GameServer.bServer) {
            LuaEventManager.triggerEvent("OnContainerUpdate", this);
         }

         if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
            ((IsoPlayer)var1).bDeathFinished = true;
         }

         this.deathTime = (float)GameTime.getInstance().getWorldAgeHours();
         this.setEatingZombies(var1.getEatingZombies());
         if (!this.wasZombie) {
    std::vector var11 = new std::vector();

            for (int var12 = -2; var12 < 2; var12++) {
               for (int var8 = -2; var8 < 2; var8++) {
    IsoGridSquare var9 = var4.getCell().getGridSquare(var4.x + var12, var4.y + var8, var4.z);
                  if (var9 != nullptr) {
                     for (int var10 = 0; var10 < var9.getMovingObjects().size(); var10++) {
                        if (var9.getMovingObjects().get(var10) instanceof IsoZombie) {
                           var11.push_back((IsoMovingObject)var9.getMovingObjects().get(var10));
                        }
                     }
                  }
               }
            }

            for (int var13 = 0; var13 < var11.size(); var13++) {
               ((IsoZombie)var11.get(var13)).pathToLocationF(this.getX() + Rand.Next(-0.3F, 0.3F), this.getY() + Rand.Next(-0.3F, 0.3F), this.getZ());
               ((IsoZombie)var11.get(var13)).bodyToEat = this;
            }
         }

         if (!GameClient.bClient) {
            this.objectID = Bodies.allocateID();
         }

         Bodies.put(this.objectID, this);
         if (!GameServer.bServer) {
            FliesSound.instance.corpseAdded((int)this.getX(), (int)this.getY(), (int)this.getZ());
         }

         DebugLog.Death.noise("Corpse created %s", this.getDescription());
      }
   }

    public IsoDeadBody(IsoCell var1) {
      super(var1, false);
      this.SpeakColor = Color.white;
      this.solid = false;
      this.shootable = false;
    BodyLocationGroup var2 = BodyLocations.getGroup("Human");
      this.wornItems = std::make_shared<WornItems>(var2);
    AttachedLocationGroup var3 = AttachedLocations.getGroup("Human");
      this.attachedItems = std::make_shared<AttachedItems>(var3);
      DebugLog.Death.noise("Corpse created on cell %s", this.getDescription());
   }

    BaseVisual getVisual() {
      return this.baseVisual;
   }

    HumanVisual getHumanVisual() {
      return (HumanVisual)Type.tryCastTo(this.baseVisual, HumanVisual.class);
   }

    void getItemVisuals(ItemVisuals var1) {
      this.wornItems.getItemVisuals(var1);
   }

    bool isFemale() {
      return this.bFemale;
   }

    bool isZombie() {
      return this.wasZombie;
   }

    bool isCrawling() {
      return this.bCrawling;
   }

    void setCrawling(bool var1) {
      this.bCrawling = var1;
   }

    bool isFakeDead() {
      return this.bFakeDead;
   }

    void setFakeDead(bool var1) {
      if (!var1 || SandboxOptions.instance.Lore.DisableFakeDead.getValue() != 3) {
         this.bFakeDead = var1;
      }
   }

    bool isSkeleton() {
      return this.wasSkeleton;
   }

    void setWornItems(WornItems var1) {
      this.wornItems = std::make_shared<WornItems>(var1);
   }

    WornItems getWornItems() {
      return this.wornItems;
   }

    void setAttachedItems(AttachedItems var1) {
      if (var1 != nullptr) {
         this.attachedItems = std::make_shared<AttachedItems>(var1);

         for (int var2 = 0; var2 < this.attachedItems.size(); var2++) {
    AttachedItem var3 = this.attachedItems.get(var2);
    InventoryItem var4 = var3.getItem();
            if (!this.container.contains(var4) && !GameClient.bClient && !GameServer.bServer) {
               var4.setContainer(this.container);
               this.container.getItems().push_back(var4);
            }
         }
      }
   }

    AttachedItems getAttachedItems() {
      return this.attachedItems;
   }

    InventoryItem getItem() {
    InventoryItem var1 = InventoryItemFactory.CreateItem("Base.CorpseMale");
      var1.storeInByteData(this);
    return var1;
   }

    IsoSprite loadSprite(ByteBuffer var1) {
    std::string var2 = GameWindow.ReadString(var1);
    float var3 = var1.getFloat();
    float var4 = var1.getFloat();
    float var5 = var1.getFloat();
    float var6 = var1.getFloat();
    return nullptr;
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.bFemale = var1.get() == 1;
      this.wasZombie = var1.get() == 1;
      if (var2 >= 192) {
         this.objectID = var1.getShort();
      } else {
         this.objectID = -1;
      }

    bool var4 = var1.get() == 1;
      if (var2 >= 171) {
         this.m_persistentOutfitID = var1.getInt();
      }

      if (var4 && var2 < 171) {
    short var5 = var1.getShort();
      }

      if (var1.get() == 1) {
         this.desc = std::make_shared<SurvivorDesc>(true);
         this.desc.load(var1, var2, nullptr);
      }

      if (var2 >= 190) {
    uint8_t var13 = var1.get();
         switch (var13) {
            case 0:
               this.baseVisual = std::make_shared<HumanVisual>(this);
               this.baseVisual.load(var1, var2);
               break;
            default:
               throw IOException("invalid visualType for corpse");
         }
      } else {
         this.baseVisual = std::make_shared<HumanVisual>(this);
         this.baseVisual.load(var1, var2);
      }

      if (var1.get() == 1) {
    int var14 = var1.getInt();

         try {
            this.setContainer(std::make_unique<ItemContainer>());
            this.container.ID = var14;
    std::vector var6 = this.container.load(var1, var2);
    uint8_t var7 = var1.get();

            for (int var8 = 0; var8 < var7; var8++) {
    std::string var9 = GameWindow.ReadString(var1);
    short var10 = var1.getShort();
               if (var10 >= 0 && var10 < var6.size() && this.wornItems.getBodyLocationGroup().getLocation(var9) != nullptr) {
                  this.wornItems.setItem(var9, (InventoryItem)var6.get(var10));
               }
            }

    uint8_t var15 = var1.get();

            for (int var16 = 0; var16 < var15; var16++) {
    std::string var17 = GameWindow.ReadString(var1);
    short var11 = var1.getShort();
               if (var11 >= 0 && var11 < var6.size() && this.attachedItems.getGroup().getLocation(var17) != nullptr) {
                  this.attachedItems.setItem(var17, (InventoryItem)var6.get(var11));
               }
            }
         } catch (Exception var12) {
            if (this.container != nullptr) {
               DebugLog.log("Failed to stream in container ID: " + this.container.ID);
            }
         }
      }

      this.deathTime = var1.getFloat();
      this.reanimateTime = var1.getFloat();
      this.fallOnFront = var1.get() == 1;
      if (var4 && (GameClient.bClient || GameServer.bServer && ServerGUI.isCreated())) {
         this.checkClothing(nullptr);
      }

      this.wasSkeleton = var1.get() == 1;
      if (var2 >= 159) {
         this.m_angle = var1.getFloat();
      } else {
         this.m_angle = this.dir.toAngle();
      }

      if (var2 >= 166) {
         this.m_zombieRotStageAtDeath = var1.get() & 255;
      }

      if (var2 >= 168) {
         this.bCrawling = var1.get() == 1;
         this.bFakeDead = var1.get() == 1;
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.put((byte)(this.bFemale ? 1 : 0));
      var1.put((byte)(this.wasZombie ? 1 : 0));
      var1.putShort(this.objectID);
      if (!GameServer.bServer && !GameClient.bClient) {
         var1.put((byte)0);
      } else {
         var1.put((byte)1);
      }

      var1.putInt(this.m_persistentOutfitID);
      if (this.desc != nullptr) {
         var1.put((byte)1);
         this.desc.save(var1);
      } else {
         var1.put((byte)0);
      }

      if (this.dynamic_cast<HumanVisual*>(baseVisual) != nullptr) {
         var1.put((byte)0);
         this.baseVisual.save(var1);
         if (this.container != nullptr) {
            var1.put((byte)1);
            var1.putInt(this.container.ID);
    std::vector var3 = this.container.save(var1);
            if (this.wornItems.size() > 127) {
               throw RuntimeException("too many worn items");
            }

            var1.put((byte)this.wornItems.size());
            this.wornItems.forEach(var2x -> {
               GameWindow.WriteString(var1, var2x.getLocation());
               var1.putShort((short)var3.indexOf(var2x.getItem()));
            });
            if (this.attachedItems == nullptr) {
               var1.put((byte)0);
            } else {
               if (this.attachedItems.size() > 127) {
                  throw RuntimeException("too many attached items");
               }

               var1.put((byte)this.attachedItems.size());
               this.attachedItems.forEach(var2x -> {
                  GameWindow.WriteString(var1, var2x.getLocation());
                  var1.putShort((short)var3.indexOf(var2x.getItem()));
               });
            }
         } else {
            var1.put((byte)0);
         }

         var1.putFloat(this.deathTime);
         var1.putFloat(this.reanimateTime);
         var1.put((byte)(this.fallOnFront ? 1 : 0));
         var1.put((byte)(this.isSkeleton() ? 1 : 0));
         var1.putFloat(this.m_angle);
         var1.put((byte)this.m_zombieRotStageAtDeath);
         var1.put((byte)(this.bCrawling ? 1 : 0));
         var1.put((byte)(this.bFakeDead ? 1 : 0));
      } else {
         throw IllegalStateException("unhandled baseVisual class");
      }
   }

    void softReset() {
      this.square.RemoveTileObject(this);
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      if ("becomeSkeleton" == var1)) {
         var3.putInt(this.getHumanVisual().getSkinTextureIndex());
      } else if ("zombieRotStage" == var1)) {
         var3.putInt(this.getHumanVisual().zombieRotStage);
      } else {
         super.saveChange(var1, var2, var3);
      }
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      if ("becomeSkeleton" == var1)) {
    int var3 = var2.getInt();
         this.getHumanVisual().setBeardModel("");
         this.getHumanVisual().setHairModel("");
         this.getHumanVisual().setSkinTextureIndex(var3);
         this.wasSkeleton = true;
         this.getWornItems().clear();
         this.getAttachedItems().clear();
         this.getContainer().clear();
         this.atlasTex = nullptr;
      } else if ("zombieRotStage" == var1)) {
         this.getHumanVisual().zombieRotStage = var2.getInt();
         this.atlasTex = nullptr;
      } else {
         super.loadChange(var1, var2);
      }
   }

    void renderlast() {
      if (this.Speaking) {
    float var1 = this.sx;
    float var2 = this.sy;
         var1 -= IsoCamera.getOffX();
         var2 -= IsoCamera.getOffY();
         var1 += 8.0F;
         var2 += 32.0F;
         if (this.sayLine != nullptr) {
            TextManager.instance
               .DrawStringCentre(UIFont.Medium, var1, var2, this.sayLine, this.SpeakColor.r, this.SpeakColor.g, this.SpeakColor.b, this.SpeakColor.a);
         }
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      this.offsetX = 0.0F;
      this.offsetY = 0.0F;
    bool var8 = this.isHighlighted();
      if (ModelManager.instance.bDebugEnableModels && ModelManager.instance.isCreated()) {
         if (this.atlasTex == nullptr) {
            this.atlasTex = DeadBodyAtlas.instance.getBodyTexture(this);
            DeadBodyAtlas.instance.render();
         }

         if (this.atlasTex != nullptr) {
            if (IsoSprite.globalOffsetX == -1.0F) {
               IsoSprite.globalOffsetX = -IsoCamera.frameState.OffX;
               IsoSprite.globalOffsetY = -IsoCamera.frameState.OffY;
            }

    float var9 = IsoUtils.XToScreen(var1, var2, var3, 0);
    float var10 = IsoUtils.YToScreen(var1, var2, var3, 0);
            this.sx = var9;
            this.sy = var10;
            var9 = this.sx + IsoSprite.globalOffsetX;
            var10 = this.sy + IsoSprite.globalOffsetY;
            if (Core.TileScale == 1) {
            }

            if (var8) {
               inf.r = this.getHighlightColor().r;
               inf.g = this.getHighlightColor().g;
               inf.b = this.getHighlightColor().b;
               inf.a = this.getHighlightColor().a;
            } else {
               inf.r = var4.r;
               inf.g = var4.g;
               inf.b = var4.b;
               inf.a = var4.a;
            }

            var4 = inf;
            if (!var8 && PerformanceSettings.LightingFrameSkip < 3 && this.getCurrentSquare() != nullptr) {
               this.getCurrentSquare().interpolateLight(var4, var1 - this.getCurrentSquare().getX(), var2 - this.getCurrentSquare().getY());
            }

            if (GameServer.bServer && ServerGUI.isCreated()) {
               inf.set(1.0F, 1.0F, 1.0F, 1.0F);
            }

            this.atlasTex.render((int)var9, (int)var10, var4.r, var4.g, var4.b, var4.a);
            if (Core.bDebug && DebugOptions.instance.DeadBodyAtlasRender.getValue()) {
               LineDrawer.DrawIsoLine(var1 - 0.5F, var2, var3, var1 + 0.5F, var2, var3, 1.0F, 1.0F, 1.0F, 0.25F, 1);
               LineDrawer.DrawIsoLine(var1, var2 - 0.5F, var3, var1, var2 + 0.5F, var3, 1.0F, 1.0F, 1.0F, 0.25F, 1);
            }

            this.sx = var9;
            this.sy = var10;
            if (IsoObjectPicker.Instance.wasDirty) {
               this.renderObjectPicker(this.getX(), this.getY(), this.getZ(), var4);
            }
         }
      }

      if (Core.bDebug && DebugOptions.instance.DeadBodyAtlasRender.getValue()) {
         _rotation.setAngleAxis(this.m_angle + (Math.PI / 2), 0.0, 0.0, 1.0);
         _transform.setRotation(_rotation);
         _transform.origin.set(this.x, this.y, this.z);
    Vector3f var30 = _tempVec3f_1;
         _transform.basis.getColumn(1, var30);
    Vector3f var34 = _tempVec3f_2;
         var30.cross(_UNIT_Z, var34);
    float var11 = 0.3F;
    float var12 = 0.9F;
         var30.x *= var12;
         var30.y *= var12;
         var34.x *= var11;
         var34.y *= var11;
    float var13 = var1 + var30.x;
    float var14 = var2 + var30.y;
    float var15 = var1 - var30.x;
    float var16 = var2 - var30.y;
    float var17 = var13 - var34.x;
    float var18 = var13 + var34.x;
    float var19 = var15 - var34.x;
    float var20 = var15 + var34.x;
    float var21 = var16 - var34.y;
    float var22 = var16 + var34.y;
    float var23 = var14 - var34.y;
    float var24 = var14 + var34.y;
    float var25 = 1.0F;
    float var26 = 1.0F;
    float var27 = 1.0F;
         if (this.isMouseOver(Mouse.getX(), Mouse.getY())) {
            var27 = 0.0F;
            var25 = 0.0F;
         }

         LineDrawer.addLine(var17, var23, 0.0F, var18, var24, 0.0F, var25, var26, var27, nullptr, true);
         LineDrawer.addLine(var17, var23, 0.0F, var19, var21, 0.0F, var25, var26, var27, nullptr, true);
         LineDrawer.addLine(var18, var24, 0.0F, var20, var22, 0.0F, var25, var26, var27, nullptr, true);
         LineDrawer.addLine(var19, var21, 0.0F, var20, var22, 0.0F, var25, var26, var27, nullptr, true);
      }

      if (this.isFakeDead() && DebugOptions.instance.ZombieRenderFakeDead.getValue()) {
    float var31 = IsoUtils.XToScreen(var1, var2, var3, 0) + IsoSprite.globalOffsetX;
    float var35 = IsoUtils.YToScreen(var1, var2, var3, 0) + IsoSprite.globalOffsetY - 16 * Core.TileScale;
    float var37 = this.getFakeDeadWakeupHours() - (float)GameTime.getInstance().getWorldAgeHours();
         var37 = Math.max(var37, 0.0F);
         TextManager.instance.DrawStringCentre(UIFont.Medium, var31, var35, std::string.format("FakeDead %.2f", var37), 1.0, 1.0, 1.0, 1.0);
      }

      if (Core.bDebug && DebugOptions.instance.MultiplayerShowZombieOwner.getValue()) {
    Color var32 = Colors.Yellow;
    float var36 = IsoUtils.XToScreenExact(var1 + 0.4F, var2 + 0.4F, var3, 0);
    float var39 = IsoUtils.YToScreenExact(var1 + 0.4F, var2 - 1.4F, var3, 0);
         TextManager.instance
            .DrawStringCentre(
               UIFont.DebugConsole,
               var36,
               var39,
               this.objectID + " / " + this.onlineID + " / " + (this.isFemale() ? "F" : "M"),
               var32.r,
               var32.g,
               var32.b,
               var32.a
            );
         TextManager.instance
            .DrawStringCentre(
               UIFont.DebugConsole,
               var36,
               var39 + 10.0F,
               std::string.format("x=%09.3f ", var1) + std::string.format("y=%09.3f ", var2) + std::string.format("z=%d", (byte)var3),
               var32.r,
               var32.g,
               var32.b,
               var32.a
            );
      }
   }

    void renderShadow() {
      _rotation.setAngleAxis(this.m_angle + (Math.PI / 2), 0.0, 0.0, 1.0);
      _transform.setRotation(_rotation);
      _transform.origin.set(this.x, this.y, this.z);
    Vector3f var1 = _tempVec3f_1;
      _transform.basis.getColumn(1, var1);
    float var2 = 0.45F;
    float var3 = 1.4F;
    float var4 = 1.125F;
    int var5 = IsoCamera.frameState.playerIndex;
    ColorInfo var6 = this.square.lighting[var5].lightInfo();
      renderShadow(this.x, this.y, this.z, var1, var2, var3, var4, var6, this.getAlpha(var5));
   }

    static void renderShadow(float var0, float var1, float var2, Vector3f var3, float var4, float var5, float var6, ColorInfo var7, float var8) {
    float var9 = var8 * ((var7.r + var7.g + var7.b) / 3.0F);
      var9 *= 0.66F;
      var3.normalize();
    Vector3f var10 = _tempVec3f_2;
      var3.cross(_UNIT_Z, var10);
      var4 = Math.max(0.65F, var4);
      var5 = Math.max(var5, 0.65F);
      var6 = Math.max(var6, 0.65F);
      var10.x *= var4;
      var10.y *= var4;
    float var11 = var0 + var3.x * var5;
    float var12 = var1 + var3.y * var5;
    float var13 = var0 - var3.x * var6;
    float var14 = var1 - var3.y * var6;
    float var15 = var11 - var10.x;
    float var16 = var11 + var10.x;
    float var17 = var13 - var10.x;
    float var18 = var13 + var10.x;
    float var19 = var14 - var10.y;
    float var20 = var14 + var10.y;
    float var21 = var12 - var10.y;
    float var22 = var12 + var10.y;
    float var23 = IsoUtils.XToScreenExact(var15, var21, var2, 0);
    float var24 = IsoUtils.YToScreenExact(var15, var21, var2, 0);
    float var25 = IsoUtils.XToScreenExact(var16, var22, var2, 0);
    float var26 = IsoUtils.YToScreenExact(var16, var22, var2, 0);
    float var27 = IsoUtils.XToScreenExact(var18, var20, var2, 0);
    float var28 = IsoUtils.YToScreenExact(var18, var20, var2, 0);
    float var29 = IsoUtils.XToScreenExact(var17, var19, var2, 0);
    float var30 = IsoUtils.YToScreenExact(var17, var19, var2, 0);
      if (DropShadow == nullptr) {
         DropShadow = Texture.getSharedTexture("media/textures/NewShadow.png");
      }

      SpriteRenderer.instance.renderPoly(DropShadow, var23, var24, var25, var26, var27, var28, var29, var30, 0.0F, 0.0F, 0.0F, var9);
      if (DebugOptions.instance.IsoSprite.DropShadowEdges.getValue()) {
         LineDrawer.addLine(var15, var21, var2, var16, var22, var2, 1, 1, 1, nullptr);
         LineDrawer.addLine(var16, var22, var2, var18, var20, var2, 1, 1, 1, nullptr);
         LineDrawer.addLine(var18, var20, var2, var17, var19, var2, 1, 1, 1, nullptr);
         LineDrawer.addLine(var17, var19, var2, var15, var21, var2, 1, 1, 1, nullptr);
      }
   }

    void renderObjectPicker(float var1, float var2, float var3, ColorInfo var4) {
      if (this.atlasTex != nullptr) {
         this.atlasTex.renderObjectPicker(this.sx, this.sy, var4, this.square, this);
      }
   }

    bool isMouseOver(float var1, float var2) {
      _rotation.setAngleAxis(this.m_angle + (Math.PI / 2), 0.0, 0.0, 1.0);
      _transform.setRotation(_rotation);
      _transform.origin.set(this.x, this.y, this.z);
      _transform.inverse();
    Vector3f var3 = _tempVec3f_1.set(IsoUtils.XToIso(var1, var2, this.z), IsoUtils.YToIso(var1, var2, this.z), this.z);
      _transform.transform(var3);
      return var3.x >= -0.3F && var3.y >= -0.9F && var3.x < 0.3F && var3.y < 0.9F;
   }

    void Burn() {
      if (!GameClient.bClient) {
         if (this.getSquare() != nullptr && this.getSquare().getProperties().Is(IsoFlagType.burning)) {
            this.burnTimer = this.burnTimer + GameTime.instance.getMultipliedSecondsSinceLastUpdate();
            if (this.burnTimer >= 10.0F) {
    bool var1 = true;

               for (int var2 = 0; var2 < this.getSquare().getObjects().size(); var2++) {
    IsoObject var3 = (IsoObject)this.getSquare().getObjects().get(var2);
                  if (var3.getName() != nullptr && "burnedCorpse" == var3.getName())) {
                     var1 = false;
                     break;
                  }
               }

               if (var1) {
    IsoObject var4 = std::make_shared<IsoObject>(this.getSquare(), "floors_burnt_01_" + Rand.Next(1, 3), "burnedCorpse");
                  this.getSquare().getObjects().push_back(var4);
                  var4.transmitCompleteItemToClients();
               }

               if (GameServer.bServer) {
                  GameServer.sendRemoveCorpseFromMap(this);
               }

               this.getSquare().removeCorpse(this, true);
            }
         }
      }
   }

    void setContainer(ItemContainer var1) {
      super.setContainer(var1);
      var1.type = this.bFemale ? "inventoryfemale" : "inventorymale";
      var1.Capacity = 8;
      var1.SourceGrid = this.square;
   }

    void checkClothing(InventoryItem var1) {
      for (int var2 = 0; var2 < this.wornItems.size(); var2++) {
    InventoryItem var3 = this.wornItems.getItemByIndex(var2);
         if (this.container == nullptr || this.container.getItems().indexOf(var3) == -1) {
            this.wornItems.remove(var3);
            this.atlasTex = nullptr;
            var2--;
         }
      }

      if (var1 == this.getPrimaryHandItem()) {
         this.setPrimaryHandItem(nullptr);
         this.atlasTex = nullptr;
      }

      if (var1 == this.getSecondaryHandItem()) {
         this.setSecondaryHandItem(nullptr);
         this.atlasTex = nullptr;
      }

      for (int var4 = 0; var4 < this.attachedItems.size(); var4++) {
    InventoryItem var5 = this.attachedItems.getItemByIndex(var4);
         if (this.container == nullptr || this.container.getItems().indexOf(var5) == -1) {
            this.attachedItems.remove(var5);
            this.atlasTex = nullptr;
            var4--;
         }
      }
   }

    bool IsSpeaking() {
      return this.Speaking;
   }

    void Say(const std::string& var1) {
      this.SpeakTime = var1.length() * 4;
      if (this.SpeakTime < 60.0F) {
         this.SpeakTime = 60.0F;
      }

      this.sayLine = var1;
      this.Speaking = true;
   }

    std::string getSayLine() {
      return this.sayLine;
   }

    std::string getTalkerType() {
      return "Talker";
   }

    void addToWorld() {
      super.addToWorld();
      if (!GameServer.bServer) {
         FliesSound.instance.corpseAdded((int)this.getX(), (int)this.getY(), (int)this.getZ());
      }

      if (!GameClient.bClient && this.objectID == -1) {
         this.objectID = Bodies.allocateID();
      }

      Bodies.put(this.objectID, this);
      if (!GameClient.bClient) {
         if (this.reanimateTime > 0.0F) {
            this.getCell().addToStaticUpdaterObjectList(this);
            if (Core.bDebug) {
               DebugLog.log("reanimate: addToWorld reanimateTime=" + this.reanimateTime + this);
            }
         }

    float var1 = (float)GameTime.getInstance().getWorldAgeHours();
         if (this.deathTime < 0.0F) {
            this.deathTime = var1;
         }

         if (this.deathTime > var1) {
            this.deathTime = var1;
         }
      }
   }

    void removeFromWorld() {
      if (!GameServer.bServer) {
         FliesSound.instance.corpseRemoved((int)this.getX(), (int)this.getY(), (int)this.getZ());
      }

      Bodies.remove(this.objectID);
      super.removeFromWorld();
   }

    static void updateBodies() {
      if (!GameClient.bClient) {
         if (Core.bDebug) {
         }

    bool var0 = false;
    float var1 = (float)SandboxOptions.instance.HoursForCorpseRemoval.getValue();
         if (!(var1 <= 0.0F)) {
    float var2 = var1 / 3.0F;
    float var3 = (float)GameTime.getInstance().getWorldAgeHours();
            tempBodies.clear();
            Bodies.getObjects(tempBodies);

    for (auto& var5 : tempBodies)               if (var5.getHumanVisual() != nullptr) {
                  if (var5.deathTime > var3) {
                     var5.deathTime = var3;
                     var5.getHumanVisual().zombieRotStage = var5.m_zombieRotStageAtDeath;
                  }

                  if (!var5.updateFakeDead() && (ServerOptions.instance.RemovePlayerCorpsesOnCorpseRemoval.getValue() || var5.wasZombie)) {
    int var6 = var5.getHumanVisual().zombieRotStage;
                     var5.updateRotting(var3, var2, var0);
                     if (var5.isFakeDead()) {
                     }

    int var7 = var5.getHumanVisual().zombieRotStage;
    float var8 = var3 - var5.deathTime;
                     if (!(var8 < var1 + (var5.isSkeleton() ? var2 : 0.0F))) {
                        if (var0) {
    int var9 = (int)(var8 / var2);
                           DebugLog.General.debugln("%s REMOVE %d -> %d age=%.2f stages=%d", var5, var6, var7, var8, var9);
                        }

                        if (GameServer.bServer) {
                           GameServer.sendRemoveCorpseFromMap(var5);
                        }

                        var5.removeFromWorld();
                        var5.removeFromSquare();
                     }
                  }
               }
            }
         }
      }
   }

    void updateRotting(float var1, float var2, bool var3) {
      if (!this.isSkeleton()) {
    float var4 = var1 - this.deathTime;
    int var5 = (int)(var4 / var2);
    int var6 = this.m_zombieRotStageAtDeath + var5;
         if (var5 < 3) {
            var6 = PZMath.clamp(var6, 1, 3);
         }

         if (var6 <= 3 && var6 != this.getHumanVisual().zombieRotStage) {
    int var7 = var6 - this.getHumanVisual().zombieRotStage;
            if (var3) {
               DebugLog.General.debugln("%s zombieRotStage %d -> %d age=%.2f stages=%d", this, this.getHumanVisual().zombieRotStage, var6, var4, var5);
            }

            this.getHumanVisual().zombieRotStage = var6;
            this.atlasTex = nullptr;
            if (GameServer.bServer) {
               this.sendObjectChange("zombieRotStage");
            }

            if (Rand.Next(100) == 0 && this.wasZombie && SandboxOptions.instance.Lore.DisableFakeDead.getValue() == 2) {
               this.setFakeDead(true);
               if (Rand.Next(5) == 0) {
                  this.setCrawling(true);
               }
            }

    std::string var8 = ClimateManager.getInstance().getSeasonName();
            if (var7 >= 1 && var8 != "Winter") {
               if (SandboxOptions.instance.MaggotSpawn.getValue() != 3) {
    uint8_t var9 = 5;
                  if (var8 == "Summer") {
                     var9 = 3;
                  }

                  for (int var10 = 0; var10 < var7; var10++) {
                     if (this.wasZombie) {
                        if (Rand.Next(var9) == 0) {
    InventoryItem var11 = InventoryItemFactory.CreateItem("Maggots");
                           if (var11 != nullptr && this.getContainer() != nullptr) {
                              this.getContainer().addItem(var11);
                              if (dynamic_cast<Food*>(var11) != nullptr) {
                                 ((Food)var11).setPoisonPower(5);
                              }
                           }
                        }

                        if (Rand.Next(var9 * 2) == 0 && SandboxOptions.instance.MaggotSpawn.getValue() != 2) {
    InventoryItem var12 = InventoryItemFactory.CreateItem("Maggots");
                           if (var12 != nullptr && this.getSquare() != nullptr) {
                              this.getSquare().AddWorldInventoryItem(var12, Rand.Next(10) / 10, Rand.Next(10) / 10, 0.0F);
                              if (dynamic_cast<Food*>(var12) != nullptr) {
                                 ((Food)var12).setPoisonPower(5);
                              }
                           }
                        }
                     } else {
                        if (Rand.Next(var9) == 0) {
    InventoryItem var13 = InventoryItemFactory.CreateItem("Maggots");
                           if (var13 != nullptr && this.getContainer() != nullptr) {
                              this.getContainer().addItem(var13);
                           }
                        }

                        if (Rand.Next(var9 * 2) == 0 && SandboxOptions.instance.MaggotSpawn.getValue() != 2) {
    InventoryItem var14 = InventoryItemFactory.CreateItem("Maggots");
                           if (var14 != nullptr && this.getSquare() != nullptr) {
                              this.getSquare().AddWorldInventoryItem(var14, Rand.Next(10) / 10, Rand.Next(10) / 10, 0.0F);
                           }
                        }
                     }
                  }
               }
            }
         } else {
            if (var5 == 3 && Rand.NextBool(7)) {
               if (var3) {
                  DebugLog.General.debugln("%s zombieRotStage %d -> x age=%.2f stages=%d", this, this.getHumanVisual().zombieRotStage, var4, var5);
               }

               this.getHumanVisual().setBeardModel("");
               this.getHumanVisual().setHairModel("");
               this.getHumanVisual().setSkinTextureIndex(Rand.Next(1, 3));
               this.wasSkeleton = true;
               this.getWornItems().clear();
               this.getAttachedItems().clear();
               this.getContainer().clear();
               this.atlasTex = nullptr;
               if (GameServer.bServer) {
                  this.sendObjectChange("becomeSkeleton");
               }
            }
         }
      }
   }

    bool updateFakeDead() {
      if (!this.isFakeDead()) {
    return false;
      } else if (this.isSkeleton()) {
    return false;
      } else if (this.getFakeDeadWakeupHours() > GameTime.getInstance().getWorldAgeHours()) {
    return false;
      } else if (!this.isPlayerNearby()) {
    return false;
      } else if (SandboxOptions.instance.Lore.DisableFakeDead.getValue() == 3) {
    return false;
      } else {
         this.reanimateNow();
    return true;
      }
   }

    float getFakeDeadWakeupHours() {
      return this.deathTime + 0.5F;
   }

    bool isPlayerNearby() {
      if (GameServer.bServer) {
         for (int var1 = 0; var1 < GameServer.Players.size(); var1++) {
    IsoPlayer var2 = (IsoPlayer)GameServer.Players.get(var1);
    bool var3 = this.square != nullptr && ServerLOS.instance.isCouldSee(var2, this.square);
            if (this.isPlayerNearby(var2, var3)) {
    return true;
            }
         }
      } else {
    IsoGridSquare var5 = this.getSquare();

         for (int var6 = 0; var6 < IsoPlayer.numPlayers; var6++) {
    IsoPlayer var7 = IsoPlayer.players[var6];
    bool var4 = var5 != nullptr && var5.isCanSee(var6);
            if (this.isPlayerNearby(var7, var4)) {
    return true;
            }
         }
      }

    return false;
   }

    bool isPlayerNearby(IsoPlayer var1, bool var2) {
      if (!var2) {
    return false;
      } else if (var1 == nullptr || var1.isDead()) {
    return false;
      } else if (var1.isGhostMode() || var1.isInvisible()) {
    return false;
      } else if (var1.getVehicle() != nullptr) {
    return false;
      } else {
    float var3 = var1.DistToSquared(this);
         return !(var3 < 4.0F) && !(var3 > 16.0F);
      }
   }

    float getReanimateTime() {
      return this.reanimateTime;
   }

    void setReanimateTime(float var1) {
      this.reanimateTime = var1;
      if (!GameClient.bClient) {
    std::vector var2 = IsoWorld.instance.CurrentCell.getStaticUpdaterObjectList();
         if (this.reanimateTime > 0.0F && !var2.contains(this)) {
            var2.push_back(this);
         } else if (this.reanimateTime <= 0.0F && var2.contains(this)) {
            var2.remove(this);
         }
      }
   }

    float getReanimateDelay() {
    float var1 = 0.0F;
    float var2 = 0.0F;

      var2 = switch (SandboxOptions.instance.Lore.Reanimate.getValue()) {
         case 2 -> 0.008333334F;
         case 3 -> 0.016666668F;
         case 4 -> 12.0F;
         case 5 -> {
            var1 = 48.0F;
            yield 72.0F;
         }
         case 6 -> {
            var1 = 168.0F;
            yield 336.0F;
         }
      };
      if (Core.bTutorial) {
         var2 = 0.25F;
      }

    return var1 = = var2 ? var1 : Rand.Next(var1, var2);
   }

    void reanimateLater() {
      this.setReanimateTime((float)GameTime.getInstance().getWorldAgeHours() + this.getReanimateDelay());
   }

    void reanimateNow() {
      this.setReanimateTime((float)GameTime.getInstance().getWorldAgeHours());
   }

    void update() {
      if (this.current == nullptr) {
         this.current = IsoWorld.instance.CurrentCell.getGridSquare(this.x, this.y, this.z);
      }

      if (!GameClient.bClient) {
         if (this.reanimateTime > 0.0F) {
    float var1 = (float)GameTime.getInstance().getWorldAgeHours();
            if (this.reanimateTime <= var1) {
               this.reanimate();
            }
         }
      }
   }

    void reanimate() {
    short var1 = -1;
      if (GameServer.bServer) {
         var1 = ServerMap.instance.getUniqueZombieId();
         if (var1 == -1) {
            return;
         }
      }

    SurvivorDesc var2 = std::make_shared<SurvivorDesc>();
      var2.setFemale(this.isFemale());
    IsoZombie var3 = std::make_shared<IsoZombie>(IsoWorld.instance.CurrentCell, var2, -1);
      var3.setPersistentOutfitID(this.m_persistentOutfitID);
      if (this.container == nullptr) {
         this.container = std::make_unique<ItemContainer>();
      }

      var3.setInventory(this.container);
      this.container = nullptr;
      var3.getHumanVisual().copyFrom(this.getHumanVisual());
      var3.getWornItems().copyFrom(this.wornItems);
      this.wornItems.clear();
      var3.getAttachedItems().copyFrom(this.attachedItems);
      this.attachedItems.clear();
      var3.setX(this.getX());
      var3.setY(this.getY());
      var3.setZ(this.getZ());
      var3.setCurrent(this.getCurrentSquare());
      var3.setMovingSquareNow();
      var3.setDir(this.dir);
      LuaManager.copyTable(var3.getModData(), this.getModData());
      var3.getAnimationPlayer().setTargetAngle(this.m_angle);
      var3.getAnimationPlayer().setAngleToTarget();
      var3.setForwardDirection(Vector2.fromLengthDirection(1.0F, this.m_angle));
      var3.setAlphaAndTarget(1.0F);
      Arrays.fill(var3.IsVisibleToPlayer, true);
      var3.setOnFloor(true);
      var3.setCrawler(this.bCrawling);
      var3.setCanWalk(!this.bCrawling);
      var3.walkVariant = "ZombieWalk";
      var3.DoZombieStats();
      var3.setFallOnFront(this.isFallOnFront());
      if (SandboxOptions.instance.Lore.Toughness.getValue() == 1) {
         var3.setHealth(3.5F + Rand.Next(0.0F, 0.3F));
      }

      if (SandboxOptions.instance.Lore.Toughness.getValue() == 2) {
         var3.setHealth(1.8F + Rand.Next(0.0F, 0.3F));
      }

      if (SandboxOptions.instance.Lore.Toughness.getValue() == 3) {
         var3.setHealth(0.5F + Rand.Next(0.0F, 0.3F));
      }

      if (GameServer.bServer) {
         var3.OnlineID = var1;
         ServerMap.instance.ZombieMap.put(var3.OnlineID, var3);
      }

      if (this.isFakeDead()) {
         var3.setWasFakeDead(true);
      } else {
         var3.setReanimatedPlayer(true);
         var3.getDescriptor().setID(0);
         SharedDescriptors.createPlayerZombieDescriptor(var3);
      }

      var3.setReanimate(this.bCrawling);
      if (!IsoWorld.instance.CurrentCell.getZombieList().contains(var3)) {
         IsoWorld.instance.CurrentCell.getZombieList().push_back(var3);
      }

      if (!IsoWorld.instance.CurrentCell.getObjectList().contains(var3) && !IsoWorld.instance.CurrentCell.getAddList().contains(var3)) {
         IsoWorld.instance.CurrentCell.getAddList().push_back(var3);
      }

      if (GameServer.bServer) {
         if (this.player != nullptr) {
            this.player.ReanimatedCorpse = var3;
            this.player.ReanimatedCorpseID = var3.OnlineID;
         }

         var3.networkAI.reanimatedBodyID = this.objectID;
      }

      if (GameServer.bServer) {
         GameServer.sendRemoveCorpseFromMap(this);
      }

      this.removeFromWorld();
      this.removeFromSquare();
      LuaEventManager.triggerEvent("OnContainerUpdate");
      var3.setReanimateTimer(0.0F);
      var3.onWornItemsChanged();
      if (this.player != nullptr) {
         if (GameServer.bServer) {
            GameServer.sendReanimatedZombieID(this.player, var3);
         } else if (!GameClient.bClient && this.player.isLocalPlayer()) {
            this.player.ReanimatedCorpse = var3;
         }

         this.player.setLeaveBodyTimedown(3601.0F);
      }

      var3.actionContext.update();
    float var4 = GameTime.getInstance().FPSMultiplier;
      GameTime.getInstance().FPSMultiplier = 100.0F;

      try {
         var3.advancedAnimator.update();
      } finally {
         GameTime.getInstance().FPSMultiplier = var4;
      }

      if (this.isFakeDead() && SoundManager.instance.isListenerInRange(this.x, this.y, 20.0F) && !GameServer.bServer) {
         var3.parameterZombieState.setState(State.Reanimate);
      }

      if (Core.bDebug) {
         DebugLog.Multiplayer
            .debugln(
               "Reanimate: corpse=%d/%d zombie=%d delay=%f",
               this.getObjectID(),
               this.getOnlineID(),
               var3.getOnlineID(),
               GameTime.getInstance().getWorldAgeHours() - this.reanimateTime
            );
      }
   }

    static void Reset() {
      Bodies.clear();
   }

    void Collision(Vector2 var1, IsoObject var2) {
      if (dynamic_cast<BaseVehicle*>(var2) != nullptr var3) {
    float var4 = 15.0F;
    Vector3f var5 = (Vector3f)((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).alloc();
    Vector3f var6 = (Vector3f)((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).alloc();
         var3.getLinearVelocity(var5);
         var5.y = 0.0F;
         var6.set(var3.x - this.x, 0.0F, var3.z - this.z);
         var6.normalize();
         var5.mul(var6);
         ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(var6);
    float var7 = var5.length();
         ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(var5);
         var7 = Math.min(var7, var4);
         if (var7 < 0.05F) {
            return;
         }

         if (Math.abs(var3.getCurrentSpeedKmHour()) > 20.0F) {
            var3.doChrHitImpulse(this);
         }
      }
   }

    bool isFallOnFront() {
      return this.fallOnFront;
   }

    void setFallOnFront(bool var1) {
      this.fallOnFront = var1;
   }

    InventoryItem getPrimaryHandItem() {
      return this.primaryHandItem;
   }

    void setPrimaryHandItem(InventoryItem var1) {
      this.primaryHandItem = var1;
      this.updateContainerWithHandItems();
   }

    void updateContainerWithHandItems() {
      if (this.getContainer() != nullptr) {
         if (this.getPrimaryHandItem() != nullptr) {
            this.getContainer().AddItem(this.getPrimaryHandItem());
         }

         if (this.getSecondaryHandItem() != nullptr) {
            this.getContainer().AddItem(this.getSecondaryHandItem());
         }
      }
   }

    InventoryItem getSecondaryHandItem() {
      return this.secondaryHandItem;
   }

    void setSecondaryHandItem(InventoryItem var1) {
      this.secondaryHandItem = var1;
      this.updateContainerWithHandItems();
   }

    float getAngle() {
      return this.m_angle;
   }

    std::string getOutfitName() {
      return this.getHumanVisual().getOutfit() != nullptr ? this.getHumanVisual().getOutfit().m_Name : nullptr;
   }

    std::string getDescription() {
      return std::string.format(
         "object-id=%d online-id=%d bFakeDead=%b bCrawling=%b isFallOnFront=%b (x=%f,y=%f,z=%f;a=%f) outfit=%d",
         this.objectID,
         this.onlineID,
         this.bFakeDead,
         this.bCrawling,
         this.fallOnFront,
         this.x,
         this.y,
         this.z,
         this.m_angle,
         this.m_persistentOutfitID
      );
   }

    std::string readInventory(ByteBuffer var1) {
    std::string var2 = GameWindow.ReadString(var1);
      if (this.getContainer() != nullptr && this.getWornItems() != nullptr && this.getAttachedItems() != nullptr) {
         this.getContainer().clear();
         this.getWornItems().clear();
         this.getAttachedItems().clear();
    bool var3 = var1.get() == 1;
         if (var3) {
            try {
    std::vector var4 = this.getContainer().load(var1, IsoWorld.getWorldVersion());
               this.getContainer().Capacity = 8;
    uint8_t var5 = var1.get();

               for (int var6 = 0; var6 < var5; var6++) {
    std::string var7 = GameWindow.ReadStringUTF(var1);
    short var8 = var1.getShort();
                  if (var8 >= 0 && var8 < var4.size() && this.getWornItems().getBodyLocationGroup().getLocation(var7) != nullptr) {
                     this.getWornItems().setItem(var7, (InventoryItem)var4.get(var8));
                  }
               }

    uint8_t var11 = var1.get();

               for (int var12 = 0; var12 < var11; var12++) {
    std::string var13 = GameWindow.ReadStringUTF(var1);
    short var9 = var1.getShort();
                  if (var9 >= 0 && var9 < var4.size() && this.getAttachedItems().getGroup().getLocation(var13) != nullptr) {
                     this.getAttachedItems().setItem(var13, (InventoryItem)var4.get(var9));
                  }
               }
            } catch (IOException var10) {
               DebugLog.Multiplayer.printException(var10, "ReadDeadBodyInventory error for dead body " + this.getOnlineID(), LogSeverity.Error);
            }
         }

    return var2;
      } else {
    return var2;
      }
   }

    short getObjectID() {
      return this.objectID;
   }

    void setObjectID(short var1) {
      this.objectID = var1;
   }

    short getOnlineID() {
      return this.onlineID;
   }

    void setOnlineID(short var1) {
      this.onlineID = var1;
   }

    bool isPlayer() {
      return this.player != nullptr;
   }

    static IsoDeadBody getDeadBody(short var0) {
      return (IsoDeadBody)Bodies.get(var0);
   }

    static void addDeadBodyID(short var0, IsoDeadBody var1) {
      Bodies.put(var0, var1);
   }

    static void removeDeadBody(short var0) {
    IsoDeadBody var1 = (IsoDeadBody)Bodies.get(var0);
      if (var1 != nullptr) {
         Bodies.remove(var0);
         if (var1.getSquare() != nullptr) {
            var1.getSquare().removeCorpse(var1, true);
         }
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
