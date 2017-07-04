#ifndef _MATH_H_INCLUDED_
#define _MATH_H_INCLUDED_

namespace chaigame {
	class math {
	public:
		bool load();
		int random(int min, int max);
		int random(int max);
		double random();
		void setRandomSeed(int seed);
		void setRandomSeed(int low, int high);

		float pi = 3.14159265358979323846f;
		float e = 2.718281828459045f;
	};
}

#endif
