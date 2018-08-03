#include "HeightsGenerator.h"
#include "../Math/GeneralMath.h"

namespace Eunoia { namespace Rendering {

	HeightsGenerator::HeightsGenerator(uint32 seed) :
		m_seed(seed)
	{}

	float HeightsGenerator::GenHeight(float x, float z, float amplitude, float octaves, float roughness) const
	{
		float total = 0.0f;
		float d = powf(2, octaves - 1);
		for (uint32 i = 0; i < octaves; i++)
		{
			float freq = powf(2, i) / d;
			float ampli = powf(roughness, i) * amplitude;
			total += GetInterpolatedNoise(x * freq, z * freq) * ampli;
		}
		return total;
	}

	float HeightsGenerator::GetNoise(float x, float z) const
	{
		srand(x * 74516 + z * 330981 + m_seed);
		return ((float)(rand()) / (float)(RAND_MAX)) * 2.0f - 1.0f;
	}

	float HeightsGenerator::GetSmoothNoise(float x, float z) const
	{
		float corners = (GetNoise(x-1, z-1) + GetNoise(x-1, z+1) + GetNoise(x+1, z+1) + GetNoise(x+1, z-1)) / 16.0f;
		float edges = (GetNoise(x - 1, 0.0f) + GetNoise(x + 1, 0.0f) + GetNoise(0.0f, z - 1) + GetNoise(0.0f, z + 1)) / 8.0f;
		float center = GetNoise(x, z) / 4.0f;
		return corners + edges + center;
	}

	float HeightsGenerator::Interpolate(float a, float b, float blend) const
	{
		float theta = blend * MATH_PI;
		float f = (1.0f - cosf(theta)) * 0.5f;
		return a * (1.0f - f) + b * f;

	}

	float HeightsGenerator::GetInterpolatedNoise(float x, float z) const
	{
		int intX = (int)x;
		int intZ = (int)z;
		float fracX = x - intX;
		float fracZ = z - intZ;

		float v1 = GetSmoothNoise(x, z);
		float v2 = GetSmoothNoise(x + 1, z);
		float v3 = GetSmoothNoise(x, z + 1);
		float v4 = GetSmoothNoise(x + 1, z + 1);
		float i1 = Interpolate(v1, v2, fracX);
		float i2 = Interpolate(v2, v2, fracX);
		return Interpolate(i1, i2, fracZ);
	}

} }
