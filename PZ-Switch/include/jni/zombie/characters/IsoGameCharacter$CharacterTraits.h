#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/traits/TraitCollection.h"
#include "zombie/characters/traits/TraitCollection/TraitSlot.h"

namespace zombie {
namespace characters {


class IsoGameCharacter {
:
    const TraitSlot Obese;
    const TraitSlot Athletic;
    const TraitSlot Overweight;
    const TraitSlot Unfit;
    const TraitSlot Emaciated;
    const TraitSlot Graceful;
    const TraitSlot Clumsy;
    const TraitSlot Strong;
    const TraitSlot Weak;
    const TraitSlot VeryUnderweight;
    const TraitSlot Underweight;
    const TraitSlot FastHealer;
    const TraitSlot SlowHealer;
    const TraitSlot ShortSighted;
    const TraitSlot EagleEyed;
    const TraitSlot Agoraphobic;
    const TraitSlot Claustophobic;
    const TraitSlot AdrenalineJunkie;
    const TraitSlot OutOfShape;
    const TraitSlot HighThirst;
    const TraitSlot LowThirst;
    const TraitSlot HeartyAppitite;
    const TraitSlot LightEater;
    const TraitSlot Cowardly;
    const TraitSlot Brave;
    const TraitSlot Brooding;
    const TraitSlot Insomniac;
    const TraitSlot NeedsLessSleep;
    const TraitSlot NeedsMoreSleep;
    const TraitSlot Asthmatic;
    const TraitSlot PlaysFootball;
    const TraitSlot Jogger;
    const TraitSlot NightVision;
    const TraitSlot FastLearner;
    const TraitSlot SlowLearner;
    const TraitSlot Pacifist;
    const TraitSlot Feeble;
    const TraitSlot Stout;
    const TraitSlot ShortTemper;
    const TraitSlot Patient;
    const TraitSlot Injured;
    const TraitSlot Inconspicuous;
    const TraitSlot Conspicuous;
    const TraitSlot Desensitized;
    const TraitSlot NightOwl;
    const TraitSlot Hemophobic;
    const TraitSlot Burglar;
    const TraitSlot KeenHearing;
    const TraitSlot Deaf;
    const TraitSlot HardOfHearing;
    const TraitSlot ThinSkinned;
    const TraitSlot ThickSkinned;
    const TraitSlot Marksman;
    const TraitSlot Outdoorsman;
    const TraitSlot Lucky;
    const TraitSlot Unlucky;
    const TraitSlot Nutritionist;
    const TraitSlot Nutritionist2;
    const TraitSlot Organized;
    const TraitSlot Disorganized;
    const TraitSlot Axeman;
    const TraitSlot IronGut;
    const TraitSlot WeakStomach;
    const TraitSlot HeavyDrinker;
    const TraitSlot LightDrinker;
    const TraitSlot Resilient;
    const TraitSlot ProneToIllness;
    const TraitSlot SpeedDemon;
    const TraitSlot SundayDriver;
    const TraitSlot Smoker;
    const TraitSlot Hypercondriac;
    const TraitSlot Illiterate;

