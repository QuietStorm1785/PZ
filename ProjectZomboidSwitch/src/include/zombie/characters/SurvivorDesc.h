#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/SurvivorFactory/SurvivorType.h"
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/characters/professions/ProfessionFactory/Profession.h"
#include "zombie/characters/skills/PerkFactory/Perk.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/characters/traits/ObservationFactory.h"
#include "zombie/characters/traits/ObservationFactory/Observation.h"
#include "zombie/core/Color.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/IsoWorld.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace characters {


class SurvivorDesc {
public:
    const HumanVisual humanVisual = std::make_shared<HumanVisual>(this);
    const WornItems wornItems = std::make_shared<WornItems>(BodyLocations.getGroup("Human"));
    SurvivorGroup group = std::make_shared<SurvivorGroup>();
    static int IDCount = 0;
   public static const std::vector<Color> TrouserCommonColors = std::make_unique<std::vector<>>();
   public static const std::vector<ImmutableColor> HairCommonColors = std::make_unique<std::vector<>>();
   private const std::unordered_map<Perk, int> xpBoostMap = std::make_unique<std::unordered_map<>>();
    KahluaTable metaTable;
    std::string Profession = "";
    std::string forename = "None";
    int ID = 0;
    IsoGameCharacter Instance = nullptr;
    bool bFemale = true;
    std::string surname = "None";
    std::string InventoryScript = nullptr;
    std::string torso = "Base_Torso";
   protected const std::unordered_map<int, int> MetCount = std::make_unique<std::unordered_map<>>();
    float bravery = 1.0F;
    float loner = 0.0F;
    float aggressiveness = 1.0F;
    float compassion = 1.0F;
    float temper = 0.0F;
    float friendliness = 0.0F;
    float favourindoors = 0.0F;
    float loyalty = 0.0F;
   public const std::vector<std::string> extra = std::make_unique<std::vector<>>();
   private const std::vector<Observation> Observations = new std::vector<>(0);
    SurvivorType type = SurvivorType.Neutral;
    bool bDead;

    HumanVisual getHumanVisual() {
      return this.humanVisual;
   }

    void getItemVisuals(ItemVisuals var1) {
      this.wornItems.getItemVisuals(var1);
   }

    bool isFemale() {
      return this.bFemale;
   }

    bool isZombie() {
    return false;
   }

    bool isSkeleton() {
    return false;
   }

    WornItems getWornItems() {
      return this.wornItems;
   }

    void setWornItem(const std::string& var1, InventoryItem var2) {
      this.wornItems.setItem(var1, var2);
   }

    InventoryItem getWornItem(const std::string& var1) {
      return this.wornItems.getItem(var1);
   }

    void dressInNamedOutfit(const std::string& var1) {
    ItemVisuals var2 = std::make_shared<ItemVisuals>();
      this.getHumanVisual().dressInNamedOutfit(var1, var2);
      this.getWornItems().setFromItemVisuals(var2);
   }

    SurvivorGroup getGroup() {
      return this.group;
   }

    bool isLeader() {
      return this.group.getLeader() == this;
   }

    static int getIDCount() {
    return IDCount;
   }

    void setProfessionSkills(Profession var1) {
      this.getXPBoostMap().clear();
      this.getXPBoostMap().putAll(var1.XPBoostMap);
   }

   public std::unordered_map<Perk, int> getXPBoostMap() {
      return this.xpBoostMap;
   }

    KahluaTable getMeta() {
      if (this.metaTable == nullptr) {
         this.metaTable = (KahluaTable)LuaManager.caller.pcall(LuaManager.thread, LuaManager.env.rawget("createMetaSurvivor"), this)[1];
      }

      return this.metaTable;
   }

    int getCalculatedToughness() {
      this.metaTable = this.getMeta();
    KahluaTable var1 = (KahluaTable)LuaManager.env.rawget("MetaSurvivor");
    double var2 = (double)LuaManager.caller.pcall(LuaManager.thread, var1.rawget("getCalculatedToughness"), this.metaTable)[1];
      return var2.intValue();
   }

    static void setIDCount(int var0) {
      IDCount = var0;
   }

    bool isDead() {
      return this.bDead;
   }

    public SurvivorDesc() {
      this.ID = IDCount++;
      IsoWorld.instance.SurvivorDescriptors.put(this.ID, this);
      this.doStats();
   }

    public SurvivorDesc(bool var1) {
      this.ID = IDCount++;
      this.doStats();
   }

