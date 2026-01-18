#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
enum class CharacterActionAnims {
 None,
 Drink,
 Read,
 Chop_tree,
 Disassemble,
 Paint,
 Eat,
 Reload,
 Dig,
 DigShovel,
 DigHoe,
 DigPickAxe,
 DigTrowel,
 Pour,
 Build,
 BuildLow,
 Craft,
 Bandage,
 TakePills,
 Destroy,
 Shave,
 InsertBullets,
 RemoveBullets;
}
} // namespace characters
} // namespace zombie
