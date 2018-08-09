#pragma once

#include "../Core/Common.h"
#include <random>

namespace Eunoia { namespace Rendering  {

	class HeightsGenerator
	{
	public:
		HeightsGenerator(uint32 seed);

		float GenHeight(float x, float z, float amplitude, float octaves, float roughness);
	private:
		float GetNoise(float x, float z);
		float GetSmoothNoise(float x, float z);
		float Interpolate(float a, float b, float blend) const;
		float GetInterpolatedNoise(float x, float z);
	private:
		uint32 m_seed;
		std::default_random_engine m_random;
		std::uniform_real_distribution<float> m_floatGen;
	};

} }