    public SurvivorDesc(SurvivorDesc var1) {
      this.aggressiveness = var1.aggressiveness;
      this.bDead = var1.bDead;
      this.bFemale = var1.bFemale;
      this.bravery = var1.bravery;
      this.compassion = var1.compassion;
      this.extra.addAll(var1.extra);
      this.favourindoors = var1.favourindoors;
      this.forename = var1.forename;
      this.friendliness = var1.friendliness;
      this.InventoryScript = var1.InventoryScript;
      this.loner = var1.loner;
      this.loyalty = var1.loyalty;
      this.Profession = var1.Profession;
      this.surname = var1.surname;
      this.temper = var1.temper;
      this.torso = var1.torso;
      this.type = var1.type;
   }

    void meet(SurvivorDesc var1) {
      if (this.MetCount.containsKey(var1.ID)) {
         this.MetCount.put(var1.ID, this.MetCount.get(var1.ID) + 1);
      } else {
         this.MetCount.put(var1.ID, 1);
      }

      if (var1.MetCount.containsKey(this.ID)) {
         var1.MetCount.put(this.ID, var1.MetCount.get(this.ID) + 1);
      } else {
         var1.MetCount.put(this.ID, 1);
      }
   }

    bool hasObservation(const std::string& var1) {
      for (int var2 = 0; var2 < this.Observations.size(); var2++) {
         if (var1 == this.Observations.get(var2).getTraitID())) {
    return true;
         }
      }

