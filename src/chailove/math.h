#ifndef CHAILOVE_MATH_H
#define CHAILOVE_MATH_H

namespace chailove {
	class math {
	public:
		bool load();
		int random(int min, int max);
		int random(int max);
		double random();
		void setRandomSeed(int seed);
		void setRandomSeed(int low, int high);
		int getRandomSeed();

		float pi = 3.14159265358979323846f;
		float e = 2.718281828459045f;
		int m_seed;
	};
}

#endif
