#ifndef _MATH_H_INCLUDED_
#define _MATH_H_INCLUDED_

#include <cmath>

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
		float acos(float x);
		float asin(float x);
		float atan(float x);
		float atan2(float y, float x);
		float ceil(float x);
		float cos(float x);
		float cosh(float x);
		float deg(float x);
		float exp(float x);
		float floor(float x);
		float fmod(float x, float y);
		float frexp(float x, int* exp);
		float ldexp(float x, int exp);
		float log(float x);
		float log10(float x);
		float modf(float x, float* iptr);
		float pow(float x, float y);
		float sin(float x);
		float sinh(float x);
		float sqrt(float x);
		float tan(float x);
		float tanh(float x);
		float pi = 3.14159265358979323846f;
		float e = 2.718281828459045f;
	};
}

#endif
