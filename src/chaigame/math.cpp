#include "math.h"
#include <cstdlib>
#include <ctime>

namespace chaigame {

	bool math::load() {
		setRandomSeed((int)time(0));
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
		m_seed = seed;
		srand(seed);
	}

	void math::setRandomSeed(int low, int high) {
		setRandomSeed(low + high);
	}

	int math::getRandomSeed() {
		return m_seed;
	}
}
