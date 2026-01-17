#pragma once
#include "zombie/core/Translator.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace Moodles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

enum class MoodleType {
  Endurance, Tired, Hungry, Panic, Sick, Bored, Unhappy, Bleeding, Wet,
  HasACold, Angry, Stress, Thirst, Injured, Pain, HeavyLoad, Drunk, Dead,
  Zombie, Hyperthermia, Hypothermia, Windchill, CantSprint, FoodEaten, MAX;

  static MoodleType FromIndex(int index){switch (index){
    case 0 : return Endurance; case 1 : return Tired; case 2 : return Hungry;
    case 3 : return Panic;
    case 4 : return Sick;
    case 5 : return Bored;
    case 6 : return Unhappy;
    case 7 : return Bleeding;
    case 8 : return Wet;
    case 9 : return HasACold;
    case 10 : return Angry;
    case 11 : return Stress;
    case 12 : return Thirst;
    case 13 : return Injured;
    case 14 : return Pain;
    case 15 : return HeavyLoad;
    case 16 : return Drunk;
    case 17 : return Dead;
    case 18 : return Zombie;
    case 19 : return FoodEaten;
    case 20 : return Hyperthermia;
    case 21 : return Hypothermia;
    case 22 : return Windchill;
    case 23 : return CantSprint;
    default : return MAX;
  }
} // namespace Moodles

static MoodleType FromString(const std::string &str) {
  if (str == "Endurance")) {
    return Endurance;
        }
  else if (str == "Tired")) {
    return Tired;
        }
  else if (str == "Hungry")) {
    return Hungry;
        }
  else if (str == "Panic")) {
    return Panic;
        }
  else if (str == "Sick")) {
    return Sick;
        }
  else if (str == "Bored")) {
    return Bored;
        }
  else if (str == "Unhappy")) {
    return Unhappy;
        }
  else if (str == "Bleeding")) {
    return Bleeding;
        }
  else if (str == "Wet")) {
    return Wet;
        }
  else if (str == "HasACold")) {
    return HasACold;
        }
  else if (str == "Angry")) {
    return Angry;
        }
  else if (str == "Stress")) {
    return Stress;
        }
  else if (str == "Thirst")) {
    return Thirst;
        }
  else if (str == "Injured")) {
    return Injured;
        }
  else if (str == "Pain")) {
    return Pain;
        }
  else if (str == "HeavyLoad")) {
    return HeavyLoad;
        }
  else if (str == "Drunk")) {
    return Drunk;
        }
  else if (str == "Dead")) {
    return Dead;
        }
  else if (str == "Zombie")) {
    return Zombie;
        }
  else if (str == "Windchill")) {
    return Windchill;
        }
  else if (str == "FoodEaten")) {
    return FoodEaten;
        }
  else if (str == "Hyperthermia")) {
    return Hyperthermia;
        }
  else if (str == "Hypothermia")) {
    return Hypothermia;
        }
  else {
            return str == "CantSprint") ? CantSprint : MAX;
  }
}

