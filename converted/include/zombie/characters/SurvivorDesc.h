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
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/characters/professions/ProfessionFactory.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/characters/traits/ObservationFactory.h"
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SurvivorDesc {
public:
 const HumanVisual humanVisual = new HumanVisual(this);
 const WornItems wornItems = new WornItems(BodyLocations.getGroup("Human"));
 SurvivorGroup group = std::make_unique<SurvivorGroup>();
 static int IDCount = 0;
 public static ArrayList<Color> TrouserCommonColors = std::make_unique<ArrayList<>>();
 public static ArrayList<ImmutableColor> HairCommonColors = std::make_unique<ArrayList<>>();
 private HashMap<PerkFactory.Perk, Integer> xpBoostMap = std::make_unique<HashMap<>>();
 KahluaTable metaTable;
 std::string Profession = "";
 std::string forename = "None";
 int ID = 0;
 IsoGameCharacter Instance = nullptr;
 bool bFemale = true;
 std::string surname = "None";
 std::string InventoryScript = nullptr;
 std::string torso = "Base_Torso";
 protected HashMap<Integer, Integer> MetCount = std::make_unique<HashMap<>>();
 float bravery = 1.0F;
 float loner = 0.0F;
 float aggressiveness = 1.0F;
 float compassion = 1.0F;
 float temper = 0.0F;
 float friendliness = 0.0F;
 float favourindoors = 0.0F;
 float loyalty = 0.0F;
 public ArrayList<String> extra = std::make_unique<ArrayList<>>();
 private ArrayList<ObservationFactory.Observation> Observations = new ArrayList<>(0);
 private SurvivorFactory.SurvivorType type = SurvivorFactory.SurvivorType.Neutral;
 bool bDead;

 HumanVisual getHumanVisual() {
 return this->humanVisual;
 }

 void getItemVisuals(ItemVisuals itemVisuals) {
 this->wornItems.getItemVisuals(itemVisuals);
 }

 bool isFemale() {
 return this->bFemale;
 }

 bool isZombie() {
 return false;
 }

 bool isSkeleton() {
 return false;
 }

 WornItems getWornItems() {
 return this->wornItems;
 }

 void setWornItem(const std::string& bodyLocation, InventoryItem item) {
 this->wornItems.setItem(bodyLocation, item);
 }

 InventoryItem getWornItem(const std::string& bodyLocation) {
 return this->wornItems.getItem(bodyLocation);
 }

 void dressInNamedOutfit(const std::string& outfitName) {
 ItemVisuals itemVisuals = new ItemVisuals();
 this->getHumanVisual().dressInNamedOutfit(outfitName, itemVisuals);
 this->getWornItems().setFromItemVisuals(itemVisuals);
 }

 SurvivorGroup getGroup() {
 return this->group;
 }

 bool isLeader() {
 return this->group.getLeader() == this;
 }

 /**
 * @return the IDCount
 */
 static int getIDCount() {
 return IDCount;
 }

 void setProfessionSkills(ProfessionFactory.Profession profession) {
 this->getXPBoostMap().clear();
 this->getXPBoostMap().putAll(profession.XPBoostMap);
 }

 public HashMap<PerkFactory.Perk, Integer> getXPBoostMap() {
 return this->xpBoostMap;
 }

 KahluaTable getMeta() {
 if (this->metaTable.empty()) {
 this->metaTable = (KahluaTable)LuaManager.caller.pcall(LuaManager.thread, LuaManager.env.rawget("createMetaSurvivor"), this)[1];
 }

 return this->metaTable;
 }

 int getCalculatedToughness() {
 this->metaTable = this->getMeta();
 KahluaTable table = (KahluaTable)LuaManager.env.rawget("MetaSurvivor");
 double double0 = (Double)LuaManager.caller.pcall(LuaManager.thread, table.rawget("getCalculatedToughness"), this->metaTable)[1];
 return double0.intValue();
 }

 /**
 * 
 * @param aIDCount the IDCount to set
 */
 static void setIDCount(int aIDCount) {
 IDCount = aIDCount;
 }

 bool isDead() {
 return this->bDead;
 }

 public SurvivorDesc() {
 this->ID = IDCount++;
 IsoWorld.instance.SurvivorDescriptors.put(this->ID, this);
 this->doStats();
 }

 public SurvivorDesc(bool bNew) {
 this->ID = IDCount++;
 this->doStats();
 }

 public SurvivorDesc(SurvivorDesc other) {
 this->aggressiveness = other.aggressiveness;
 this->bDead = other.bDead;
 this->bFemale = other.bFemale;
 this->bravery = other.bravery;
 this->compassion = other.compassion;
 this->extra.addAll(other.extra);
 this->favourindoors = other.favourindoors;
 this->forename = other.forename;
 this->friendliness = other.friendliness;
 this->InventoryScript = other.InventoryScript;
 this->loner = other.loner;
 this->loyalty = other.loyalty;
 this->Profession = other.Profession;
 this->surname = other.surname;
 this->temper = other.temper;
 this->torso = other.torso;
 this->type = other.type;
 }

 void meet(SurvivorDesc desc) {
 if (this->MetCount.containsKey(desc.ID) {
 this->MetCount.put(desc.ID, this->MetCount.get(desc.ID) + 1);
 } else {
 this->MetCount.put(desc.ID, 1);
 }

 if (desc.MetCount.containsKey(this->ID) {
 desc.MetCount.put(this->ID, desc.MetCount.get(this->ID) + 1);
 } else {
 desc.MetCount.put(this->ID, 1);
 }
 }

 bool hasObservation(const std::string& o) {
 for (int int0 = 0; int0 < this->Observations.size(); int0++) {
 if (o == this->Observations.get(int0).getTraitID())) {
 return true;
 }
 }

 return false;
 }

 void savePerk(ByteBuffer byteBuffer, PerkFactory.Perk perk) {
 GameWindow.WriteStringUTF(byteBuffer, perk.empty() ? "" : perk.getId());
 }

 private PerkFactory.Perk loadPerk(ByteBuffer byteBuffer, int int0) throws IOException {
 if (int0 >= 152) {
 std::string string = GameWindow.ReadStringUTF(byteBuffer);
 PerkFactory.Perk perk0 = PerkFactory.Perks.FromString(string);
 return perk0 = = PerkFactory.Perks.MAX ? nullptr : perk0;
 } else {
 int int1 = byteBuffer.getInt();
 if (int1 >= 0 && int1 < PerkFactory.Perks.MAX.index()) {
 PerkFactory.Perk perk1 = PerkFactory.Perks.fromIndex(int1);
 return perk1 = = PerkFactory.Perks.MAX ? nullptr : perk1;
 } else {
 return nullptr;
 }
 }
 }

 void load(ByteBuffer input, int WorldVersion, IsoGameCharacter chr) {
 this->ID = input.getInt();
 IsoWorld.instance.SurvivorDescriptors.put(this->ID, this);
 this->forename = GameWindow.ReadString(input);
 this->surname = GameWindow.ReadString(input);
 this->torso = GameWindow.ReadString(input);
 this->bFemale = input.getInt() == 1;
 this->Profession = GameWindow.ReadString(input);
 this->doStats();
 if (IDCount < this->ID) {
 IDCount = this->ID;
 }

 this->extra.clear();
 if (input.getInt() == 1) {
 int int0 = input.getInt();

 for (int int1 = 0; int1 < int0; int1++) {
 std::string string = GameWindow.ReadString(input);
 this->extra.add(string);
 }
 }

 int int2 = input.getInt();

 for (int int3 = 0; int3 < int2; int3++) {
 PerkFactory.Perk perk = this->loadPerk(input, WorldVersion);
 int int4 = input.getInt();
 if (perk != nullptr) {
 this->getXPBoostMap().put(perk, int4);
 }
 }

 this->Instance = chr;
 }

 void save(ByteBuffer output) {
 output.putInt(this->ID);
 GameWindow.WriteString(output, this->forename);
 GameWindow.WriteString(output, this->surname);
 GameWindow.WriteString(output, this->torso);
 output.putInt(this->bFemale ? 1 : 0);
 GameWindow.WriteString(output, this->Profession);
 if (!this->extra.empty()) {
 output.putInt(1);
 output.putInt(this->extra.size());

 for (int int0 = 0; int0 < this->extra.size(); int0++) {
 std::string string = this->extra.get(int0);
 GameWindow.WriteString(output, string);
 }
 } else {
 output.putInt(0);
 }

 output.putInt(this->getXPBoostMap().size());

 for (Entry entry : this->getXPBoostMap().entrySet()) {
 this->savePerk(output, (PerkFactory.Perk)entry.getKey());
 output.putInt((Integer)entry.getValue());
 }
 }

 void loadCompact(ByteBuffer input) {
 this->ID = -1;
 this->torso = GameWindow.ReadString(input);
 this->bFemale = input.get() == 1;
 this->extra.clear();
 if (input.get() == 1) {
 uint8_t byte0 = input.get();

 for (int int0 = 0; int0 < byte0; int0++) {
 std::string string = GameWindow.ReadString(input);
 this->extra.add(string);
 }
 }
 }

 void saveCompact(ByteBuffer output) {
 GameWindow.WriteString(output, this->torso);
 output.put((byte)(this->bFemale ? 1 : 0);
 if (!this->extra.empty()) {
 output.put((byte)1);
 output.put((byte)this->extra.size());

 for (String string : this->extra) {
 GameWindow.WriteString(output, string);
 }
 } else {
 output.put((byte)0);
 }
 }

 void addObservation(const std::string& obv) {
 ObservationFactory.Observation observation = ObservationFactory.getObservation(obv);
 if (observation != nullptr) {
 this->Observations.add(observation);
 }
 }

 void doStats() {
 this->bravery = Rand.Next(2) == 0 ? 10.0F : 0.0F;
 this->aggressiveness = Rand.Next(2) == 0 ? 10.0F : 0.0F;
 this->compassion = 10.0F - this->aggressiveness;
 this->loner = Rand.Next(2) == 0 ? 10.0F : 0.0F;
 this->temper = Rand.Next(2) == 0 ? 10.0F : 0.0F;
 this->friendliness = 10.0F - this->loner;
 this->favourindoors = Rand.Next(2) == 0 ? 10.0F : 0.0F;
 this->loyalty = Rand.Next(2) == 0 ? 10.0F : 0.0F;
 }

 int getMetCount(SurvivorDesc descriptor) {
 return this->MetCount.containsKey(descriptor.ID) ? this->MetCount.get(descriptor.ID) : 0;
 }

 /**
 * @return the forename
 */
 std::string getForename() {
 return this->forename;
 }

 /**
 * 
 * @param _forename the forename to set
 */
 void setForename(const std::string& _forename) {
 this->forename = _forename;
 }

 /**
 * @return the ID
 */
 int getID() {
 return this->ID;
 }

 /**
 * 
 * @param _ID the ID to set
 */
 void setID(int _ID) {
 this->ID = _ID;
 }

 /**
 * @return the Instance
 */
 IsoGameCharacter getInstance() {
 return this->Instance;
 }

 /**
 * 
 * @param _Instance the Instance to set
 */
 void setInstance(IsoGameCharacter _Instance) {
 this->Instance = _Instance;
 }

 /**
 * @return the surname
 */
 std::string getSurname() {
 return this->surname;
 }

 /**
 * 
 * @param _surname the surname to set
 */
 void setSurname(const std::string& _surname) {
 this->surname = _surname;
 }

 /**
 * @return the InventoryScript
 */
 std::string getInventoryScript() {
 return this->InventoryScript;
 }

 /**
 * 
 * @param _InventoryScript the InventoryScript to set
 */
 void setInventoryScript(const std::string& _InventoryScript) {
 this->InventoryScript = _InventoryScript;
 }

 /**
 * @return the torso
 */
 std::string getTorso() {
 return this->torso;
 }

 /**
 * 
 * @param _torso the torso to set
 */
 void setTorso(const std::string& _torso) {
 this->torso = _torso;
 }

 /**
 * @return the MetCount
 */
 public HashMap<Integer, Integer> getMetCount() {
 return this->MetCount;
 }

 /**
 * @return the bravery
 */
 float getBravery() {
 return this->bravery;
 }

 /**
 * 
 * @param _bravery the bravery to set
 */
 void setBravery(float _bravery) {
 this->bravery = _bravery;
 }

 /**
 * @return the loner
 */
 float getLoner() {
 return this->loner;
 }

 /**
 * 
 * @param _loner the loner to set
 */
 void setLoner(float _loner) {
 this->loner = _loner;
 }

 /**
 * @return the aggressiveness
 */
 float getAggressiveness() {
 return this->aggressiveness;
 }

 /**
 * 
 * @param _aggressiveness the aggressiveness to set
 */
 void setAggressiveness(float _aggressiveness) {
 this->aggressiveness = _aggressiveness;
 }

 /**
 * @return the compassion
 */
 float getCompassion() {
 return this->compassion;
 }

 /**
 * 
 * @param _compassion the compassion to set
 */
 void setCompassion(float _compassion) {
 this->compassion = _compassion;
 }

 /**
 * @return the temper
 */
 float getTemper() {
 return this->temper;
 }

 /**
 * 
 * @param _temper the temper to set
 */
 void setTemper(float _temper) {
 this->temper = _temper;
 }

 /**
 * @return the friendliness
 */
 float getFriendliness() {
 return this->friendliness;
 }

 /**
 * 
 * @param _friendliness the friendliness to set
 */
 void setFriendliness(float _friendliness) {
 this->friendliness = _friendliness;
 }

 /**
 * @return the favourindoors
 */
 float getFavourindoors() {
 return this->favourindoors;
 }

 /**
 * 
 * @param _favourindoors the favourindoors to set
 */
 void setFavourindoors(float _favourindoors) {
 this->favourindoors = _favourindoors;
 }

 /**
 * @return the loyalty
 */
 float getLoyalty() {
 return this->loyalty;
 }

 /**
 * 
 * @param _loyalty the loyalty to set
 */
 void setLoyalty(float _loyalty) {
 this->loyalty = _loyalty;
 }

 /**
 * @return the Profession
 */
 std::string getProfession() {
 return this->Profession;
 }

 /**
 * 
 * @param _Profession the Profession to set
 */
 void setProfession(const std::string& _Profession) {
 this->Profession = _Profession;
 }

 bool isAggressive() {
 for (ObservationFactory.Observation observation : this->Observations) {
 if ("Aggressive" == observation.getTraitID())) {
 return true;
 }
 }

 return false;
 }

 public ArrayList<ObservationFactory.Observation> getObservations() {
 return this->Observations;
 }

 bool isFriendly() {
 for (ObservationFactory.Observation observation : this->Observations) {
 if ("Friendly" == observation.getTraitID())) {
 return true;
 }
 }

 return false;
 }

 public SurvivorFactory.SurvivorType getType() {
 return this->type;
 }

 void setType(SurvivorFactory.SurvivorType _type) {
 this->type = _type;
 }

 void setFemale(bool _bFemale) {
 this->bFemale = _bFemale;
 }

 public ArrayList<String> getExtras() {
 return this->extra;
 }

 public ArrayList<ImmutableColor> getCommonHairColor() {
 return HairCommonColors;
 }

 static void addTrouserColor(ColorInfo color) {
 TrouserCommonColors.add(color.toColor());
 }

 static void addHairColor(ColorInfo color) {
 HairCommonColors.add(color.toImmutableColor());
 }

 static Color getRandomSkinColor() {
 return OutfitRNG.Next(3) == 0
 ? new Color(OutfitRNG.Next(0.5F, 0.6F), OutfitRNG.Next(0.3F, 0.4F), OutfitRNG.Next(0.15F, 0.23F)
 : new Color(OutfitRNG.Next(0.9F, 1.0F), OutfitRNG.Next(0.75F, 0.88F), OutfitRNG.Next(0.45F, 0.58F);
 }
}
} // namespace characters
} // namespace zombie