    return false;
   }

    void savePerk(ByteBuffer var1, Perk var2) {
      GameWindow.WriteStringUTF(var1, var2 == nullptr ? "" : var2.getId());
   }

    Perk loadPerk(ByteBuffer var1, int var2) {
      if (var2 >= 152) {
    std::string var5 = GameWindow.ReadStringUTF(var1);
    Perk var6 = Perks.FromString(var5);
    return var6 = = Perks.MAX ? nullptr : var6;
      } else {
    int var3 = var1.getInt();
         if (var3 >= 0 && var3 < Perks.MAX.index()) {
    Perk var4 = Perks.fromIndex(var3);
    return var4 = = Perks.MAX ? nullptr : var4;
         } else {
    return nullptr;
         }
      }
   }

    void load(ByteBuffer var1, int var2, IsoGameCharacter var3) {
      this.ID = var1.getInt();
      IsoWorld.instance.SurvivorDescriptors.put(this.ID, this);
      this.forename = GameWindow.ReadString(var1);
      this.surname = GameWindow.ReadString(var1);
      this.torso = GameWindow.ReadString(var1);
      this.bFemale = var1.getInt() == 1;
      this.Profession = GameWindow.ReadString(var1);
      this.doStats();
      if (IDCount < this.ID) {
         IDCount = this.ID;
      }

      this.extra.clear();
      if (var1.getInt() == 1) {
    int var4 = var1.getInt();

         for (int var5 = 0; var5 < var4; var5++) {
    std::string var6 = GameWindow.ReadString(var1);
            this.extra.push_back(var6);
         }
      }

    int var8 = var1.getInt();

      for (int var9 = 0; var9 < var8; var9++) {
    Perk var10 = this.loadPerk(var1, var2);
    int var7 = var1.getInt();
         if (var10 != nullptr) {
            this.getXPBoostMap().put(var10, var7);
         }
      }

      this.Instance = var3;
   }

    void save(ByteBuffer var1) {
      var1.putInt(this.ID);
      GameWindow.WriteString(var1, this.forename);
      GameWindow.WriteString(var1, this.surname);
      GameWindow.WriteString(var1, this.torso);
      var1.putInt(this.bFemale ? 1 : 0);
      GameWindow.WriteString(var1, this.Profession);
      if (!this.extra.empty()) {
         var1.putInt(1);
         var1.putInt(this.extra.size());

         for (int var2 = 0; var2 < this.extra.size(); var2++) {
    std::string var3 = this.extra.get(var2);
            GameWindow.WriteString(var1, var3);
         }
      } else {
         var1.putInt(0);
      }

      var1.putInt(this.getXPBoostMap().size());

      for (Entry var5 : this.getXPBoostMap().entrySet()) {
         this.savePerk(var1, (Perk)var5.getKey());
         var1.putInt((int)var5.getValue());
      }
   }

    void loadCompact(ByteBuffer var1) {
      this.ID = -1;
      this.torso = GameWindow.ReadString(var1);
      this.bFemale = var1.get() == 1;
      this.extra.clear();
      if (var1.get() == 1) {
    uint8_t var2 = var1.get();

         for (int var3 = 0; var3 < var2; var3++) {
    std::string var4 = GameWindow.ReadString(var1);
            this.extra.push_back(var4);
         }
      }
   }

    void saveCompact(ByteBuffer var1) {
      GameWindow.WriteString(var1, this.torso);
      var1.put((byte)(this.bFemale ? 1 : 0));
      if (!this.extra.empty()) {
         var1.put((byte)1);
         var1.put((byte)this.extra.size());

         for (std::string var3 : this.extra) {
            GameWindow.WriteString(var1, var3);
         }
      } else {
         var1.put((byte)0);
      }
   }

    void addObservation(const std::string& var1) {
    Observation var2 = ObservationFactory.getObservation(var1);
      if (var2 != nullptr) {
         this.Observations.push_back(var2);
      }
   }

    void doStats() {
      this.bravery = Rand.Next(2) == 0 ? 10.0F : 0.0F;
      this.aggressiveness = Rand.Next(2) == 0 ? 10.0F : 0.0F;
      this.compassion = 10.0F - this.aggressiveness;
      this.loner = Rand.Next(2) == 0 ? 10.0F : 0.0F;
      this.temper = Rand.Next(2) == 0 ? 10.0F : 0.0F;
      this.friendliness = 10.0F - this.loner;
      this.favourindoors = Rand.Next(2) == 0 ? 10.0F : 0.0F;
      this.loyalty = Rand.Next(2) == 0 ? 10.0F : 0.0F;
   }

    int getMetCount(SurvivorDesc var1) {
      return this.MetCount.containsKey(var1.ID) ? this.MetCount.get(var1.ID) : 0;
   }

    std::string getForename() {
      return this.forename;
   }

    void setForename(const std::string& var1) {
      this.forename = var1;
   }

    int getID() {
      return this.ID;
   }

    void setID(int var1) {
      this.ID = var1;
   }

    IsoGameCharacter getInstance() {
      return this.Instance;
   }

    void setInstance(IsoGameCharacter var1) {
      this.Instance = var1;
   }

    std::string getSurname() {
      return this.surname;
   }

    void setSurname(const std::string& var1) {
      this.surname = var1;
   }

    std::string getInventoryScript() {
      return this.InventoryScript;
   }

    void setInventoryScript(const std::string& var1) {
      this.InventoryScript = var1;
   }

    std::string getTorso() {
      return this.torso;
   }

    void setTorso(const std::string& var1) {
      this.torso = var1;
   }

   public std::unordered_map<int, int> getMetCount() {
      return this.MetCount;
   }

    float getBravery() {
      return this.bravery;
   }

    void setBravery(float var1) {
      this.bravery = var1;
   }

    float getLoner() {
      return this.loner;
   }

    void setLoner(float var1) {
      this.loner = var1;
   }

    float getAggressiveness() {
      return this.aggressiveness;
   }

    void setAggressiveness(float var1) {
      this.aggressiveness = var1;
   }

    float getCompassion() {
      return this.compassion;
   }

    void setCompassion(float var1) {
      this.compassion = var1;
   }

    float getTemper() {
      return this.temper;
   }

    void setTemper(float var1) {
      this.temper = var1;
   }

    float getFriendliness() {
      return this.friendliness;
   }

    void setFriendliness(float var1) {
      this.friendliness = var1;
   }

    float getFavourindoors() {
      return this.favourindoors;
   }

    void setFavourindoors(float var1) {
      this.favourindoors = var1;
   }

    float getLoyalty() {
      return this.loyalty;
   }

    void setLoyalty(float var1) {
      this.loyalty = var1;
   }

    std::string getProfession() {
      return this.Profession;
   }

    void setProfession(const std::string& var1) {
      this.Profession = var1;
   }

    bool isAggressive() {
      for (Observation var2 : this.Observations) {
         if ("Aggressive" == var2.getTraitID())) {
    return true;
         }
      }

    return false;
   }

   public std::vector<Observation> getObservations() {
      return this.Observations;
   }

    bool isFriendly() {
      for (Observation var2 : this.Observations) {
         if ("Friendly" == var2.getTraitID())) {
    return true;
         }
      }

    return false;
   }

    SurvivorType getType() {
      return this.type;
   }

    void setType(SurvivorType var1) {
      this.type = var1;
   }

    void setFemale(bool var1) {
      this.bFemale = var1;
   }

   public std::vector<std::string> getExtras() {
      return this.extra;
   }

   public std::vector<ImmutableColor> getCommonHairColor() {
    return HairCommonColors;
   }

    static void addTrouserColor(ColorInfo var0) {
      TrouserCommonColors.push_back(var0.toColor());
   }

    static void addHairColor(ColorInfo var0) {
      HairCommonColors.push_back(var0.toImmutableColor());
   }

    static Color getRandomSkinColor() {
      return OutfitRNG.Next(3) == 0
         ? std::make_shared<Color>(OutfitRNG.Next(0.5F, 0.6F), OutfitRNG.Next(0.3F, 0.4F), OutfitRNG.Next(0.15F, 0.23F))
         : std::make_shared<Color>(OutfitRNG.Next(0.9F, 1.0F), OutfitRNG.Next(0.75F, 0.88F), OutfitRNG.Next(0.45F, 0.58F));
   }
}
} // namespace characters
} // namespace zombie
