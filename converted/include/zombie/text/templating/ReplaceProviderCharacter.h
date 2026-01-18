#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace text {
namespace templating {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * TurboTuTone. Example of ReplaceProvider that registers firstname and lastname keys for the supplied character.
 */
class ReplaceProviderCharacter : public ReplaceProvider {
public:
 public ReplaceProviderCharacter( IsoGameCharacter) {
 this->addReplacer(
 "firstname",
 new IReplace() {
 std::string getString() {
 return character != nullptr && character.getDescriptor() != nullptr && character.getDescriptor().getForename() != nullptr
 ? character.getDescriptor().getForename()
 : "Bob";
 }
 }
 );
 this->addReplacer(
 "lastname",
 new IReplace() {
 std::string getString() {
 return character != nullptr && character.getDescriptor() != nullptr && character.getDescriptor().getSurname() != nullptr
 ? character.getDescriptor().getSurname()
 : "Smith";
 }
 }
 );
 }
}
} // namespace templating
} // namespace text
} // namespace zombie
