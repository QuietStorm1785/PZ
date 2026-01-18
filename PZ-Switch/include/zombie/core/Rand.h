//#pragma once
#pragma once
#include <random>

namespace zombie { namespace core {

class Rand {
public:
	static void init() {
		std::random_device rd;
		rng.seed(rd());
		rngLua.seed(rd());
	}

	static int Next(int max) {
		if (max <= 0) return 0;
		incrementId();
		std::uniform_int_distribution<int> dist(0, max - 1);
		return dist(rng);
	}

	static int Next(int min, int max) {
		if (max <= min) return min;
		incrementId();
		std::uniform_int_distribution<int> dist(min, max - 1);
		return dist(rng);
	}

	static long Next(long max) {
		if (max <= 0) return 0;
		incrementId();
		std::uniform_int_distribution<long> dist(0, max - 1);
		return dist(rng);
	}

	static long Next(long min, long max) {
		if (max <= min) return min;
		incrementId();
		std::uniform_int_distribution<long> dist(min, max - 1);
		return dist(rng);
	}

	static float Next(float min, float max) {
		if (max <= min) return min;
		incrementId();
		std::uniform_real_distribution<float> dist(min, max);
		return dist(rng);
	}

	static bool NextBool(int chancePercent) {
		if (chancePercent <= 0) return false;
		if (chancePercent >= 100) return true;
		incrementId();
		std::uniform_int_distribution<int> dist(1, 100);
		return dist(rng) <= chancePercent;
	}

	static int AdjustForFramerate(int value) { return value; }

private:
	static void incrementId() { if (++id >= 10000) id = 0; }
	static std::mt19937 rng;
	static std::mt19937 rngLua;
	static int id;
};

// Define static members
std::mt19937 Rand::rng{std::mt19937::default_seed};
std::mt19937 Rand::rngLua{std::mt19937::default_seed};
int Rand::id = 0;

}} // namespace zombie::core
