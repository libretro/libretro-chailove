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

		float abs(float x);
		float sin(float x);
		float cos(float x);
		float tan(float x);
	};
}

#endif