static std::string getDisplayName(MoodleType MT, int Level) {
  if (Level > 4) {
    Level = 4;
  }

  if (Level == 0) {
    return "Invalid Moodle Level";
  } else if (MT == CantSprint) {
    return Translator.getText("Moodles_CantSprint");
  } else {
    if (MT == Endurance) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_endurance_lvl1");
      case 2:
        return Translator.getText("Moodles_endurance_lvl2");
      case 3:
        return Translator.getText("Moodles_endurance_lvl3");
      case 4:
        return Translator.getText("Moodles_endurance_lvl4");
      }
    }

    if (MT == Angry) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_angry_lvl1");
      case 2:
        return Translator.getText("Moodles_angry_lvl2");
      case 3:
        return Translator.getText("Moodles_angry_lvl3");
      case 4:
        return Translator.getText("Moodles_angry_lvl4");
      }
    }

    if (MT == Stress) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_stress_lvl1");
      case 2:
        return Translator.getText("Moodles_stress_lvl2");
      case 3:
        return Translator.getText("Moodles_stress_lvl3");
      case 4:
        return Translator.getText("Moodles_stress_lvl4");
      }
    }

    if (MT == Thirst) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_thirst_lvl1");
      case 2:
        return Translator.getText("Moodles_thirst_lvl2");
      case 3:
        return Translator.getText("Moodles_thirst_lvl3");
      case 4:
        return Translator.getText("Moodles_thirst_lvl4");
      }
    }

    if (MT == Tired) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_tired_lvl1");
      case 2:
        return Translator.getText("Moodles_tired_lvl2");
      case 3:
        return Translator.getText("Moodles_tired_lvl3");
      case 4:
        return Translator.getText("Moodles_tired_lvl4");
      }
    }

    if (MT == Hungry) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_hungry_lvl1");
      case 2:
        return Translator.getText("Moodles_hungry_lvl2");
      case 3:
        return Translator.getText("Moodles_hungry_lvl3");
      case 4:
        return Translator.getText("Moodles_hungry_lvl4");
      }
    }

    if (MT == Panic) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_panic_lvl1");
      case 2:
        return Translator.getText("Moodles_panic_lvl2");
      case 3:
        return Translator.getText("Moodles_panic_lvl3");
      case 4:
        return Translator.getText("Moodles_panic_lvl4");
      }
    }

    if (MT == Sick) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_sick_lvl1");
      case 2:
        return Translator.getText("Moodles_sick_lvl2");
      case 3:
        return Translator.getText("Moodles_sick_lvl3");
      case 4:
        return Translator.getText("Moodles_sick_lvl4");
      }
    }

    if (MT == Bored) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_bored_lvl1");
      case 2:
        return Translator.getText("Moodles_bored_lvl2");
      case 3:
        return Translator.getText("Moodles_bored_lvl3");
      case 4:
        return Translator.getText("Moodles_bored_lvl4");
      }
    }

    if (MT == Unhappy) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_unhappy_lvl1");
      case 2:
        return Translator.getText("Moodles_unhappy_lvl2");
      case 3:
        return Translator.getText("Moodles_unhappy_lvl3");
      case 4:
        return Translator.getText("Moodles_unhappy_lvl4");
      }
    }

    if (MT == Bleeding) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_bleeding_lvl1");
      case 2:
        return Translator.getText("Moodles_bleeding_lvl2");
      case 3:
        return Translator.getText("Moodles_bleeding_lvl3");
      case 4:
        return Translator.getText("Moodles_bleeding_lvl4");
      }
    }

    if (MT == Wet) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_wet_lvl1");
      case 2:
        return Translator.getText("Moodles_wet_lvl2");
      case 3:
        return Translator.getText("Moodles_wet_lvl3");
      case 4:
        return Translator.getText("Moodles_wet_lvl4");
      }
    }

    if (MT == HasACold) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_hascold_lvl1");
      case 2:
        return Translator.getText("Moodles_hascold_lvl2");
      case 3:
        return Translator.getText("Moodles_hascold_lvl3");
      case 4:
        return Translator.getText("Moodles_hascold_lvl4");
      }
    }

    if (MT == Injured) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_injured_lvl1");
      case 2:
        return Translator.getText("Moodles_injured_lvl2");
      case 3:
        return Translator.getText("Moodles_injured_lvl3");
      case 4:
        return Translator.getText("Moodles_injured_lvl4");
      }
    }

    if (MT == Pain) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_pain_lvl1");
      case 2:
        return Translator.getText("Moodles_pain_lvl2");
      case 3:
        return Translator.getText("Moodles_pain_lvl3");
      case 4:
        return Translator.getText("Moodles_pain_lvl4");
      }
    }

    if (MT == HeavyLoad) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_heavyload_lvl1");
      case 2:
        return Translator.getText("Moodles_heavyload_lvl2");
      case 3:
        return Translator.getText("Moodles_heavyload_lvl3");
      case 4:
        return Translator.getText("Moodles_heavyload_lvl4");
      }
    }

    if (MT == Drunk) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_drunk_lvl1");
      case 2:
        return Translator.getText("Moodles_drunk_lvl2");
      case 3:
        return Translator.getText("Moodles_drunk_lvl3");
      case 4:
        return Translator.getText("Moodles_drunk_lvl4");
      }
    }

    if (MT == Dead) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_dead_lvl1");
      case 2:
        return Translator.getText("Moodles_dead_lvl1");
      case 3:
        return Translator.getText("Moodles_dead_lvl1");
      case 4:
        return Translator.getText("Moodles_dead_lvl1");
      }
    }

    if (MT == Zombie) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_zombie_lvl1");
      case 2:
        return Translator.getText("Moodles_zombie_lvl1");
      case 3:
        return Translator.getText("Moodles_zombie_lvl1");
      case 4:
        return Translator.getText("Moodles_zombie_lvl1");
      }
    }

    if (MT == Windchill) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_windchill_lvl1");
      case 2:
        return Translator.getText("Moodles_windchill_lvl2");
      case 3:
        return Translator.getText("Moodles_windchill_lvl3");
      case 4:
        return Translator.getText("Moodles_windchill_lvl4");
      }
    }

    if (MT == FoodEaten) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_foodeaten_lvl1");
      case 2:
        return Translator.getText("Moodles_foodeaten_lvl2");
      case 3:
        return Translator.getText("Moodles_foodeaten_lvl3");
      case 4:
        return Translator.getText("Moodles_foodeaten_lvl4");
      }
    }

    if (MT == Hyperthermia) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_hyperthermia_lvl1");
      case 2:
        return Translator.getText("Moodles_hyperthermia_lvl2");
      case 3:
        return Translator.getText("Moodles_hyperthermia_lvl3");
      case 4:
        return Translator.getText("Moodles_hyperthermia_lvl4");
      }
    }

    if (MT == Hypothermia) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_hypothermia_lvl1");
      case 2:
        return Translator.getText("Moodles_hypothermia_lvl2");
      case 3:
        return Translator.getText("Moodles_hypothermia_lvl3");
      case 4:
        return Translator.getText("Moodles_hypothermia_lvl4");
      }
    }

    return "Unkown Moodle Type";
  }
}

