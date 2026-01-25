
#pragma once

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: PacketValidator and all inner classes

class PacketValidator {
public:
    PacketValidator();
    ~PacketValidator();
    // TODO: Port fields and methods from Java PacketValidator

    // Inner classes from Java (CheckState, RecipeDetails, RecipeDetails$Skill)
    class CheckState {
    public:
        CheckState();
        ~CheckState();
        // TODO: Port fields and methods from Java PacketValidator.CheckState
    };
    class RecipeDetails {
    public:
        RecipeDetails();
        ~RecipeDetails();
        // TODO: Port fields and methods from Java PacketValidator.RecipeDetails
        class Skill {
        public:
            Skill();
            ~Skill();
            // TODO: Port fields and methods from Java PacketValidator.RecipeDetails.Skill
        };
    };
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
