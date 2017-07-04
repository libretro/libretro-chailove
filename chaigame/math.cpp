#include "math.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

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
		srand(seed);
	}
	void math::setRandomSeed(int low, int high) {
		srand(low + high);
	}
	float math::abs(float x) {
		return std::abs(x);
	}
	float math::acos(float x) {
		return std::acos(x);
	}
	float math::asin(float x) {
		return std::asin(x);
	}
	float math::atan(float x) {
		return std::atan(x);
	}
	float math::atan2(float y, float x) {
		return std::atan2(y, x);
	}
	float math::ceil(float x) {
		return std::ceil(x);
	}
	float math::cos(float x) {
		return std::cos(x);
	}
	float math::cosh(float x) {
		return std::cosh(x);
	}
	float math::deg(float x) {
		return std::tan(x * pi / 180.0f);
	}
	float math::exp(float x) {
		return std::exp(x);
	}
	float math::floor(float x) {
		return std::floor(x);
	}
	float math::fmod(float x, float y) {
		return std::fmod(x, y);
	}
	float math::frexp(float x, int* exp) {
		return std::frexp(x, exp);
	}
	float math::ldexp(float x, int exp) {
		return std::ldexp(x, exp);
	}
	float math::log(float x) {
		return std::log(x);
	}
	float math::log10(float x) {
		return std::log10(x);
	}
	float math::modf(float x, float* iptr) {
		return std::modf(x, iptr);
	}
	float math::pow(float x, float y) {
		return std::pow(x, y);
	}
	float math::sin(float x) {
		return std::sin(x);
	}
	float math::sinh(float x) {
		return std::sinh(x);
	}
	float math::sqrt(float x) {
		return std::sqrt(x);
	}
	float math::tan(float x) {
		return std::tan(x);
	}
	float math::tanh(float x) {
		return std::tanh(x);
	}
}
