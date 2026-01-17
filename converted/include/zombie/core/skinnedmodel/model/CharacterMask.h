#pragma once
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/util/Pool.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class CharacterMask {
public:
private
  final boolean[] m_visibleFlags =
      createFlags(CharacterMask.Part.values().length, true);

  bool isBloodBodyPartVisible(BloodBodyPartType bpt) {
    for (CharacterMask.Part part : bpt.getCharacterMaskParts()) {
      if (this.isPartVisible(part)) {
        return true;
      }
    }

    return false;
  }

private
  static boolean[] createFlags(int int0, boolean boolean0) {
    boolean[] booleans = new boolean[int0];

    for (int int1 = 0; int1 < int0; int1++) {
      booleans[int1] = boolean0;
    }

    return booleans;
  }

  void setAllVisible(bool isVisible) {
    Arrays.fill(this.m_visibleFlags, isVisible);
  }

  void copyFrom(CharacterMask rhs) {
    System.arraycopy(rhs.m_visibleFlags, 0, this.m_visibleFlags, 0,
                     this.m_visibleFlags.length);
  }

  void setPartVisible(CharacterMask.Part part, bool isVisible) {
    if (part.hasSubdivisions()) {
      for (CharacterMask.Part _part : part.subDivisions()) {
        this.setPartVisible(_part, isVisible);
      }
    } else {
      this.m_visibleFlags[part.getValue()] = isVisible;
    }
  }

  void setPartsVisible(ArrayList<Integer> parts, bool isVisible) {
    for (int int0 = 0; int0 < parts.size(); int0++) {
      int int1 = (Integer)parts.get(int0);
      CharacterMask.Part part = CharacterMask.Part.fromInt(int1);
      if (part == nullptr) {
        if (DebugLog.isEnabled(DebugType.Clothing)) {
          DebugLog.Clothing.warn("MaskValue out of bounds: " + int1);
        }
      } else {
        this.setPartVisible(part, isVisible);
      }
    }
  }

  bool isPartVisible(CharacterMask.Part part) {
    if (part == nullptr) {
      return false;
    } else if (!part.hasSubdivisions()) {
      return this.m_visibleFlags[part.getValue()];
    } else {
      bool boolean0 = true;

      for (int int0 = 0; boolean0 && int0 < part.subDivisions().length;
           int0++) {
        CharacterMask.Part _part = part.subDivisions()[int0];
        boolean0 = this.m_visibleFlags[_part.getValue()];
      }

      return boolean0;
    }
  }

  bool isTorsoVisible() { return this.isPartVisible(CharacterMask.Part.Torso); }

  std::string toString() {
    return this.getClass().getSimpleName() + "{VisibleFlags:(" +
           this.contentsToString() + ")}";
  }

  /**
   * Returns a list of all Visible components.
   */
  std::string contentsToString() {
    if (this.isAllVisible()) {
      return "All Visible";
    } else if (this.isNothingVisible()) {
      return "Nothing Visible";
    } else {
      StringBuilder stringBuilder = new StringBuilder();
      int int0 = 0;

      for (int int1 = 0; int0 < CharacterMask.Part.leaves().length; int0++) {
        CharacterMask.Part part = CharacterMask.Part.leaves()[int0];
        if (this.isPartVisible(part)) {
          if (int1 > 0) {
            stringBuilder.append(',');
          }

          stringBuilder.append(part);
          int1++;
        }
      }

      return stringBuilder.toString();
    }
  }

  bool isAll(bool boolean1) {
    bool boolean0 = true;
    int int0 = 0;

    for (int int1 = CharacterMask.Part.leaves().length; boolean0 && int0 < int1;
         int0++) {
      CharacterMask.Part part = CharacterMask.Part.leaves()[int0];
      boolean0 = this.isPartVisible(part) == boolean1;
    }

    return boolean0;
  }

  bool isNothingVisible() { return this.isAll(false); }

  bool isAllVisible() { return this.isAll(true); }

  void forEachVisible(Consumer<CharacterMask.Part> action) {
    try {
      for (int int0 = 0; int0 < CharacterMask.Part.leaves().length; int0++) {
        CharacterMask.Part part = CharacterMask.Part.leaves()[int0];
        if (this.isPartVisible(part)) {
          action.accept(part);
        }
      }
    } finally {
      Pool.tryRelease(action);
    }
  }

public
  static enum Part {
    Head(0), Torso(1, true), Pelvis(2, true), LeftArm(3), LeftHand(4),
    RightArm(5), RightHand(6), LeftLeg(7), LeftFoot(8), RightLeg(9),
    RightFoot(10), Dress(11), Chest(12, Torso), Waist(13, Torso),
    Belt(14, Pelvis), Crotch(15, Pelvis);

    const int value; private final CharacterMask.Part parent;
    const bool isSubdivided; private CharacterMask.Part[] subDivisions;
    private BloodBodyPartType[] m_bloodBodyPartTypes;
    private static final CharacterMask.Part[] s_leaves = leavesInternal();

    private Part(int int1){this.value = int1; this.parent = nullptr;
                           this.isSubdivided = false;}

  private Part(int int1, CharacterMask.Part part1) {
    this.value = int1;
    this.parent = part1;
    this.isSubdivided = false;
  }

private
  Part(int int1, bool boolean0) {
    this.value = int1;
    this.parent = nullptr;
    this.isSubdivided = boolean0;
  }

  static int count() { return values(); }

public
  static CharacterMask.Part[] leaves() { return s_leaves; }

public
  static CharacterMask.Part fromInt(int index) {
    return index >= 0 && index < count() ? values()[index] : nullptr;
  }

  int getValue() { return this.value; }

public
  CharacterMask.Part getParent() { return this.parent; }

  bool isSubdivision() { return this.parent != nullptr; }

  bool hasSubdivisions() { return this.isSubdivided; }

public
  CharacterMask.Part[] subDivisions() {
    if (this.subDivisions != nullptr) {
      return this.subDivisions;
    } else {
      if (!this.isSubdivided) {
        this.subDivisions = new CharacterMask.Part[0];
      }

      std::vector arrayList = new ArrayList();

      for (CharacterMask.Part part1 : values()) {
        if (part1.parent == this) {
          arrayList.add(part1);
        }
      }

      this.subDivisions = arrayList.toArray(new CharacterMask.Part[0]);
      return this.subDivisions;
    }
  }

private
  static CharacterMask.Part[] leavesInternal() {
    std::vector arrayList = new ArrayList();

    for (CharacterMask.Part part : values()) {
      if (!part.hasSubdivisions()) {
        arrayList.add(part);
      }
    }

    return arrayList.toArray(new CharacterMask.Part[0]);
  }

public
  BloodBodyPartType[] getBloodBodyPartTypes() {
    if (this.m_bloodBodyPartTypes != nullptr) {
      return this.m_bloodBodyPartTypes;
    } else {
      std::vector arrayList = new ArrayList();
      switch (this) {
      case Head:
        arrayList.add(BloodBodyPartType.Head);
        break;
      case Torso:
        arrayList.add(BloodBodyPartType.Torso_Upper);
        arrayList.add(BloodBodyPartType.Torso_Lower);
        break;
      case Pelvis:
        arrayList.add(BloodBodyPartType.UpperLeg_L);
        arrayList.add(BloodBodyPartType.UpperLeg_R);
        arrayList.add(BloodBodyPartType.Groin);
        break;
      case LeftArm:
        arrayList.add(BloodBodyPartType.UpperArm_L);
        arrayList.add(BloodBodyPartType.ForeArm_L);
        break;
      case LeftHand:
        arrayList.add(BloodBodyPartType.Hand_L);
        break;
      case RightArm:
        arrayList.add(BloodBodyPartType.UpperArm_R);
        arrayList.add(BloodBodyPartType.ForeArm_R);
        break;
      case RightHand:
        arrayList.add(BloodBodyPartType.Hand_R);
        break;
      case LeftLeg:
        arrayList.add(BloodBodyPartType.UpperLeg_L);
        arrayList.add(BloodBodyPartType.LowerLeg_L);
        break;
      case LeftFoot:
        arrayList.add(BloodBodyPartType.Foot_L);
        break;
      case RightLeg:
        arrayList.add(BloodBodyPartType.UpperLeg_R);
        arrayList.add(BloodBodyPartType.LowerLeg_R);
        break;
      case RightFoot:
        arrayList.add(BloodBodyPartType.Foot_R);
      case Dress:
      default:
        break;
      case Chest:
        arrayList.add(BloodBodyPartType.Torso_Upper);
        break;
      case Waist:
        arrayList.add(BloodBodyPartType.Torso_Lower);
        break;
      case Belt:
        arrayList.add(BloodBodyPartType.UpperLeg_L);
        arrayList.add(BloodBodyPartType.UpperLeg_R);
        break;
      case Crotch:
        arrayList.add(BloodBodyPartType.Groin);
      }

      this.m_bloodBodyPartTypes = new BloodBodyPartType[arrayList.size()];

      for (int int0 = 0; int0 < arrayList.size(); int0++) {
        this.m_bloodBodyPartTypes[int0] =
            (BloodBodyPartType)arrayList.get(int0);
      }

      return this.m_bloodBodyPartTypes;
    }
  }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
} // namespace zombie
