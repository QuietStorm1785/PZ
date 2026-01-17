#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace text {
namespace templating {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.  Example of ReplaceProvider that registers firstname and
 * lastname keys for the supplied character.
 */
class ReplaceProviderCharacter : public ReplaceProvider {
public:
public
  ReplaceProviderCharacter(final IsoGameCharacter) {
        this.addReplacer(
            "firstname",
    new IReplace() {
    std::string getString() {
                    return character != nullptr && character.getDescriptor() != nullptr && character.getDescriptor().getForename() != nullptr
                        ? character.getDescriptor().getForename()
                        : "Bob";
  }
            }
        );
        this.addReplacer(
            "lastname",
    new IReplace() {
    std::string getString() {
                    return character != nullptr && character.getDescriptor() != nullptr && character.getDescriptor().getSurname() != nullptr
                        ? character.getDescriptor().getSurname()
                        : "Smith";
        } // namespace templating
        } // namespace text
        );
        } // namespace zombie
        }
        } // namespace templating
        } // namespace text
        } // namespace zombie
