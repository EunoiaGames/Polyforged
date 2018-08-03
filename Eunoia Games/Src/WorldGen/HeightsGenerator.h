#pragma once

#include "../Core/Common.h"
#include <random>

namespace Eunoia { namespace Rendering  {

	class HeightsGenerator
	{
	public:
		HeightsGenerator(uint32 seed);

		float GenHeight(float x, float z, float amplitude, float octaves, float roughness) const;
	private:
		float GetNoise(float x, float z) const;
		float GetSmoothNoise(float x, float z) const;
		float Interpolate(float a, float b, float blend) const;
		float GetInterpolatedNoise(float x, float z) const;
	private:
		uint32 m_seed;
	};

} }