    IsoGameCharacter$CharacterTraits(IsoGameCharacter var1) {
      this.this$0 = var1;
      this.Obese = this.getTraitSlot("Obese");
      this.Athletic = this.getTraitSlot("Athletic");
      this.Overweight = this.getTraitSlot("Overweight");
      this.Unfit = this.getTraitSlot("Unfit");
      this.Emaciated = this.getTraitSlot("Emaciated");
      this.Graceful = this.getTraitSlot("Graceful");
      this.Clumsy = this.getTraitSlot("Clumsy");
      this.Strong = this.getTraitSlot("Strong");
      this.Weak = this.getTraitSlot("Weak");
      this.VeryUnderweight = this.getTraitSlot("Very Underweight");
      this.Underweight = this.getTraitSlot("Underweight");
      this.FastHealer = this.getTraitSlot("FastHealer");
      this.SlowHealer = this.getTraitSlot("SlowHealer");
      this.ShortSighted = this.getTraitSlot("ShortSighted");
      this.EagleEyed = this.getTraitSlot("EagleEyed");
      this.Agoraphobic = this.getTraitSlot("Agoraphobic");
      this.Claustophobic = this.getTraitSlot("Claustophobic");
      this.AdrenalineJunkie = this.getTraitSlot("AdrenalineJunkie");
      this.OutOfShape = this.getTraitSlot("Out of Shape");
      this.HighThirst = this.getTraitSlot("HighThirst");
      this.LowThirst = this.getTraitSlot("LowThirst");
      this.HeartyAppitite = this.getTraitSlot("HeartyAppitite");
      this.LightEater = this.getTraitSlot("LightEater");
      this.Cowardly = this.getTraitSlot("Cowardly");
      this.Brave = this.getTraitSlot("Brave");
      this.Brooding = this.getTraitSlot("Brooding");
      this.Insomniac = this.getTraitSlot("Insomniac");
      this.NeedsLessSleep = this.getTraitSlot("NeedsLessSleep");
      this.NeedsMoreSleep = this.getTraitSlot("NeedsMoreSleep");
      this.Asthmatic = this.getTraitSlot("Asthmatic");
      this.PlaysFootball = this.getTraitSlot("PlaysFootball");
      this.Jogger = this.getTraitSlot("Jogger");
      this.NightVision = this.getTraitSlot("NightVision");
      this.FastLearner = this.getTraitSlot("FastLearner");
      this.SlowLearner = this.getTraitSlot("SlowLearner");
      this.Pacifist = this.getTraitSlot("Pacifist");
      this.Feeble = this.getTraitSlot("Feeble");
      this.Stout = this.getTraitSlot("Stout");
      this.ShortTemper = this.getTraitSlot("ShortTemper");
      this.Patient = this.getTraitSlot("Patient");
      this.Injured = this.getTraitSlot("Injured");
      this.Inconspicuous = this.getTraitSlot("Inconspicuous");
      this.Conspicuous = this.getTraitSlot("Conspicuous");
      this.Desensitized = this.getTraitSlot("Desensitized");
      this.NightOwl = this.getTraitSlot("NightOwl");
      this.Hemophobic = this.getTraitSlot("Hemophobic");
      this.Burglar = this.getTraitSlot("Burglar");
      this.KeenHearing = this.getTraitSlot("KeenHearing");
      this.Deaf = this.getTraitSlot("Deaf");
      this.HardOfHearing = this.getTraitSlot("HardOfHearing");
      this.ThinSkinned = this.getTraitSlot("ThinSkinned");
      this.ThickSkinned = this.getTraitSlot("ThickSkinned");
      this.Marksman = this.getTraitSlot("Marksman");
      this.Outdoorsman = this.getTraitSlot("Outdoorsman");
      this.Lucky = this.getTraitSlot("Lucky");
      this.Unlucky = this.getTraitSlot("Unlucky");
      this.Nutritionist = this.getTraitSlot("Nutritionist");
      this.Nutritionist2 = this.getTraitSlot("Nutritionist2");
      this.Organized = this.getTraitSlot("Organized");
      this.Disorganized = this.getTraitSlot("Disorganized");
      this.Axeman = this.getTraitSlot("Axeman");
      this.IronGut = this.getTraitSlot("IronGut");
      this.WeakStomach = this.getTraitSlot("WeakStomach");
      this.HeavyDrinker = this.getTraitSlot("HeavyDrinker");
      this.LightDrinker = this.getTraitSlot("LightDrinker");
      this.Resilient = this.getTraitSlot("Resilient");
      this.ProneToIllness = this.getTraitSlot("ProneToIllness");
      this.SpeedDemon = this.getTraitSlot("SpeedDemon");
      this.SundayDriver = this.getTraitSlot("SundayDriver");
      this.Smoker = this.getTraitSlot("Smoker");
      this.Hypercondriac = this.getTraitSlot("Hypercondriac");
      this.Illiterate = this.getTraitSlot("Illiterate");
   }

    bool isIlliterate() {
      return this.Illiterate.isSet();
   }
}
} // namespace characters
} // namespace zombie
