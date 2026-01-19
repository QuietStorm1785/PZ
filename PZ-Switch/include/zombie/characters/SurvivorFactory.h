#pragma once
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoCell.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SurvivorFactory {
public:
public
 static ArrayList<String> FemaleForenames =
 std::make_unique<ArrayList<>>();
public
 static ArrayList<String> MaleForenames =
 std::make_unique<ArrayList<>>();
public
 static ArrayList<String> Surnames = std::make_unique<ArrayList<>>();

 static void Reset() {
 FemaleForenames.clear();
 MaleForenames.clear();
 Surnames.clear();
 SurvivorDesc.HairCommonColors.clear();
 SurvivorDesc.TrouserCommonColors.clear();
 }

public
 static SurvivorDesc[] CreateFamily(int nCount) {
 SurvivorDesc[] survivorDescs = new SurvivorDesc[nCount];

 for (int int0 = 0; int0 < nCount; int0++) {
 survivorDescs[int0] = CreateSurvivor();
 if (int0 > 0) {
 survivorDescs[int0].surname = survivorDescs[0].surname;
 }
 }

 return survivorDescs;
 }

 static SurvivorDesc CreateSurvivor() {
 switch (Rand.Next(3) {
 case 0:
 return CreateSurvivor();
 case 1:
 return CreateSurvivor();
 case 2:
 return CreateSurvivor();
 default:
 return nullptr;
 }
 }

 static SurvivorDesc CreateSurvivor(SurvivorFactory.SurvivorType survivorType,
 bool bFemale) {
 SurvivorDesc survivorDesc = new SurvivorDesc();
 survivorDesc.setType(survivorType);
 IsoGameCharacter.getSurvivorMap().put(survivorDesc.ID, survivorDesc);
 survivorDesc.setFemale(bFemale);
 randomName(survivorDesc);
 if (survivorDesc.isFemale()) {
 setTorso(survivorDesc);
 } else {
 setTorso(survivorDesc);
 }

 return survivorDesc;
 }

 static void setTorso(SurvivorDesc survivor) {
 if (survivor.isFemale()) {
 survivor.torso = "Kate";
 } else {
 survivor.torso = "Male";
 }
 }

 static SurvivorDesc
 CreateSurvivor(SurvivorFactory.SurvivorType survivorType) {
 return CreateSurvivor();
 }

public
 static SurvivorDesc[] CreateSurvivorGroup(int nCount) {
 SurvivorDesc[] survivorDescs = new SurvivorDesc[nCount];

 for (int int0 = 0; int0 < nCount; int0++) {
 survivorDescs[int0] = CreateSurvivor();
 }

 return survivorDescs;
 }

 static IsoSurvivor InstansiateInCell(SurvivorDesc desc, IsoCell cell, int x,
 int y, int z) {
 desc.Instance = new IsoSurvivor(desc, cell, x, y, z);
 return (IsoSurvivor)desc.Instance;
 }

 static void randomName(SurvivorDesc desc) {
 if (desc.isFemale()) {
 desc.forename = FemaleForenames.get(Rand.Next(FemaleForenames.size()));
 } else {
 desc.forename = MaleForenames.get(Rand.Next(MaleForenames.size()));
 }

 desc.surname = Surnames.get(Rand.Next(Surnames.size()));
 }

 static void addSurname(std::string_view surName) { Surnames.add(surName); }

 static void addFemaleForename(std::string_view forename) {
 FemaleForenames.add(forename);
 }

 static void addMaleForename(std::string_view forename) {
 MaleForenames.add(forename);
 }

 static std::string getRandomSurname() {
 return Surnames.get(Rand.Next(Surnames.size()));
 }

 static std::string getRandomForename(bool bFemale) {
 return bFemale ? FemaleForenames.get(Rand.Next(FemaleForenames.size()))
 : MaleForenames.get(Rand.Next(MaleForenames.size()));
 }

public
 static enum SurvivorType { Friendly, Neutral, Aggressive; }
}
} // namespace characters
} // namespace zombie
