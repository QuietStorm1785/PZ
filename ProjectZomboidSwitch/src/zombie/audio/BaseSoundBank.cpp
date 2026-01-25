#include "zombie/audio/BaseSoundBank.h"

namespace zombie {
namespace audio {

BaseSoundBank& BaseSoundBank::instance() {
	static BaseSoundBank* inst = nullptr;
	if (!inst) {
		throw std::runtime_error("BaseSoundBank::instance() called but no implementation exists.");
	}
	return *inst;
}

} // namespace audio
} // namespace zombie
