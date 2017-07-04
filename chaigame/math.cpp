#include "math.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

namespace chaigame {

	bool math::load() {
		srand((int)time(0));
		return true;
	}

	double math::random() {
		int num = rand();
		return (double)num / (double)(RAND_MAX);
	}

	int math::random(int max) {
		int num = rand();
		return num % max + 1;
	}

	int math::random(int min, int max) {
		int num = rand();
        if (min > max) {
            min ^= max;
            max ^= min;
            min ^= max;
        }
        num = num % (max-min+1);
        num += min;
        return num;
	}
	void math::setRandomSeed(int seed) {
		srand(seed);
	}
	void math::setRandomSeed(int low, int high) {
		srand(low + high);
	}
	float math::abs(float x) {
		return std::abs(x);
	}
	float math::sin(float x) {
		return std::sin(x);
	}
	float math::cos(float x) {
		return std::cos(x);
	}
	float math::tan(float x) {
		return std::tan(x);
	}
}