static std::string getDescriptionText(MoodleType MT, int Level) {
  if (Level > 4) {
    Level = 4;
  }

  if (Level == 0) {
    return "Invalid Moodle Level";
  } else if (MT == CantSprint) {
    return Translator.getText("Moodles_CantSprint_desc");
  } else {
    if (MT == Endurance) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_endurance_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_endurance_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_endurance_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_endurance_desc_lvl4");
      }
    }

    if (MT == Angry) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_angry_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_angry_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_angry_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_angry_desc_lvl4");
      }
    }

    if (MT == Stress) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_stress_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_stress_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_stress_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_stress_desc_lvl4");
      }
    }

    if (MT == Thirst) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_thirst_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_thirst_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_thirst_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_thirst_desc_lvl4");
      }
    }

    if (MT == Tired) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_tired_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_tired_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_tired_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_tired_desc_lvl4");
      }
    }

    if (MT == Hungry) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_hungry_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_hungry_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_hungry_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_hungry_desc_lvl4");
      }
    }

    if (MT == Panic) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_panic_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_panic_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_panic_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_panic_desc_lvl4");
      }
    }

    if (MT == Sick) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_sick_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_sick_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_sick_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_sick_desc_lvl4");
      }
    }

    if (MT == Bored) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_bored_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_bored_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_bored_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_bored_desc_lvl4");
      }
    }

    if (MT == Unhappy) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_unhappy_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_unhappy_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_unhappy_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_unhappy_desc_lvl4");
      }
    }

    if (MT == Bleeding) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_bleed_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_bleed_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_bleed_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_bleed_desc_lvl4");
      }
    }

    if (MT == Wet) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_wet_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_wet_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_wet_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_wet_desc_lvl4");
      }
    }

    if (MT == HasACold) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_hasacold_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_hasacold_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_hasacold_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_hasacold_desc_lvl4");
      }
    }

    if (MT == Injured) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_injured_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_injured_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_injured_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_injured_desc_lvl4");
      }
    }

    if (MT == Pain) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_pain_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_pain_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_pain_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_pain_desc_lvl4");
      }
    }

    if (MT == HeavyLoad) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_heavyload_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_heavyload_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_heavyload_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_heavyload_desc_lvl4");
      }
    }

    if (MT == Drunk) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_drunk_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_drunk_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_drunk_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_drunk_desc_lvl4");
      }
    }

    if (MT == Dead) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_dead_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_dead_desc_lvl1");
      case 3:
        return Translator.getText("Moodles_dead_desc_lvl1");
      case 4:
        return Translator.getText("Moodles_dead_desc_lvl1");
      }
    }

    if (MT == Zombie) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_zombified_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_zombified_desc_lvl1");
      case 3:
        return Translator.getText("Moodles_zombified_desc_lvl1");
      case 4:
        return Translator.getText("Moodles_zombified_desc_lvl1");
      }
    }

    if (MT == Windchill) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_windchill_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_windchill_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_windchill_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_windchill_desc_lvl4");
      }
    }

    if (MT == FoodEaten) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_foodeaten_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_foodeaten_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_foodeaten_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_foodeaten_desc_lvl4");
      }
    }

    if (MT == Hyperthermia) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_hyperthermia_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_hyperthermia_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_hyperthermia_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_hyperthermia_desc_lvl4");
      }
    }

    if (MT == Hypothermia) {
      switch (Level) {
      case 1:
        return Translator.getText("Moodles_hypothermia_desc_lvl1");
      case 2:
        return Translator.getText("Moodles_hypothermia_desc_lvl2");
      case 3:
        return Translator.getText("Moodles_hypothermia_desc_lvl3");
      case 4:
        return Translator.getText("Moodles_hypothermia_desc_lvl4");
      }
    }

    return "Unkown Moodle Type";
  }
}

