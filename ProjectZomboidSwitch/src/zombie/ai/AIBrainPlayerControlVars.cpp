#include "zombie/ai/AIBrainPlayerControlVars.h"


namespace zombie {
namespace ai {
    // Default constructor implementation
    AIBrainPlayerControlVars::AIBrainPlayerControlVars()
	: bAiming(false), bMelee(false), bBannedAttacking(false), initiateAttack(false),
	  bRunning(false), strafeX(0.0f), strafeY(0.0f), JustMoved(false)
{
	// All fields initialized to default values
}

} // namespace ai
} // namespace zombie
