#ifndef RANDOMHELPER_H
#define RANDOMHELPER_H

#include <random>

//Returns random between [0.0f, 1.0f]
float getRandom() {
	static std::random_device rd;
	static std::mt19937 generator(rd());
	static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

	return distribution(generator);
}

#endif //RANDOMHELPER_H