static int GoodBadNeutral(MoodleType MT) {
  if (MT == Endurance) {
    return 2;
  } else if (MT == Tired) {
    return 2;
  } else if (MT == Hungry) {
    return 2;
  } else if (MT == Panic) {
    return 2;
  } else if (MT == Sick) {
    return 2;
  } else if (MT == Bored) {
    return 2;
  } else if (MT == Unhappy) {
    return 2;
  } else if (MT == Bleeding) {
    return 2;
  } else if (MT == Wet) {
    return 2;
  } else if (MT == HasACold) {
    return 2;
  } else if (MT == Angry) {
    return 2;
  } else if (MT == Stress) {
    return 2;
  } else if (MT == Thirst) {
    return 2;
  } else if (MT == CantSprint) {
    return 2;
  } else if (MT == Injured) {
    return 2;
  } else if (MT == Pain) {
    return 2;
  } else if (MT == HeavyLoad) {
    return 2;
  } else if (MT == Drunk) {
    return 2;
  } else if (MT == Dead) {
    return 2;
  } else if (MT == Zombie) {
    return 2;
  } else if (MT == Windchill) {
    return 2;
  } else if (MT == FoodEaten) {
    return 1;
  } else if (MT == Hyperthermia) {
    return 2;
  } else {
    return MT = = Hypothermia ? 2 : 2;
  }
}

static int ToIndex(MoodleType MT) {
  if (MT == nullptr) {
    return 0;
  } else {
    switch (MT) {
    case Endurance:
      return 0;
    case Tired:
      return 1;
    case Hungry:
      return 2;
    case Panic:
      return 3;
    case Sick:
      return 4;
    case Bored:
      return 5;
    case Unhappy:
      return 6;
    case Bleeding:
      return 7;
    case Wet:
      return 8;
    case HasACold:
      return 9;
    case Angry:
      return 10;
    case Stress:
      return 11;
    case Thirst:
      return 12;
    case Injured:
      return 13;
    case Pain:
      return 14;
    case HeavyLoad:
      return 15;
    case Drunk:
      return 16;
    case Dead:
      return 17;
    case Zombie:
      return 18;
    case FoodEaten:
      return 19;
    case Hyperthermia:
      return 20;
    case Hypothermia:
      return 21;
    case Windchill:
      return 22;
    case CantSprint:
      return 23;
    case MAX:
      return 24;
    default:
      return 0;
    }
  }
}
} // namespace characters
} // namespace zombie
} // namespace characters
} // namespace zombie
