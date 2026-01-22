#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/SurvivorFactory/SurvivorType.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoCell.h"

namespace zombie {
namespace characters {


class SurvivorFactory {
public:
   public static const std::vector<std::string> FemaleForenames = std::make_unique<std::vector<>>();
   public static const std::vector<std::string> MaleForenames = std::make_unique<std::vector<>>();
   public static const std::vector<std::string> Surnames = std::make_unique<std::vector<>>();

    static void Reset() {
      FemaleForenames.clear();
      MaleForenames.clear();
      Surnames.clear();
      SurvivorDesc.HairCommonColors.clear();
      SurvivorDesc.TrouserCommonColors.clear();
   }

   public static SurvivorDesc[] CreateFamily(int var0) {
      SurvivorDesc[] var1 = new SurvivorDesc[var0];

      for (int var2 = 0; var2 < var0; var2++) {
         var1[var2] = CreateSurvivor();
         if (var2 > 0) {
            var1[var2].surname = var1[0].surname;
         }
      }

    return var1;
   }

    static SurvivorDesc CreateSurvivor() {
      switch (Rand.Next(3)) {
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

    static SurvivorDesc CreateSurvivor(SurvivorType var0, bool var1) {
    SurvivorDesc var2 = std::make_shared<SurvivorDesc>();
      var2.setType(var0);
      IsoGameCharacter.getSurvivorMap().put(var2.ID, var2);
      var2.setFemale(var1);
      randomName(var2);
      if (var2.isFemale()) {
         setTorso(var2);
      } else {
         setTorso(var2);
      }

    return var2;
   }

    static void setTorso(SurvivorDesc var0) {
      if (var0.isFemale()) {
         var0.torso = "Kate";
      } else {
         var0.torso = "Male";
      }
   }

    static SurvivorDesc CreateSurvivor(SurvivorType var0) {
    return CreateSurvivor();
   }

   public static SurvivorDesc[] CreateSurvivorGroup(int var0) {
      SurvivorDesc[] var1 = new SurvivorDesc[var0];

      for (int var2 = 0; var2 < var0; var2++) {
         var1[var2] = CreateSurvivor();
      }

    return var1;
   }

    static IsoSurvivor InstansiateInCell(SurvivorDesc var0, IsoCell var1, int var2, int var3, int var4) {
      var0.Instance = std::make_shared<IsoSurvivor>(var0, var1, var2, var3, var4);
      return (IsoSurvivor)var0.Instance;
   }

    static void randomName(SurvivorDesc var0) {
      if (var0.isFemale()) {
         var0.forename = FemaleForenames.get(Rand.Next(FemaleForenames.size()));
      } else {
         var0.forename = MaleForenames.get(Rand.Next(MaleForenames.size()));
      }

      var0.surname = Surnames.get(Rand.Next(Surnames.size()));
   }

    static void addSurname(const std::string& var0) {
      Surnames.push_back(var0);
   }

    static void addFemaleForename(const std::string& var0) {
      FemaleForenames.push_back(var0);
   }

    static void addMaleForename(const std::string& var0) {
      MaleForenames.push_back(var0);
   }

    static std::string getRandomSurname() {
      return Surnames.get(Rand.Next(Surnames.size()));
   }

    static std::string getRandomForename(bool var0) {
      return var0 ? FemaleForenames.get(Rand.Next(FemaleForenames.size())) : MaleForenames.get(Rand.Next(MaleForenames.size()));
   }
}
} // namespace characters
} // namespace zombie
