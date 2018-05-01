#include "math.h"
#include "effolkronium/random.hpp"

using Random = effolkronium::random_static;

namespace love {

bool math::load() {
	return true;
}

float math::random() {
	return random(0.0f, 1.0f);
}

float math::random(float max) {
	return random(0.0f, max);
}

float math::random(float min, float max) {
	return Random::get<float>(min, max);
}

int math::random(int max) {
	return random(0, max);
}

int math::random(int min, int max) {
	return Random::get<int>(min, max);
}
double math::random(double max) {
	return random(0.0, max);
}

double math::random(double min, double max) {
	return Random::get<double>(min, max);
}

math& math::setRandomSeed(int min, int max) {
	return setRandomSeed(random(min, max));
}

math& math::setRandomSeed(int seed) {
	Random::seed(seed);
	m_seed = seed;
	return *this;
}

int math::getRandomSeed() {
	return m_seed;
}

float math::rad(float degress) {
	return degress * pi / 180.0f;
}

float math::degrees(float rad) {
	return rad * 180.0f / pi;
}

}  // namespace love
