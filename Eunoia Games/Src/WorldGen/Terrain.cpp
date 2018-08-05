#include "Terrain.h"

namespace Eunoia { namespace Rendering {

	Terrain::Terrain(uint32 x, uint32 z, float gap) :
		m_heightsGenerator(198337)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;
		GenerateMeshInfo(x, z, gap, vertices, indices);


	}

	void Terrain::GenerateMeshInfo(uint32 xsize, uint32 zsize, float gap, std::vector<Vertex>& vertices, std::vector<uint32>& indices)
	{
		for (uint32 x = 0; x < xsize; x++)
		{
			for (uint32 z = 0; z < zsize; z++)
			{
				float y = m_heightsGenerator.GenHeight(x * gap, z * gap, 10.f, 3, 0.3f);
				Vertex vertex(Math::Vector3f(x * gap, y, z * gap), Math::Vector3f(0.0f, 1.0f, 0.0f));

				vertices.push_back(vertex);
				if ((x != 0 && x != xsize - 1) && (z < zsize - 2))
					vertices.push_back(vertex);
				
			}
		}

		uint32 numTriangles = (xsize - 1) * (zsize - 1) * 2;
		
		for (uint32 x = 0; x < xsize - 1; x++)
		{
			for (uint32 z = 0; z < zsize - 1; z++)
			{
				if (z == zsize - 2)
				{


					continue;
				}

				if (z % 2 == 0)
				{
					if (x % 2 == 0)
					{
						
					}
					else
					{

					}
				}
				else
				{
					if (x % 2 == 0)
					{

					}
					else
					{

					}
				}
			}
		}
	}

} }
